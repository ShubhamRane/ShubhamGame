all: program
project: player.o alien.o main.o score.o utilities.o menu_win.o
	cc main.o player.o alien.o score.o utilities.o menu_win.o -o program -lncurses -lmenu -lpthread
player.o: player.c globals.h
	cc -c player.c -Wall
utilities.o: utilities.c utilities.h
	cc -c utilities.c -Wall
alien.o: alien.c globals.h
	cc -c alien.c -Wall
score.o: score.c score.h
	cc -c score.c -Wall
menu_win.o: menu_win.c menu_win.h
	cc -c menu_win.c -lmenu -lncurses -Wall
main.o: main.c globals1.h
	cc -c main.c -Wall
anyway:
	touch *.c
	make
clean:
	rm program *.o
