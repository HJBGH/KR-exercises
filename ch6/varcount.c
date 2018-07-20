/*This file contains a solution to project 6.2 of chapter six of K&R 2nd 
 * edition*/

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAXWORD 100

char * keywords[] = {
    "auto",
    "break",
    "case",
    "char",
    "const",
    "continue",
    "default",
    "unsigned", 
    "void",
    "volatile",
    "while",
    "sizeof"
};


/*binary tree nodes for collecting variable names*/
struct tnode{
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
}

#define NKEYS (sizeof keytab / sizeof keytab[0])

int getword(char *, int);
struct tnode * bintreesearch(struct tnode *p, char *w); /*search a binary tree*/
void treeprint(struct tnode *p); /*in order print function*/
struct tnode * addtree(struct tnode *p, char *w);
/*remember to define support functions for this*/
enum{CODE, COMMENT, PRE_PROC, STRING_LIT};

unsigned int status = CODE;
/*collect variable names in a C source file*/
int main(int argc, char *argv[])
{
    int n;
    char lastc;
    char word[MAXWORD];
    
    while(getword(word, MAXWORD) != EOF)
    {
        if(isalpha(word[0]) && status == CODE)
        {
            /*if((n = binsearch(word, keytab, NKEYS)) >= 0)*/
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
    /* the loop below will be replaced with a call to treeprint(struct tnode *p)
    for(n = 0; n < NKEYS; n++)
        if(keytab[n].count > 0)
            printf("%4d %s\n", keytab[n].count, keytab[n].word);*/
    return 0;
}


/*binary search for the keytab array, needs to be updated to search a bin tree*/
struct tnode * bintreesearch(struct tnode * p, char *w)
{
    if(p == NULL)/*the word doesn't occur in the tree*/
        return p;

    int c = strcmp(w, p->word); 
    if(c < 0)
    {
        return bintreesearch(p->left, w);
    }
    else if (c > 0)
    {
        return bintreesearch(p->right, w);
    }
    else if (c == 0)
    {
        return p;
    }
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
