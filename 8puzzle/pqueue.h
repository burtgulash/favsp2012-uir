#ifndef PQUEUE_H
#define PQUEUE_H
#include "grid.h"

typedef struct _pqueue {
    int alloc, used;
    Grid **elems;
} Pqueue;

int empty(Pqueue *pq);
void pqueue_insert(Pqueue *pq, Grid *g);
Grid *pqueue_extract_min(Pqueue *pq);
Pqueue *pqueue_new();
void pqueue_dispose(Pqueue *pq);

#endif
