#ifndef SET_H
#define SET_H
#include "list.h"

typedef struct _set {
    int num_elems;
    int size;
    List **buckets;
} Set;

int set_contains(Set *s, int position);
void set_insert(Set *s, int position);
Set *set_new(int size);
void set_dispose(Set *s);
#endif
