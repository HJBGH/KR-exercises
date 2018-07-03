/*This file contains the program outlined on pages 108-110 of K & R, with the
 * readline subroutine modified according to the suggestions in exercise 5-7*/
/*Modifications have been made to this program in accordance with the suggestions
 * outlined in exercises 5-14 through 5-17*/
/*note that I haven't actually measured the runtime difference, but I have 
 * googled the exercise as included some notes*/
/*As it stands I don't think either method of managing memory produces much
 * difference in this toy example because the only thing that changes is the
 * function managing it. In a real world example using stack memory instead of
 * heap memory would be fast I think, as heap memory would have to be assigned
 * by the OS during runtime*/
#include <stdio.h>
#include <string.h>/*case insensitive strcmp, not portable*/
#include <stdlib.h>
#include <ctype.h>



#define ALLOCSIZE 10000 /*size of available space*/
#define MAXLINES 5000
#define MAXLEN 100

char *lineptr[MAXLINES]; /*pointers to text lines*/

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
char * dirOrderHelper(char *vi, char *c1);

void hb_qsort(void *lineptr[], int left, int right, int (*comp)(void *, void *));

int numcmp(const char *, const char *);
int caseless_strcmp(const char *, const char *);

static int reverse_flag = 0;/*swap function to determine swap order*/
/*main routine organises it all, sorts input lines*/
static int no_case_flag = 0;
static int dir_order_flag = 0;/*order only by considering letters, numbers and
blanks*/

int main(int argc, char *argv[])
{
    int nlines, i;
    char *arg_char;
    int numeric = 0;

    printf("argc -> %d\n", argc);
    /*this isn't very good argument parsing*/
    for(i = 1; i < argc; i++)
    {
        if(*argv[i] == '-')/*array indexing has a higher priority than deref op*/
        {
            arg_char = argv[i]+1;
            while(*arg_char != '\0')
            {
                switch(*arg_char)
                {
                    case 'n': numeric = 1; break;
                    case 'r': reverse_flag = 1; break;
                    case 'f': no_case_flag = 1; break;
                    case 'd': dir_order_flag = 1; break;
                    default:
                        printf("Error: unrecognized arguments\n");
                        return -1;
                }
                arg_char++;
            }   
        }
    }
    if((nlines = readlines(lineptr, MAXLINES)) >= 0)
    {   
        /*TODO: use the flags to set the comparison function pointer
         * earlier, then pass it into the qsort*/
        int(*picked_strcmp)(void *, void *) = 
                (no_case_flag ? (int (*)(void*, void*))caseless_strcmp :
                                (int (*)(void*, void*))strcmp);
        hb_qsort((void **) lineptr, 0, nlines-1,
                (numeric ? (int (*)(void*, void*))numcmp : picked_strcmp));
        writelines(lineptr, nlines);
        printf("Number of lines -> %d\n", nlines);
        return 0;
    }
    else
    {
        printf("Error: input too big to sort\n");
        return 1;
    }
}

int getline(char * s, size_t n);
char * alloc(int); /*custom memory allocation routine*/

/*readlines: read input lines*/
int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while((len = getline(line, MAXLEN)) > 0)
    {
        if(nlines >= maxlines || (p = alloc(len)) == NULL)
        {
            return -1;
        }
        else
        {
            line[len-1] = '\0'; /*delete newline*/
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }
    return nlines;
}

/*writelines: write output lines*/
void writelines(char * lineptr[], int nlines)
{
    int i;
    for(i = 0; i < nlines; i++)
    {
        printf("%s\n", lineptr[i]);
    }
}

/*This dumb function is used to turn regular strings into directory names for
 * comparison according to directory order.*/
char * dirOrderHelper(char *vi, char *c1)
{
    /*initialize *vi elsewhere, avoid side effects*/
    while(*c1 != '\0')
    {
        if(*c1 == '\t' || *c1 == '\n' || *c1 == ' ' || (*c1 >= '0' && *c1<='9')
            || (*c1 >= 'a' && *c1 <= 'z') || (*c1 >= 'A' && *c1 <= 'Z'))
        {
            *vi = *c1;
            vi++;
        }
        c1++;
    }
    vi++;
    *vi = '\0';
    return vi;
}

/*recursive quicksort*/
/*sort v[left]...v[right] into increasing order*/
void hb_qsort(void *v[], int left, int right, int (*comp)(void *, void *))
{
    /*NOTE ON IGNORING CASE:
     * Add two member variables to hb_qsort that will be used to contain
     * lowercase versions of the strings for comparison in the appropriate
     * flag is set*/
    int i, last;
    void swap(void *v[], int i, int j);/*nested function prototype?*/
    char * s1;
    char * s2;
    char dirBuf[MAXLEN]; 

    if(left >= right)/*Array has fewer tha 2 elements*/
    {
        return;
    }

    swap(v, left, (left + right)/2);
    last = left;
    for(i = left+1; i <= right; i++)
    {
        /*this is where I should call the directory order name conversion*/ 
        s1 = v[i];
        s2 = v[left];
        if(dir_order_flag)
        {
           s1 = dirOrderHelper(dirBuf, s1);
           s2 = dirOrderHelper(dirBuf, s2);
        }
        if(reverse_flag)/*If we're sorting into reverse order*/
        {
            if((*comp)(s1, s2) > 0)
            {
                swap(v, ++last, i);
            }
        }
        else
        {
            if((*comp)(s1, s2) < 0)
            {
                swap(v, ++last, i);
            }
        }
    }
    swap(v, left, last);
    hb_qsort(v, left, last-1, comp);
    hb_qsort(v, last+1, right, comp);
}

int numcmp(const char *s1, const char *s2)
{
    double v1, v2;
    if(no_case_flag)
    {
        const unsigned char lv1 = (const unsigned char) tolower(*s1);
        const unsigned char lv2 = (const unsigned char) tolower(*s2);
        v1 = atof(&lv1);
        v2 = atof(&lv2);
    }
    else
    {
        v1 = atof(s1);
        v2 = atof(s2);
    }
    if (v1 < v2)
        return -1;
    else if(v1 > v2)
        return 1;
    else 
        return 0;
}

void swap(void *v[], int i, int j)
{
    void * temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}


static char allocbuf[ALLOCSIZE];
static char * allocp = allocbuf;

char * alloc(int n)
{
    if(allocbuf + ALLOCSIZE - allocp >= n)
    {
        allocp += n;
        return allocp - n; /*old p*/
    }
    else
    {
        return 0;
    }
}

void afree(char * p)
{
    if(p >= allocbuf && p < allocbuf + ALLOCSIZE)
        allocp = p;
}

int getline(char * s, size_t n)
{
    int c;
    char * s_head = s;
    while(--n > 0 && (c=getchar()) != EOF && c != '\n')
    {
        *s = c;
        s++;
    }
    if(c == '\n')
    {
        *s = c;
        s++;
    }
    *s = '\0';
    return s - s_head;
}

int caseless_strcmp(const char *p1, const char *p2)
{
    /* I'm modifying code from glibc string library, there's
     * this bit, which is for casting the signed const char pointer args to
     * unsigned const char pointers*/
    const unsigned char *s1 = (const unsigned char *) p1;
    const unsigned char *s2 = (const unsigned char *) p2;
    unsigned char c1, c2;
     /* I'm fairly certain this odd declaration
      * is some form of input sanitization */
    do
    {
        c1 = (unsigned char) tolower(*s1++);
        c2 = (unsigned char) tolower(*s2++);
        if(c1 == '\0')
            return c1 - c2;
    }
    while(c1 == c2);
    return c1 - c2;
}
