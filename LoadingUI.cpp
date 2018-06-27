#include "LoadingUI.h"
#include "Utils.h"


LoadingUI::LoadingUI(float x, float y, hgeSprite *(*sprite_loading))
{
	this->x = x;
	this->y = y;
	this->sprite_loading = sprite_loading;
	this->status = false;
	this->sprite_index = 0;
	updateTime = 0;
}

void LoadingUI::Render()
{
	if(status)
	this->sprite_loading[sprite_index]->Render(x, y);
}

void LoadingUI::Update()
{
	
		status = true;
		if (sprite_index < 5) {
			//Utils::alertInt(sprite_index);
			sprite_index++;
		}
		else {
			sprite_index = 0;
			status = false; //½áÊø
		}
	
}


bool LoadingUI::isLoading()
{
	return status;
}

float LoadingUI::getUpdateTime()
{
	return updateTime;
}

void LoadingUI::setUpdateTime(float time)
{
	this->updateTime = time;
}

LoadingUI::~LoadingUI()
{
}
