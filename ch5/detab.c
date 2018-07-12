/*This file contains one half of a response to exercise 5-11, detab will accept
 * a list of tab stops as arguments and use the default if there are none*/
/*Due to the somewhat ambiguous exercise spec I'm implementing the following
 * default behaviour: A list of tab stops is provided specifying columns to be
 * used as stops for the next tab char, after each of these columns is passed,
 * a default tab stop is used. To give an example; input 6 14 20 will set
 * tab stops at columns 6, 14 and 20, after which tab stop colums will revert
 * to being multiples of the default*/
/*This doesn't handle backspace control chars '\b' at the moment*/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#define TAB_COLUMNS 4
#define LINE_LENGTH 128
#define MAX_TABSTOPS 64
#define BASE_TEN 10
#define MIN_ARGS 1

unsigned long tabstops[MAX_TABSTOPS];
static int have_args = 0;

int getline(char line[], int ll);
int detabline(char line[]); /*does detab operations until it encounters EOF or \n*/
int parseargs(int argc, char *argv[]); /*really harsh validation will be
required*/

int main(int argc, char *argv[])
{
    char line[LINE_LENGTH];
    int len;
    have_args = argc;
    if(have_args > MIN_ARGS)
    {
        printf("Calling parseargs\n");
        if(parseargs(argc, argv) != 0)
        {
            printf("Error, bad arguments provided to detab\n");
            return 1;/* I know I should use something like exit(0) but I'm
            not familiar with those conventions*/
        }
    }
    /*  
    while((len = getline(line, LINE_LENGTH)) > 0)
    {
        detabline(line);
    }*/
    return 0;
}

/*returns -1 on error*/
int parseargs(int argc, char *argv[])
{
    /*parse the arguments, convert and validate them*/
    printf("called parseargs\n");
    int i = 1;
    errno = 0;
    unsigned long tab;
    char *endp;
    while(i != MAX_TABSTOPS && argc != 0)
    {
        errno = 0; /*reset errno before we call strtoul*/
        printf("About to call strtoul\n");
        tab = strtoul(*(argv+i), &endp, BASE_TEN);  
        printf("Survived strtoul!\n");
        /*I can check for errors by inspecting the contents of *endp*/
        if(errno != 0 || *endp != '\0' || (errno != 0 && tab == 0))
        {
            /*It's gone wrong*/
            return -1;
        }
        tabstops[i] = tab;
    }
    return 0;
}
    

int getline(char line[], int ll)
{
    int c, i;
    for(i = 0; i < ll-1 && (c = getchar()) != EOF && c != '\n'; i++)
    {
        line[i] = c;
    }
    if(c == '\n')
    {
        line[i] = c;
        i++;
    }
    line[i] = '\0';
    return i;
}

/*An unfortunate consequence of converting all tab chars to the equivalent
 * number of space chars is that it increases the size of the line in terms of
 * memory space by an uncomfortable amount*/
int detabline(char line[])
{
    /*used to construct the version of the line with the tabs replaced*/
    int i, j, k;
    for(i = 0, k = 0;   line[i] != EOF && line[i] != '\n'; i++)
    {
        switch(line[i])
        {
            case '\t':
            /*handle tabs*/
                for(j = TAB_COLUMNS - (k%TAB_COLUMNS); j>0; j--, k++)
                {
                    putchar('#');
                }
                break;
            case '\n':
                putchar('\n');
                break;
            default:
                putchar(line[i]);
                k++;
                break;
        }
    }
}
