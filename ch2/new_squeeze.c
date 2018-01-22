/*response to exercise 2-4, editing the squeeze subroutine on page 47 to
 * delete any char in s1 that exists in s2*/

#include <stdio.h>

void squeeze(char s1[], char s2[]);

int main()
{
	/*TODO: write test calls*/
	char test[] = "I'm a goofy goober yea!";
	char remove[] = "fog!";
	squeeze(test, remove);
	printf("%s\n", test);
	char test2[] = "the quicAk browYn foxY jumpeLd Mover the lAzy dOg";
	char remove2[] = "abcdefghijklmnopqrstuvwxyz";
	squeeze(test2, remove2);
	printf("%s\n", test2);
}

void squeeze(char s1[], char s2[])
{
	/*the O(mn) complexity isn't great.*/
	int i, j, k;

	for(i = 0; s2[i] != '\0'; i++)
	{
		for(j = k = 0; s1[j] != '\0'; j++)
		{
			if(s1[j] != s2[i])
			{
				s1[k++] = s1[j];
			}
		}
		s1[k] = '\0';
	}
}

