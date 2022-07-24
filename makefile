paint.out: main.o board.o
	gcc -g -Wall -Werror -o paint.out main.o board.o

main.o: main.c board.h
	gcc -g -Wall -Werror -c main.c

board.o: board.c board.h
	gcc -g -Wall -Werror -c board.c

clean:
	rm -f *.o *.out