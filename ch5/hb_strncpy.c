/*One part of the answers to exercise 5-5, write your own version of library
 * functions*/

/*strncpy is described on tutorialspoint.com thusly: The C Library function
 * char * strncpy(char * dest, const char * src, size_t n) copies up to n 
 * characters from the string pointed to, by src to dest. In a case where the
 * length or src is less than that of n, the remainder of dest will be padded
 * with null bytes.*/

#include <stdio.h>
#include <string.h>

char * hb_strncpy(char * s, char * t, size_t n);

int main()
{
	/*TODO: write tests*/
	return 0;
}

char * hb_strncpy(char * s, char * t, size_t n)
{
	char * t_head = t;
	/*TODO: implement this function*/
}

