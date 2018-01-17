#include <stdio.h>

/*Exercise 1-8, count blanks, tabs and newlines */
main()
{
	int c, total;

	total = 0;

	while((c = getchar()) != EOF)
	{
		if(c == '\n')
			++total;
		if(c == ' ')
			++total;
		if(c == '\t')
			++total;
	}
	printf("%d in total.\n", total);
}
