/*Solution to exercise 2-7, returns x with the n bits that begin at position p 
 * inverted, leaves the others unchanged*/

#include <stdio.h>

unsigned invert(unsigned x, int n, int p); /* prototype*/

int main()
{
	/*TODO: write tests*/
	printf("%u -> %u\n", 403,  invert(403, 5, 3));
	return 0;
}

unsigned invert(unsigned x, int p, int n)
{
	unsigned mask = ((~x >> (p+1-n)) & ~(~0 << n));
	printf("one's complement x: %u\n", ~x);
	printf("shifted x: %u\n", (~x >> (p+1-n)));
	printf("mask: %u\n", mask);
	/*set target bits to 0*/
	x = x & ~(~(~0 << n) << ((p+1)-n));
	return x | mask;
}
