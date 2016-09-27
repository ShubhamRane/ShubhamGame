#include <stdio.h>
#include <sys/time.h>
#include <signal.h>
#include <ncurses.h>
#include "globals.h"
//global to track player position and player missile status
// test function

void alienGroupInit() {
	alienGroup = newwin(ALIEN_MAXH, ALIEN_MAXW, 0, alienX);
	wrefresh(alienGroup);
}

void alienGroupDisplay() {
	int i, j;
	static int Anime = 0;		//decides which animation to display
	if(Anime == 0)
		Anime = 1;
	else
		Anime = 0;
	char alienType[2][4][4] = { {"{o}", "</>", "(>)", "   "}, {"{O}","<P>","(*)","   "}};
/*	declared in globals
	static int alienGroupBin[ALIEN_MAXH][ALIEN_MAXW] { 
					{1, 1, 1, 1, 1, 1, 1, 1, 1},
					{2, 2, 2, 2, 2, 2, 2, 2, 2},
					{2, 2, 2, 2, 2, 2, 2, 2, 2},
					{3, 3, 3, 3, 3, 3, 3, 3, 3},
					{3, 3, 3, 3, 3, 3, 3, 3, 3},
	} */
	for(i = 0; i < 5; i++) {
		for(j = 0; j < 9; j++) {
			mvwaddstr(alienGroup, i, j * 4, alienType[0][3]);
		}
	}
	wrefresh(alienGroup);
	delwin(alienGroup);
	alienGroup = newwin(ALIEN_MAXH, ALIEN_MAXW, 0, alienX);
	for(i = 0; i < 5; i++) {
		for(j = 0; j < 9; j++) {
			//check if alien is alive
			switch(alienGroupBin[i][j]) {
				case 0: 
					wattrset(alienGroup, COLOR_PAIR(1));
					mvwaddstr(alienGroup, i, j * 4, alienType[Anime][3]); //print the blank
					break;
				case 1:
					wattrset(alienGroup, COLOR_PAIR(2));
					mvwaddstr(alienGroup, i, j * 4, alienType[Anime][0]);
					break;
				case 2:
					wattrset(alienGroup, COLOR_PAIR(3));
					mvwaddstr(alienGroup, i, j * 4, alienType[Anime][1]);
					break;
				case 3:
					wattrset(alienGroup, COLOR_PAIR(4));
					mvwaddstr(alienGroup, i, j * 4, alienType[Anime][2]);
					break;
					
			}
			//print the alien	
		}
	}
	wrefresh(alienGroup);
}
//alienX declared as global
void alienMovement() {

	static int journey = 0;         //checks if aliens should move right(0) or left(1)
	int i, j;	
	if(alienX == 0)
		journey = 0;

	else if(alienX + ALIEN_MAXW == 80) //80 is the field field width
		journey = 1;

	if(journey == 0) {
		alienX++;
		alienGroupDisplay();
	}
	else {
		alienX--;
		alienGroupDisplay();
	}
}
// test-function
void playerShipInit() {
	player.playerX = 40;
	playerShip = newwin(1, PLAYER_WIDTH, 24, player.playerX);
	wattrset(playerShip, COLOR_PAIR(4));
	mvwprintw(playerShip,0, 0, ")-[^]-(");
	wrefresh(playerShip);
}

// declare player position x as global

void playerShipDisplay() {
	//delete original position
	mvwprintw(playerShip, 0, 0, "       ");
	wrefresh(playerShip);
	delwin(playerShip);
	playerShip = newwin(1, PLAYER_WIDTH, 24, player.playerX); // player height is 1(1 line player ship)
	wattrset(playerShip, COLOR_PAIR(4));
	mvwprintw(playerShip, 0, 0, ")-[^]-(");
	wrefresh(playerShip);
}

void movePlayerRight() {
	if(player.playerX != FIELD_WIDTH) {
		player.playerX++;
		playerShipDisplay();
	}
}

void movePlayerLeft() {
	if(player.playerX != 0) {
		player.playerX--;
		playerShipDisplay();
	}
}

//initiate the player missile
void playerMissileShoot() {
	if(player.playerMissileExist == 0) {
		//launch new missile
		player.playerMissileExist = 1;
		player.playerMissileY = player.playerY - 1;
		playerMissile = newwin(1, 1, player.playerMissileY, player.playerX + PLAYER_WIDTH / 2); // playerY - 1 = 23
		mvwaddch(playerMissile, 0, 0, "|");
		wrefresh(alienMissile);
	}
	else {
		//do nothing
	}
}
void playerMissile() {
	//move player missile one forward
	//delete previous location
	mvwaddch(playerMissile, 0, 0, " ");
	refresh();
	wrefresh(playerMissile);
	player.playerMissileY -= 2;
	alienMissile = newwin(1, 1, player.playerMissileY, playerX + PLAYER_WIDTH / 2); // playerY - 1 = 23
	mvwaddch(playerMissile, 0, 0, "|");
	wrefresh(playerMissile);
	//check collision using function below
	if(collided = 1) {
		//reload missile
		//set corr. alienGroupBin = 0;
	}
	else if(out of boundary = 2) {
		//reload missile
	}
	
}
int playerMissileAlienCollision() {
	//check collision using missileX and alienX
	if(missileX) {
	}
	//return 1  return 2 for out of boundary for yes 0 for no
	//also check if missile has reached boundary of the field	
}
void alienShoot() {
	if(alienMissileExist = 0) {
		alienMissileExist = 1;
	}
	else {
		//move missile missile y++
		
		//clear the old position
		if(alienMissilePlayerCollision) {
			relaod the missiles
		}
		//or check boundary collision
		//do action
	}
}
int alienMissilePlayerCollision() {
	if(collided or reached boundary) {
		return 1 or 2;
		//reload the missile
	}
	else if {
		return 0;
	}
}
	
// test function
void bunkersInit() {
	bunkers = newwin(4, 7, 0, 0);
	char a[4][] = {   "#####",
			"#######",
			"#     #",
			"#     #"
			}
	waddstr(bunkers, a[0]);
	waddstr(bunkers, a[1]);
	waddstr(bunkers, a[2]);
	waddstr(bunkers, a[3]);
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
	refresh();
	playerShipInit();
	alienGroupInit();
	colorsInit();
//	bunkersInit();
}
/* This Method is called every 1 / FPS seconds( #define ) */
void MyThread() {
	// handles all the cases like pause, game over, player movement, 
	alienMovement();
//	alienShoot();
	playerMissile();	
}
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
		case game pause
		case game over
		case other
		default :
			break;
			
	}
}
/*
	void evaluateCommandLine() {
	}
*/
void setUpThread()
{
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
	battleFieldInit();
	//set up function that runs continuously depending on time
	setUpThread();
	while(1) {
		takeInput();
	}
	return 0;
}
