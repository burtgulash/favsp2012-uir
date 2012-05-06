/*
 * 8puzzle
 * set.h
 *
 * @author: Tomáš Maršálek
 * @date: 06.05.2012
 * @version: 1.0
 */

#ifndef SET_H
#define SET_H
#include "list.h"

typedef struct _set {
    int num_elems;
    int size;
    List **buckets;
} Set;

/*
 * Existence of element test.
 */
int set_contains(Set *s, int position);

/*
 * Inserts element into set.
 */
void set_insert(Set *s, int position);

/*
 * Initializes new set.
 */
Set *set_new(int size);

/*
 * Destroys set.
 */
void set_dispose(Set *s);
#endif
