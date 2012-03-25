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

Grid *goal, *root;


int main(int argc, char **argv)
{
    Grid *cur, *child, *iter, **result;
    Pqueue *pq;
    Set *visited;
    int goal_grid_code, child_code;
    int i, ch;
    int path_length;
    int verbose;

    verbose = 0;
    while (--argc) {
        argv++;
        if (argv[0][0] == '-' && argv[0][1] == 'v')
            verbose = 1;
    }

    root = (Grid *) malloc(sizeof(Grid));
    memcpy(root->g, start, sizeof(int) * 9);
    root->parent = NULL;
    root->hole = 1;
    root->depth = 0;

    goal = (Grid *) malloc(sizeof(Grid));
    memcpy(goal->g, end, sizeof(int) * 9);
    goal_grid_code = grid_code(goal);
    get_correct_positions(goal);

    path_length = 0;
    i = 0;
    pq = pqueue_new();
    visited = set_new(4);
    pqueue_insert(pq, root);
    set_insert(visited, grid_code(root));


    while (!empty(pq)) {
        cur = pqueue_extract_min(pq);
        if (verbose) {
            printf("----------------\n");
            grid_print(cur);
            printf("Step   : %d\n", ++i);
            grid_details(cur);
            printf("----------------\n");
            printf("\n");
        }
        if (grid_code(cur) == goal_grid_code)
            break;

        ch = 0;

#define ADD_CHILD() {                                                         \
    child_code = grid_code(child);                                            \
    if (!set_contains(visited, child_code)) {                                 \
        set_insert(visited, child_code);                                      \
        pqueue_insert(pq, child);                                             \
        cur->child[ch++] = child;                                             \
    } else                                                                    \
        free(child);                                                          \
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
#undef ADD_CHILD

        /* End of children character. */
        cur->child[ch] = NULL;
    }

    /* Collect result path. */
    for (iter = cur; iter != NULL; iter = iter->parent)
        path_length ++;

    result = (Grid**) malloc(sizeof(Grid*) * path_length);

    i = path_length - 1;
    for (iter = cur; iter != NULL; iter = iter->parent)
        result[i--] = iter;

    if (verbose)
        printf("Solution sequence:\n");

    for (i = 0; i < path_length; i++)
        grid_print(result[i]);


    /* Clean up. */
    grid_dispose(root);
    set_dispose(visited);
    pqueue_dispose(pq);
    free(result);
    free(goal);

    return 0;
}
