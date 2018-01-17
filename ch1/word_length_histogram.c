#include <stdio.h>

#define IN_WORD 1
#define OUT_WORD 0
/*response to exercise 1-13, draws a histogram of the lengths of words in its'
 * input, up to a length of 100, words longer that 100 will be recorded in the
 * 101st element of the array*/
main()
{
	int i, c, l, state, sl; /*c for char, l for length, sl for specific length*/
	int lengths[101];
	state = OUT_WORD;

	for(sl = 0; sl < 101; sl++)
	{
		lengths[i] = 0;
	}
	sl = 0;
	while((c = getchar()) != EOF)
	{
		if(c == ' ' || c == '\n' || c == '\t')
		{
			if(state == IN_WORD)
			{
				lengths[sl]++;
				sl = 0;
			}
			state = OUT_WORD;
		}
		else
		{
			state = IN_WORD;
			sl++;
		}
	}

	/*print horizontal histograph*/
	for(sl = 0; sl < 101; sl++)
	{
		printf("%4d > ", sl);
		for(i = 0; i <= lengths[sl]; i++)
		{
			putchar('|');
		}
		putchar('\n');
	}
}

				
	

