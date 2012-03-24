#include <stdio.h>
#include <stdlib.h>

#include "grid.h"
#include "pqueue.h"


extern Grid goal, root;
extern int correct_position[9], next_position[9];

static void get_positions()
{
    int i;

    for (i = 0; i < 9; i++)
        correct_position[root->g[i]] = i;
}


int main()
{
    Grid *cur;
    Pqueue *pq;
    Set *visited;
    int goal_grid_code;

    root.g = {1, 0, 3, 6, 2, 4, 8, 7, 5}
    root.parent = NULL;
    get_positions();

    goal.g = {1, 2, 3, 8, 0, 4, 7, 6, 5};
    goal_grid_code = grid_code(&goal);

    pq = pqueue_new();
    visited = set_new(4);
    pqueue_insert(pq, &root);
    set_insert(visited, grid_code(&root));

    while (!empty(pq)) {
        cur = pqueue_extract_min(pq);
        if (grid_code(cur) == goal_grid_code)
            break;

        /* TODO generate children. */
        /* TODO put children to visited and to pq. */
    }


    return 0;
}
