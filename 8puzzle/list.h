#ifndef LIST_H
#define LIST_H

typedef struct _list {
    int position;
    struct _list *next;
} List;

/*
 * Tests for presence of an element.
 */
int list_contains(List *l, int position);

/*
 * Inserts element into the list.
 */
void list_insert(List *l, int position);

/*
 * Initializes new list.
 */
List *list_new(int position, List *next);

/*
 * Destroys the list.
 */
void list_dispose(List *l);

#endif
