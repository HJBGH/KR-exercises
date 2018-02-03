/* This is just some notes for now. But my idea is to use a stack which pops 
 * the relevant symbol when its appropriate counterpart is found*/

#include <stdio.h>

#define STACK_SIZE 1024

/*used to determine where the program is as it reads the source code*/
enum states {COMMENT, CODE, STRING};

int main()
{
	/*ideally I'd use a linked list to implement this stack, but we haven't
	 * reached that point in the book yet and I'd like to keep things by
	 * the numbers*/
	/*use multiple stacks for different symbols?*/
	char stack[STACK_SIZE];
	int c;
	int nextc;
	int stack_head; /*This would be better as a pointer*/
	enum states state = CODE;

	c = getchar();
	if(c == EOF)
	{
		return 0;
	}

	while((nextc = getchar()) != EOF)
	{
		/*analyse syntax*/
		if(state == CODE)
		{
			/*handle cases*/
		}
		else if(state == COMMENT)
		{
			/*handle cases*/
		}
		else if(state == STRING)
		{
			/*handle cases*/
		}
	}
}

