/*This file will contain a solution to project 6.4 of K&R 2nd 
 * edition, the efficiency of this solution is utter garbage*/
/*The idea of this program is according to the requirements laid out on page
 * 143: This program reprints the words in it's input ordered by the frequency
 * by which they occur.
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

/*binary tree nodes for collecting variable names*/
struct tnode
{
    char *word;
    unsigned int count;
    struct tnode *left;
    struct tnode *right;
};


int getalphaword(char *, int);
void treeprint(struct tnode *p); /*in order print function*/
/*lexical add tree constructs a bt based on the lexical ordering of the
 * data*/
struct tnode * lexicaladdtree(struct tnode *p, char *w);
struct tnode * newtree(struct tnode *t, struct tnode *old);

/*rebuilds an existing binary tree according to the "count" attribute of the
 * tnode struct*/

/*collect variable names in a C source file*/
int main(int argc, char *argv[])
{
    int line;
    char word[MAXWORD];
    struct tnode *tree = NULL;
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
            tree = lexicaladdtree(tree, word);
        }
    }
    struct tnode *new = NULL; 
    new = newtree(new, tree);
    treeprint(new);
    return 0;
}

/*helper functions for addtree*/
struct tnode *talloc(void);

/*adding something to a binary tree*/
struct tnode * lexicaladdtree(struct tnode *p, char *w)
{
    int cond;    
    /* I need to malloc new space*/
    if(p == NULL)
    {
        /*printf("creating new node\n");*/
        p = talloc();
        p->word = strdup(w); /*this needs to be fixed*/
        p->count = 1;
        p->left = p->right = NULL;
    } 
    else if ((cond = strcmp(w, p->word)) == 0)
        p->count++;
    else if(cond < 0)
        p->left = lexicaladdtree(p->left, w);
    else if(cond > 0)
        p->right = lexicaladdtree(p->right, w);
    return p; 
}

/*n will consist of nodes copied from the original tree*/
struct tnode * qntaddtree(struct tnode *t, struct tnode *n)
{
    if(t == NULL)
    {
        t = n;
    }
    else if(t->count == n->count)
    {
        n->left = t->left;
        t->left = n;
    }
    else if(t->count > n->count)
        t->left = qntaddtree(t->left, n);
    else if(t->count < n->count)
        t->right = qntaddtree(t->right, n);

    return t;
}

struct tnode * newtree(struct tnode *new, struct tnode *old)
{
    if(old != NULL)
    {
        new = newtree(new, old->left);
        new = newtree(new, old->right);

        /*copy the node across*/
        struct tnode * nn = talloc();
        nn->count = old->count;
        nn->word = strdup(old->word);
        nn->left = nn->right = NULL;
        new = qntaddtree(new, nn);
    }
    return new;
}
/*treeprint: in-order print of tree p, ripped from page 142*/
void treeprint(struct tnode *p)
{
    if(p != NULL)
    {
        treeprint(p->left);
        printf("%d,  %s\n",  p->count, p->word);
        treeprint(p->right);
    }
}

/*talloc: allocate memory fro a tnode, ripped from page 142*/
struct tnode *talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}

/*how to quicksort a binary tree?*/
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
