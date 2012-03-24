#ifndef GRID_H
#define GRID_H

typedef struct _grid {
    int g[9];
    int depth;
    struct _grid *parent;
} Grid;

int grid_code(Grid *grid);
int weight(Grid *grid);

#endif
