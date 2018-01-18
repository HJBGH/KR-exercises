/*a response to exercise 1-18, removes blanks and tabs from input and deletes
 * blank lines entirely.*/

#include <stdio.h>
#define MAX_LENGTH 128
int remove_trailing_ws(char line[], int ll); //ll -> line length

main()
{

}

/*this function gets a newline and processes it in one go, perhaps I should
 * separate these two operations*/
int remove_trailing_ws(char line[], int ll)
{
	int i, c, k; /*you should know what i and c are by now, k is used to record
	the position of the last non whitespace, non newline character*/
	for(i = 0; i < ll-1 && (c = getchar()) != EOF && c != '\n'; i++)
	{
		line[i] = c;
		if(c != ' ' && c != '\t')
		{
			k = i;
		}
	}

	/*doesn't handle full buffer array nicely, crashes*/
	if(c == '\n')
	{
		k++;
		line[k] == '\n';
		k++
		line[k] == '\0';
	}
	/*delete lines that are entirely whitespace*/
	if(k == 0)
	{
		return 0;
	}
	return i
	
	/*need to consider edge cases*/
