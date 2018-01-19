#include <stdio.h>
#define TAB_COLUMNS 8
#define LINE_LENGTH 128
/*in answer to the question at the end of the exercise spec, tabs should be
 * given preference as this program is trying to eliminate blanks*/

/*compile with -ansi argument for compiler as getline() is already defined in
 * stdio*/
int getline(char line[], int ll);
int entabline(char line[]); /*does detab operations until it encounters EOF or \n*/

main()
{
	char line[LINE_LENGTH];
	int len;
	while((len = getline(line, LINE_LENGTH)) > 0)
	{
		entabline(line);
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
int entabline(char line[])
{
	/*used to print the version of the line with the tabs replaced*/
	int i, k, j;
	i = k = j = 0;
	for(; line[i] != EOF && line[i] != '\n'; i++)
	{		
		if(i%TAB_COLUMNS == 0)
		{
			if(line[i] == ' ')
			{	
				putchar('\t');
				k++;	
				j = 0;
			}
			else
			{
				putchar(line[i]);
			}
		}
		else
		{
			if(line[i] == ' ')
			{
				j++;
			}
			else
			{
				for(; j > 0; j--)
				{
					putchar(' ');
					k++;
				}
				k++;
				putchar(line[i]);
			}
		}
	}
	if(line[i] == '\n')
		putchar('\n');
}
