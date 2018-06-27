#include <hgeanim.h>
#include <hgesprite.h>
#include <thread>
#include "Box.h"
#include "Timer.h"
#include "Utils.h"
#pragma once
enum DIRE
{
	DIRE_UP, DIRE_RIGHT, DIRE_DOWN, DIRE_LEFT,
};
class Player 
{
private:
	hgeAnimation *upAnimation;
	int map_side;//地图坐标边长
	int x, y;  //地图坐标
	float sence_x, sence_y;//场景坐标
	int speed; //移动速度
	int dire;//当前方向
	float renderTime = 0; //上次渲染时间
	float updateTime = 0; //上次更新动画时间
	float boxStopTime; //箱子停止时间
	float *timer;
	bool isMoving = 0;
	Box *box=NULL;
	int (*map)[15];
	void moveUP();
	void moveRight();
	void moveDown();
	void moveLeft();
public:
	Player(HTEXTURE tex, int map_side);
	void setX(int x);
	void setY(int y);
	int getX();
	int getY();
	void setDire(DIRE dire);
	void Render(float,float); //渲染玩家
	void update(int);
	void move(DIRE dire,float *timer, Box *box[],int map[10][15]);
	void findBox(Box * box[], int x, int y);
	void pushBox(Box *box[],int x,int y);
	void stopBox(Box * box[], int x, int y);
	void stopBoxThread();
	~Player();
};

