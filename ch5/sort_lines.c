/*This file contains the program outlined on pages 108-110 of K & R, with the
 * readline subroutine modified according to the suggestions in exercise 5-7*/

#include <stdio.h>
#include <string.h>


#define MAXLINES 5000
#define MAXLEN 100

char * lineptr[MAXLINES]; /*pointers to text lines*/

int readlines(char * lineptr[], int nlines);
int writelines(char * lineptr[], int nlines);

void qsort(char * lineptr[], int left, int right);

/*main routine organises it all, sorts input lines*/
int main()
{
	int nlines;

	if((nlines = readlines(lineptr, MAXLINES)) >= 0)
	{
		qsort(lineptr, 0, nlines-1);
		writelines(lineptr, nlines);
		return 0;
	}
	else
	{
		printf("Error: input to big to sort\n");
		return 1;
	}
}

int getline(char *, int);
char * alloc(int); /*custom memory allocation routine*/

/*readlines: read input lines*/
int readlines(char * lineptr[], int maxlines)
{
	int len, nlines;
	char *p, line[MAXLEN];

	nlines = 0;
	while((len = getline(line, MAXLEN)) > 0)
	{
		if(nlines >= maxlines || (p = alloc(len)) == NULL)
		{
			return -1;
		}
		else
		{
			line[len-1] = '\0'; /*delete newline*/
			strcpy(p, line);
			lineptr[nlines++] = p;
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
void qsort(char *v[], int left, int right)
{
	int i, last;
	void swap(char *v[], int i, int j);
	
	if(left >= right)/*Array has fewer tha 2 elements*/
		return;

	swap(v, left, (left + right) /2);
	last = left;
	for(i = left+1l i <= right; i++)
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

#define ALLOCSIZE 10000 /*size of available space*/

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
