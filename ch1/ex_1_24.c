/* This is just some notes for now. But my idea is to use a stack which pops 
 * the relevant symbol when its appropriate counterpart is found*/

#include <stdio.h>

#define STACK_SIZE 1024

enum states {COMMENT, CODE};

int main()
{
	/*ideally I'd use a linked list to implement this stack, but we haven't
	 * reached that point in the book yet and I'd like to keep things by
	 * the numbers*/
	char stack[STACK_SIZE];
	int c;
	int nextc;
	int stack_head; /*This would be better as a pointer*/
	enum states state = CODE;
}

