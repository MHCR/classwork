#include <stdio.h>
#include <stdlib.h>

int
main()
{
	float fh,cl;

	printf("Enter temperature value in Fahrenheit: ");
	scanf("%f", &fh);
	cl = (fh - 32) / 1.8;
	printf("Converted Celsius value: %f\n", cl);

	exit(0);
}
