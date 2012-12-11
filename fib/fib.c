#include <stdio.h>
#include <stdlib.h>
#include <quadmath.h>

unsigned long long
fib_recursive(unsigned int n)
{
	switch(n) {
	case 0: return 0;
	case 1: return 1;
	default: 
		return fib_recursive(n-1) + fib_recursive(n-2);
	}
}

enum { N_MINUS_1, N_MINUS_2, N_END, };

void
fib_interative(unsigned int n)
{
	unsigned long long prev[N_END], cur;
	int i;

	printf("[  0] %30llu\n", (unsigned long long)0); prev[N_MINUS_2] = 0;
	if(n == 1)
		return;

	printf("[  1] %30llu\n", (unsigned long long)1); prev[N_MINUS_1] = 1;
	if(n == 2)
		return;

	for (i = 2; i < n; i++) {
		cur = prev[N_MINUS_2] + prev[N_MINUS_1];
		if(cur < prev[N_MINUS_1]) {
			printf("Overflow occurred\n");
			return;
		}
		printf("[%3d] %30llu\n", i, cur);
		prev[N_MINUS_2] = prev[N_MINUS_1];
		prev[N_MINUS_1] = cur;
	}
}

void
fib_calc(unsigned int n)
{
	__float128 sq5;
	__float128 half;
	__float128 phi;
	__float128 lphi;
	__float128 f;
	char buf[512];

	// set up constants
	f = strtoflt128("5.0", NULL);
	sq5 = sqrtq(f);
	half = strtoflt128("0.5", NULL);
	f = strtoflt128("1.0", NULL);
	phi = (f + sq5) * half;
	lphi = logq(phi);

	sprintf(buf, "%d", n);
	f = strtoflt128(buf, NULL);
	f *= lphi;
	f = expq(f);
	f /= sq5;
	f += half;
	f = floorq(f);

	(void)quadmath_snprintf(buf, sizeof buf, "%30.0Qf", f);
	printf("[%3d] %s\n", n, buf);
}

void
usage(int status)
{
	printf("usage: fib <number of fibinocci terms to print> <method>\n");
	printf("where number of terms must be > 0, and method is r, i, c\n");
	exit(status);
}

int
main(int argc, char **argv)
{
	int i, num;

	if(argc != 3)
		usage(1);

	num = atoi(argv[1]);
	if(num <= 0) {
		printf("Invalid argurment: %s\n", argv[1]);
		usage(1);
	}

	switch (argv[2][0]) {
		case 'r': // recursive solution
			for(i=0; i<num; i++)
				printf("[%3d] %30llu\n", i, fib_recursive(i));
			break;

		case 'i': // interative solution
			fib_interative(num);
			break;

		case 'c': // combinatoric solution
			for(i=0; i<num; i++)
				fib_calc(i);
			break;

		default:
			printf("Invalid argument: %s, please chose r or i\n", argv[2]);
			usage(1);
	}
	exit(0);
}
