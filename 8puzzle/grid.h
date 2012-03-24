#ifndef GRID_H
#define GRID_H

typedef struct _grid {
    int g[9];
    int depth;
    int hole;
    struct _grid *parent;
    struct _grid *child[5];
} Grid;

void grid_print(Grid *grid);
void grid_move_hole(Grid *grid, int new_pos);
Grid *make_child(Grid *grid);
void grid_dispose(Grid *grid);
int grid_code(Grid *grid);
int weight(Grid *grid);

#endif
