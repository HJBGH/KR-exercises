/*This file will contain the extended reverse polish calculator code that 
 * results from completing exercises 4-4 through to 4-10*/
/*This should be split into multiple source files, but this is apparantly 
 * discussed later*/

#include <stdio.h>
#include <stdlib.h> /*atof()*/
#include <ctype.h>

#define MAXOP 100
#define BUFSIZE 100
#define NUMBER '0'
#define MAXVAL 100 /*maximum depth of value stack*/

int getop(char []);
void push(double);
double pop(void);
int printtop(void);
int dupe(void);/*ints are to return error codes*/
void clear(void);
int swap(void);


/* reverse Polish calculator */

int main()
{
	int type;
	double op2;
	char s[MAXOP];

	while((type = getop(s)) != EOF)
	{
		switch(type)
		{
			case NUMBER:
				push(atof(s));
				break;
			case '+':
				push(pop() + pop());
				break;
			case '*':
				push(pop() + pop());
				break;
			case '-':
				op2 = pop();
				push(pop() - op2);
				break;
			case '/':
				op2 = pop();
				if(op2 != 0.0)
				{
					push(pop() / op2);
				}
				else
				{
					printf("error: zero divisor\n");
				}
				break;
			case '%':
				op2 = pop();
				if(op2 != 0.0)
				{
					push(pop() % op2);
				}
				else
				{
					printf("error: zero divisor\n");
				}
				break;
			case '\n':
				printf("\t%.8g\n", pop());
				break;
			case 'S': /*S for swap*/
				if(swap() != 0)
					printf("error: not enough stack data to swap\n");
				break;
			case 'P':
				if(printtop() != 0)
					printf("error: nothing to print\n");
				break;
			case 'D':
				if(dupe() != 0)
					printf("error: nothing to duplicate on stack\n");
				break;
			case 'C':
				clear();/*no error codes for this one*/
				break;
			default:
				printf("error: inknown command %s\n", s);
				break;
		}
	}
	return 0;
}

/*EXTERNAL STACK VARS ARE HERE*/
int sp = 0; /*external var, next free stack position*/
double val[MAXVAL]; /*value stack*/

/*push: push f onto the stack*/
void push(double f)
{
	if(sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
}

/*pop: pop and return top value from stack*/
double pop(void)
{
	if(sp > 0)
		return val[--sp];
	else
	{
		printf("error: stack empty\n");
		return 0.0;
	}
}

/*none of the functions I've just added do any error checking, i'm unsure of
 * how to do it properly*/
int dupe(void)
{
	/*A basic implementation, does no error checking*/
	double x = pop();
	push(x);
	push(x);
	return 0;
}

int swap(void)
{
	/*todo*/
	double x = pop();
	double y = pop();
	push(y);
	push(x);
	return 0;
}

int printtop(void)
{
	double x = pop();
	push(x);
	printf("Stack top: %f\n", x);
	return 0;
}

void clear(void)
{
	sp = 0; /*cheat method, reset stack position to 0, leave data as is*/	
}


/*and now, for your enjoyment, i/o funtion prototypes*/
int getch(void); /*getch as in get-char*/
int ungetch(int);

/*getop: get next operator or numeric operand, goddamn this code is awful*/
/*s[] is the recepticle*/
int getop(char s[])
{
	int i, c, d;

	/*the idiom below eats whitespace, also sets the first character of s to
	 * be whitespace*/
	while((s[0] = c = getch()) == ' ' || c == '\t')
		;

	s[1] = '\0';/*this is such crap*/
	if(!isdigit(c) && c != '.' && c != '-')
		return c;

	/*handle negatives*/
	if(c == '-')
	{
		if(!isdigit(d = getch()) && d != '.')
		{

			return c;
		}
		c = d;
	}
	else
	{
		c = getch();
	}

	i = 0;
	if(isdigit(c)) /* collect int part*/
		while(isdigit(s[++i] = c = getch()))
			;
	if (c == '.') /*collect fraction*/
		while(isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	if(c != EOF)
		ungetch(c);
	return NUMBER;
}

/*EXTERNAL CHAR BUFFER VARS ARE HERE*/
char buf[BUFSIZE];
int bufp = 0;

/*buffer functions here*/
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
