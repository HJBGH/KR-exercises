#include <stdio.h>

/*exercise twelve, print each word of input on a new line*/

main()
{
	int c;

	while((c = getchar()) != EOF)
	{
		if(c == '\n' || c == '\t' || c == ' ')
			putchar('\n');
		else
			putchar(c);
	}
}
