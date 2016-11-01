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
#include <ncurses.h>
#include <stdlib.h>
#include "globals.h"
#include "utilities.h"

void updateBoard(WINDOW *board) {

	int i;
	char *diff;
	diff = malloc(15);
	werase(board);
	wattron(board, COLOR_PAIR(7));
	box(healthBoard, 0, 0);
	wattroff(board, COLOR_PAIR(7));
	wattron(board, COLOR_PAIR(3));
	mvwprintw(healthBoard, 1, 5, "HEALTH : |                     |");
	mvwprintw(healthBoard, 3, 5, "SCORE  : ");
	mvwprintw(healthBoard, 5, 5, "LEVEL  : ");
	mvwprintw(healthBoard, 5, 30,"DIFFICULTY  : ");
	wattroff(board, COLOR_PAIR(3));
	wattron(board, COLOR_PAIR(1));
	mvwprintw(healthBoard, 3, 15, "%-10d", score);
	mvwprintw(healthBoard, 5, 15, "%d", level);
	switch(difficulty) {
		case 0:
			diff = "EASY";
			break;
		case 1:
			diff = "MEDIUM";
			break;
		case 2:
			diff = "HARD";
			break;
		case 3:
			diff = "IMPOSSIBLE";
			break;
		default:
			break;
	}
	mvwprintw(healthBoard, 5, 45, "%s", diff);

	for(i = 0; i <= player.health; i++) {
		mvwaddch(healthBoard, 1, 15 + i, ACS_CKBOARD);
	}
	wattroff(board, COLOR_PAIR(1));
	wrefresh(healthBoard);

}
void healthBoardInit() {
	player.health = 10;
	level = 1;
	score = 0;
	healthBoard = newwin(7, FIELD_WIDTH + 2, FIELD_HEIGHT + 2, 0);
	updateBoard(healthBoard);
}

