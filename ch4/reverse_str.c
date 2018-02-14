/*A solution to exercise 4-13, recursively reverse a string*/

#include <stdio.h>
#include <string.h>

void reverse(char string[], int left, int right); /*on the initial call, left is 0, right is strlen()-1;*/

int main()
{
	/*TODO: write tests*/
	char test[] = "Test string";
	reverse(test, 0, strlen(test)-1);
	printf("%s\n", test);
	return 0;
}

void reverse(char string[], int left, int right)
{
	if(left < right)
	{
		reverse(string, left+1, right-1);
	}
	printf("left -> %d\n", left);
	printf("right -> %d\n", right);
	char temp = string[left];
	string[left] = string[right];
	string[right] = temp;
}

