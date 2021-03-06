#include <stdio.h>

#define LINE_LEN 80
#define THRESHOLD 30

/*need to handle the following exceptional cases:
 * where the line is 2 or more times greater than the threshold line length
 * and
 * where the line has no blanks before the threshold*/

/*prints the folded version of the line*/
/*newline should be longer than line*/
int fold_line(char line[], char newline[]);
int getline(char line[], int line_len);

int main()
{	
	/*write tests for:
	 * edge cases -
	 * 		very short / non existant lines
	 * 		very long lines
	 * 		lines without blanks
	 * normal cases -
	 * 		Actual sentences
	 * these are all contained in the test file called ./fold_tests.txt
	 * note that these tests are very basic and only check the algorithm,
	 * not validate input error recovery.
	 */
	char line[LINE_LEN];
	char newline[2 * LINE_LEN];
	int len;
	int test_count = 0;
	while((len = getline(line, LINE_LEN)) > 0)
	{
		/*printf("test count: %d\n", test_count);*/
		fold(line, newline);
		printf("%s", newline);
		test_count++;
	}
	putchar('\n');
	return 0;
}

int getline(char line[], int ll)
{
	int c, i;
	for(i = 0; i < ll-1 && (c = getchar()) != EOF && c != '\n'; i++)
	{
		line[i] = c;
	}
	if(c == '\n')
	{
		line[i] = c;
		i++;
	}
	line[i] = '\0';
	return i;
}

/*there is no defensive programming in this function, the ideal use case is
 * all that is considered*/
/*also, newlines should really be called newlines[], as there are multiple in 
 * a single array*/
int fold(char line[], char newline[])
{
	int last_blank = -1;
	int i, j;
	for(j = i = 0; line[i] != '\n' && line[i] != '\0'; i++, j++)
	{
		newline[j] = line[i];
		if(line[i] == '\t' || line[i] == ' ')
		{
			last_blank = i;
		}
		if(i%THRESHOLD == 0 && i != 0)/*Handle really long lines*/
		{
			/*descisions to be made here*/
			/*normal case found*/
			if(last_blank > -1)
			{
				newline[last_blank + (j-i)] = '\n';
				last_blank = -1;
			}
			/*things get interesting here, we have to add an additonal two
		 	* characters to indicate that a line has been continued into
		 	* it's neighbour */
			else if(last_blank == -1)
			{
				char swap = newline[j]; /* we have to replace this char*/
				newline[j] = '-'; /*hypen to indicate that line continues
				on next line*/
				newline[++j] = '\n'; /*newline*/
				newline[++j] = swap; /*put the original character back where
				it should be*/
			}
		}
	}
	if(line[i] == '\n')
	{
		/*off by one?*/
		newline[j] = '\n';
	}
	newline[++j] = '\0';
	return j;
}

