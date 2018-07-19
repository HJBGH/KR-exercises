/*This file contains a solution to project 6.2 of chapter six of K&R 2nd 
 * edition*/

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


/*binary tree nodes for collecting variable names*/
struct tnode{
     *word;
    int count;
    struct tnode *left;
    struct tnode *right;
}

#define NKEYS (sizeof keytab / sizeof keytab[0])

int getword(char *, int);
int binsearch(char *, struct key *, int);
void treeprint(struct tnode *p); /*in order print function*/
struct tnode *addtree(struct tnode *p, char *w);
/*remember to define support functions for this*/
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
        else if(word[0] == '*' && lastc == '/' && 
                strlen(word) == 1 && status == CODE)
        {
            status = COMMENT;
        }
        else if(word[0] == '/' && lastc == '*' && 
                strlen(word) == 1 && status == COMMENT)
        {
            status = CODE;
        }
        else if(word[0] == '#' && status == CODE && strlen(word) == 1)
        {
            /*printf("pre processor instruction detected\n");*/
            status = PRE_PROC;
        }
        else if(word[0] == '\n' && status == PRE_PROC && strlen(word) == 1)
        {
            status = CODE;
        }
        else if(word[0] == '"' && strlen(word) == 1 && status == CODE)
        {
            if(lastc != '\''){
                status = STRING_LIT;
                /*printf("string lit\n");*/}
        }
        else if(word[0] == '"' && strlen(word) == 1 && status == STRING_LIT)
        {
            status = CODE;
            /*printf("code\n");*/
        }
        lastc = word[0];
    }
    for(n = 0; n < NKEYS; n++)
        if(keytab[n].count > 0)
            printf("%4d %s\n", keytab[n].count, keytab[n].word);
    return 0;
}

struct * tnode bintreesearch(struct *tnode p); /*search a binary tree*/

/*binary search for the keytab array, needs to be updated to search a bin tree*/
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

/*getword and the getch-ungetch pair are essential to pretty much
 * any project in this chapter*/
/*getword; get the next word or character from input*/
int getword(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;
    
    /*I have to modify this to return newlines*/
    do{
        c = getch();
    }while(isspace(c) && c != '\n');
    /*
    while(isspace(c = getch()))
        ;*/
    if(c != EOF)
        *w++ = c; 
    if(!isalpha(c) && c != '_')
    {
        *w = '\0';
        return c;
    }
    for(; --lim > 0; w++)
        if(!isalnum(*w = getch()) && *w != '_')
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
