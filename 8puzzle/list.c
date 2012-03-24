#include <stdlib.h>

#include "list.h"


int list_contains(List *l, int position)
{
	/* Skip dummy. */
	l = l->next;
	for (; l != NULL; l = l->next)
		if (l->position == position)
			return 1;
	return 0;
}

void list_insert(List *l, int position)
{
	List *new;

	new = list_new(position, l->next);
	l->next = new;
}

List *list_new(int position, List *next)
{
	List *new;
	
	new = (List *) malloc(sizeof(List));
	new->position = position;
	new->next = next;

	return new;
}

void list_dispose(List *l)
{
	List *next;

	next = l->next;
	for (; l != NULL; l = next) {
		next = l->next;
		free(l);
	}
}
