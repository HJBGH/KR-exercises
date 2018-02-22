/*This file contains a response to exercise 5-10, a basic command line 
 * reverse polish notation evaluator, written to practise using command line
 * arguments with C.*/

#include <stdio.h>
#define STACK_MAX 128

double pop();
void push(double new);
int parsearg(char * arg);/*this abuses the convertability of char to int and back*/

static double stack[STACK_MAX];
static double *stack_head = stack;

/*we only evaluate one expression per execution*/

int main(int argc, char *argv[])
{
	char * arg;
	if(argc == 1)
	{
		/*this isn't an entirly correct error message*/
		printf("expr should be called as 'expr <arg>|<op> ... <arg>|<op>\n'");
		return 1;
	}

	/*I'll break this into functions later*/

	
	return 0; /*Everything went smoothly*/
}

double pop()
{
	if(stack != stackhead)
		return *stack--; /*idk if this'll work*/
	/*god-awful error handling*/
	printf("Error: empty stack");
	return 0;
}

void push(double new)
{
	if(stack != stackhead+STACK_MAX)
	{
		*++stack = new;
		return;
	}
	printf("Error: full stack");
	return;
}

int parsearg(char * arg)
{
	/*TODO: write argument parsing function*/
	return 0;
}
	

