#include <hgeanim.h>
#include <hgesprite.h>
#pragma once
enum DIRE
{
	DIRE_UP, DIRE_RIGHT, DIRE_DOWN, DIRE_LEFT,
};
class Player 
{
private:
	hgeAnimation *upAnimation;
	hgeAnimation *nowAnimation; //当前动画
	int x, y,dire;
public:
	Player(HTEXTURE tex);
	void setX(int x);
	void setY(int y);
	void setDire(DIRE dire);
	void Render(int map_side); //渲染玩家
	void moveUP(){
		this->y--;
	}
	~Player();
};

