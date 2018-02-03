/*This is a test program to ensure that the comments_b_gone program works as
 * intended*/
#include <stdio.h>


int main() /*test comment*/
{
	printf("/*this should stay here */");
	putchar('\"');
	/*this should be removed*/
}
