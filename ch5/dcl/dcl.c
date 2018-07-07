/*this is a copy of the dcl program as depicted in K&R in section 5.12*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100
#define BUFSIZE 100 /*character limit on ungetch buffer*/

enum {NAME, PARENS, BRACKETS};

/*support functions*/
int gettoken();
int tokentype;
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
        strcpy(datatype, token);
        out[0] = '\0';
        dcl(); /*parse the rest of the line*/
        if(tokentype != '\n')
        {
            printf("syntax error\n");
        }
        printf("%s: %s %s\n", name, out, datatype);
    }
    return 0;
}

void dcl(void)
{
    int ns;

    for(ns = 0; gettoken() == '*';) /*count asterixes*/
        ns++;
    dirdcl();
    while(ns-- > 0)
        strcat(out, " pointer to");
}

void dirdcl(void)
{
    int type;
    
    /*each of these if/else statements represents a fork in the grammar*/
    if(tokentype == '(')
    {
        /* (dcl) */
        dcl();
        if(tokentype != ')')
            printf("error: missing ')' \n");
    }
    else if(tokentype == NAME) 
    { 
        /*var name*/
        strcpy(name, token);
    }
    else
    {
        printf("error: expected name or (dcl)\n");
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
}

/*need to re-declare getch and ungetch*/

int gettoken(void)
{
    int c, getch(void);
    void ungetch(int);
    char * p = token;

    while((c = getch()) == ' ' || c == '\t')
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
        return tokentype = c;
    }
}

char buf[BUFSIZE];
int bufp = 0;

/*get a char from input or from the pushback buffer*/
int getch(void)
{
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
