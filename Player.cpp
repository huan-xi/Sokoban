#include "Player.h"
#include <stdio.h>


Player::Player(HTEXTURE tex,int map_side)
{
	this->upAnimation =new hgeAnimation(tex, 3, 1, 0, 0, 55, 80);
	this->map_side = map_side;
	this->speed = 16;
}
void Player::setX(int x) {
	this->x = x;
	sence_x = x*map_side;
}
void Player::setY(int y) {
	this->y = y;
	sence_y = y*map_side;
}

int Player::getX()
{
	return x;
}

int Player::getY()
{
	return y;
}

void Player::setDire(DIRE dire)
{
	this->dire = dire;
}

void Player::Render()//渲染当前动画
{
	switch (dire) {
	case DIRE_UP :
			this->upAnimation->Render(sence_x, sence_y-10);
			break;
	default:
		this->upAnimation->Render(sence_x, sence_y-10);
	}
	
}

void Player::update(int time)
{
	this->upAnimation->Update(time);
}

void Player::move(DIRE dire,Timer *timer,Box *box[],int map[15][10])
{

	if (!isMoving) {
		this->dire = dire;
		this->timer = timer;
		switch (this->dire)
		{
		case DIRE_UP: 
		{
			if (!map[x][y-1] == 2)
			{
			std::thread t(&Player::moveUP, this);  //多线程移动
			t.detach();
			isMoving = true;
			}
			break;
		}
		case DIRE_RIGHT:
		{	
			if (!map[x+1][y] == 2 )
			{
				if (map[x + 1][y] == 3)
					pushBox(box,x+1,y);
				std::thread t(&Player::moveRight, this);
				t.detach();
				isMoving = true;
			}	break;
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



void Player::pushBox(Box *box[], int x, int y) //开始推箱子
{
	for (int i = 0; i < Box::box_count;i++) {
		if (box[i]->x==x&&box[i]->y==y)
		{
			this->box = box[i];
			break;
		}
	}

	this->box->isMoving = true;
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
	sence_y = y*map_side;
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
			if (box)
			{
				box->sence_x=this->sence_x+map_side;
			}
			renderTime = timer->getTime();
		}

	}
	//移动结束
	x++;
	isMoving = false;
	upAnimation->Stop();
	if (box) {
		//箱子移动结束
		this->box->x++;
		this->box->isMoving = false;
		box = NULL;
	}
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
	sence_y = y*map_side;
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
	sence_x = x*map_side;
	isMoving = false;
	upAnimation->Stop();
}
Player::~Player()
{
	delete(upAnimation);
}
