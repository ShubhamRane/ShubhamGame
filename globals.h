#define COLOR 5
#define FIELD_WIDTH 80     //may change
#define FIELD_HEIGHT 24
#define ALIEN_MAXW  36   //define later(27)
#define ALIEN_MAXH 5  //define later(9)
#define PLAYER_WIDTH 7
#define FPS 5

extern WINDOW *alienGroup;
extern WINDOW *playerShip;
extern WINDOW *bunkers;
extern WINDOW *alienMissile;	
extern WINDOW *playerMissile;
extern WINDOW *healthBoard;

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
extern int alienX;
extern int alienY;
extern int alienMissileY;
extern int alienMissileX;
extern int alienMissileExist;	 //to check missile status
extern int alienGroupBin[5][9];
