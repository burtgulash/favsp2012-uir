#include "grid.h"


Grid root, goal;
int correct_position[9];

/*
 * Next position is a map from grid positions
 * to next positions in circular grid.
 *
 *     0 1 2        1 2 5
 *     3 4 5  --->  4 - 8
 *     6 7 8        3 6 7
 */
int next_position[9] = {1, 2, 5, 4, -1, 8, 3, 6, 7};


/* Get unique id of the grid. */
int grid_code(Grid *grid)
{
    int i, code;

    code = 0;
    for (i = 0; i < 9; i++)
        code = code * 9 + grid->g[i];

    return code;
}


static int manhattan_distance(Grid *grid, int pos)
{
    int dist;

    dist = pos - correct_position[grid->g[pos]];
    if (dist < 0)
        dist = -dist;

    /* Y-coordinate + X-coordinate. */
    return dist / 3 + dist % 3;
}


static int order_violation(Grid *grid)
{
    int i, v;

    v = 0;

    /* Middle element is weighted by 1. */
    if (grid->g[4] != 0)
        v += 1;

    /* All others have weight 2 upon violation. */
    for (i = 0; i < 9; i++)
        if (i != 4)
            if (grid->g[i] + 1 != grid->g[next_position[i]])
                v += 2;

    return v;
}


int weight(Grid *grid)
{
    int i;
    int g, P, Q;

    g = grid->depth;
    P = 0;

    /* Hole is excluded. To include, let i start from 0. */
    for (i = 1; i < 9; i++)
        P += manhattan_distance(grid, i);

    Q = order_violation(grid);

    return g + P + 3 * Q;
}
