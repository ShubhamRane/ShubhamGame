#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include "globals.h"
void gameOver() {
	WINDOW *temp;
	temp = newwin(32, 90, 0, 0);
	werase(temp);
	mvwprintw(temp, FIELD_HEIGHT / 2, FIELD_WIDTH / 2, "SORRY : GAME OVER");
	wrefresh(temp);
	usleep(1000000);
	delwin(temp);
	endwin();
	exit(1);
}
