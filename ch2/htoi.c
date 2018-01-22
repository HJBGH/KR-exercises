/*contains the function htoi(s), which converts the string representation 
 *of a hexadecimal integer into it's integer counterpart. This file also 
 contains a small test driver in main() and a utility function for converting
 the alphabetical characters of the hex string into integer values*/

#include <stdio.h> 
#include <ctype.h>
#include <stdlib.h>

int htoi(char hex_str[]);/*hex string to in converter*/
int hatoi_util(char c); 
/*hatoi is a utility function for determining the validity of an alphabetical
 * character in a hex string, returns -1 if invalid char*/

main()
{
	/*TODO; write test cases*/
	printf("%s -> %d\n", "asdf", htoi("asdf"));
	printf("%s -> %d\n", "0001", htoi("0001"));
	printf("%s -> %d\n", "0xAAAA", htoi("0xAAAA"));
}

/*this is a derivative of atoi from page 43*/
/*need to negative signs*/
/*need to check for string length, otherwise segfault or garbage read*/
int htoi(char hex_str[])
{
	int i, n;
	/*use isxdigit(c) on each char to check each char, there is an optional
	 * 0X or 0x prefix at the start of each string*/
	/*TODO*/
	i = 0; /*i for iterate*/
	n = 0;
	int sign_factor = 1;/*assume the number to be positive*/
	if(hex_str[i] == '-')
	{
		i++;
		sign_factor = -1;
	}
	if(hex_str[i] == '0' && (hex_str[i+1] == 'x' || hex_str[i+1] == 'X'))
	{
		i+=2; /*skip over the acceptable prefix*/
	}
	/*maybe no prefix found.*/
	for(i; hex_str[i] != '\0'; i++)
	{
		if(!isxdigit(hex_str[i]))
		{
			return 0;/*I don't really know how to handle errors nicely*/
		}
		if(isdigit(hex_str[i]))
		{
			/*We can leverage the contiguity of numeric characters in both ASCII
			 * and EBCDIC*/
			n = n * 16 + (hex_str[i] - '0');
		}
		else
		{
			n = n * 16 + (hatoi_util(hex_str[i]));
		}
	}
	return sign_factor * n;
}

int hatoi_util(char c)
{
	c = tolower(c);
	switch(c)
	{
		case 'a': return 10;
		case 'b': return 11;
		case 'c': return 12;
		case 'd': return 13;
		case 'e': return 14;
		case 'f': return 15;
		default : return -1; /*unrecognised alpha char*/
	}
}
