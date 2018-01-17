#include <stdio.h>

/* print Celsius -> Fahrenheit table
 * for fahrenheit = 0, 20, ..., 300 */
main()
{
	float fahr, celsius;
	float lower, upper, step;

	lower = 0; /*lower limit of temp table*/
	upper = 300; /*upper limit of temp table*/
	step = 20; /*increment size*/

	celsius = lower;
	printf("C -> F\n");
	while(celsius <= upper)
	{
		fahr = ((celsius * 9.0) / 5.0) + 32;
		printf("%3.0f %6.2f\n", celsius, fahr);
		celsius = celsius + step;
	}
}

