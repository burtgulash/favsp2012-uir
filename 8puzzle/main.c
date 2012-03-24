#include <stdio.h>
#include <stdlib.h>

#include "set.h"
#include "list.h"

int main()
{
	Set *s;
	int i;

	s = set_new();
	set_insert(s, 31);
	set_insert(s, 4);
	set_insert(s, 1337);

	for (i = 0; i < 2000; i++)
		if (set_contains(s, i))
			printf("%d\n", i);
	set_dispose(s);

	return 0;
}
