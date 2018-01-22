/*response to exercise 2-4, editing the squeeze subroutine on page 47 to
 * delete any char in s1 that exists in s2*/

#include <stdio.h>

void squeeze(char s1[], char s2[]);

int main()
{
	/*TODO: write test calls*/
}

void squeeze(char s1[], char s2[])
{
	/*the O(mn) complexity isn't great.*/
	int i, j, k;

	for(i = 0; i != '\0'; i++)
	{
		for(j = k = 0; j!= '\0'; j++)
		{
			if(s1[j] != s2[i])
			{
				s1[k++] = s1[j];
			}
		}
		s1[k] = '\0';
	}
}

