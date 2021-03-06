/*
 * 8puzzle
 * grid.c
 *
 * @author: Tomáš Maršálek
 * @date: 06.05.2012
 * @version: 1.0
 */

#include <stdio.h>
#include <stdlib.h>

#include "grid.h"


static int correct_position[9];

/*
 * Next position is a map from grid positions
 * to next positions in circular grid.
 *
 *     0 1 2        1 2 5
 *     3 4 5  --->  4 - 8
 *     6 7 8        3 6 7
 */
static int next_position[9] = {1, 2, 5, 4, -1, 8, 3, 6, 7};


void get_correct_positions(Grid *goal)
{
    int i;

    for (i = 0; i < 9; i++)
        correct_position[goal->g[i]] = i;
}


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

static int successor(int position)
{
    return (position + 1) % 9;
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
            if (successor(grid->g[i]) != grid->g[next_position[i]])
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


Grid *make_child(Grid *grid)
{
    Grid *child;
    int i;

    child = (Grid*) malloc(sizeof(Grid));

    child->depth = grid->depth + 1;
    child->hole = grid->hole;
    child->parent = grid;
    child->child[0] = NULL;

    for (i = 0; i < 9; i++)
        child->g[i] = grid->g[i];

    return child;
}


void grid_dispose(Grid *grid)
{
    int ch;

    for (ch = 0; grid->child[ch] != NULL; ch++)
        grid_dispose(grid->child[ch]);

    free(grid);
}


void grid_move_hole(Grid *grid, int new_pos)
{
    grid->g[grid->hole] = grid->g[new_pos];
    grid->g[new_pos] = 0;
    grid->hole = new_pos;
}


void grid_print(FILE* output, Grid *grid)
{
    int i, j;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (grid->g[3 * i + j] == 0)
                fprintf(output, "  ");
            else
                fprintf(output, "%d ", grid->g[3 * i + j]);
        }
        fprintf(output, "\n");
    }
}


void grid_children(FILE* output, Grid *grid)
{
    int ch, i, j;

    for (i = 0; i < 3; i++) {
        for (ch = 0; grid->child[ch]; ch++) {
            for (j = 0; j < 3; j++) {
                if (grid->child[ch]->g[3 * i + j] == 0)
                    fprintf(output, "  ");
                else
                    fprintf(output, "%d ", grid->child[ch]->g[3 * i + j]);
            }
            fprintf(output, "   ");
        }
        fprintf(output, "\n");
    }

    for (ch = 0; grid->child[ch]; ch++)
        fprintf(output, "f: %2d    ", weight(grid->child[ch]));
    fprintf(output, "\n");
}
