#define COLOR 5
#define FIELD_WIDTH 80     //may change
#define FIELD_HEIGHT 24
#define ALIEN_MAXW  36   //define later(27)
#define ALIEN_MAXH 5  //define later(9)
#define PLAYER_WIDTH 7
#define FPS 25

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
int alienGroupBin[5][9] = { 
					{1, 1, 1, 1, 1, 1, 1, 1, 1},
					{2, 2, 2, 2, 2, 2, 2, 2, 2},
					{3, 3, 3, 3, 3, 3, 3, 3, 3},
					{4, 0, 0, 4, 4, 4, 0, 0, 4},
					{1, 1, 1, 1, 5, 1, 1, 1, 1}
};
