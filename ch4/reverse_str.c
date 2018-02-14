/*A solution to exercise 4-13, recursively reverse a string*/

#include <stdio.h>
#include <string.h>

void swap(int x, int y); /*non generic swap routine, used in reverse*/
void reverse(char string[], int left, int right); /*on the initial call, left is 0, right is strlen()-1;*/

int main()
{
	/*TODO: write tests*/
	return 0;
}

void reverse(char string[], int left, int right)
{
	/*TODO*/
}

void swap(int x, int y)
{
	int temp;
	temp = x;
	x = y;
	y = temp;
}
