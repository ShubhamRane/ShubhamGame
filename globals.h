
#define FIELD_WIDTH 80     //may change
#define FIELD_HEIGHT 24
#define ALIEN_MAXW  45   //define later(27)
#define ALIEN_MAXH 9  //define later(9)
#define PLAYER_WIDTH 7
#define FPS 3

WINDOW *alienGroup;
WINDOW *playerShip;
WINDOW *bunkers;
WINDOW *alienMissile;
WINDOW *playerMissile;

struct playerShip  {
	int playerMissileExist;	 //to check missile status
	int playerX;
	int playerY;
	int playerMissileX;
	int playerMissileY;
};
struct playerShip player;
int alienX = 0;
int alienMissileExist = 0;
int alienGroupBin[5][9] = { 
					{1, 1, 1, 1, 1, 1, 1, 1, 1},
					{2, 2, 2, 2, 2, 2, 2, 2, 2},
					{2, 2, 2, 2, 2, 2, 2, 2, 2},
					{3, 3, 3, 3, 3, 3, 3, 3, 3},
					{3, 3, 3, 3, 3, 3, 3, 3, 3},
};

