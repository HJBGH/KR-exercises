/*A personal implementation of strncat() as per exercise 5-5 of K & R,
 * append n characters of one string to the end of another*/

#include <stdio.h>
#include <string.h>

/*this goes a lot like strncpy, except one has to advance the pointer
 * of the destination string to the first null char*/

char * hb_strncat(char * s, char * t, size_t n);

int main()
{
	/*TODO: write tests*/
	char testdest[100] = "TEST DESTINATION";
	hb_strncat(testdest, "lollapallooza", 8);
	printf("%s\n", testdest);
	return 0;
}

char * hb_strncat(char * s, char * t, size_t n)
{
	char * s_head = s;
	while(*s != '\0') s++;
	for(n; n > 0; n--)
	{
		*s = *t;
		s++; /*advance s*/
		if(*t != '\0')
			t++;
	}
	*s = '\0';
	return s_head;
}

