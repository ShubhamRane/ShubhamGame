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

	
}player;

int alienX = 0;
int alienY = 0;
int alienMissileY = 0;
int alienMissileX = 0;
int alienMissileExist;
int alienGroupBin[5][9] = { 
					{1, 1, 1, 1, 1, 1, 1, 1, 1},
					{2, 2, 2, 2, 2, 2, 2, 2, 2},
					{0, 0, 3, 3, 3, 3, 3, 0, 0},
					{0, 0, 0, 4, 4, 4, 0, 0, 0},
					{0, 0, 0, 0, 5, 0, 0, 0, 0}
};
