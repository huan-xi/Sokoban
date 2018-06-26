#include "Box.h"
#include "Utils.h"


Box::Box(hgeSprite *sprite, hgeSprite *sprite_moving,int map_side)
{
	this->map_side = map_side;
	this->sprite = sprite;
	this->sprite_moving = sprite_moving;
}
void Box::setX(int x) {
	this->x = x;
	sence_x = x*map_side;
}
void Box::setY(int y) {
	this->y = y;
	sence_y = y*map_side;
}

void Box::Render()
{
	
	if (isMoving)
		this->sprite_moving->Render(sence_x, sence_y);
	else
		this->sprite->Render(sence_x,sence_y);
}

Box::~Box()
{
}

int Box::getX()
{
	return x;
}

int Box::getY()
{
	return y;
}
