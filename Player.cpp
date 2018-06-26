#include "Player.h"
#include <stdio.h>


Player::Player(HTEXTURE tex,int map_side)
{
	this->upAnimation =new hgeAnimation(tex, 3, 1, 0, 0, 55, 80);
	this->map_side = map_side;
	this->speed = 20;
}
void Player::setX(int x) {
	this->x = x;
	sence_x = x*map_side;
}
void Player::setY(int y) {
	this->y = y;
	sence_y = y*map_side;
}

void Player::setDire(DIRE dire)
{
	this->dire = dire;
}

void Player::Render()//渲染当前动画
{
	switch (dire) {
	case DIRE_UP :
			this->upAnimation->Render(sence_x, sence_y);
			break;
	}
	
}

void Player::update(int time)
{
	this->upAnimation->Update(time);
}

void Player::move(DIRE dire,Timer *timer)
{
	this->dire = dire;
	this->timer = timer;
	if (!isMoving) {
		switch (this->dire)
		{
		case DIRE_UP: 
		{
			std::thread t(&Player::moveUP, this);  //多线程移动
			t.detach();
			isMoving = true;
			break;
		}
		case DIRE_RIGHT:
		{	std::thread t(&Player::moveRight, this);
		t.detach();
		isMoving = true;
		break;
		}
		case DIRE_DOWN:
		{
			std::thread t(&Player::moveDown, this);
			t.detach();
			isMoving = true;
			break;
		}
		case DIRE_LEFT:
			std::thread t(&Player::moveLeft, this);
			t.detach();
			isMoving = true;
			break;
		}
	}
	
}


void Player::moveUP()
{
	upAnimation->Play();
//开始移动
	while (sence_y > (y-1)*map_side)
	{
		if (timer->getTime() - renderTime > 1) {
			this->sence_y -= speed;
			renderTime = timer->getTime();
		}
		
	}
	//移动结束
	y--;
	isMoving = false;
	upAnimation->Stop();
}

void Player::moveRight()
{
	upAnimation->Play();
	//开始移动
	while (sence_x < (x+ 1)*map_side)
	{
		if (timer->getTime() - renderTime > 1) {
			this->sence_x += speed;
			renderTime = timer->getTime();
		}

	}
	//移动结束
	x++;
	isMoving = false;
	upAnimation->Stop();
}

void Player::moveDown()
{
	upAnimation->Play();
	//开始移动
	while (sence_y < (y + 1)*map_side)
	{
		if (timer->getTime() - renderTime > 1) {
			this->sence_y += speed;
			renderTime = timer->getTime();
		}

	}
	//移动结束
	y++;
	isMoving = false;
	upAnimation->Stop();
}
void Player::moveLeft()
{
	upAnimation->Play();
	//开始移动
	while (sence_x > (x - 1)*map_side)
	{
		if (timer->getTime() - renderTime > 1) {
			this->sence_x -= speed;
			renderTime = timer->getTime();
		}

	}
	//移动结束
	x--;
	isMoving = false;
	upAnimation->Stop();
}
Player::~Player()
{
	delete(upAnimation);
}
