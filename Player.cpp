#include "Player.h"
#include <stdio.h>


Player::Player(HTEXTURE tex)
{
	this->upAnimation =new hgeAnimation(tex, 3, 10, 0, 0, 55, 80);
	this->upAnimation->Play();
}
void Player::setX(int x) {
	this->x = x;
}
void Player::setY(int y) {
	this->y = y;
}

void Player::setDire(DIRE dire)
{
	this->dire = dire;
}

void Player::Render(int map_side)//äÖÈ¾µ±Ç°¶¯»­
{
	switch (dire) {
	case DIRE_UP :
			this->upAnimation->Render(this->x*map_side, this->y*map_side); 
			break;
	}
	
}


Player::~Player()
{
	delete(upAnimation);
}
