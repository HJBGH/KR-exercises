/*This file contains a response to exercise 5-10, a basic command line 
 * reverse polish notation evaluator, written to practise using command line
 * arguments with C.*/

#include <stdio.h>
#include <string.h>
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
	char * arg_p;
	int parsed_arg;
	if(argc == 1)
	{
		/*this isn't an entirly correct error message*/
		printf("expr should be called as 'expr <arg>|<op> ... <arg>|<op>\n'");
		return 1;
	}

	arg_p = argv+1;/*set to first argument*/
	double hold;
	/*I'll break this into functions later*/
	do
	{
		parsed_arg = parsearg(arg_p);
		switch(parsed_arg)
		{
			case NUMBER:
				push(strtod(arg_p));
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
				printf("Error: parsing argument failed %s\n", arg_p);
				return -1;
		}
	}
	while(arg_p != argv + (argc + 1))
	
	return 0; /*Everything went smoothly*/
}

double pop()
{
	if(stack != stack_p)
		return *stack_p--; /*idk if this'll work*/
	/*god-awful error handling*/
	printf("Error: empty stack");
	return 0;
}

void push(double new)
{
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
	int arglen = strlen(arg);
	char *arg_head = arg;

	/*needs facilities for parsing negatives*/
	/*begin the parsing*/
	if(isdigit(*arg))
	{
		while(isdigit(*arg)) arg++;
		if(*arg == '.')
		{
			arg++;
		}
		else
		{
			return -1;
		}
		while(isdigit(*arg)) arg++;
		if(*arg != '\0')
		{
			return -1;
		}
		else
		{
			return NUMBER;
		}
	}
	
	return 0;
}
	

