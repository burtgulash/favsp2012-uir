#include <stdio.h>
#include <stdlib.h>

#include "set.h"
#include "list.h"
#include "pqueue.h"

int main()
{
/*
    Set *s;
    List *l;
    int i;

    s = set_new(2);
    set_insert(s, 31);
    set_insert(s, 31);
    set_insert(s, 310);
    set_insert(s, 32);
    set_insert(s, 4);
    set_insert(s, 1337);
    set_insert(s, 2337);

    for (i = 0; i < s->size; i++) {
        l = s->buckets[i];
        if (l != NULL) {
            for (l = s->buckets[i]->next; l != NULL; l=l->next)
                printf("%d, ", l->position);
        }
        printf("\n");
    }
    printf("size: %d\n", s->size);
    set_dispose(s);
*/

    Pqueue *pq;
    Grid g[20];
    int i;

    pq = pqueue_new();
    g[0] = 1;
    g[1] = 5;
    g[2] = 3;
    g[3] = 4;
    g[4] = 7;
    g[5] = 2;
    g[6] = 19;
    g[7] = 11;
    g[8] = 9;
    g[9] = 10;
    g[10] = 13;
    g[11] = 8;
    g[12] = 0;
    g[13] = 1;
    g[14] = 15;
    g[15] = -9;
    g[16] = 190;
    g[17] = 0;
    g[18] = -1;

    for (i = 0; i < 19; i++)
        pqueue_insert(pq, g + i);

    for (i = 1; i < pq->used; i++)
        printf("%d, ", (int) *pq->elems[i]);
    printf("\n");

printf("used: %d\n", pq->used);
printf("allo: %d\n", pq->alloc);

    while (!empty(pq)) {
        printf("%d, ", (int) *pqueue_extract_min(pq));
    }
    printf("\n");

	pqueue_dispose(pq);


    return 0;
}
