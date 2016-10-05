#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <signal.h>
#include <ncurses.h>
#include "globals1.h"
#include "player.h"
#include "alien.h"

//shoot the player missile
/*void playerMissileShoot() {
	static int m_exist = 0; //checks if missile exists
	
}*/
/*void alienMissile() {
	//move missile missile y++
	//clear the old position
}*/
	
// test function
void bunkersInit() {
	bunkers = newwin(3, 3, 20, FIELD_WIDTH / 2);
	char a[3][3] = {
			"\\O ",
			" |\\",
			"/ \\"
			};
	mvwaddstr(bunkers, 0, 0, a[0]);
	mvwaddstr(bunkers, 1, 0, a[1]);
	mvwaddstr(bunkers, 2, 0, a[2]);
	wrefresh(bunkers);
}
void colorsInit() {
	start_color();
	init_pair(1, COLOR_RED,		COLOR_BLACK);
	init_pair(2, COLOR_GREEN,	COLOR_BLACK);
	init_pair(3, COLOR_YELLOW,	COLOR_BLACK);
	init_pair(4, COLOR_BLUE,	COLOR_BLACK);
	init_pair(5, COLOR_MAGENTA,	COLOR_BLACK);
	init_pair(6, COLOR_CYAN,	COLOR_BLACK);
	init_pair(7, COLOR_WHITE,	COLOR_BLACK);
}
void battleFieldInit() {
	// initialize Windows for everything
	initscr();
	keypad(stdscr, TRUE);
	nonl();
	noecho();
	cbreak();
	start_color();
	refresh();
	colorsInit();
	bunkersInit();
	playerShipInit();
	alienGroupInit();
}
/* This Method is called every 1 / FPS seconds( #define ) */
void MyThread() {
	// handles all the cases like pause, game over, player movement, 
	alienMovement();
	alienShoot();
	playerMissileFun();	
}
void takeInput() {
	int ch; //take integer for ascii values of other key are greater than 256
	ch = getch();
	switch(ch) {
		case KEY_RIGHT:
			movePlayerRight();
			break;
		case KEY_LEFT:
			movePlayerLeft();
			break;
		case ' ':
			playerMissileShoot();
			break;	
		//case game pause
		//case game over
		//case other
		default :
			break;
			
	}
}
void startscreen() {
	int ch;
	WINDOW *startup;
	startup = newwin(FIELD_HEIGHT, FIELD_WIDTH, 0, 0);
	wattrset(startup, COLOR_PAIR(4));
	wprintw(startup, "\n");
	wprintw(startup, "\n");
	wprintw(startup, "\n");
	wprintw(startup, "\n");
	wprintw(startup, "\n");
	wrefresh(startup);
	while(ch != ' ')	
		ch = getch();
	
}
void setUpTimer() {
	struct itimerval mytimer;
	struct sigaction myaction;
	mytimer.it_value.tv_sec = 0;
	mytimer.it_value.tv_usec = 1000000 / FPS ;
	mytimer.it_interval.tv_sec = 0;
	mytimer.it_interval.tv_usec = 1000000 / FPS;
	setitimer(ITIMER_REAL, &mytimer, NULL);
	myaction.sa_handler = &MyThread;
	myaction.sa_flags = SA_RESTART;
	sigaction(SIGALRM, &myaction, NULL);
}
int main() {
	// initialize the attributes and begin curses mode
	//set up function that runs continuously depending on time
	battleFieldInit();
	setUpTimer();
	while(1) {
		takeInput();
	}
	return 0;
}
