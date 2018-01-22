/*This is a response to exercise 2-6, write a function that returns x with the n
 * bits that begin a tposition p set to teh righmost n bits of y, the others
 * are to be left unchanged*/

#include <stdio.h>

/*I'm not sure why this returns an unsigned variable as opposed to anything
 * else, but the book does it this way so for now I'll copy it.*/
unsigned setbits(unsigned x, int p, int n, unsigned y);

int main()
{
	/*TODO: write test cases*/
	/*write a binary print method*/
	return 0;
}

/*doesn't do size checking or any other validation*/
unsigned setbits(unsigned x, int p, int n, unsigned y)
{
	unsigned mask = ~((~(~0 << n)) << (p+1-n));
	x = x & mask;
	mask = (y & ~(~0 << n)) /*this still needs to be shifted*/
	/* XOR x and the final mask*/

}
