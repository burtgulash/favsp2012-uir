#include <stdlib.h>

#include "list.h"
#include "set.h"


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
	int bucket_position;

	bucket_position = position % s->size;
	list = s->buckets[bucket_position];
	if (list == NULL) {
		list = list_new(-1, NULL);
		s->buckets[bucket_position] = list;
	}

	if (!list_contains(list, position))
		list_insert(list, position);
}

Set *set_new()
{
	Set *new;

	new = (Set*) malloc(sizeof(Set));
	new->num_elems = 0;
	new->size = 4;
	new->buckets = (List**) malloc(new->size * sizeof(List*));

	return new;
}

void set_dispose(Set *s)
{
	int i;

	for (i = 0; i < s->size; i++)
		if (s->buckets[i] != NULL)
			list_dispose(s->buckets[i]);

	free(s->buckets);
	free(s);
}
