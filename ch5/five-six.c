/*This contains pointer based re-implementations of some of the functions
 * given in K & R second ed, as per exercise 5-6*/

#include <stdio.h>
#include <string.h>

int getline(char * s, size_t n); /*get n characters int s, return it's length*/
int getop(char * s); /*get next operator or numeric operand*/
char * reverse(char * s, size_t l); /*reverse a string l chars long*/

int main()
{
	/*TODO: write tests*/
	return 0;
}

int getline(char * s, size_t n)
{
	int c;
	char * s_head = s;
	while(--n > 0 && (c=getchar()) != EOF && c != '\n')
	{
		*s = c;
		s++;
	}
	if(c == '\n')
	{
		*s = c;
		s++;
	}
	*s = '\0';
	return s - s_head;
}

int getop(char * s)
{
	/*TODO: write this function*/
	return 0;
}

char * reverse(char * s, size_t l)
{
	/*TODO: write this function*/
	return NULL;
}
