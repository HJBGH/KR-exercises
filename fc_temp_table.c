#include <stdio.h>

/* print Fahrenheit -> Celsius table
 * for fahrenheit = 0, 20, ..., 300 */
main()
{
	float fahr, celsius;
	float lower, upper, step;

	lower = 0; /*lower limit of temp table*/
	upper = 300; /*upper limit of temp table*/
	step = 20; /*increment size*/

	fahr = lower;
	printf("F -> C\n");
	while(fahr <= upper)
	{
		celsius = (5.0/9.0) * (fahr - 32);
		printf("%3.0f %6.2f\n", fahr, celsius);
		fahr = fahr + step;
	}
}

