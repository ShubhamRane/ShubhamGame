all: try
try: player.o alien.o TUTORIAL.o
	cc TUTORIAL.o player.o alien.o -o try -lncurses
player.o: player.c
	cc -c player.c
alien.o: alien.c
	cc -c alien.c
TUTORIAL.o: TUTORIAL.c
	cc -c TUTORIAL.c
clean:
	rm *.o
