/*
** Haaf's Game Engine 1.8
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** hge_tut01 - Minimal HGE application
*/


#include "hge.h"
#include <hgesprite.h>
#include<hgeParticle.h>
//粒子
hgeParticleSystem *psi;

//地图
int const map_side= 64;
int const map_height = 10;
int const map_width = 15;
int map[15][10] = { 0 };
HGE *hge = 0;
//纹理资源
HTEXTURE tex;
hgeSprite *sprite;
//人物(24 * 58)
hgeSprite *sprite_player[10];
//地板(64 * 64)
hgeSprite *sprite_floor[10];
//墙
hgeSprite *sprite_wall[10];
//箱子
hgeSprite *sprite_box[10];
//终点
hgeSprite *sprite_end_up[10];
hgeSprite *sprite_end_down[10];
int time = 0; //时间
int times = 0; //时间记速器
int oldTime = 0;
// This function will be called by HGE once per frame.
// Put your game loop code here. In this example we
// just check whether ESC key has been pressed.
int x=5, y=5;
bool FrameFunc()
{
	// By returning "true" we tell HGE
	// to stop running the application.
	if (hge->Input_GetKeyState(HGEK_ESCAPE)) return true;
	if (hge->Input_GetKeyState(HGEK_W))
	{
		if (time-oldTime>1)
		{
			map[x][y] = 0;
			y--;
			map[x][y] = 1;
			oldTime = time;
		}
		
	}
	if (hge->Input_GetKeyState(HGEK_D))
	{
		if (time - oldTime>1)
		{
			map[x][y] = 0;
			x++;
			map[x][y] = 1;
			oldTime = time;
		}

	}
	// Continue execution
	return false;
}
// This function will be called by HGE when
// the application window should be redrawn.
// Put your rendering code here.
bool RenderFunc()
{
	times++;
	if (times>=10) //100ms
	{
		time++;
		times = 0;
	}
	


	// Begin rendering quads.
	// This function must be called
	// before any actual rendering.
	hge->Gfx_BeginScene();
	// Clear screen with black color
	hge->Gfx_Clear(0);

	//sprite_floor[0]->Render(14*map_side,9*map_side);
	for (int i=0;i<map_width;i++)
		for (int j=0;j<map_height;j++)
		{
			sprite_floor[2]->Render(i * map_side, j* map_side);
			switch (map[i][j])
			{
			case 0: //不画
				break;
			case 1: //画人物
				sprite_player[0]->Render(i * map_side+10, j* map_side);
				break;
			case 2://画墙
				break;
			case 3://画箱子
				sprite_box[0]->Render(i * map_side, j* map_side);
				break;
			default:
				
				sprite_player[0]->Render(i * map_side, j* map_side);
				break;
			}
			
		}

	// End rendering and update the screen
	hge->Gfx_EndScene();

	// RenderFunc should always return false
	return FrameFunc();
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// Here we use global pointer to HGE interface.
	// Instead you may use hgeCreate() every
	// time you need access to HGE. Just be sure to
	// have a corresponding hge->Release()
	// for each call to hgeCreate()
	hge = hgeCreate(HGE_VERSION);

	// Set our frame function
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_FRAMEFUNC, RenderFunc);
	// Set the window title
	hge->System_SetState(HGE_TITLE, "推箱子游戏");
	
	// Run in windowed mode
	// Default window size is 800x600
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_SCREENHEIGHT,map_height*map_side);
	hge->System_SetState(HGE_SCREENWIDTH, map_width*map_side);
	hge->System_SetState(HGE_FPS,60); //执行60次为一秒
	
	if(hge->System_Initiate())
	{
		//加载资源
		tex = hge->Texture_Load("res/image/bj.jpg");
		sprite=new hgeSprite(tex,0,0,1000,600);
		map[5][5]=1;
		map[5][6] = 3;
		map[5][4] = 3;
		map[4][6] = 3;
		map[4][4] = 3;
		sprite_player[0] = new hgeSprite(hge->Texture_Load("res/image/Character2.png"), 0, 0, 42, 58);
		psi = new hgeParticleSystem("psi/test.psi", sprite_player[0]);
		int nSprite = ((DWORD)psi->sprite & 0xFFFF);
		int blend = ((DWORD)psi->sprite >> 16);
		ps->FireAt(100, 100);
		sprite_floor[0] = new hgeSprite(hge->Texture_Load("res/image/GroundGravel_Concrete.png"), 0, 0, 64, 64);
		sprite_floor[1] = new hgeSprite(hge->Texture_Load("res/image/GroundGravel_Dirt.png"), 0, 0, 64, 64);
		sprite_floor[2] = new hgeSprite(hge->Texture_Load("res/image/GroundGravel_Grass.png"), 0, 0, 64, 64);
		sprite_floor[3] = new hgeSprite(hge->Texture_Load("res/image/GroundGravel_Sand.png"), 0, 0, 64, 64);
		sprite_box[0] = new hgeSprite(hge->Texture_Load("res/image/Crate_Blue.png"), 0, 0, 64, 64);
		// Starts running FrameFunc().
		// Note that the execution "stops" here
		// until "true" is returned from FrameFunc().
		hge->System_Start();
	}
	else
	{	
		// If HGE initialization failed show error message
		MessageBox(NULL, hge->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
	}

	// Now ESC has been pressed or the user
	// has closed the window by other means.

	// Restore video mode and free
	// all allocated resources
	hge->System_Shutdown();

	// Release the HGE interface.
	// If there are no more references,
	// the HGE object will be deleted.
	hge->Release();

	return 0;
}
