/*a response to exercise 1-18, removes blanks and tabs from input and deletes
 * blank lines entirely.*/

#include <stdio.h>
#define MAX_LENGTH 128
int reverse_line(char line[], int ll);
int getline(char line[], int ll); /*ll > line length*/


int main()
{	
	char line[MAX_LENGTH];
	int len, newlen;
	while((len = getline(line, MAX_LENGTH)) > 0)
	{
		reverse_line(line, len);
		printf("%s", line);
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
/*reverses a string, does not include any ending newlines or null termies in the 
 * reversal*/
int reverse_line(char line[], int len)
{
	int i, swap;	
	
	for(i = 0; i <= (len-1)-i; i++)
	{
		swap = line[(len-1)-i];
		line[(len-1)-i] = line[i];
		line[i] = swap;
	}
	return i;
}	
