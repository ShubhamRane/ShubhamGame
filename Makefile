all: exe
exe: player.o alien.o main.o score.o utilities.o
	cc main.o player.o alien.o score.o utilities.o -o exe -lncurses
player.o: player.c globals.h
	cc -c player.c
utilities.o: utilities.c utilities.h
	cc -c utilities.c
alien.o: alien.c globals.h
	cc -c alien.c
score.o: score.c score.h
	cc -c score.c
main.o: main.c globals1.h
	cc -c main.c
clean:
	rm *.o
