#include <stdio.h>

/* print Fahrenheit -> Celsius table
 * for fahrenheit = 0, 20, ..., 300 */
int convertAndPrintTemps(float lower, float upper, float step);

main()
{
	convertAndPrintTemps(0.0, 300.0, 20.0);	
}

int convertAndPrintTemps(float lower, float upper, float step)
{
	if(lower > upper || step < 0)
	{
		return 1;
	}
	float fahr, celsius;

	fahr = lower;
	printf("F -> C\n");
	while(fahr <= upper)
	{
		celsius = (5.0/9.0) * (fahr - 32);
		printf("%3.0f %6.2f\n", fahr, celsius);
		fahr = fahr + step;
	}

	return 0;
}
