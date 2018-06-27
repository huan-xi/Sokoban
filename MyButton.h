#pragma once
#include <hgesprite.h>
#include <thread>
#include "Timer.h"
class MyButton
{
private:
	bool status; //真为按下
	float x, y;
	hgeSprite *sprite_up;
	hgeSprite *sprite_down;
	void(*click)();
	float updateTime;
public:
	MyButton(float x, float y, hgeSprite *sprite_up, hgeSprite *sprite_down,void click());
	void keyDown(float point_x, float point_y,float time);
	void stopThread(); //通知按下特效结束
	void Render();
	// 通知GUI鼠标右键点击
	~MyButton();
};

