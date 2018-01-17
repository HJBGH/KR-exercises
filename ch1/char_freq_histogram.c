#include <stdio.h>

main()
{
	int c, i, k, white_s, other_c;
	int ndigit[10];

	white_s = other_c = 0;
	for(i = 0; i < 10; i++)
	{
		ndigit[i] = 0;
	}

	while((c = getchar()) != EOF)
	{
		if(c >= '0' && c <= '9')
		{
			++ndigit[c-'0'];
		}
		else if (c == ' ' || c == '\n' || c == '\t')
		{
			++white_s;
		}
		else
		{
			++other_c;
		}
	}

	printf("WS > ");
	for(i = 0; i <= white_s; i++)
	{
		putchar('|');
	}
	putchar('\n');

	printf("OC > ");
	for(i = 0; i <= other_c; i++)
	{
		putchar('|');
	}
	putchar('\n');

	for(i = 0; i < 10; i++)
	{
		printf("%2d > ", i);
		for(k = 0; k < ndigit[i]; k++)
		{
			putchar('|');
		}
		putchar('\n');
	}
}
