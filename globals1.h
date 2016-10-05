#include <ncurses.h>
#define COLOR 5
#define FIELD_WIDTH 80     //may change
#define FIELD_HEIGHT 24
#define ALIEN_MAXW  36   //define later(27)
#define ALIEN_MAXH 5  //define later(9)
#define PLAYER_WIDTH 7
#define FPS 20
WINDOW *alienGroup;
WINDOW *playerShip;
WINDOW *bunkers;
WINDOW *alienMissile;	
WINDOW *playerMissile;
struct playerShip  {
	int playerMissile;	 //to check missile status
	int playerMissileExist;	 //to check missile status
	int playerX;
	int playerY;
	int playerMissileY;	 //to check missile status
	int playerMissileX;	 //to check missile status
			 //to check player position along x axis
};
struct playerShip player;
int alienX = 0;
int alienY = 0;
int alienMissileY = 0;
int alienMissileX = 0;
int alienMissileExist;	 //to check missile status
int alienGroupBin[5][9] = { 
					{1, 1, 1, 1, 1, 1, 1, 1, 1},
					{2, 2, 2, 2, 2, 2, 2, 2, 2},
					{0, 0, 2, 2, 2, 2, 2, 0, 0},
					{0, 0, 0, 3, 3, 3, 0, 0, 0},
					{0, 0, 0, 0, 3, 0, 0, 0, 0}
};
