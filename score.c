#include <ncurses.h>
#include "globals.h"
//define window params
void updateScore() {
	/*
	static int health = 100;
	if(playerHits) {
		health -= 20;
	}
	if(levelUp) {
		health += 10;
	}
	if(health == 0) {
		gameOver();
	}*/
	
}
void healthBoardInit() {
	static int health = 5; /* declare this variable later as a global */
	healthBoard = newwin(5, FIELD_WIDTH + 2, FIELD_HEIGHT + 2, 0);
	box(healthBoard, 0, 0);
	mvwprintw(healthBoard, 1, 5, "lives : ");
	move(1, 15);
	for(int i = 0; i <= health; i++)
		wprintw(healthBoard, "/[]\\ ");
	mvwprintw(healthBoard, 3, 5, "health : ");
	mvwprintw(healthBoard, 3, 15, "|!!!!!!!!!!!!!      |");
	wrefresh(healthBoard);
}
void displayScore() {
	//display player health
	//display score
	//display player level
}
