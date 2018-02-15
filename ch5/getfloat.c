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
	float test;
	char result;
	result = getfloat(&test);
	printf("buffer -> %s\n", buf);
	printf("test -> %f\n", test);
	printf("result -> %d\n", result);
	return 0;
}

int getch(void);
void ungetch(int);

int getfloat(float *pn)
{
	int c, sign, signchar = 0, pointchar, mag = 1;

	while(isspace(c = getch())) /*skip whitespace*/
		;
	/*check validity of input*/
	if(!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.')
	{
		ungetch(c);/*I HATE UNGETCH, also; it's not a number*/
		return 0;
	}

	/*process sign*/
	sign = (c == '-') ? -1 : 1;
	/*avoid treating "-\n" or "+\n" as 0*/
	if(c == '+' || c == '-')
	{
		signchar = c;
		c = getch();
	}

	/*this bit is going to cause problems for a '.' char*/
	if(!isdigit(c) && c != '.')
	{
		ungetch(c);
		ungetch(signchar);
		return 0;
	}
	/* By the time execution reaches this point we don't need to worry about
	 * the sign*/
	for(*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');

	/*process optional fractional part*/
	if(c == '.')
	{
		/*re-use this should work, not a good idea considering it's name*/
		pointchar = c;
		if(!isdigit(c = getch()))
		{
			ungetch(c);
			if(signchar) ungetch(signchar);
			ungetch(pointchar);
			return 0;
		}
		/*process the further digits*/
		for(*pn; isdigit(c); c = getch())
		{
			*pn = 10 * *pn + (c - '0');
			mag*=10;
		}
		*pn = *pn / mag;
	}
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
