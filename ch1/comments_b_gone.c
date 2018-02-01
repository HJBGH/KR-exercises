/*this is a specific version of the more general problem presented in exercise
 * 1-24, the solution is to use a stack to record relevant characters and a
 * finite state machine (here represented by if-else conditions) to decide
 * how to behave*/
/*the exercise description is as follows:
 * Write a program to remove all comments from a C program. Don't forget to 
 * handle quoted strings and character constants properly*/
#include <stdio.h>

/*comments may span multiple lines, which means that the input cannot be
 * interpreted on a strictly line by line basis*/
/*this program only checks for ANSI style comments with a slash and an asterix*/
/*unfortunately the structure of this program is going to be fairly basic
 * in order to avoid having an expressed limit on the size of the input.*/

int main()
{
	int c; /*character*/
	int nextc; /*next character, together these form the sliding window*/

	c = getchar();
	if(c == EOF)
	{
		return; /*spaghetti defensive programming*/
	}

	while((nextc = getchar())!= EOF)
	{
		/*do the thing*/
	}
}
