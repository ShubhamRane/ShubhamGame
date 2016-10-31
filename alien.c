#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include "globals.h"
#include "player.h"
#include "score.h"
#include "utilities.h"
enum{RED = 1, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE}; 
void alienGroupDisplay() {
	int i, j;
	static int Anime = 0;		
	
	/* Decides which animation to display */
	Anime = 1 - Anime;
	
	char alienType[2][6][5] = {{"|--|", "\\v/ ", "[--]", "\\::/", "/^^\\", "    "}, {"|--|","VvvV","[__]", "\\''/", "/--\\", "    "}};
	
	/* Made changes here */
	werase(alienGroup);
	wrefresh(alienGroup);
	delwin(alienGroup);
	alienGroup = newwin(ALIEN_MAXH, ALIEN_MAXW, alienY, alienX);
	for(i = 0; i < 5; i++) {
		for(j = 0; j < 9; j++) {
			/* check if alien is alive */
			switch(alienGroupBin[i][j]) {
				case 0: 
					wattrset(alienGroup, COLOR_PAIR(WHITE));
					mvwaddstr(alienGroup, i, j * 4, alienType[Anime][5]); //print the blank
					break;
				case 1:
					wattrset(alienGroup, COLOR_PAIR(MAGENTA));
					mvwaddstr(alienGroup, i, j * 4, alienType[Anime][1]);
					break;
				case 2:
					wattrset(alienGroup, COLOR_PAIR(CYAN));
					mvwaddstr(alienGroup, i, j * 4, alienType[Anime][2]);
					break;
				case 3:
					wattrset(alienGroup, COLOR_PAIR(YELLOW));
					mvwaddstr(alienGroup, i, j * 4, alienType[Anime][3]);
					break;
                                case 4:
					wattrset(alienGroup, COLOR_PAIR(4));
					mvwaddstr(alienGroup, i, j * 4, alienType[Anime][4]);
					break;
				case 5:
					wattrset(alienGroup, COLOR_PAIR(5));
					mvwaddstr(alienGroup, i, j * 4, alienType[Anime][0]);
					break;

			}
		}
	}
	wrefresh(alienGroup);
}

void alienGroupInit() { 
	
	int i, j;
	alienCount = 0;
	alienY = alienX = 0;	
	alienGroup = newwin(ALIEN_MAXH, ALIEN_MAXW, alienY, alienX);
	wrefresh(alienGroup);
	for(i = 0; i < 5; i++) { 
		for(j = 0; j < 9; j++) {
			alienGroupBin[i][j] = i+1;  
			alienCount++;
		}
	}
	refresh();
}

void alienMovement() {
	static int journey = 0;		/* checks if aliens should move right(0) ar left(1) */
	static int status = 0;		/* checks if alien has instantly reached boundary */
	
	/* if at right boundary */
	if(alienX == 0) {
		if(status == 0) {
			alienY++;
			journey = 0;
			status = 1;
		}
		else
			status = 0;
	}

	/* If at left boundary */
	else if(alienX + ALIEN_MAXW == 80) {
		if(status == 0) {
			journey = 1;
			alienY++;
			status = 1;
		}
		else
			status = 0;
	}

	/* Should move right */
	if(journey == 0) {
		if(status == 0)
			alienX++;
	}
	
	/* Should move left */
	else {
		if(status == 0)
			alienX--;
	}
	
	alienGroupDisplay();
}

void displayPlayerAnimation() {
	int i = 0;
	int ch;
	/* Display random characters */
	while(i <= 3) {

		/* 33 to 47 Ascii value character generate */
		ch = rand() % 15 + 33;
		mvwprintw(playerShip, 0, player.playerX, "%c%c%c%c%c%c%c", ch, ch+1, ch+2, ch+3, ch+4, ch+5, ch+6);
		wrefresh(playerShip);
		usleep(35000);
		i++;

		/* show player dismantle slowly 
		usleep(60000);
		i++;
		werase(playerShip);
		wrefresh(playerShip);
		werase(playerShip);
		werase(playerShip);
		i++;*/
		
	}

	mvwprintw(playerShip, 0, player.playerX, "<-)^(->");
	wrefresh(playerShip);

	/* initialize the player in the middle position again */
}

/* returns 1 if missile hits player , 2 if hits boundary, 0 otherwise */
int alienMissilePlayerCollision() {
	
	/* check co-ordinates of missile against player position */
	if(alienMissileY == player.playerY - 1 || alienMissileY == player.playerY) {

		if(alienMissileX >= player.playerX && alienMissileX <= player.playerX + PLAYER_WIDTH) {
			player.health-=2;
			displayPlayerAnimation();
			return 1;
		}

	}

	/* check if missile has reached boundary */
	else if(alienMissileY >= FIELD_HEIGHT)
		return 2;
	return 0;
}

void alienShoot() {
	
	/* if no current missile generate new missile */
	if(alienMissileExist == 0) {
		alienMissileExist = 1;
		alienMissileY = alienY + ALIEN_MAXH;
		alienMissileX = alienX + ALIEN_MAXW / 2 - 5;
		alienMissile = newwin(1, 1, alienMissileY, alienMissileX);
		wattrset(alienMissile, COLOR_PAIR(4));
		waddch(alienMissile, ':');
		wrefresh(alienMissile);
	}
	
	/* if missile already present perform missile actions */
	else {
		/* move alien missile y++ */
		alienMissileY += 1;
		waddch(alienMissile, ' ');
		wrefresh(alienMissile);
		delwin(alienMissile);
		alienMissile = newwin(1, 1, alienMissileY, alienMissileX);
		alienMissile = newwin(1, 1, alienMissileY, alienMissileX);
		wattrset(alienMissile, COLOR_PAIR(4));
		waddch(alienMissile, ACS_DEGREE);
		wrefresh(alienMissile);

		/* clear the old position */
		if(alienMissilePlayerCollision() == 1) {
			//player health reduce
			alienMissileExist = 0;
			waddch(alienMissile, ' ');
			wrefresh(alienMissile);
			delwin(alienMissile);
		}

		/* check boundary collision */
		else if(alienMissilePlayerCollision() == 2) {
			alienMissileExist = 0;
			waddch(alienMissile, ' ');
			wrefresh(alienMissile);
			delwin(alienMissile);
		}
	}
}

