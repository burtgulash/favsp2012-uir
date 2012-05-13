/*
 * 8puzzle
 * set.c
 *
 * @author: Tomáš Maršálek
 * @date: 06.05.2012
 * @version: 1.0
 */

#include <assert.h>
#include <stdlib.h>

#include "list.h"
#include "set.h"

static void copy_over(Set *old, Set *new);
static void dispose_buckets(Set *s);


/*
 * Copies all elements from old set to new set.
 */
static void copy_over(Set *old, Set *new)
{
    List *l;
    int i;

    for (i = 0; i < old->size; i++) {
        l = old->buckets[i];
        if (l != NULL)
            for (l = l->next; l != NULL; l = l->next)
                set_insert(new, l->position);
    }
}


int set_contains(Set *s, int position)
{
    List *list;
    int bucket_position;

    bucket_position = position % s->size;
    list = s->buckets[bucket_position];

    if (list == NULL)
        return 0;

    return list_contains(list, position);
}


void set_insert(Set *s, int position)
{
    List *list;
    Set *tmp;
    int bucket_position;

    if (s->num_elems * 100 / s->size > 75) {
        tmp = set_new(2 * s->size);
        copy_over(s, tmp);

        dispose_buckets(s);

        s->num_elems = tmp->num_elems;
        s->size = tmp->size;
        s->buckets = tmp->buckets;

        free(tmp);
    }

    bucket_position = position % s->size;
    list = s->buckets[bucket_position];
    if (list == NULL) {
        list = list_new(-1, NULL);
        s->buckets[bucket_position] = list;
    }

    if (!list_contains(list, position)) {
        list_insert(list, position);
        s->num_elems++;
    }
}


Set *set_new(int size)
{
    Set *new;

    assert(size > 0);

    new = (Set*) malloc(sizeof(Set));
    new->num_elems = 0;
    new->size = size;
    new->buckets = (List**) calloc(new->size, sizeof(List*));

    return new;
}


static void dispose_buckets(Set *s)
{
    int i;

    for (i = 0; i < s->size; i++)
        if (s->buckets[i] != NULL)
            list_dispose(s->buckets[i]);

    free(s->buckets);
}


void set_dispose(Set *s)
{
    dispose_buckets(s);
    free(s);
}
