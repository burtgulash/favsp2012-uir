/*
 * @author: Tomáš Maršálek
 * @date: 06.05.2012
 * @version: 1.0
 */

#ifndef GRID_H
#define GRID_H
#include <stdio.h>

typedef struct _grid {
    int g[9];
    int depth;
    int hole;
    struct _grid *parent;
    struct _grid *child[5];
} Grid;


/*
 * Initialization procedure for the grid module.
 */
void get_correct_positions(Grid *goal);

/*
 * Prints the grid to output file.
 */
void grid_print(FILE* output, Grid *grid);

/*
 * Prints all children of the grid and their weigths.
 */
void grid_children(FILE* output, Grid *grid);

/*
 * Moves the hole to a position specified by new_pos.
 */
void grid_move_hole(Grid *grid, int new_pos);

/*
 * Creates and returns a grid whose parent is provided grid.
 */
Grid *make_child(Grid *grid);

/*
 * Destroy the grid.
 */
void grid_dispose(Grid *grid);

/*
 * Get unique id of the grid.
 */
int grid_code(Grid *grid);

/*
 * Get value of the heuristic function for the grid.
 */
int weight(Grid *grid);

#endif
