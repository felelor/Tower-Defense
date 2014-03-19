//Nathan Kowaleski
//Enemy .h file

#include "SDL/SDL.h"

class Enemy
{
private:
	int x;//x position
	int y;//y position
	int xv;//x velocity
	int yv;//y velocity
	int speed;
	int maxhealth;
	int currenthealth;

public:
	Enemy();
	void direction(char);
	void move();
	void show();
	void damage(int);
	int getx();
	int gety();
	int getxv();
	int getxy();
	int getSpeed();
	int getmaxhealth();
	int get currenthealth();
	void setx(int);
	void sety(int);
	void setxv(int);
	void setxy(int);
	void setSpeed(int);
	void setmaxhealth(int);
	void setcurrenthealth(int);

};
