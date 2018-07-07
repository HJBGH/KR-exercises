/*undcl.c contains an instance of the undcl program as depicted in K&R on page
 * 126*/


#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum {NAME, PARENS, BRACKETS};

int main(int argc, char * argv[])
{
    int type;
    char temp[MAXTOKEN];

    while (gettoken() != EOF)
    {
        strcpy(out, token);
        while((type = gettoken()) != '\n')
        {
            if(type == PARENS || type == BRACKETS)
            {
                strcat(out, token);
            }
            else if(type == '*')
            {
                sprintf(temp, "(*%s)", out);
                strcpy(out, temp);
            }
            else if (type == NAME)
            {
                sprintf(temp, "%s, %s", token, out);
                strcpy(out, temp);
            }
            else
            {
                printf("Invalid input at %s\n", token);
            }
        printf("%s\n", out);
    }
    return 0;
}

