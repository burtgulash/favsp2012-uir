#ifndef LIST_H
#define LIST_H

typedef struct _list {
	int position;
	struct _list *next;
} List;

int list_contains(List l, int position);
void list_insert(List l, int position);
void list_dispose(List l);

#endif
