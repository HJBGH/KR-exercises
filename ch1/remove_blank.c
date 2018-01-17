#include <stdio.h>

/* Exercise 1-9, copy input to output, replace strings of blanks with singles*/

#define FALSE 0
#define TRUE 1

main()
{
	int blank = FALSE;
	int c;

	while((c = getchar()) != EOF)
	{
		if(c != ' ')
		{
			putchar(c);
			blank = FALSE;
		}
		if(c == ' ' && blank == FALSE)
		{
			putchar(c);
			blank = TRUE;
		}
	}
}
