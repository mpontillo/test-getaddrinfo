test: test.o
	gcc -o test test.o -Wall

test.o: test.c
	gcc -o test.o -c test.c -Wall

clean:
	rm -f test test.o

