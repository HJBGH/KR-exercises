/*implementation of strcat using pointers as per exercise 5.3*/

#include <stdio.h>

void hb_strcat(char * s, char * t);

int main()
{
	/*TODO: write tests*/
	char s[50] = "hello ";
	char * t = "world!";
	hb_strcat(s, t);
	printf("%s\n", s);
	return 0;
}

/*This is not memory safe in the slightest, it probably segfaults*/
void hb_strcat(char * s, char * t)
{
	while(*s != '\0')
	{
		s++; /*increment the pointer*/
	}
	while((*s++ = *t++) != '\0'); 
	/*the idiom above copies t onto the end of s assuming there's enough space
	 * and segfaults otherwise*/
}
