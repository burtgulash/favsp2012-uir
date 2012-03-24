#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grid.h"
#include "pqueue.h"
#include "set.h"

static int start[] = {1, 0, 3,
                      6, 2, 4,
                      8, 7, 5};
static int end[]   = {1, 2, 3,
                      8, 0, 4,
                      7, 6, 5};

extern Grid goal, root;
extern int correct_position[9], next_position[9];

static void get_positions()
{
    int i;

    for (i = 0; i < 9; i++)
        correct_position[root.g[i]] = i;
}


int main()
{
    Grid *cur, *child;
    Pqueue *pq;
    Set *visited;
    int goal_grid_code, child_code;
    int ch;

    memcpy(root.g, start, sizeof(int) * 9);
    root.parent = NULL;
    root.hole = 1;
    root.depth = 0;
    get_positions();

grid_print(&root);

    memcpy(goal.g, end, sizeof(int) * 9);
    goal_grid_code = grid_code(&goal);

    pq = pqueue_new();
    visited = set_new(4);
    pqueue_insert(pq, &root);
    set_insert(visited, grid_code(&root));

    while (!empty(pq)) {
        cur = pqueue_extract_min(pq);
        if (grid_code(cur) == goal_grid_code)
            break;

        ch = 0;

#define ADD_CHILD() {                                                         \
    child_code = grid_code(child);                                            \
    if (!set_contains(visited, child_code)) {                                 \
        set_insert(visited, child_code);                                      \
        pqueue_insert(pq, child);                                             \
        cur->child[ch++] = child;                                             \
    }                                                                         \
}
        /* Hole not on the left wall. */
        if (cur->hole % 3 > 0) {
            child = make_child(cur);
            grid_move_hole(child, child->hole - 1);
            ADD_CHILD();
        }
        /* Hole not on the right wall. */
        if (cur->hole % 3 < 2) {
            child = make_child(cur);
            grid_move_hole(child, child->hole + 1);
            ADD_CHILD();
        }
        /* Hole not on the top wall. */
        if (cur->hole / 3 > 0) {
            child = make_child(cur);
            grid_move_hole(child, child->hole - 3);
            ADD_CHILD();
        }
        /* Hole not on the bottom wall. */
        if (cur->hole / 3 < 2) {
            child = make_child(cur);
            grid_move_hole(child, child->hole + 3);
            ADD_CHILD();
        }

        /* End of children character. */
        cur->child[ch] = NULL;
    }

#undef ADD_CHILD

    return 0;
}
