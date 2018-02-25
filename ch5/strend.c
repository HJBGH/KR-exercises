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
	printf("t_start -> %c\n", *t_start);
	while(*s != '\0' && *t != '\0')
	{
		t++;
		s++;
	}

	if(*t == '\0')
		printf("t is where it should be\n");

	if(*s == '\0' && *t != '\0')
	{	
		printf("t is longer than s\n");
		return 0; /*string t is longer than string s*/
	}
	else
	{
		printf("incrementing s\n");
		while(*s != '\0') s++;
	}
	
	if(*t == *s)
		printf("true\n");

	while(t != t_start)
	{
		/*this should run more than once*/
		printf("t -> %c and s -> %c\n", *t, *s);
		if(t == t_start)
		{
			printf("FUCK");
		}
		if(*t-- != *s--)
		{
			printf("%c and %c are not the same\n", *t, *s);
			return 0;
		}
	}
	return 1;
}
	
