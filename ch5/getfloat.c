/*a solution to exercise 5-2 of k&r, write getfloat*/
/*In answer to the the question: What type does getfloat return as its function
 * value? It returns an int, as this is an indicator of execution status not
 * a piece of data*/

#define BUFSIZE 100
#include <stdio.h>
#include <ctype.h>

int getfloat(float *pn);
char buf[BUFSIZE];

int main()
{
	int test;
	char result;
	result = getfloat(&test);
	printf("buffer -> %s\n", buf);
	return 0;
}

int getch(void);
void ungetch(int);

int getfloat(float *pn)
{
	int c, sign, signchar;

	while(isspace(c = getch())) /*skip whitespace*/
		;
	if(!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.')
	{
		ungetch(c);/*I HATE UNGETCH, also; it's not a number*/
		return 0;
	}

	sign = (c == '-') ? -1 : 1;
	if(c == '+' || c == '-')
	{
		signchar = c;
		c = getch();
	}
	if(!isdigit(c))
	{
		ungetch(c);
		ungetch(signchar);
		return 0;
	}
	for(*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	*pn *= sign;
	if(c != EOF)
		ungetch(c);
	return c;
}

int bufp = 0;

int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}
