#include <stdio.h>

/* Response to exercise 1 - 17, prints all input lines that are longer than
 * 80 chars*/

#define THRESHOLD_LENGTH 80
#define MAX_LENGTH 128

int getline(char line[], int ll); /* ll for line length*/

main()
{
	char line[MAX_LENGTH];
	int length;
	printf("printing lines with length > %d\n", THRESHOLD_LENGTH);
	/*0 is returned by getline on reading EOF*/
	while((length = getline(line, MAX_LENGTH)) > 0)
	{
		if(length > THRESHOLD_LENGTH)
		{
			printf("%s", line);
		}
	}
}

int getline(char line[], int ll)
{
	int c, i; /*c for character, i for increment*/

	/*complex loop condition here*/
	for(i = 0; i < ll-1 && (c = getchar()) != EOF && c != '\n'; i++)
		line[i] = c;
	
	if(c == '\n')
	{
		line[i] = c;
		++i;
	}
	line[i] = '\0'; /*append a null terminator to indicate end of string*/
	return i;
}

