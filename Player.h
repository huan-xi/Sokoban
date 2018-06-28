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
	hgeSprite *rightAnimation[4];
	hgeSprite *upAnimation[4];
	hgeSprite *downAnimation[4];
	hgeSprite *leftAnimation[4];
	int spr_index;//当前状态精灵索引
	int map_side;//地图坐标边长
	int x, y;  //地图坐标
	float sence_x, sence_y;//场景坐标
	int speed; //移动速度
	DIRE dire;//当前方向
	float renderTime = 0; //上次渲染时间
	float updateTime = 0; //上次更新动画时间
	float boxStopTime; //箱子停止时间
	float *timer;
	bool isMoving = 0;
	Box *box=NULL;
	int (*map)[9];
	int (*map_back)[8][9]; //记录历史步数指针
	int *step;
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
	void move(DIRE dire,float *timer, Box *box[],int map[8][9], int map_back[][8][9], int *step);
	void findBox(Box * box[], int x, int y);
	void pushBox(Box *box[],int x,int y);
	void stopBox(Box * box[], int x, int y);
	void stopBoxThread();
	void recodeMap();
	DIRE getDir();
	~Player();
};

