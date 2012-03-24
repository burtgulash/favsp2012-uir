#ifndef GRID_H
#define GRID_H

typedef struct _grid {
    int g[9];
    int depth;
    struct _grid *parent;
    struct _grid *child[5];
} Grid;

#endif
