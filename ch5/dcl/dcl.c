/*this is a copy of the dcl program as depicted in K&R in section 5.12*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

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

int main(int argc, char *argv[])
{
    //todo
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
        printf("error: expected name of (dcl)\n");
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

