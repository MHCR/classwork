#include <stdlib.h>
#include <stdio.h>
#include <quadmath.h>
#include <math.h>
#include <time.h>

#define TIME_SIZE 40

void test01(void);
void test02(void);
void test03(void);
void test04(void);
void timestamp(void);


int 
main(int argc, char **argv)
{
	timestamp();
	printf("\nGCC_QUADMATH:\n");
	printf("Test the GCC quadmath library.\n");
	test01();
	test02();
	test03();
	test04();
  	printf("\nGCC_QUADMATH:\n" );
	printf("Normal end of execution.\n" );
	timestamp();
	exit(0);
}

void
test01(void)
{
	int divs;
	float x, x_old, y, z;

	printf("\nTEST01\n");
	printf("Using FLOAT arithmetic:\n");
	printf("Compute smallest 1/2^DIV that can be added to 1.\n");

	x = z = 1.0;
	divs = 0;

	for(;;) {
		x_old = x;
		x /= 2.0;
		y = 1.0 + x;
		if(y <= z) 
			break;
    		divs = divs + 1;
	}

	printf("Number of divisions DIV = %d\n", divs );
	printf("1/2^DIV =         %e\n", x_old);

	return;
}

void 
test02(void)
{
	int divs;
	double x, x_old, y, z;

	printf("\nTEST02\n");
	printf("Using DOUBLE arithmetic:\n");
	printf("Compute smallest 1/2^DIV that can be added to 1.\n");

	x = z = 1.0;
	divs = 0;

	for(;;) {
		x_old = x;
		x /= 2.0;
		y = 1.0 + x;
		if(y <= z) 
			break;
    		divs = divs + 1;
	}

	printf("Number of divisions DIV = %d\n", divs );
	printf("1/2^DIV =         %e\n", x_old);

	return;
}

void 
test03(void)
{
	int divs;
	__float80 x, x_old, y, z;

	printf("\nTEST03\n");
	printf("Using __FLOAT80 arithmetic:\n");
	printf("Compute smallest 1/2^DIV that can be added to 1.\n");

	x = z = 1.0;
	divs = 0;

	for(;;) {
		x_old = x;
		x /= 2.0;
		y = 1.0 + x;
		if(y <= z) 
			break;
    		divs = divs + 1;
	}

	printf("Number of divisions DIV = %d\n", divs );
	printf("1/2^DIV =         %Le\n", x_old);

	return;
}

void 
test04(void)
{
	int divs;
	char results[80];

	__float128 x, x_old, y, z, one, two;

	printf ("\nTEST04\n" );
	printf ("Using __FLOAT128 arithmetic:\n" );
	printf ("Compute smallest 1/2^DIV that can be added to 1.\n");

	x = z = strtoflt128("1.0", NULL);
	divs = 0;
	one = x;
	two = one + one;

	for(;;) {
		x_old = x;
		x /= two;
		y = one + x;
		if ( y <= z )
			break;
		divs = divs + 1;
	}

	printf ( "  Number of divisions DIV = %d\n", divs );
	quadmath_snprintf(results, sizeof(results), "%Qe", x_old );
	printf ( "  1/2^DIV =         %s\n", results );

	return;
}

void 
timestamp(void)
{

	static char time_buffer[TIME_SIZE];
	const struct tm *tm;
	time_t now;

	now = time(NULL);
	tm = localtime(&now);

	strftime(time_buffer, TIME_SIZE, "%d %B %Y %I:%M:%S %p", tm);
	printf("%s\n", time_buffer);
	return;
}
