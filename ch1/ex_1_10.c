/* I've gotten bored with naming things, this is exercise 1.10,
 * copy input to output replace tabs, backspaces and backslashes with their
 * escape sequence*/
#include <stdio.h>

main()
{
	int c;

	while((c = getchar()) != EOF)
	{
		/*I won't actually be able to test this until the book teaches me how
		 * to provide command line input*/
		if(c == '\t')
		{
			putchar('\\');
			c = 't';
		}
		if(c == '\b')
		{
			putchar('\\');
			c = 'b';
		}
		if(c == '\\')
		{
			putchar('\\');
			c = '\\';
		}
		putchar(c);
	}
}

