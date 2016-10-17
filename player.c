#include <ncurses.h>
#include "globals.h"
void playerShipInit() {
	player.playerX = 40;
	player.playerY = 19;
	playerShip = newwin(1, PLAYER_WIDTH, player.playerY, player.playerX);
	wattrset(playerShip, COLOR_PAIR(4));
	mvwprintw(playerShip, 0, 0, "/-[^]-\\");
	wrefresh(playerShip);
}

// declare player position x as global
void playerShipDisplay() {
	//delete original position
	mvwprintw(playerShip, 0, 0, "        ");
	wrefresh(playerShip);
	delwin(playerShip);
	playerShip = newwin(1, PLAYER_WIDTH, player.playerY, player.playerX); // player height is 1(1 line player ship)
	wattrset(playerShip, COLOR_PAIR(4));
	mvwprintw(playerShip, 0, 0, "/-[^]-\\");
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
//initiate the player missile
void playerMissileShoot() {
	if(player.playerMissileExist == 0) {
		//launch new missile
		player.playerMissileExist = 1;
		player.playerMissileY = player.playerY - 1;
		player.playerMissileX = player.playerX + PLAYER_WIDTH / 2;
		playerMissile = newwin(1, 1, player.playerMissileY, player.playerMissileX); // playerY - 1 = 23
		mvwaddch(playerMissile, 0, 0, '|');
		wrefresh(alienMissile);
	}
}

int playerMissileAlienCollision() {
	int i, j;
	i = player.playerMissileY - alienY;
	j = (player.playerMissileX - alienX) / 4;
	if(i <= 4 && i>=0 && j<= 9 && j>=0) {
		if(alienGroupBin[i][j] != 0) {
			alienGroupBin[i][j] = 0;
			wrefresh(alienGroup);
			return 1;
		}
	}
	/*	
	//check collision using missileX and alienX
	if(player.playerMissileX >= alienX && player.playerMissileX <= alienX + ALIEN_MAXW ) {
		if(player.playerMissileY >= alienY && player.playerMissileX <= alienX + ALIEN_MAXH ) {
			i = player.playerMissileY - alienY;
			j = player.playerMissileX - alienX;
			alienGroupBin[i][j] = 0;
			refresh();
			return 1;
		}
	}
	//return 1  return 2 for out of boundary for yes 0 for no
	//also check if missile has reached boundary of the field*/
	else if(player.playerMissileY <= 0)
		return 2;
	return 0;
}
void playerMissileFun() {
	//move player missile one forward
	//delete previous location
	if(player.playerMissileExist == 1) {
		mvwaddch(playerMissile, 0, 0, ' ');
		wrefresh(playerMissile);
		delwin(playerMissile);
		player.playerMissileY -= 1;
		playerMissile = newwin(1, 1, player.playerMissileY, player.playerMissileX); // playerY - 1 = 23
		mvwaddch(playerMissile, 0, 0, '|');
		wrefresh(playerMissile);
		//check collision using function below
		if(playerMissileAlienCollision() != 0) {
			player.playerMissileExist = 0;
			mvwaddch(playerMissile, 0, 0, ' ');
			wrefresh(playerMissile);
			delwin(playerMissile);
		}
	}
	
}
