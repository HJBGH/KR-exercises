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
int comments_b_gone(char line[]); /*use a sliding window to read*/
