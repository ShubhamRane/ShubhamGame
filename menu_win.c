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
#include <menu.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"
#include "menu_win.h"
#include "utilities.h"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]));
char *choices[] = {
	" Play Game              ",
	" Difficulty             ",
	" High-Scores            ",
	" Credits                ",
	" Exit                   ",
	(char *)NULL
};

char *choicesD[] = {
	" Easy              ",
	" Medium            ",
	" Hard              ",
	" Impossible        ",
	(char *)NULL
};
int startMenu() {
	int c;
	int ch = 100;
	int x, y;
	int n_choices, i;
	ITEM **my_items;
	MENU *my_menu;
	WINDOW *my_menu_win;
	/* Initialize curses */
	initscr();
	start_color();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(0);
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(6, COLOR_CYAN, COLOR_BLACK);
	init_pair(7, COLOR_WHITE, COLOR_BLACK);
	getmaxyx(stdscr, y, x);
	y = 5;
	/* Game Name Display */
	attron(COLOR_PAIR(6));
	x = (x-70)/2;
	mvprintw(y++, x,"    ////// ////// ////// ////// //////       ////// ////// //  //  ");
	mvprintw(y++, x,"   //     //  // //  // //     //             //   //  // // //    ");
	mvprintw(y++, x,"  ////// ////// ////// //     /////  //////  //   ////// ////      ");
	mvprintw(y++, x,"     // //     //  // //     //             //   //  // //  //     ");
	mvprintw(y++, x,"////// //     //  // ////// //////         //   //  // //   //     ");
	attroff(COLOR_PAIR(6)); 
	refresh();

	/* All menu related */
	/* Create items */
	n_choices = ARRAY_SIZE(choices);
	my_items = (ITEM **)calloc(n_choices, sizeof(ITEM *));
	for(i = 0; i < n_choices; i++) {
		my_items[i] = new_item(choices[i], NULL);
		set_item_userptr(my_items[i], func);
	}
	/*set_item_userptr(my_items[1], difficultyMenu);*/
	/* Crate menu */
	my_menu = new_menu((ITEM **)my_items);

	/* Create the window to be associated with the menu */
	my_menu_win = newwin(10, 30, 12, (x + 70) / 2);
	keypad(my_menu_win, TRUE);

	/* Set main window and sub window */
	set_menu_win(my_menu, my_menu_win);
	set_menu_sub(my_menu, derwin(my_menu_win, 7, 29, 3, 1));

	/* Set menu mark to the string " * " */
	set_menu_mark(my_menu, "> ");

	/* Print a border around the main window and print a title */
	displayMainMenu(my_menu_win);

	/* Post the menu */
	post_menu(my_menu);
	wrefresh(my_menu_win);
	i = 0;

	while(1) {

		if(ch != 1 && ch != 3) {
			c = wgetch(my_menu_win);
		}
		else {
			ch = 10;
			c = KEY_UP;
		}
		switch(c) {
			case KEY_DOWN:
				menu_driver(my_menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(my_menu, REQ_UP_ITEM);
				break;
			case '\n': {
					   ITEM *cur;
					   int (*p)(char *);
					   cur = current_item(my_menu);
					   p = item_userptr(cur);
					   ch = p((char *)item_name(cur));
					   break;
				   }
		}
		displayMainMenu(my_menu_win);
		wrefresh(my_menu_win);
		if(ch == 0 || ch == 4)
			return ch;
		if(ch == 1 || ch == 2) {
			c = KEY_DOWN;
			continue;
		}

	}	
	/* Unpost and free all the memory taken up */
	unpost_menu(my_menu);
	free_menu(my_menu);

	for(i = 0; i < n_choices; ++i)
		free_item(my_items[i]);

	endwin();
}

void displayMainMenu(WINDOW *my_menu_win) {

	box(my_menu_win, 0, 0);
	menu_title(my_menu_win, 1, 0, 32, "Space-Tak", COLOR_PAIR(5));
	mvwaddch(my_menu_win, 2, 0, ACS_LTEE);
	mvwhline(my_menu_win, 2, 1, ACS_HLINE, 29);
	mvwaddch(my_menu_win, 2, 29, ACS_RTEE);
	refresh();
}

void difficultyMenu() {
	int c;
	int x, y;			
	int n_choices, i;
	ITEM **my_items;
	MENU *my_menu;
	WINDOW *my_menu_win;
	keypad(stdscr, TRUE);
	curs_set(0);
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	getmaxyx(stdscr, y, x);
	y = 12;
	x = (x - 70) / 2;
	n_choices = ARRAY_SIZE(choicesD);
	my_items = (ITEM **)calloc(n_choices, sizeof(ITEM *));

	for(i = 0; i < n_choices; ++i) {
		my_items[i] = new_item(choicesD[i], NULL);
	}

	my_menu = new_menu((ITEM **)my_items);

	my_menu_win = newwin(10, 30, y, (x + 70) / 2);
	keypad(my_menu_win, TRUE);

	set_menu_win(my_menu, my_menu_win);
	set_menu_sub(my_menu, derwin(my_menu_win, 7, 29, 3, 1));

	set_menu_mark(my_menu, "> ");

	box(my_menu_win, 0, 0);


	menu_title(my_menu_win, 1, 0, 32, "Difficulty", 5);
	mvwaddch(my_menu_win, 2, 0, ACS_LTEE);
	mvwhline(my_menu_win, 2, 1, ACS_HLINE, 29);
	mvwaddch(my_menu_win, 2, 29, ACS_RTEE);
	refresh();

	post_menu(my_menu);
	wrefresh(my_menu_win);

	while((c = wgetch(my_menu_win)) != 'q') {       
		switch(c) {
			case KEY_DOWN:
				menu_driver(my_menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(my_menu, REQ_UP_ITEM);
				break;
			case '\n': {
					   ITEM *cur;
					   cur = current_item(my_menu);
					   i = 0;
					   while(strcmp(item_name(cur), choicesD[i]) != 0)
						   i++;
					   difficulty = i;
					   break;
				   }
				   break;
		}
		if(c == '\n')
			break;
	}
	wrefresh(my_menu_win);

	unpost_menu(my_menu);
	free_menu(my_menu);

	for(i = 0; i < n_choices; ++i)
		free_item(my_items[i]);

}

void credits() {
	WINDOW *cred;
	int ch, x, y;	
	cred = newwin(25, 80, 12, 30);
	refresh();

	mvwhline(cred, 0, 0, ACS_DIAMOND, 80);
	wattron(cred, COLOR_PAIR(6));
	wmove(cred, 2, 0);
	wprintw(cred, "* Copyright (C) Shubham T. Rane, Mail id: shubhamr022@gmail.com\n\n");
	wprintw(cred, "* This program is free software; you can redistribute it and/or modify it\n");
	wprintw(cred, "* under the terms of the GNU Lesser General Public License as published by\n");
	wprintw(cred, "* the Free Software Foundation; either version 2.1 of the License, or\n");
	wprintw(cred, "* (at your option) any later version.\n\n");
	wprintw(cred, "* This program is distributed in the hope that it will be useful,\n");
	wprintw(cred, "* but WITHOUT ANY WARRANTY; without even the implied warranty of\n");
	wprintw(cred, "* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the\n");
	wprintw(cred, "* GNU Lesser General Public License for more details.\n\n");
	wprintw(cred, "* You should have received a copy of the GNU Lesser General Public License\n");
	wprintw(cred, "* along with this program; if not, write to the Free Software Foundation,\n");
	wprintw(cred, "* Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.\n\n");
	
	wattron(cred, COLOR_PAIR(3));
	wprintw(cred, "                           Press q to return                              \n");
	wattroff(cred, COLOR_PAIR(2));
	getyx(cred, y, x);
	mvwhline(cred, y+1, x, ACS_DIAMOND, 80);
	wattroff(cred, COLOR_PAIR(1));
	wrefresh(cred);

	while((ch = getch()) != 'q'){}
	werase(cred);
	wrefresh(cred);
}

int func(char *name) {
	int i, choice;
	int size = ARRAY_SIZE(choices);
	move(40, 0);
	clrtoeol();
	for(i = 0; i < size; i++) {
		if(strcmp(name, choices[i]) == 0) {
			choice = i;
			break;
		}
	}
	//mvprintw(40, 0, "%s %d %d", name, choice, size);
	//refresh();
	switch(choice) {
		case 1:
			difficultyMenu();
			refresh();
			break;
		case 3:
			credits();
			refresh();
			break;

		case 2:
			displayHighScores();
			refresh();
			break;
		default:
			break;
	}
	return choice;

}

void menu_title(WINDOW *win, int starty, int startx, int width, char *string, chtype color) {
	int length, x, y;
	int temp;

	if(win == NULL)
		win = stdscr;
	getyx(win, y, x);
	if(startx != 0)
		x = startx;
	if(starty != 0)
		y = starty;
	if(width == 0)
		width = 80;

	length = strlen(string);
	temp = (width - length) / 2;
	wattron(win, COLOR_PAIR(6));
	x = startx + temp;
	mvwprintw(win, y, x, "%s", string);
	wattroff(win, COLOR_PAIR(6));
	refresh();
}
