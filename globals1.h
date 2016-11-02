/*
 * Copyright (C) Shubham T. Rane shubhamr022@gmail.com
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 "This program is distributed in the hope that it will be useful,"
 "but WITHOUT ANY WARRANTY; without even the implied warranty of"
 "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the"
 "GNU Lesser General Public License for more details."
 *
 "You should have received a copy of the GNU Lesser General Public License
 "along with this program; if not, write to the Free Software Foundation,
 "Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *
 */

#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <signal.h>
#include <ncurses.h>
#include <string.h>

#include "player.h"
#include "alien.h"
#include "score.h"
#include "menu_win.h"
#include "utilities.h"


#define COLOR 5
#define FIELD_WIDTH 80
#define FIELD_HEIGHT 24
#define ALIEN_MAXW  36 
#define ALIEN_MAXH 5
#define PLAYER_WIDTH 7

WINDOW *alienGroup;
WINDOW *playerShip;
WINDOW *bunkers;
WINDOW *alienMissile;	
WINDOW *playerMissile;
WINDOW *healthBoard;

struct playerShip  {

	/* check player missile status */
	int playerMissile;
	int playerMissileExist;

	/* to check player and player missile position along x axis */
	int playerX;
	int playerY;
	int playerMissileY;
	int playerMissileX;
	int health;

	
}player;

pthread_t t1;

int state;
int difficulty = 1;
int level = 10;
int score = 10;
int alienX = 0;
int alienY = 0;
int alienCount;
int alienMissileY = 0;
int alienMissileX = 0;
int alienMissileExist;
int alienGroupBin[5][9]; 
