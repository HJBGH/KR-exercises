/*This file contains the program outlined on pages 108-110 of K & R, with the
 * readline subroutine modified according to the suggestions in exercise 5-7*/
/*note that I haven't actually measured the runtime difference, but I have 
 * googled the exercise as included some notes*/
/*As it stands I don't think either method of managing memory produces much
 * difference in this toy example because the only thing that changes is the
 * function managing it. In a real world example using stack memory instead of
 * heap memory would be fast I think, as heap memory would have to be assigned
 * by the OS during runtime*/
#include <stdio.h>
#include <string.h>


#define ALLOCSIZE 10000 /*size of available space*/
#define MAXLINES 5000
#define MAXLEN 100

char * lineptr[MAXLINES]; /*pointers to text lines*/

int readlines(char * lineptr[], int nlines, char * lines);
void writelines(char * lineptr[], int nlines);

void qsort(char * lineptr[], int left, int right);

/*main routine organises it all, sorts input lines*/
int main()
{
	int nlines;
	char lines[ALLOCSIZE];

	if((nlines = readlines(lineptr, MAXLINES, lines)) >= 0)
	{
		qsort(lineptr, 0, nlines-1);
		writelines(lineptr, nlines);
		printf("Number of lines -> %d\n", nlines);
		return 0;
	}
	else
	{
		printf("Error: input to big to sort\n");
		return 1;
	}
}

int getline(char * s, size_t n);
char * alloc(int); /*custom memory allocation routine*/

/*readlines: read input lines*/
int readlines(char * lineptr[], int maxlines, char * lines)
{
	int len, nlines;
	char *p, line[MAXLEN];
	static char * lines_p = NULL;

	if(lines_p == NULL)
	{
		lines_p = lines;
	}
	nlines = 0;
	while((len = getline(line, MAXLEN)) > 0)
	{
		if(nlines >= maxlines || (lines_p + len) >= lines + ALLOCSIZE )
		{
			return -1;
		}
		else
		{
			line[len-1] = '\0'; /*delete newline*/
			strcpy(lines_p, line);
			printf("got line -> %s\n", lines_p);
			lineptr[nlines++] = lines_p;
			lines_p += len;
		}
	}
	return nlines;
}

/*writelines: write output lines*/
void writelines(char * lineptr[], int nlines)
{
	while(nlines-- > 0)
		printf("%s\n", *lineptr++);
}

/*recursive quicksort*/
/*sort v[left]...v[right] into increasing order*/
void qsort(char *v[], int left, int right)
{
	printf("quicksorting\n");
	int i, last;
	void swap(char *v[], int i, int j);/*nested function prototype?*/
	
	if(left >= right)/*Array has fewer tha 2 elements*/
	{
		printf("done here\n");
		return;
	}

	swap(v, left, (left + right)/2);
	last = left;
	for(i = left+1; i <= right; i++)
	{
		if(strcmp(v[i], v[left]) < 0)
		{
			swap(v, ++last, i);
		}
	}
	swap(v, left, last);
	qsort(v, left, last-1);
	qsort(v, last+1, right);
}
	
void swap(char *v[], int i, int j)
{
	char * temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}


static char allocbuf[ALLOCSIZE];
static char * allocp = allocbuf;

char * alloc(int n)
{
	if(allocbuf + ALLOCSIZE - allocp >= n)
	{
		allocp += n;
		return allocp - n; /*old p*/
	}
	else
	{
		return 0;
	}
}

void afree(char * p)
{
	if(p >= allocbuf && p < allocbuf + ALLOCSIZE)
		allocp = p;
}

int getline(char * s, size_t n)
{
	int c;
	char * s_head = s;
	while(--n > 0 && (c=getchar()) != EOF && c != '\n')
	{
		*s = c;
		s++;
	}
	if(c == '\n')
	{
		*s = c;
		s++;
	}
	*s = '\0';
	return s - s_head;
}

