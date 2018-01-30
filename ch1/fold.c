#include <stdio.h>

#define LINE_LEN 80
#define THRESHOLD 30

/*need to handle the following exceptional cases:
 * where the line is 2 or more times greater than the threshold line length
 * and
 * where the line has no blanks before the threshold*/

/*prints the folded version of the line*/
int fold_line(char line[]);
int getline(char line[], int line_len);

int main()
{
	
	/*TODO: write tests*/
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

int fold(char line[])
{
	/*TODO*/
	return 0;
}
