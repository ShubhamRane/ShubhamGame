#include <ncurses.h>
#include "globals.h"
#include "alien.h"

void playerShipInit() {
	player.playerX = 40;
	player.playerY = 24;
	player.health = 5;
	playerShip = newwin(1, 143, player.playerY, 0);
	wattrset(playerShip, COLOR_PAIR(2));
	mvwprintw(playerShip, 0, player.playerX, "<-)^(->");
	wrefresh(playerShip);
}

/* declared player position x as global */
void playerShipDisplay() {
	/* delete original position */
	mvwprintw(playerShip, 0, player.playerX - 2, "              ");
	wrefresh(playerShip);
	wattrset(playerShip, COLOR_PAIR(2));
	mvwprintw(playerShip, 0, player.playerX, "<-)^(->");
	wrefresh(playerShip);
}

void movePlayerRight() {
	if(player.playerX != FIELD_WIDTH) {
		player.playerX+=2;
		playerShipDisplay();
	}
}

void movePlayerLeft() {
	if(player.playerX != 0) {
		player.playerX-=2;
		playerShipDisplay();
	}
}
/* Initiate the player missile */
void playerMissileShoot() {
	
	if(player.playerMissileExist == 0) {
		/* launch new missile */
		player.playerMissileExist += 1;
		player.playerMissileY = player.playerY - 1;
		player.playerMissileX = player.playerX + PLAYER_WIDTH / 2;
		playerMissile = newwin(1, 1, player.playerMissileY, player.playerMissileX); // playerY - 1 = 23
		mvwaddch(playerMissile, 0, 0, ACS_PI);
		wrefresh(alienMissile);
	}
}

int playerMissileAlienCollision() {
	int i, j;
	i = player.playerMissileY - alienY;
	j = (player.playerMissileX - alienX) / 4;
	if(i <= 4 && i>=0 && j<= 8 && j>=0) {
		if(alienGroupBin[i][j] != 0) {
			alienGroupBin[i][j] = 0;
			alienGroupDisplay();
			alienCount--;
			score += i;
			return 1;
		}
	}
	
	else if(player.playerMissileY <= alienY  -  1)
		return 2;
	return 0;
}
void playerMissileFun() {
	/* move player missile one forward
	 * delete previous location */

	if(player.playerMissileExist == 1) {

		mvwaddch(playerMissile, 0, 0, ' ');
		wrefresh(playerMissile);
		delwin(playerMissile);
		player.playerMissileY -= 1;
		playerMissile = newwin(1, 1, player.playerMissileY, player.playerMissileX); /* */
		mvwaddch(playerMissile, 0, 0, ACS_UARROW);
		wrefresh(playerMissile);

		/* check collision using function below */
		if(playerMissileAlienCollision() != 0) {
			player.playerMissileExist = 0;
			mvwaddch(playerMissile, 0, 0, ' ');
			wrefresh(playerMissile);
			delwin(playerMissile);
		}
	}
	
}
