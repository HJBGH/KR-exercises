/*a response to exercise 1-18, removes blanks and tabs from input and deletes
 * blank lines entirely.*/

#include <stdio.h>
#define MAX_LENGTH 128
int remove_trailing_ws(char line[]); /*line[] should be terminated with a null termi or a 
										newline*/
int getline(char line[], int ll); /*ll > line length*/


int main()
{	
	char line[MAX_LENGTH];
	int len, newlen;
	while((len = getline(line, MAX_LENGTH)) > 0)
	{
		newlen = remove_trailing_ws(line);
		if(newlen > 0)
		{
			printf("%s", line);
		}
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

	
int remove_trailing_ws(char line[])
{
	int i, k; /*you should know what i and c are by now, k is used to record
	the position of the last non whitespace, non newline character*/
	k = 0;
	for(i = 0; line[i] != EOF && line[i] != '\n'; i++)
	{
		if(line[i] != ' ' && line[i] != '\t')
		{
			k = i;
		}
	}
	/*doesn't handle full buffer array nicely, crashes*/
	if(line[i] == '\n' && k > 0)
	{
		k++;
		line[k] == '\n';
		k++;
		line[k] == '\0';
	}
	else
	{
		line[k] == '\0';	
	}
	return k;
}	
