#include <stdio.h>
#define MAX_LEN 128

/*answer and implementation to exercise 2-2*/
int main()
{
	char line[MAX_LEN];
	int len;
	while((len = getline(line, MAX_LEN)) > 0)
	{
		printf("%s", line);
	}

}

int getline(char line[], int ll)
{
	int c, i, loop;
	loop = 1;
	i = 0;
	c = getchar();
	while(loop)
	{
		if(i >= ll-1)
		{
			break;
		}
		if(c == EOF)
		{
			break;
		}
		if(c == '\n')
		{	
			break;
		}
		line[i] = c;
		i++;
		c = getchar();
	}
	if(c == '\n')
	{
		line[i] = c;
		i++;
	}
	line[i] = '\0';
	return i;
}


