#pragma once
#include <hgesprite.h>
#include <thread>
#include "Timer.h"
class LoadingUI
{
private:
	bool status; //真为正在加载
	float x, y;
	hgeSprite *(*sprite_loading);
	int sprite_index;
	float updateTime;
public:
	LoadingUI(float x,float y, hgeSprite *(*sprite_loading));
	void Render();
	void Update();
	bool isLoading();
	float getUpdateTime();
	void setUpdateTime(float time);
	~LoadingUI();
};

