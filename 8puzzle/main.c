#include <stdio.h>
#include <stdlib.h>

#include "grid.h"
#include "pqueue.h"


int code(Grid *grid)
{
    int i, code;

    code = 0;
    for (i = 0; i < 9; i++)
        code = code * 9 + grid->g[i];

    return code;
}


int main()
{
    Grid goal, root, *cur;
    Pqueue *pq;
    Set *visited;
    int goal_code;

    root.g = {1, 0, 3, 6, 2, 4, 8, 7, 5}
    root.parent = NULL;

    goal.g = {1, 2, 3, 8, 0, 4, 7, 6, 5};
    goal_code = code(&goal);

    pq = pqueue_new();
    visited = set_new(4);
    pqueue_insert(pq, &root);
    set_insert(visited, code(&root));

    while (!empty(pq)) {
        cur = pqueue_extract_min(pq);
        if (code(cur) == goal_code)
            break;

        /* TODO generate children. */
        /* TODO put children to visited and to pq. */
    }


    return 0;
}
