/*This file contains solutions to 6-5 and 6-6 of K&R, the solution to 6-6 is
 * not very robust, it will break if comments are present in the middle of
 * a definition*/

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100

#define TEST "replacement text"
#define OTHER_TEST 'a'
#define HASHSIZE 101

struct nlist/*lookup table entry*/
{
    struct nlist *next;/*next entry in chain*/
    char *name;/*defined name*/
    char *defn;/*replacement text*/
};

unsigned hash(char *s);
struct nlist * lookup(char *s);
struct nlist * install(char *name, char *defn);
int getword(char *, int);
int getdefn(char *, int); /*a variant of getword, returns every part of a line
up until the '\n'*/
enum{CODE, COMMENT, PRE_PROC, STRING_LIT};
unsigned int status = CODE;

static struct nlist *hashtab[HASHSIZE]; /*pointer array (for some reason K&R
refer to this as a table*/

/*super basic #define pre-processor*/
int main(int argc, char *argv[])
{
    int n; /* I don't remember what n was used for*/
    char lastc;
    char word[MAXWORD];
    /*printf("%d\n", BUFSIZE); trying to use a macro before it's defined
     * doesn't work*/
    while(getword(word, MAXWORD) != EOF)
    {
        /*This doesn't write out to file, it just prints the 
         * processed text straight to terminal*/

        if(strcmp("define", word) == 0 && status == PRE_PROC)
        {
            char name[MAXWORD], defn[MAXWORD];
            getword(name, MAXWORD);
            getdefn(defn, MAXWORD);
            printf("installing new definition: %s, %s\n", name, defn);
            install(name, defn);
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
        else if(status == CODE)
        {
            struct nlist * replacement = lookup(word);
            if(replacement != NULL)
                printf("%s", replacement->defn);
            /*else
                printf("%s", word);*/
        }
        lastc = word[0];
    }

    return 0;
}

/*hash function copied verbatim from book, page 144*/
unsigned hash(char *s)
{
    unsigned hashval;
    for(hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

/*look for s in hashtab*/
struct nlist *lookup(char *s)
{
    struct nlist *np;

    for(np = hashtab[hash(s)]; np != NULL; np = np->next)
        if(strcmp(s, np->name) == 0)
            return np; /*found it*/

    return NULL; /*not here*/
}

struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;

    if((np = lookup(name)) == NULL)
    {
        np = (struct nlist *) malloc(sizeof(*np));
        if(np == NULL || (np->name = strdup(name)) == NULL)
            return NULL; /*something went wrong in memory allocation*/
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    }
    else
        free((void *) np->defn);
    if((np->defn = strdup(defn)) == NULL)
        return NULL;
    return np;
}

/*this is kind of a pointless weird exercise, it remains untested, I'm fairly
 * certain that this solution would work*/
struct nlist *undef(char *s)
{
    /*standard algorithm for removing elements from a linked list*/
    struct nlist *last = NULL;
    struct nlist *np;

    for(np = hashtab[hash(s)]; np != NULL; last = np, np = np->next)
        if(strcmp(s, np->name) == 0)
        {
            last->next = np->next;
            free((void*) np);
            return last; /*found it*/
        }
    return NULL; /*not here*/
}

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

/*used to get the replacement string after a #define declaration is detected*/
int getdefn(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;
    
    do
    {
        c = getch();
    }
    while(isspace(c)); /*eat whitespace*/

    if(c != EOF)
        *w++ = c; 
    /*get the remaining string*/
    for(; --lim > 0; w++)
        if((*w = getch()) == '\n')
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
