prog: dynamicArray.o main.o
	gcc -Wall -std=c99 -c dynamicArray.c main.c

dynArray.o: dynamicArray.c
	gcc -Wall -std=c99 -c dynamicArray.c

main.o: main.c
	gcc -Wall -std=c99 -c main.c

prog: dynamicArray.o main.o
	gcc -Wall -std=c99 -o Assignment2 dynamicArray.o main.o

clean: 
	rm dynamicArray.o main.o;
