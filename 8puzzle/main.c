#include <stdio.h>
#include <stdlib.h>

#include "set.h"
#include "list.h"

int main()
{
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

    return 0;
}
