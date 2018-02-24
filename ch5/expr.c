/*This file contains a response to exercise 5-10, a basic command line 
 * reverse polish notation evaluator, written to practise using command line
 * arguments with C.*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define STACK_MAX 128
#define NUMBER '0' /*signal passed from parsearg to main to signal that an arg
is a number*/

double pop();
void push(double new);
int parsearg(char * arg);/*this abuses the convertability of char to int and back*/

static double stack[STACK_MAX];
static double *stack_p = stack;

/*we only evaluate one expression per execution*/

int main(int argc, char *argv[])
{
	char plbt = 'b';
	char *arg_p = &plbt;
	int parsed_arg;
	double hold;

	if(argc == 1)
	{
		/*this isn't an entirely correct error message*/
		printf("expr should be called as 'expr <arg>|<op> ... <arg>|<op>\n'");
		return 1;
	}
	
	/*I'll break this into functions later*/
	printf("TEST\n%f\nEND TEST\n", strtod("444.333", &arg_p));
	printf("Evaluating expression\n");
	while(--argc > 0)
	{
		printf("argc -> %d\n", argc);
		parsed_arg = parsearg(*++argv);
		printf("argv -> %s\n", *argv);
		printf("atof(*argv) -> %f\n", atof(*argv));
		printf("*argp -> %c\n", *arg_p);
		printf("argv -> %s\n", *argv);
		switch(parsed_arg)
		{
			case NUMBER:
				push(strtod(*argv, &arg_p));
				break;
			case '*':
				push(pop() * pop());
				break;
			case '+':
				push(pop() + pop());
				break;
			case '/':
				hold = pop();
				push(pop() / hold);
				break;
			case '-':
				hold = pop();
				push(pop() - hold);
				break;
			default:
				printf("Error: parsing argument failed %s\n", *argv);
				return -1;
		}
	}
	/*print whatever pops from the stack*/
	printf("Result -> %f\n", pop());
	return 0; /*Everything went smoothly*/
}

double pop()
{
	printf("pop called\n");
	if(stack != stack_p)
		return *stack_p--; /*idk if this'll work*/
	/*god-awful error handling*/
	printf("Error: empty stack");
	return 0;
}

void push(double new)
{
	printf("push called with arg %f\n", new);
	if(stack_p != stack+STACK_MAX)
	{
		*++stack_p = new;
		return;
	}
	printf("Error: full stack");
	return;
}

int parsearg(char *arg)
{
	printf("parsing arg %s\n", arg);
	int arglen = strlen(arg);
	char *arg_head = arg;

	/*needs facilities for parsing negatives*/
	/*begin the parsing*/
	if(isdigit(*arg))
	{
		printf("it's a digit\n");
		while(isdigit(*arg)) arg++;
		if(*arg == '.')
		{
			printf("it has a fractional part\n");
			arg++;
		}
		else if(*arg != '\0')
		{
			return -1;
		}
		while(isdigit(*arg)) arg++;
		if(*arg != '\0')
		{
			return -1;
		}
		printf("returning NUMBER signal\n");
		return NUMBER;
	}
	else if(strlen(arg) == 1)
	{
		printf("returning operator\n");
		return *arg; /*return the operator char*/
	}
	else
	{
		return -1;
	}	
}
	

