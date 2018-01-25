/*This is a response to exercise 2-8 from on page 49,
 * return the value of the integer x rotated to the right by n bit positions*/

#include <stdio.h>

unsigned rightrot(unsigned x, int n);

int main()
{
	/*TODO: write more tests*/
	printf("%u -> %u\n", 255, rightrot(255, 4));
	return 0;
}

unsigned rightrot(unsigned x, int n)
{
	/*Get rightmost n bits into a mask*/
	/*shift x n bits to the right*/
	/*shift the mask sizeof(x)-n to the left*/
	/* return x OR mask*/
	unsigned mask = (x & ~(~0 << n)) << ((sizeof(x)*8) - n); /*get rightmost n bits*/
	printf("mask: %u\n", mask);
	x = x >> n;
	return x | mask;
}


