/*This file will contain the extended reverse polish calculator code that 
 * results from completing exercises 4-4 through to 4-10*/
/*This should be split into multiple source files, but this is apparantly 
 * discussed later*/

#include <stdio.h>
#include <stdlib.h> /*atof()*/
#include <ctype.h>
#include <math.h>/*access to pow, exp, and sin*/

#define MAXOP 100
#define BUFSIZE 100
#define NUMBER '0'
#define MEM_LEN 27
#define MAXVAL 100 /*maximum depth of value stack*/

int getop(char []);
void push(double);
double pop(void);
int printtop(void);
int dupe(void);/*ints are to return error codes*/
void clear(void);
int swap(void);

double mem[MEM_LEN]; /*memory indexable by alphabetical characters*/

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
				printf("pushing a number to the stack\n");
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
					push(fmod(pop(),op2));
				}
				else
				{
					printf("error: zero divisor\n");
				}
				break;
			case 's': /*little s for sin()*/
				push(sin(pop()));
				break;
			case 'e': /*little e for exp()*/
				push(exp(pop()));
				break;
			case '^': /*little p for pow()*/
				op2 = pop();
				push(pow(pop(), op2));/*this might blow up if there's an empty
				stack of if a 0 is on it*/
				break;
			case '>': /*setting vars, this doesn't handle bad input well*/
				type = getop(s);
				if(type - 'a' < 0 || type - 'a' > 26)
				{
					printf("error: invalid var name\n");
				}
				else
				{
					op2 = pop();
					printf("setting %d to %f\n", type-'a', op2);
					mem[type - 'a'] = op2;/*this is buggy, it allow the 
					user to fill the memory with 0.0, as pop() returns 0.0
					when there's nothing on the stack,
					I still don't know how to manager error recovery in this
					language*/
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
				printf("error: unknown command %s\n", s);
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
void ungetch(int);

/*getop: get next operator or numeric operand, goddamn this code is awful*/
/*s[] is the recepticle*/
int getop(char s[])
{
	printf("calling getop\n");
	int i = 0, c, d;/*ALWAYS INITIALIZE AS YOU DECLARE*/

	while((s[i++] = c = getch()) == ' ' || c == '\t')
		;

	s[i] = '\0';
	if(!isdigit(c) && c != '.' && c != '-')
	{
		return c; /*not a number*/
	}

	/*handle negative number*/
	if(c == '-')
	{
		printf("Negative case\n");
		d = getch();
		if(!isdigit(c) && c != '.')
		{
			printf("Returning c\n");
			return c;
		}
		/*s[0] has already been set to c*/
		c = d;
	}
	else
	{
		c = getch();
	}

	if(isdigit(c)) /*collect integer bit*/
	{
		while(isdigit(s[++i] = c = getch()))
			;
	}
	if(c == '.') /*collect fraction bit*/
	{	
		while(isdigit(s[++i] = c = getch()))
			;
	}
	s[i] = '\0';
	if(c != EOF)
		ungetch(c);
	printf("%s\n", s);
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
	{
		printf("ungetching\n");
		buf[bufp++] = c;
	}
}
