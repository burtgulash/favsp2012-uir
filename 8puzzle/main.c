#include <stdio.h>
#include <stdlib.h>

#include "list.h"

int main()
{
	List *l, *ll;

	l = list_new(0, NULL);
	list_insert(l, -137);
	list_insert(l, 1337);
	list_insert(l, 137);
	list_insert(l, 137);
	
	for (ll = l; ll != NULL; ll = ll->next)
		printf("%d, ", ll->position);
	list_dispose(l);

	return 0;
}
