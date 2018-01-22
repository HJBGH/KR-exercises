/*A response to exercise 2-5, return the first location in the string s1 where
 * any char of s2 occurs*/

#include <stdio.h>

int any(char s1[], char s2[]);

int main()
{
	printf("%d\n", any("this is a test string", "snakes"));
	printf("%d\n", any("This is another test string", "!!!!"));

}

int any(char s1[], char s2[])
{
	/*the O(mn) complexity isn't great.*/
	int i, j;

	for(i = 0; s2[i] != '\0'; i++)
	{
		for(j = 0; s1[j] != '\0'; j++)
		{
			if(s1[j] == s2[i])
			{
				return j;
			}
		}
	}
	return -1;
}

