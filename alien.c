#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include "globals.h"
#include "player.h"
#include "utilities.h"
#define BORDER 10
#define MIDDLE 20

void alienGroupDisplay() {
	int i, j;
	static int Anime = 0;		
	
	/* decides which animation to display */
	if(Anime == 0)
		Anime = 1;
	else
		Anime = 0;
	
	char alienType[2][6][5] = { {"|=| ", "\\^/", "[--]", "    ", "/^^\\", "\\::/"}, {"|=| ","\\:/","[__]", "    ", "/--\\", "\\''/"}};
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
					wattrset(alienGroup, COLOR_PAIR(1));
					mvwaddstr(alienGroup, i, j * 4, alienType[Anime][0]);
					break;
				case 2:
					wattrset(alienGroup, COLOR_PAIR(2));
					mvwaddstr(alienGroup, i, j * 4, alienType[Anime][1]);
					break;
				case 3:
					wattrset(alienGroup, COLOR_PAIR(3));
					mvwaddstr(alienGroup, i, j * 4, alienType[Anime][2]);
					break;
                                case 4:
					wattrset(alienGroup, COLOR_PAIR(4));
					mvwaddstr(alienGroup, i, j * 4, alienType[Anime][4]);
					break;
				case 5:
					wattrset(alienGroup, COLOR_PAIR(5));
					mvwaddstr(alienGroup, i, j * 4, alienType[Anime][5]);
					break;

			}
			//print the alien	
		}
	}
	wrefresh(alienGroup);
}

void alienGroupInit() {
	alienGroup = newwin(ALIEN_MAXH, ALIEN_MAXW, alienY, alienX);	
	wrefresh(alienGroup);
}

void alienMovement() {
	static int journey = 0;		/* checks if aliens should move right(0) ar left(1) */
	static int status = 0;		/* checks if alien has instantly reached boundary */
	int i, j;
	
	if(alienY + ALIEN_MAXH == player.playerY - 1) {
		/*call game_over function*/
		gameOver();
		return;
	}
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

	/* if at left boundary */
	else if(alienX + ALIEN_MAXW == 80) {
		if(status == 0) {
			journey = 1;
			alienY++;
			status = 1;
		}
		else
			status = 0;
	}

	/* should move right */
	if(journey == 0) {
		if(status == 0)
			alienX++;
	}
	
	/* should move left */
	else {
		if(status == 0)
			alienX--;
	}
	
	alienGroupDisplay();
}

void displayPlayerAnimation() {
	int i = 0, ch;

	/* display random characters */
	while(i <= 5) {

		/* 33 to 47 Ascii value character generate */
		ch = rand() % 15 + 33;
		mvwprintw(playerShip, 0, 0, "%c%c%c%c%c%c%c", ch, ch+1, ch+2, ch+3, ch+4, ch+5, ch+6);
		wrefresh(playerShip);

		/* show player dismantle slowly */
		usleep(60000);
		i++;
	}

	mvwprintw(playerShip, 0, 0, "       ");
	wrefresh(playerShip);
	delwin(playerShip);

	/* initialize the player in the middle position again */
	playerShipInit();
}

/* returns 1 if missile hits player , 2 if hits boundary, 0 otherwise */
int alienMissilePlayerCollision() {
	
	/* check co-ordinates of missile against player position */
	if(alienMissileY == player.playerY - 1 || alienMissileY == player.playerY) {

		if(alienMissileX >= player.playerX && alienMissileX <= player.playerX + PLAYER_WIDTH) {
			displayPlayerAnimation();
			return 1;
		}

	}

	/* check if missile has reached boundary */
	else if(alienMissileY >= FIELD_HEIGHT)
		return 2;
	else
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
		waddch(alienMissile, '*');
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

