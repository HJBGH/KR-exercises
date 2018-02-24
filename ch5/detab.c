/*This file contains one half of a response to exercise 5-11, detab will accept
 * a list of tab stops as arguments and use the default if there are none*/
#include <stdio.h>
#include <stdlib.h>
#define TAB_COLUMNS 4
#define LINE_LENGTH 128

int getline(char line[], int ll);
int detabline(char line[]); /*does detab operations until it encounters EOF or \n*/

main()
{
	char line[LINE_LENGTH];
	int len;
	while((len = getline(line, LINE_LENGTH)) > 0)
	{
		detabline(line);
	}
	return 0;
}

int getline(char line[], int ll)
{
	int c, i;
	for(i = 0; i < ll-1 && (c = getchar()) != EOF && c != '\n'; i++)
	{
		line[i] = c;
	}
	if(c == '\n')
	{
		line[i] = c;
		i++;
	}
	line[i] = '\0';
	return i;
}

/*An unfortunate consequence of converting all tab chars to the equivalent
 * number of space chars is that it increases the size of the line in terms of
 * memory space by an uncomfortable amount*/
int detabline(char line[])
{
	/*used to construct the version of the line with the tabs replaced*/
	int i, j, k;
	for(i = 0, k = 0;	line[i] != EOF && line[i] != '\n'; i++)
	{
		if(line[i] == '\t')
		{
			/*handle tabs*/
			for(j = TAB_COLUMNS - (k%TAB_COLUMNS); j>0; j--, k++)
			{
				/*printf("%d\n", j);*/
				putchar('#');
			}

		}
		else
		{
			putchar(line[i]);
			k++;
		}
	}
	if(line[i] == '\n')
		putchar('\n');
}
