/*this is a copy of the dcl program as depicted in K&R in section 5.12*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100
#define BUFSIZE 100 /*character limit on ungetch buffer*/
#define FALSE 0
#define TRUE 1
enum {NAME, PARENS, BRACKETS};

/*support functions*/
int gettoken();

int error = FALSE;
int tokentype = -1;/*initialize this to avoid fuckery*/
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];/*output string*/


/*heart and soul functions*/
void dcl(void); /*parse a declarator*/
void dirdcl(void); /*parse a declarator*/
int gettoken(void);/*gets a token*/

int main(int argc, char *argv[])
{
    while(gettoken() != EOF)
    {
        /*1st token on a the line*/
        printf("---------------\n");
        strcpy(datatype, token);
        out[0] = '\0';
        error = FALSE;
        printf("pre parse sanity print.\n");
        printf("token: %s\n", token);
        printf("name: %s\n", name);
        printf("datatype: %s\n", datatype);
        printf("tokentype: %d\n", tokentype);

        dcl(); /*parse the rest of the line*/

        if(error != FALSE)
        {            
            printf("syntax error\n");
            /*I need to reset all the buffers and variables in here*/
        }
        else
        {
            printf("declaration -> %s: %s %s\n", name, out, datatype);
        } 
        printf("post parse sanity print.\n");
        printf("token: %s\n", token);
        printf("name: %s\n", name);
        printf("datatype: %s\n", datatype);
        printf("tokentype: %d\n", tokentype);
        printf("end of parse ----\n");
    }
    return 0;
}

void dcl(void)
{
    int ns;

    for(ns = 0; gettoken() == '*';)
    {
        /*count asterixes*/
        printf("counting asterix\n");
        ns++;
    }
    dirdcl();
    while(ns-- > 0)
        strcat(out, " pointer to");
}

void dirdcl(void)
{
    printf("dirdcl called\n");
    int type;
    
    /*each of these if/else statements represents a fork in the grammar*/
    if(tokentype == '(')
    {
        /* (dcl) */
        dcl();
        if(tokentype != ')')
        {
            error = TRUE;
            printf("error: missing ')' \n");
        }
    }
    else if(tokentype == NAME) 
    { 
        /*var name*/
        strcpy(name, token);
    }
    else
    {
        printf("error: expected name or (dcl)\n");
        error = TRUE;
        if(tokentype == '\n')
        {
            return;/*prevent redundant calls to gettoken() causing hangs*/
        }
    }
    while ((type = gettoken()) == PARENS || type == BRACKETS)
    {
        if(type == PARENS)
        {
            strcat(out, " function returning");
        }
        else
        {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
    }
    /*printf("returning from dirdcl\n");*/
}

/*need to re-declare getch and ungetch*/

int gettoken(void)
{
    printf("gettoken called\n");
    int c, getch(void);
    void ungetch(int);
    char * p = token;

    while((c = getch()) == ' ' || c == '\t') printf("eating whitespace\n")
        ;
    if(c == '(')
    {
        if((c = getch()) == ')')
        {
            strcpy(token, "()");
            return tokentype = PARENS;
        }
        else
        {
            ungetch(c);
            return tokentype = '(';
        }
    }
    else if (c == '[')
    {
        for(*p++ = c; (*p++ = getch()) != ']';)
            ;
        *p = '\0';
        return tokentype = BRACKETS;
    }
    else if (isalpha(c))
    {
        for(*p++ = c; isalnum(c = getch()); )
            *p++ = c;

        *p = '\0';
        ungetch(c);
        return tokentype = NAME;
    }
    else
    {
        printf("returning unrecognized token\n");
        if(c == '\n')
            printf("it's a newline char\n");
        return tokentype = c;
    }
}

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
}
