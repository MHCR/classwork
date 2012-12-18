all: fib quadtest

clean:
	rm -f fib quadtest

fib: fib.c
	$(CC) -O $< -o $@ -lquadmath

quadtest: quadtest.c
	$(CC) -O $< -o $@ -lquadmath
