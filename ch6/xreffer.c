/*This file will contain a solution to project 6.3 of chapter six of K&R 2nd 
 * edition, the efficiency of this solution is utter garbage*/
/*The idea of this program is according to the requirements laid out on page
 * 143: This is a cross referencer that prints a list of all words in
 * a document, and, for each word a list of the line numbers it occurs on. 
 * Note that this solution differs from the prescribed conditions in that it 
 * does not ignore "noise"; prepositions, conjunctives, etc*/
/*for the sake of the exercise we consider a word to be any string of 
 * alphabetical characters that are not interrupted by whitespace, numerals,
 * punctuation, mathematical symbols, underscores, etc*/

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hb_strncmp.h"

#define MAXWORD 100

/*linked list nodes for keeping arranging variable groups*/
/*I'll have to update my method of insertion*/
struct llnode
{
    int line;
    struct llnode *next;
};

/*binary tree nodes for collecting variable names*/
struct tnode
{
    char *word;
    struct llnode *lines;
    struct tnode *left;
    struct tnode *right;
};

#define NKEYS (sizeof keytab / sizeof keytab[0])

int getalphaword(char *, int);
void treeprint(struct tnode *p); /*in order print function*/
struct tnode * addtree(struct tnode *p, char *w, int linenum);

/*collect variable names in a C source file*/
int main(int argc, char *argv[])
{
    int line;
    char word[MAXWORD];
    struct tnode *tree = NULL;
    /* 
    char * test_string = hb_strndup("This is a test string, do not be afraid", 15);
    printf("result: %s\n", test_string);*/
    /*check arguments*/
    printf("trying to run core of program\n");
    while(getalphaword(word, MAXWORD) != EOF)
    {
        if(word[0] == '\n') line++;
        else if(isalpha(word[0]))
        {
            /*getalphaword is designed to ensure that a whole string is
             * alphabetical or only of length 1*/
            /*printf("%s\n", word);*/
            tree = addtree(tree, word, line);
        }
    }   
    treeprint(tree);
    return 0;
}

/*helper functions for addtree*/
struct tnode *talloc(void);
struct llnode *llalloc(void);
//char *strdup(char *);

/*adding something to a binary tree*/
struct tnode * addtree(struct tnode *p, char *w, int linenum)
{
    int cond;    
    /* I need to malloc new space*/
    if(p == NULL)
    {
        /*printf("creating new node\n");*/
        p = talloc();
        p->word = strdup(w); /*this needs to be fixed*/
        p->lines = llalloc();
        p->lines->line = linenum;
        p->lines->next = NULL;
        p->left = p->right = NULL;
    } 
    else if ((cond = strcmp(w, p->word)) == 0)
    {
        /*uh oh, I've found a pre-existing list, time to insert on the 
         * linked list, do this iteratively otherwise the stack gets too deep*/
        struct llnode * new = llalloc();
        new->next = p->lines;
        p->lines = new;
        new->line = linenum;
    }
    else if(cond < 0)
        p->left = addtree(p->left, w, linenum);
    else if(cond > 0)
        p->right = addtree(p->right, w, linenum);
    /*I also need to add a condition wherein the specified number of chars match*/

    /*printf("returning p\n");*/
    return p; 
}

void llprint(struct llnode *n);
/*treeprint: in-order print of tree p, ripped from page 142*/
void treeprint(struct tnode *p)
{
    if(p != NULL)
    {
        treeprint(p->left);
        printf("word: %s\n",  p->word);
        llprint(p->lines);
        printf("-------------\n");
        treeprint(p->right);
    }
}

void llprint(struct llnode *n)
{
    while(n != NULL)
    {
        printf("%d,", n->line);
        n = n->next;
    }
    printf("\n");
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

/*getword and the getch-ungetch pair are essential to pretty much
 * any project in this chapter*/
/*getword; get the next word or character from input*/
int getalphaword(char *word, int lim)
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
    if(!isalpha(c))
    {
        *w = '\0';
        return c;
    }
    for(; --lim > 0; w++)
        if(!isalpha(*w = getch()))
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
