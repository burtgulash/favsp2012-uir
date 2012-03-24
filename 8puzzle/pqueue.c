#include <assert.h>
#include <stdlib.h>

#include "pqueue.h"


static int weight(Grid *g)
{
    return (int) *g;
}

static void swap(Pqueue *pq, int pos1, int pos2)
{
    Grid *tmp;

    tmp = pq->elems[pos1];
    pq->elems[pos1] = pq->elems[pos2];
    pq->elems[pos2] = tmp;
}


static void up(Pqueue *pq, int pos)
{
    assert (pos < pq->used);

    while (pos > 1
        && weight(pq->elems[pos]) < weight(pq->elems[pos / 2])) {
        swap(pq, pos, pos / 2);
        pos /= 2;
    }
}


static void down(Pqueue *pq, int pos)
{
    int next;
    Grid **elems;

    assert (pos < pq->used);

    elems = pq->elems;
    next = pos * 2;

    while (next < pq->used) {
        if (next + 1 < pq->used
         && weight(elems[next]) > weight(elems[next + 1]))
            next ++;
        if (weight(elems[pos]) > weight(elems[next]))
            swap(pq, pos, next);
        else
            break;

        pos = next;
        next *= 2;
    }
}

void pqueue_insert(Pqueue *pq, Grid *g)
{
    if (pq->used >= pq->alloc) {
        pq->alloc = 1 + (pq->alloc - 1) * 2;
        pq->elems = realloc(pq->elems, pq->alloc * sizeof(Grid*));
    }

    pq->elems[pq->used] = g;
    pq->used++;
    up(pq, pq->used - 1);
}

Grid *pqueue_extract_min(Pqueue *pq)
{
    Grid *min;

    min = pq->elems[1];

    pq->elems[1] = pq->elems[pq->used - 1];
    down(pq, 1);
    pq->used--;

    return min;
}

int empty(Pqueue *pq)
{
    return pq->used <= 1;
}


Pqueue *pqueue_new()
{
    Pqueue *new;

    new = (Pqueue*) malloc(sizeof(Pqueue));
    new->used  = 1;
    new->alloc = 1 + 4;
    new->elems = (Grid**) malloc(new->alloc * sizeof(Grid*));

    return new;
}

void pqueue_dispose(Pqueue *pq)
{
    free(pq->elems);
    free(pq);
}
