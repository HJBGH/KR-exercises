/*This file will contain the extended reverse polish calculator code that 
 * results from completing exercises 4-4 through to 4-10*/
/*This should be split into multiple source files, but this is apparantly 
 * discussed later*/
/*The code in here handles bad input insufficiently, I don't know how to do
 * error management in C yet*/
/*due to the mind numbingly dull nature of the exercise 4.8 has been skipped*/
/*This file contains the RPC as implemented with getline instead of getch and 
 * ungetch as prescribed by exercise 4-10*/

/*THE ASSIGNMENT OPERATOR EVALUATES RIGHT TO LEFT YOU USELESS JACKASS MORON*/

#include <stdio.h>
#include <stdlib.h> /*atof()*/
#include <ctype.h>
#include <math.h>/*access to pow, exp, and sin*/
#include <string.h>

#define MAXOP 100
#define BUFSIZE 100
#define LINE_LEN 128
#define NUMBER '0'
#define MEM_LEN 27
#define MAXVAL 100 /*maximum depth of value stack*/
#define VAR_NAME '&' /*use a character that wouldn't ever be used*/
#define MATH_FUNC 'F'

int getop(char []);
void push(double);
double pop(void);
int printtop(void);
int dupe(void);/*ints are to return error codes*/
void clear(void);
int swap(void);
double runfunction(char []);
int getline(void);

double mem[MEM_LEN]; /*memory indexable by alphabetical characters*/
char expression[LINE_LEN];
int exp_p = 0; /*expression position, I'll have to reset this after each 
use*/


/* reverse Polish calculator */
int main()
{
	int type;
	double op2;
	char s[MAXOP];
	char active_var;

	int i = 0;
	for(i; i<MEM_LEN; i++)
		mem[i] = 0.0; /*reset memory*/

	while(getline() > 0) /*empty input causes program to exit*/
	{
		/*call getop here*/
		switch(type)
		{
			case NUMBER:
				push(atof(s));
				break;
			case MATH_FUNC:
				push(runfunction(s));
				break;
			case VAR_NAME:
				/*how the fuck do i deal with this?*/
				active_var = s[0] - 'a';
				push(mem[active_var]);/*takes a variable an puts it on the stack*/
				break;
			case '+':
				push(pop() + pop());
				break;
			case '*':
				push(pop() * pop());
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
			case '>': /*setting vars, this doesn't handle bad input well*/
				getop(s);
				if(strlen(s) > 1)
				{
					printf("error: variable names must be one character.\n");
				}
				if(s[0] - 'a' < 0 || s[0] - 'a' > 25)
				{
					printf("error: invalid var name: %c\n", s[0]);
				}
				else
				{
					op2 = pop();
					printf("setting %c to %f\n", s[0]-'a', op2);
					mem[s[0] - 'a'] = op2;/*this is buggy, it allow the 
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


double runfunction(char s[])
{
	/*deal with function call*/
	int spare;	
	if(strcmp("exp", s) == 0)
	{
		/*call exp*/
		return exp(pop());
	}
	if(strcmp("sin", s) == 0)
	{
		return sin(pop());
	}
	if(strcmp("pow", s) == 0)
	{
		spare = pop();
		return pow(pop(), spare);
	}
	printf("Error. function name %s not recognized.\n", s);
	return 0.0;
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

/*getop: get next operator, numeric operand, function call or variable,
 * goddamn this code is awful*/
/*s[] is the recepticle*/
int getop(char s[])
{
	int i = 0, c, d;/*ALWAYS INITIALIZE AS YOU DECLARE*/
	s[1] = '\0'; /*clear the string*/

	/*getop uses the exp_p and the expression string to operate*/
	while((s[i] = c = expression[exp_p]) == ' ' || expression[exp_p] == '\t')
	{
		exp_p++;
	}

	/*deal with function calls and variable names*/
	if(isalpha(c))
	{
		while(isalpha(c = expression[exp_p++]))
		{
			s[++i] = c; /*avoid erroneous string contents*/
		}

		s[++i] = '\0';

		if(strlen(s) == 1)
		{
			return VAR_NAME;
		}
		else
		{
			return MATH_FUNC;
		}
	}

	if(!isdigit(c) && c != '.' && c != '-')
	{
		return c; /*not a number, some form of instruction*/
	}

	/*handle negative number*/
	if(c == '-')
	{
		d = expression[exp_p++];
		if(!isdigit(d) && d != '.')
		{
			/*we've found a Subtraction command*/
			return c;
		}
		s[i] = c;
		s[++i] = d;
		c = d;
	}

	if(isdigit(c)) /*collect integer bit*/
	{
		while(isdigit(s[++i] = c = expression[exp_p++]))
			;
	}
	if(c == '.') /*collect fraction bit*/
	{	
		while(isdigit(s[++i] = c = expression[exp_p++]))
			;
	}
	s[i] = '\0';
	printf("%s\n", s);
	return NUMBER;
}
/*no function arguments just copy straight to the expression var*/
int getline()
{
	/*get the line mang*/
	int c, i = 0;
	for(i; i < LINE_LEN -1  && ((c = getchar()) != '\n' && c != EOF); i++)
	{
		expression[i] = c;
	}
	if(c == '\n')
	{
		expression[i] = '\n';
		i++;
	}
	expression[i] = '\0';
	/*this is convienient, we don't have to worry about EOF anymore*/
	return i;
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
	mem[26] = x;/*save most recently printed value to last available variable*/
	return 0;
}

void clear(void)
{
	sp = 0; /*cheat method, reset stack position to 0, leave data as is*/	
}
