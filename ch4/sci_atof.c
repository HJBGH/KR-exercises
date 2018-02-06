/*Response to exercise 4-2, extend atof to handle scientific notation of
 * the form zzz.yye-x, where a floating point number can be followed by 'e' or 
 * 'E' and an optionally signed exponent*/


/*REMEMBER TO INITALIZE VARIABLES BEFORE USE OTHERWISE GARBAGE GETS USED*/
#include <ctype.h>
#include <stdio.h>
#include <math.h> /*this is probably cheating*/

double atof(char s[]);

int main()
{
	/*tests*/
	printf("%.10f\n", atof("123.34e3"));
	printf("%.10f\n", atof("12.345e-4"));
	printf("%.10f\n", atof("-23.3333E6"));
	printf("%.10f\n", atof("-45.89"));
	return 0;
}

/*this toy implementation of atof does no appropriate error checking, it
 * also assumes that there are only integers in the exponent*/
/*this is spaghetti code*/
double atof(char s[])
{
	double val, power;
	int i, sign;

	/*variables for dealing with exponent*/
	double exp_sign, exp_val, exp_mag; /*no floating point exponents*/

	printf("converting %s\n", s);
	for(i = 0; isspace(s[i]); i++) /*skip whitespace*/
		;

	sign = (s[i] == '-') ? -1 : 1;
	
	if(s[i] == '+' || s[i] == '-')
	{
		/*printf("skipping sign\n");*/
		i++;
	}

	for(val = 0.0; isdigit(s[i]); i++)
	{
		val = 10.0 * val + (s[i] - '0');/*this is a cheap hack*/
		/*printf("incrementing val\n");*/
	}
	
	if(s[i] == '.')
		i++;
	
	for(power = 1.0; isdigit(s[i]); i++)
	{
		val = 10.0 * val + (s[i] - '0');
		power *= 10.0;
	}
	
	if(s[i] == 'e' || s[i] == 'E')
	{
		i++;
		exp_sign = (s[i] == '-') ? -1 : 1;
		if(s[i] == '-' || s[i] == '+')
		{
			i++;
		}
		for(exp_val = 0; isdigit(s[i]); i++)
		{
			exp_val = 10 * exp_val + (s[i] - '0'); /*i'm certain this isn't portable*/
		}
	/*the return statements here could probably be condensed into one with
	 * proper structure, but this exercise is damn boring, so I'm not going
	 * to do that*/
		if(exp_sign > 0)
		{
			return (sign * val / power) * pow(10,  exp_val);
		}
		else
		{
			/*printf("exp_val %.10f\n", exp_val);
			printf("10 raised to exponent: %.10f\n", pow(10, exp_val));*/
			return (sign * val / power) / pow(10, exp_val);
		}
	}
	return (sign * val) / power;	
}


