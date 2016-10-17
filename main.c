#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <signal.h>
#include <ncurses.h>
#include <string.h>
#include "globals1.h"
#include "player.h"
#include "alien.h"
#include "score.h"
	
/* test function */
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

/* initialize colors for black background */
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
	healthBoardInit();
}

/* This Method is called every 1 / FPS seconds( #define ) */
void MyThread() {
	// handles all the cases like pause, game over, player movement, 
	alienMovement();
	alienShoot();
	playerMissileFun();	
}

/* this function takes inputs to control the game */
void takeInput() {
	int ch;
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
		/* case game pause
		 * case game over
		 * case other */
		default :
			break;
			
	}
}

/* starting display screen will include menu */
void startscreen() {
	int ch;
	WINDOW *startup;
	startup = newwin(FIELD_HEIGHT, FIELD_WIDTH, 0, 0);
	wattrset(startup, COLOR_PAIR(4));
	wprintw(startup, "\n\n\n\n\n\n\n\n");
	wrefresh(startup);
	while(ch != ' ')	
		ch = getch();
	
}

/* set up sigaction to run function MyThread after FPS seconds */
void setUpTimer() {
	struct itimerval mytimer;
	struct sigaction myaction;
	mytimer.it_value.tv_sec = 0;
	mytimer.it_value.tv_usec = 1000000 / FPS ;
	mytimer.it_interval.tv_sec = 0;
	mytimer.it_interval.tv_usec = 1000000 / FPS;

	/* this library function generates SIGALRM signal after time corr. to mytimer */
	setitimer(ITIMER_REAL, &mytimer, NULL);
	myaction.sa_handler = &MyThread;
	myaction.sa_flags = SA_RESTART;
	sigaction(SIGALRM, &myaction, NULL);
}

/*show usage to the user */
void usage() {
	printf("Game : Space-Attack\n");
	printf(" Usage :\n");
	printf(" Run only ./exe without arguments\n");
	printf(" Use 'SpaceBar' to shoot and 'Arrow keys' to move left / right\n");
	printf(" Use Ctrl-C to exit (Under construction)\n");
}

/* main function */
int main(int argc, char *argv[]) {
	
	if(argc != 1 && strcmp(argv[1], "-h") == 0) {
		usage();
		exit(1);
	}
	/* initialize the attributes and begin curses mode */
	battleFieldInit();
	
	/* set up function that runs continuously depending on time */
	setUpTimer();
	
	while(1) {
		takeInput();
	}
	
	return 0;
}
