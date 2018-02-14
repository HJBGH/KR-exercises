/*a solution to exercise 5-1 of k&r, fix getint to avoid treating a lonesome
 * '+' or '-' as a valid represetation of 0*/

#define BUFSIZE 100
#include <stdio.h>
#include <ctype.h>

int getint(int *pn);
char buf[BUFSIZE];

int main()
{
	int test;
	char result;
	result = getint(&test);
	printf("buffer -> %s\n", buf);
	return 0;
}

int getch(void);
void ungetch(int);

int getint(int *pn)
{
	int c, sign, signchar;

	while(isspace(c = getch())) /*skip whitespace*/
		;
	if(!isdigit(c) && c != EOF && c != '+' && c != '-')
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
