all: exe
exe: player.o alien.o TUTORIAL.o score.o utilities.o
	cc TUTORIAL.o player.o alien.o score.o utilities.o -o exe -lncurses
player.o: player.c globals.h
	cc -c player.c
utilities.o: utilities.c utilities.h
	cc -c utilities.c
alien.o: alien.c globals.h
	cc -c alien.c
score.o: score.c score.h
	cc -c score.c
TUTORIAL.o: TUTORIAL.c globals1.h
	cc -c TUTORIAL.c
clean:
	rm *.o
