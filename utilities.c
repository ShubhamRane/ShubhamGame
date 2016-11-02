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
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "globals.h"
#include "utilities.h"
#include "alien.h"

/* the below functions should be called in order storeScore() sortScore() and then displayScore()*/
/* sort sorts 8 indexes and stores 7 */
void sortScore() {
	data d1[8];
	data temp;
	FILE *fp;
	fp = fopen("high.txt", "r");
	int index = 0, i, j;
	while(fscanf(fp, "%s%d", d1[index].name, &d1[index].score) != EOF) {
		index++;
	}
	fclose(fp);
	for(j = 7; j > 0; j--) {
		for(i = 0; i < j; i++) {
			if(d1[i].score < d1[i + 1].score) {
				temp = d1[i];
				d1[i] = d1[i + 1];
				d1[i + 1] = temp;
			}
		}
	}
	fp = fopen("high.txt", "w");
	for(i = 0; i < 7; i++) {
		fprintf(fp, "%s %d\n", d1[i].name, d1[i].score);
	}
	fclose(fp);
}

/* Stores a new score at the end of file */
void storeScore(char *new_name, int score) {
	FILE *fp;
	fp = fopen("high.txt", "a");
	if(fp == NULL)
		return;
	fprintf(fp, "%s %d\n", new_name, score);
	fclose(fp);
	sortScore();
}

void displayHighScores() {

	int row, col, height = 21, width = 40, i;
	char head[]= "High-Scores";
	char name[15];
	int score;
	/* Initialize curses mode */
	refresh();
	/* Create a window with head and borders */
	WINDOW *Score;
	getmaxyx(stdscr, col, row);
	Score = newwin(height, width, (col-height)/2, (row-width)/2);
	wattron(Score, COLOR_PAIR(6));
	box(Score, 0, 0);
	mvwaddch(Score, 2, 0, ACS_LTEE);
	mvwhline(Score, 2, 1, ACS_HLINE, width - 2);
	mvwaddch(Score, 2, width - 1, ACS_RTEE);
	mvwprintw(Score, 1, (width-strlen(head))/2, "%s", head);
	wattroff(Score, COLOR_PAIR(6));

	/* Scan scores from file and display */
	FILE *fp;
	fp = fopen("high.txt", "r");
	i = 2;
	while(fscanf(fp, "%s%d", name, &score) != EOF) {
		wattron(Score, COLOR_PAIR(i % 2 + 6));
		mvwprintw(Score, i * 2, (width - 26)/2, "%-15s %10d", name, score);
		i++;
	}
	fclose(fp);
	wattron(Score, COLOR_PAIR(6));
	mvwhline(Score, 18, 1, ACS_HLINE, width - 2);
	mvwprintw(Score, 19, 12, "Press Q to Return");
	wrefresh(Score);
	wattroff(Score, COLOR_PAIR(6));

	/* End curses Mode */
	while((i = getch())) {
		if(i == 'q' || i == 'Q')
			break;
	}
	werase(Score);
	wrefresh(Score);
	delwin(Score);
	endwin();
}

/* accepts name of the player and stores */
void form(char *name) {
	int y, x, i, ch;
	char *str = "default";
	WINDOW *my_win;
	getmaxyx(stdscr, y, x);
	my_win = newwin(15, 33, y/2 - 15, x/2 - 34);
	keypad(my_win, true);
	wattron(my_win, COLOR_PAIR(6));
	box(my_win, 0, 0);
	mvwprintw(my_win, 2, 5, "!!!!! Well Played !!!!!");
	mvwprintw(my_win, 4, 11, "Your Score :");
	mvwprintw(my_win, 6, 16, "%d", score);
	mvwprintw(my_win, 8, 9, "Enter Your name : ");
	mvwprintw(my_win, 9, 5, "(Press Enter to submit)");
	mvwhline(my_win, 13, 8, ACS_HLINE, 17);
	mvwprintw(my_win, 12, 7, "|                 |");
	wmove(my_win, 12, 9);
	wrefresh(my_win);
	wattron(my_win, COLOR_PAIR(3));
	i = 0; /* points to end '\0' */
	name[i] = '\0';
	while(((ch = wgetch(my_win)) != 13)) {	/* Enter */
		if(ch == ' ')
			ch = '_';
		if(ch == 263) { 	/* backspace */
			if(i > 0)
				name[--i] = '\0';
		}
		else if(!((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9') || (ch == '_')))
			continue;	
		else if(i >= 14) 
			continue;
		else
			name[i++] = ch;

		name[i] = '\0';
		mvwprintw(my_win, 12, 9, "               ");
		mvwprintw(my_win, 12, 9, "%s", name, ch);
		wrefresh(my_win);
	}
	if(i == 0)
		strcpy(name, str);
	else
		name[i] = '\0';
	werase(my_win);
	wrefresh(my_win);
}

int checkGameOver() {
	/* alien win condition */
	if((alienY + ALIEN_MAXH >= player.playerY) || player.health <= 0)
		return 1;
	else if(alienCount <= 0) {
		alienGroupInit();
		if(player.health < 10)
			player.health++;
		level++;
	}
	return 0;
}
void clearArena() {
	WINDOW *temp;
	temp = newwin(43, 143, 0, 0);
	werase(temp);
	wrefresh(temp);
	delwin(temp);
}
