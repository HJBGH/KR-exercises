
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int hb_strncmp(const char * s, const char * t, size_t n)
{
    int result; 
    for(n; n > 0; n--)
    {
        result = *t++ - *s++;
        if(result != 0)
            return result;
        
    }
    return 0; /*default case*/
}

/*copy n characters from t to s or until '\0'*/
void hb_strncpy(char * s, const char * t, size_t n)
{
    while(*t != '\0' && n > 0)
    {
        *s++ = *t++;
        n--;/*maybe I can do this in the loop declaration?*/
    }
    *s = '\0'; /*terminate properly*/
}

/*duplicates a specific section of characters in a string*/
char * hb_strndup(const char * t, size_t n)
{
    char * out = (char *) malloc((n +1) * sizeof(char)); /*+1 for '\0'*/
    if(out != NULL)
        hb_strncpy(out, t, n);
    return out;
}
