#include <hgesprite.h>
#pragma once
class Box //箱子类
{
	friend class Player;
private:
	hgeSprite *sprite; //箱子图片
	hgeSprite *sprite_moving; //移动时图片
	int map_side;//地图坐标边长
	int x, y;  //地图坐标
	float sence_x, sence_y;//场景坐标
	bool isMoving = 0;
public:
	static int box_count;       //记录箱子个数
	static void clear();
	void setX(int x);
	void setY(int y);
	int getX();
	int getY();
	Box(hgeSprite *sprite, hgeSprite *sprite_moving, int map_side);
	void Render(); //渲染箱子
	~Box();
};

