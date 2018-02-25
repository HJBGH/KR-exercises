/*A personal re-implmentation of strncmp, as per exercise 5-5 of K & R, 
 * strncmp compares a maximum of n chars from each input string returning
 * an int value of:
 * less than zero if the 1st string is lexicographically lesser than the 2nd 
 * greater than zero if the 1st string is lexicographically greater that the 2nd
 * equal to zero if the 1st string is lexicographically equal to the 2nd*/

#include <stdio.h>
#include <string.h>

int hb_strncmp(const char * s, const char * t, size_t n);

int main()
{
	/*TODO: write tests*/
	printf("This should be zero ->\t%d\n", hb_strncmp("implore", "imply", 3));
	printf("This should be > zero ->\t%d\n", hb_strncmp("abelone", "zebra", 3));
	printf("This should be < zero ->\t%d\n", hb_strncmp("zone", "aleph", 2));
	return 0;
}

int hb_strncmp(const char * s, const char * t, size_t n)
{
	int result;	
	for(n; n > 0; n--)
	{
		result = *t++ - *s++;
		if(result != 0)
			return result;
		
	}

	return 0; /*default case*/
}
