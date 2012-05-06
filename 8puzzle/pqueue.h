/*
 * 8puzzle
 * pqueue.h
 *
 * @author: Tomáš Maršálek
 * @date: 06.05.2012
 * @version: 1.0
 */

#ifndef PQUEUE_H
#define PQUEUE_H
#include "grid.h"

typedef struct _pqueue {
    int alloc, used;
    Grid **elems;
} Pqueue;

/*
 * Emptiness test.
 */
int empty(Pqueue *pq);

/*
 * Priority queue element insertion.
 */
void pqueue_insert(Pqueue *pq, Grid *g);

/*
 * Priority queue retrieve element with minimal weight.
 */
Grid *pqueue_extract_min(Pqueue *pq);

/*
 * Initialize new priority queue.
 */
Pqueue *pqueue_new();

/*
 * Destroy priority queue.
 */
void pqueue_dispose(Pqueue *pq);

#endif
