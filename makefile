compile: forkboi.o
	gcc forkboi.o

run:
	./a.out

clean:
	-rm -rf ./a.out *.o

all:
	make clean
	make
	echo "\n\n\n"
	make run

forkboi.o:
	gcc -c forkboi.c
