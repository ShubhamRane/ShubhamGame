#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include "globals.h"
#include "player.h"
void alienGroupDisplay() {
	int i, j;
	static int Anime = 0;		//decides which animation to display
	if(Anime == 0)
		Anime = 1;
	else
		Anime = 0;
	static int scounter = 0;
	char alienType[2][4][5] = { {"____", "||||", "[--]", "    "}, {"_--_","||||","[__]","    "}};
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
	alienGroup = newwin(ALIEN_MAXH, ALIEN_MAXW, alienY, alienX);
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
		//newline
	}
	wrefresh(alienGroup);
}
void alienGroupInit() {
	alienGroup = newwin(ALIEN_MAXH, ALIEN_MAXW, alienY, alienX);	
	wrefresh(alienGroup);
}
//create new window
//alienX declared as global
void alienMovement() {
	static int journey = 0;		//checks if aliens should move right(0) ar left(1)
	int i, j;	
	if(alienX == 0) {
		journey = 0;
		alienY++;
	}

	else if(alienX + ALIEN_MAXW == 80) {
		journey = 1;
		alienY++;
	}

	if(journey == 0) {
		alienX++;
		alienGroupDisplay();
	}
	else {
		alienX--;
		alienGroupDisplay();
	}
}

void displayPlayerAnimation() {
	int i = 0, ch;
	while(i<=10) {
		ch = rand() % 15 + 33;
		mvwprintw(playerShip, 0, 0, "%c%c%c%c%c%c%c", ch, ch+1, ch+2, ch+3, ch+4, ch+5, ch+6);
		wrefresh(playerShip);
		usleep(80000);
		i++;
	}
	mvwprintw(playerShip, 0, 0, "       ");
	wrefresh(playerShip);
	delwin(playerShip);
	playerShipInit();
}
int alienMissilePlayerCollision() {
	
	if(alienMissileY == player.playerY - 1 || alienMissileY == player.playerY) {
		if(alienMissileX >= player.playerX && alienMissileX <= player.playerX + PLAYER_WIDTH) {
			displayPlayerAnimation();
			return 1;
		}
	}
	else if(alienMissileY >= FIELD_HEIGHT) {
		return 2;
	}
	else  {
		return 0;
	}
}
void alienShoot() {
	if(alienMissileExist == 0) {
		alienMissileExist = 1;
		alienMissileY = alienY + ALIEN_MAXH;
		alienMissileX = alienX + ALIEN_MAXW / 2 - 5;
		alienMissile = newwin(1, 1, alienMissileY, alienMissileX);
		wattrset(alienMissile, COLOR_PAIR(4));
		waddch(alienMissile, '*');
		wrefresh(alienMissile);
	}
	else {
		//move alien missile y++
		alienMissileY += 1;
		waddch(alienMissile, ' ');
		wrefresh(alienMissile);
		delwin(alienMissile);
		alienMissile = newwin(1, 1, alienMissileY, alienMissileX);
		alienMissile = newwin(1, 1, alienMissileY, alienMissileX);
		wattrset(alienMissile, COLOR_PAIR(4));
		waddch(alienMissile, '*');
		wrefresh(alienMissile);
		//clear the old position
		if(alienMissilePlayerCollision() == 1) {
			//player health reduce
			alienMissileExist = 0;
			waddch(alienMissile, ' ');
			wrefresh(alienMissile);
			delwin(alienMissile);
		}
		//or check boundary collision
		else if(alienMissilePlayerCollision() == 2) {
			alienMissileExist = 0;
			waddch(alienMissile, ' ');
			wrefresh(alienMissile);
			delwin(alienMissile);
		}
		//do action
	}
}

