/*this is a specific version of the more general problem presented in exercise
 * 1-24, the solution is to use a stack to record relevant characters and a
 * finite state machine (here represented by if-else conditions) to decide
 * how to behave*/
/*the exercise description is as follows:
 * Write a program to remove all comments from a C program. Don't forget to 
 * handle quoted strings and character constants properly*/
#include <stdio.h>
#define IN 1;
#define OUT 0;
/*comments may span multiple lines, which means that the input cannot be
 * interpreted on a strictly line by line basis*/
/*this program only checks for ANSI style comments with a slash and an asterix*/
/*unfortunately the structure of this program is going to be fairly basic
 * in order to avoid having an expressed limit on the size of the input.*/

int main()
{
	int c; /*character*/
	int nextc; /*next character, together these form the sliding window*/
	int state = OUT;
	int string_state = OUT; 
	/*Behaviour should be different if comment declarations are inside a string*/

	c = getchar();
	if(c == EOF)
	{
		return; /*spaghetti defensive programming*/
	}

	/*this doesn't do syntax validation, i.e. no brackets or comment
	 * declaration matching */
	/*this method doesn't handle strings*/
	while((nextc = getchar())!= EOF)
	{

		/*I need to check string state*/
		if(c == '\\' && nextc == '"')
		{
			/*found a character literal for " char, no state changes needed*/
		}
		else if(nextc == '"')
		{
			string_state == OUT ? string_state = IN : string_state = OUT;
		}

		/* now do comment elimination*/
		if(c == '/' && nextc == '*' && state == OUT && string_state == OUT)
		{
			/*change state to in, don't print characters*/
			state = IN;
		}
		else if(c == '*' && nextc == '/' && state == IN && string_state == OUT)
		{
			/*change state to out*/
			state = OUT;
		}
		else if(state == OUT)
		{
			putchar(c);
		}
		c = nextc; /*slide the window*/
	}
}
