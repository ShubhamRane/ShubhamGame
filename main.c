
#include "globals1.h"

#define GAME_OVER 10
#define PAUSE 20
#define INPUT 30
#define QUIT 40
#define FPS 22

/* initialize colors for black background */
void colorsInit() {
	start_color();
	init_pair(1, COLOR_RED,	COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(6, COLOR_CYAN, COLOR_BLACK);
	init_pair(7, COLOR_WHITE, COLOR_BLACK);
}

/* returns 0 if successful returns 1 if interrupt */
int battleFieldInit() {
	int menuChoice;
	/* initialize Windows for everything */
	menuChoice = startMenu();
	if(menuChoice == 4)
		return 1;
	initscr();
	keypad(stdscr, TRUE);
	nonl();
	noecho();
	cbreak();
	clearArena();
	start_color();
	refresh();
	colorsInit();
	healthBoardInit();
	alienGroupInit();
	playerShipInit();
	return 0;
}

/* This Method is called every frequency seconds defined in setUpTimer function */
void MyThread() {
	/* handles all the cases like pause, game over, player movement */
	static int i = 0;
	if(state == GAME_OVER)
		return;
	if(i == 0) { 
		alienMovement();
		alienShoot();
		playerMissileFun();
		updateBoard(healthBoard);
		i = 2;	
	} else if(i >= 1) {
		playerMissileFun();
		i--;
	}
	if(checkGameOver() == 1) {
		updateBoard(healthBoard);
		clearArena();
		mvprintw(FIELD_HEIGHT / 2, FIELD_WIDTH / 2 + 4, "GAME OVER");
		mvprintw(FIELD_HEIGHT / 2 + 2, FIELD_WIDTH / 2, "Press Q to continue");
		refresh();
		state = GAME_OVER;
	}
}

/* this function takes inputs to control the game */
void takeInput() {
	int ch;
	static int debug = 0;
	if(debug == 0) {
		state = INPUT;
		debug = 1;
	}
	ch = getch();
	switch(state) {
		case INPUT:	
			switch(ch) {
				case KEY_RIGHT:
					movePlayerRight();
					break;
				case KEY_LEFT:
					movePlayerLeft();
					break;
				case ' ':
				case KEY_UP:
					playerMissileShoot();
					break;
				case 'p':
					state = PAUSE;
					sigset_t mask;
					sigaddset(&mask, SIGALRM);
					sigprocmask(SIG_BLOCK, &mask, NULL);
					updateBoard(healthBoard);
					break;
				case 'Q':
					state = QUIT;
					break;
				default:
					break;
			}
			break;
		case PAUSE:
			if(ch == 'p') {
				state = INPUT;	
				sigset_t mask;
				sigaddset(&mask, SIGALRM);
				sigprocmask(SIG_UNBLOCK, &mask, NULL);
				updateBoard(healthBoard);
			}
			break;
		case GAME_OVER: 
			while(ch != 'q')
			{ch = getch();}
			{
				sigset_t mask;
				sigaddset(&mask, SIGALRM);
				sigprocmask(SIG_BLOCK, &mask, NULL); 
			}
			break;
		default :
			break;

	}
}

/* starting display screen will include menu */
void startscreen() {
	int ch;
	WINDOW *startup;
	startup = newwin(FIELD_HEIGHT, FIELD_WIDTH, 0, 0);
	wattrset(startup, COLOR_PAIR(4));
	wprintw(startup, "\n\n\n\n\n\n\n\n");
	wrefresh(startup);
	while(ch != ' ')	
		ch = getch();

}

/* set up sigaction to run function MyThread after FPS seconds */
void setUpTimer() {
	int frequency = FPS + difficulty * 6;
	struct itimerval mytimer;
	struct sigaction myaction;
	mytimer.it_value.tv_sec = 0;
	mytimer.it_value.tv_usec = 1000000 / frequency ;
	mytimer.it_interval.tv_sec = 0;
	mytimer.it_interval.tv_usec = 1000000 / frequency;

	/* this library function generates SIGALRM signal after time corr. to mytimer */
	setitimer(ITIMER_REAL, &mytimer, NULL);
	myaction.sa_handler = &MyThread;
	myaction.sa_flags = SA_RESTART;
	sigaction(SIGALRM, &myaction, NULL);
}

/*show usage to the user */
void usage() {
	printf("Game : Space-Attack\n");
	printf(" Usage :\n");
	printf(" Run only ./project without arguments\n");
	printf(" Use 'SpaceBar' or 'UP-Arrow-Key' to shoot and 'Arrow keys' to move left OR right\n");
	printf(" Use 'p' to pause running game\n");
	printf(" Use shift-q (Q) to quit running game\n");
}

/* main function */
int main(int argc, char *argv[]) {
	int deg, y, x;
	char name[15];
	initscr();
	getmaxyx(stdscr, y, x);
	endwin();
	if(x < 140 || y < 40) {
		printf("Warning : Make Window Full size before running\n");
		return 0;
	}
	if(argc != 1 && strcmp(argv[1], "-h") == 0) {
		usage();
		return 0;
	}

	deg = battleFieldInit();
	if(deg == 1) {
		endwin();
		return 0;}

	/* initialize the attributes and begin curses mode
	 * deg == 0 */
	/* set up function that runs continuously depending on time */
	setUpTimer();
	while(state != GAME_OVER && state != QUIT) {
		takeInput();
	}
	if(state == GAME_OVER) {
		clearArena();
		form(name);
		storeScore(name, score);
		displayHighScores();
	}
	clearArena();
	endwin();
	return 0;
}
