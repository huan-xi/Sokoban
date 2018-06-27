#include "MyButton.h"



MyButton::MyButton(float x,float y,hgeSprite *sprite_up, hgeSprite *sprite_down, void click())
{
	this->click = click;
	this->sprite_down = sprite_down;
	this->sprite_up = sprite_up;
	this->x = x;
	this->y = y;
	this->status = false;
}


void MyButton::keyDown(float point_x,float point_y,float time)
{
	hgeRect rect;
	sprite_up->GetBoundingBox(this->x,this->y, &rect);
	if (rect.TestPoint(point_x,point_y)) //判断一个点是否在矩形区域中
	{
		status = true;
		this->click();
		std::thread t(&MyButton::stopThread, this);  //启动线程通知结束
		t.detach();
	}
}
void MyButton::stopThread() {
	Sleep(100);
	this->status = false;
}
void MyButton::Render()
{
	this->status ? this->sprite_down->Render(x, y) :this->sprite_up->Render(x, y);
}

MyButton::~MyButton()
{
}
