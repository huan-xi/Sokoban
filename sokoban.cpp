/*
** Haaf's Game Engine 1.8
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** hge_tut01 - Minimal HGE application
*/


#include "hge.h"
#include <hgesprite.h>
#include <hgeanim.h>
#include "Timer.h"
#include "Player.h"
#include "Utils.h"
#include <thread> 
//地图
int const map_side = 64;
int const map_height = 10;
int const map_width = 15;
int map[15][10] = { 0 };
HGE *hge = 0;
//纹理资源
HTEXTURE tex;
hgeSprite *sprite;
//人物(24 * 58)
Player *player;
hgeSprite *sprite_player[10];
HTEXTURE tex_players;
hgeAnimation *player_animation;
int player_index = 0; //图片索引
//地板(64 * 64)
hgeSprite *sprite_floor[10];
//墙
hgeSprite *sprite_wall[10];
//箱子
hgeSprite *sprite_box[10];
//终点
hgeSprite *sprite_end_up[10];
hgeSprite *sprite_end_down[10];
//鼠标指针
hgeSprite *sprite_point;
float point_x, point_y;

//全局计时器
Timer timer;
// This function will be called by HGE once per frame.
// Put your game loop code here. In this example we
// just check whether ESC key has been pressed.
int x = 5, y = 5;
bool FrameFunc()
{


	hge->Input_GetMousePos(&point_x,&point_y);
	if (hge->Input_GetKeyState(HGEK_ESCAPE)) return true;
	if (hge->Input_GetKeyState(HGEK_W))
	{
		player->move(DIRE_UP,&timer);

	}
	if (hge->Input_GetKeyState(HGEK_D))
	{
		
	}
	if (hge->Input_GetKeyState(HGEK_S))
	{

	}
	if (hge->Input_GetKeyState(HGEK_A))
	{

	}

	player->update(1);
	return false;
}
// This function will be called by HGE when
// the application window should be redrawn.
// Put your rendering code here.
bool RenderFunc()
{
	timer.run();//记录
	hge->Gfx_BeginScene();
	// Clear screen with black color
	hge->Gfx_Clear(0);
	
	for (int i = 0; i < map_width; i++)
		for (int j = 0; j < map_height; j++)
		{
			sprite_floor[2]->Render(i * map_side, j* map_side);
			switch (map[i][j])
			{
			case 0: //不画
				break;
			case 1: //画人物
				sprite_player[player_index]->Render(i * map_side + 10, j* map_side);
				break;
			case 2://画墙
				break;
			case 3://画箱子
				sprite_box[0]->Render(i * map_side, j* map_side);
				break;
			default:
				break;
			}

		}
	player->Render();
	player_animation->Render(100, 100);

	//渲染鼠标.
	sprite_point->Render(point_x,point_y);
	hge->Gfx_EndScene();

	// RenderFunc should always return false
	return false;
}
void init() {
	//初始化地图
	map[5][5] = 1;
	map[5][6] = 3;
	map[5][4] = 3;
	map[4][6] = 3;
	map[4][4] = 3;
	//加载资源
	tex = hge->Texture_Load("res/image/bj.jpg");
	tex_players = hge->Texture_Load("res/image/players.png");

	//构造玩家
	player=new Player(tex_players,map_side);
	player->setDire(DIRE_UP);
	player->setX(8);
	player->setY(8);

	player_animation = new hgeAnimation(tex_players, 3, 10,0, 0,55, 80);
	sprite = new hgeSprite(tex, 0, 0, 1000, 600);
	sprite_player[0] = new hgeSprite(hge->Texture_Load("res/image/Character2.png"), 0, 0, 42, 58);//右
	sprite_player[1] = new hgeSprite(hge->Texture_Load("res/image/Character3.png"), 0, 0, 42, 58);
	sprite_player[2] = new hgeSprite(hge->Texture_Load("res/image/Character4.png"), 0, 0, 42, 58);//下
	sprite_player[3] = new hgeSprite(hge->Texture_Load("res/image/Character5.png"), 0, 0, 42, 58);
	sprite_player[4] = new hgeSprite(hge->Texture_Load("res/image/Character6.png"), 0, 0, 42, 58);
	sprite_player[5] = new hgeSprite(hge->Texture_Load("res/image/Character7.png"), 0, 0, 42, 58);//上
	sprite_player[6] = new hgeSprite(hge->Texture_Load("res/image/Character8.png"), 0, 0, 42, 58);
	sprite_player[7] = new hgeSprite(hge->Texture_Load("res/image/Character9.png"), 0, 0, 42, 58);
	sprite_player[8] = new hgeSprite(hge->Texture_Load("res/image/Character10.png"), 0, 0, 42, 58);//左
	sprite_player[9] = new hgeSprite(hge->Texture_Load("res/image/Character11.png"), 0, 0, 42, 58);
	sprite_floor[0] = new hgeSprite(hge->Texture_Load("res/image/GroundGravel_Concrete.png"), 0, 0, 64, 64);
	sprite_floor[1] = new hgeSprite(hge->Texture_Load("res/image/GroundGravel_Dirt.png"), 0, 0, 64, 64);
	sprite_floor[2] = new hgeSprite(hge->Texture_Load("res/image/GroundGravel_Grass.png"), 0, 0, 64, 64);
	sprite_floor[3] = new hgeSprite(hge->Texture_Load("res/image/GroundGravel_Sand.png"), 0, 0, 64, 64);

	sprite_box[0] = new hgeSprite(hge->Texture_Load("res/image/Crate_Blue.png"), 0, 0, 64, 64);

	sprite_point = new hgeSprite(hge->Texture_Load("res/image/cur.png"), 0, 0, 32, 32);
}
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

	hge = hgeCreate(HGE_VERSION);

	// Set our frame function
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
	// Set the window title
	hge->System_SetState(HGE_TITLE, "推箱子游戏");

	// Run in windowed mode
	// Default window size is 800x600
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_SCREENHEIGHT, map_height*map_side);
	hge->System_SetState(HGE_SCREENWIDTH, map_width*map_side);
	hge->System_SetState(HGE_FPS, 60); //执行60次为一秒
	 // 是否使用声音
	hge->System_SetState(HGE_USESOUND, false);
	if (hge->System_Initiate())
	{
		init();
		//启动hge引擎(不停的调用更新函数和渲染函数,直到更新函数返回true)
		hge->System_Start();
	}
	else
	{
		// If HGE initialization failed show error message
		MessageBox(NULL, hge->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
	}



	//关闭引擎
	hge->System_Shutdown();
	//释放指针
	hge->Release();

	return 0;
}