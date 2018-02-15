/*A solution to exercise 5-4, return 1 if the string t occurs at the end of
 * string s*/
#include <stdio.h>
int strend(char * s, char * t);

int main()
{
	/*TODO: write tests*/
	char * s = "yellow";
	char * t = "low";
	printf("%d\n", strend(s, t));
	return 0;
}

/*I don't know how this function would handle empty strings*/
int strend(char * s, char * t)
{
	char * t_start = t; /*save starting position, avoids indexing*/
	while(*s++ != '\0' && *t++ != '\0');

	if(*s == '\0' && *t != '\0')
		return 0; /*string t is longer than string s*/
	else
	{
		while(*s++ != '\0');
	}

	while(t != t_start)
	{
		if(t-- != s--)
		{
			return 0;
		}
	}
	return 1;
}
	
