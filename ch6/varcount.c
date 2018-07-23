/*This file contains a solution to project 6.2 of chapter six of K&R 2nd 
 * edition, the efficiency of this solution is utter garbage*/

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hb_strncmp.h"

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


/*linked list nodes for keeping arranging variable groups*/
struct llnode
{
    char *word;
    struct llnode *next;
};

/*binary tree nodes for collecting variable names*/
struct tnode
{
    char *title;
    struct llnode *word; /*<- this shouldn't be here, it's useless for this program*/
    struct tnode *left;
    struct tnode *right;
};

#define NKEYS (sizeof keytab / sizeof keytab[0])
int comp_len;
int getword(char *, int);
int validateName(const char *); /*check to see if a string is valid variable name*/
struct tnode * bintreesearch(struct tnode *p, char *w); /*search a binary tree*/
void treeprint(struct tnode *p); /*in order print function*/
struct tnode * addtree(struct tnode *p, char *w);
/*remember to define support functions for this*/
enum{CODE, COMMENT, PRE_PROC, STRING_LIT};

unsigned int status = CODE;

/*takes a null terminated string*/
int isuintstr(char * string)
{
    printf("trying to run isunitstr()\n");
    int c = 0;
    printf("string: %s\n", string);
    while(*(string+c) != '\0' && isdigit(*(string+c))) c++;

    if(*(string+c) !=  '\0') return 0;
    /*i.e. a non numeric character has been found
    */
    return 1;
}

/*collect variable names in a C source file*/
int main(int argc, char *argv[])
{
    /*these are some test variables to see if I've got the variable
     * identification nailed down*/
    char test = 'a';
    int _test = 10000;
    const float t35t = 3.5f;
    unsigned char _t35t = '\n';

    int n;
    char last_word[MAXWORD] = "";
    char word[MAXWORD];
    char lastc = '\0';
    struct tnode *tree = NULL;
    
    char * test_string = hb_strndup("This is a test string, do not be afraid", 15);
    printf("result: %s\n", test_string);
    /*check arguments*/
    if(argc != 2)
    {   
        printf("takes a single argument twat mackerel\n");
        return EXIT_FAILURE;
    }
    printf("arg: %s\n", argv[1]);
    if(!isuintstr(argv[1]))
    {
        printf("AAAAAAA");
        return EXIT_FAILURE;
    }
    comp_len = atoi(argv[1]); /*the length of string to compare*/

    printf("trying to run core of program\n");
    while(getword(word, MAXWORD) != EOF)
    {
        if((word[0] == '=' || word[0] == '[') && strlen(word) == 1 && status == CODE)
        {
            /*if((n = binsearch(word, keytab, NKEYS)) >= 0)*/
            /*validate a variable name*/
            if(validateName(last_word))
            {
                tree = addtree(tree, last_word);
            }
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
        strcpy(last_word, word);
        lastc = word[0];
    }
    /* the loop below will be replaced with a call to treeprint(struct tnode *p)
    for(n = 0; n < NKEYS; n++)
        if(keytab[n].count > 0)
            printf("%4d %s\n", keytab[n].count, keytab[n].word);*/
    treeprint(tree);
    return 0;
}

/*check to see if a string is a valid string*/
int validateName(const char *name)
{
    const char *p = name;

    if(!isalpha(*p) && *p != '_')/*check if the first character is correct*/
    {
        /*printf("wrong start: %c\n", *p);*/
        return 0;
    }

    p++; 

    /*check the rest of the string*/
    while(*p != '\0')
    {
        if(!isalnum(*p) && *p != '_')
        {
            return 0;
        }
        p++;
    }
    
    /*valid variable name found*/
    return *name;
}


/*helper functions for addtree*/
struct tnode *talloc(void);
struct llnode *llalloc(void);
//char *strdup(char *);

/*adding something to a binary tree*/
struct tnode * addtree(struct tnode *p, char *w)
{
    int cond;    
    /* I need to malloc new space*/
    if(p == NULL)
    {
        /*printf("creating new node\n");*/
        p = talloc();
        p->title = "fug:D"; /*this needs to be fixed*/
        p->word = llalloc();
        p->word->word = strdup(w);
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) < 0)
        p->left = addtree(p->left, w);
    else if(cond > 0)
        p->right = addtree(p->right, w);
    /*I also need to add a condition wherein the specified number of chars match*/

    /*printf("returning p\n");*/
    return p; 
}

/*treeprint: in-order print of tree p, ripped from page 142*/
void treeprint(struct tnode *p)
{
    if(p != NULL)
    {
        treeprint(p->left);
        printf("%s\n",  p->word);
        treeprint(p->right);
    }
}

/*talloc: allocate memory fro a tnode, ripped from page 142*/
struct tnode *talloc(void)
{
    /*printf("talloc called\n");*/
    return (struct tnode *) malloc(sizeof(struct tnode));
}

struct llnode *llalloc(void)
{
    return (struct llnode *) malloc(sizeof(struct llnode));
}
/*strdup, duplicate a string*/
/*
char *strdup(char *s)
{
    char *p;
    p = (char *) malloc(strlen(s) + 1); 
    if(p != NULL)
        strcpy(p, s);
    return p;
}*/

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
    /*printf("word: %s\n" , word);*/
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
