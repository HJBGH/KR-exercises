/*This file contains a copy of the getword program as given in chapter 
 * six of K&R 2nd edition*/

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAXWORD 100

struct key{
    char *word;
    int count;
} keytab[] = {
    "auto", 0,
    "break", 0,
    "case", 0,
    "char", 0,
    "const", 0,
    "continue", 0,
    "default", 0,
    /*... more may go here*/
    "unsigned", 0,
    "void", 0,
    "volatile", 0,
    "while", 0
};

#define NKEYS (sizeof keytab / sizeof keytab[0])

int getword(char *, int);
int binsearch(char *, struct key *, int);
enum{CODE, COMMENT, PRE_PROC, STRING_LIT};
unsigned int status = CODE;
/*count C keywords*/
int main(int argc, char *argv[])
{
    int n;
    char lastc;
    char word[MAXWORD];

    while(getword(word, MAXWORD) != EOF)
    {
        if(isalpha(word[0]) && status == CODE)
        {
            if((n = binsearch(word, keytab, NKEYS)) >= 0)
                keytab[n].count++;
        }
        /*detect comments*/
        else if(word[0] == '*' && lastc == '/' && strlen(word))
        {
            printf("COMMENT START DETECTED\n");
        }
        lastc = word[0];
    }
    for(n = 0; n < NKEYS; n++)
        if(keytab[n].count > 0)
            printf("%4d %s\n", keytab[n].count, keytab[n].word);
    return 0;
}

/*binary search for the keytab array*/
int binsearch(char *word, struct key tab[], int n)
{
    int cond;
    int low, high, mid;

    low = 0;
    high = n - 1;
    while(low <= high)
    {
        mid = (low+high)/2;
        if((cond = strcmp(word, tab[mid].word)) < 0)
            high = mid -1;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;/*return the position of the element*/
    }
    return -1;/*element not in array*/
}

/*getword; get the next word or character from input*/
int getword(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while(isspace(c = getch()))
        ;
    if(c != EOF)
        *w++ = c; 
    if(!isalpha(c))
    {
        *w = '\0';
        return c;
    }
    for(; --lim > 0; w++)
        if(!isalnum(*w = getch()))
        {
            ungetch(*w);
            break;
        }
    *w = '\0';
    return word[0];
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

/*get a char from input or from the pushback buffer*/
int getch(void)
{
    /*printf("getch called\n");
    printf("bufp: %d\n", bufp);*/
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/*stick a char in the pushback buffer*/
void ungetch(int c)
{
    if(bufp >= BUFSIZE)
        printf("ungetch error: too many characters\n");
    else
        buf[bufp++] = c;
} /*This is a test comment here are some keywords char int while while while*/
