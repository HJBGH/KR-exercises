/*One part of the answers to exercise 5-5, write your own version of library
 * functions*/

/*strncpy is described on tutorialspoint.com thusly: The C Library function
 * char * strncpy(char * dest, const char * src, size_t n) copies up to n 
 * characters from the string pointed to, by src to dest. In a case where the
 * length or src is less than that of n, the remainder of dest will be padded
 * with null bytes.*/

#include <stdio.h>
#include <string.h>

char * hb_strncpy(char * s, const char * t, size_t n);

int main()
{
	char testdest[20];
	char * testsrc = "test source";
	hb_strncpy(testdest, testsrc, 10);
	printf("%s\n", testdest);
	/*Write more tests*/
	return 0;
}

/*in this version s is dest, t is src*/
/*disregard memory safety when padding with '\0'*/
char * hb_strncpy(char * s, const char * t, size_t n)
{
	char * s_head = s;
	for(n; n > 0; n--)
	{
		printf("looping\n");
		*s = *t;
		s++;
		if(*t != '\0')
			t++;	
	}
	/*incorrect use of '\0'*/
	return s_head;
}

