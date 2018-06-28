/*
** Haaf's Game Engine 1.8
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** hge_tut01 - Minimal HGE application
*/
 //__vsnprintf，该符号在函数 "public: void __cdecl hgeFont::printf(float,float,int,char const *,...)" (? printf@hgeFont@@QAAXMMHPBDZZ) 中被引用	sokoban	C : \Users\huanzi\Source\Repos\Sokoban\hgehelp.lib(hgefont.obj)	1


#include "hge.h"
#include <hgesprite.h>
#include <hgeanim.h>
#include "Timer.h"
#include "Player.h"
#include "Utils.h"
#include <thread> 
#include"Box.h"
#include <hgefont.h>
#include <hgeguictrls.h>
#include <iostream>
#include "MyButton.h"
#include "LoadingUI.h"
void level_init();
enum Map_TYPE //地图类型枚举
{
	MAP_FLLOR, MAP_PLAYER, MAP_WALL, MAP_BOX, MAP_END
};
enum GameState{ Start, Game,Win,Loading }g_GameState;
//地图
int const map_side = 64;
int const map_height = 8;
int const map_width = 9;
int const map_off_x = 0;
int const map_off_y = 0;
int map[8][9] = {0};
int map_back[200][8][9]; //记录回退地图
int step = 0; //当前步数
HGE *hge = 0;
//人物(24 * 58)
Player *player=NULL;
HTEXTURE tex_players;
DIRE dir;
int player_index = 0; //图片索引
//地板(64 * 64)
hgeSprite *sprite_floor[10];
//墙
hgeSprite *sprite_wall[10];
//箱子
Box *box[10];   
hgeSprite *sprite_box[10];
//终点
hgeSprite *sprite_end_up[10];
hgeSprite *sprite_end_down[10];
//鼠标指针
hgeSprite *sprite_point;
float point_x, point_y;
//全局计时器
float timer;
float updateTime=0; //上次更新时间
//背景
hgeSprite *sprite_backgroud;
hgeSprite *sprite_start;
//人物动画
hgeSprite *sprite_man;
float man_x = 100, man_y = 200;
float man_time=0;
//进度条
HTEXTURE tex_loadings;
hgeSprite *sprite_loading[6];
LoadingUI *loading;
int man_status=0; //上升
//字体
hgeFont *font;
hgeGUIText *text;
//按钮
hgeSprite * btn_start_spr[2];
MyButton *btn_start;
hgeSprite * btn_back_spr[2]; //回退按钮
MyButton *btn_back;
hgeSprite * btn_restart_spr[2]; //从新开始按钮
MyButton *btn_restart;
//开始按钮点击
void start_click() {
	g_GameState = Loading;  //进入加载状态
}
bool isBack = false;  //记录是否是回退状态，如果是关卡初始化使用回退地图
void back_click() {
	isBack = true;
	level_init();
	isBack = false;
}
void restart_click() {
	level_init();
}
//开始游戏
bool btn_statu = 0;
//当前关卡
int level;
void ReadMap(int num) //读取地图
{
	char path[20] = "res/map/";
	char c[20] = "";
	itoa(num, c, 10);
	char c1[10] = ".map";
	strcat(c, c1);
	strcat(path, c);
	FILE *pflie = fopen(path, "rb");
	//文件的写
	fread(&map[0][0], sizeof(int), 8 * 9, pflie);
	fclose(pflie);
}
bool isWin() {
	if (Box::box_count!=0) {
		int i;
		for ( i=0;i<Box::box_count;i++)
		{
			if (!box[i]->getDone())break;
		}
		if (i == Box::box_count) return true;
		else return false;
	}
	return false;
}
void doWin() { //游戏胜利
	//g_GameState = Win;
	level++;
	level_init();
}

bool GameUpdate() {
	if (hge->Input_GetKeyState(HGEK_ESCAPE)) return true;
	if (hge->Input_GetKeyState(HGEK_W))
	{
		player->move(DIRE_UP, &timer, box, map,map_back,&step);
	}
	if (hge->Input_GetKeyState(HGEK_D))
	{
		player->move(DIRE_RIGHT, &timer, box, map, map_back, &step);
	}
	if (hge->Input_GetKeyState(HGEK_S))
	{
		player->move(DIRE_DOWN, &timer, box, map, map_back, &step);
	}
	if (hge->Input_GetKeyState(HGEK_A))
	{
		player->move(DIRE_LEFT, &timer, box, map, map_back, &step);
	}
	if (hge->Input_KeyDown(HGEK_LBUTTON)) {
		btn_restart->keyDown(point_x, point_y, hge->Timer_GetTime());
		btn_back->keyDown(point_x, point_y, hge->Timer_GetTime());
	}
	if (isWin()) doWin();
	return false;
}
bool StartUpdate() {
	if (hge->Timer_GetTime()-man_time>0.2) //人物上下移动特效
	{
		if (man_y == 70) man_status = 1;
		if (man_y == 200) man_status = 0;
		man_status?man_y++:man_y--;
	}
	if (hge->Input_KeyDown(HGEK_LBUTTON)) {
		btn_start->keyDown(point_x,point_y,hge->Timer_GetTime());
	}
	return false;
}
bool LoadingUpdate() {
	
	if (hge->Timer_GetTime() - loading->getUpdateTime() > 0.7) {
		loading->Update();
		if (!loading->isLoading()) //加载完毕
			g_GameState = Game;
		loading->setUpdateTime(hge->Timer_GetTime());
	}
	
	return false;
}
bool FrameFunc()
{
	timer=hge->Timer_GetTime();//每次调用记录时间，让移动线程知道时间
	hge->Input_GetMousePos(&point_x, &point_y);
	switch (g_GameState)
	{
	case Start:
		return StartUpdate();
	case Game:
		return GameUpdate();
	case Loading:
		return LoadingUpdate();
	}
	return false;
}
//开始界面渲染
void startRender() {
 	sprite_start->Render(0, 0);
 	sprite_man->Render(man_x,man_y);
	btn_start->Render();
}
//渲染地图
void RenderMap() {
	for (int i = 0; i < map_height; i++)
		for (int j = 0; j < map_width; j++)
		{
			float x = j * map_side + map_off_x, y = i* map_side + map_off_y;
			map[i][j] == 2 ? sprite_wall[0]->Render(x,y ) : sprite_floor[2]->Render(x, y);
			if (map[i][j]==4) sprite_end_up[0]->Render(x, y);
			switch (map[i][j])
			{
			case 0:
				sprite_floor[2]->Render(x, y);
				break;
			case 2:
				sprite_wall[0]->Render(x, y);
				break;
			case 4:
				sprite_floor[2]->Render(x, y);
				sprite_end_up[0]->Render(x, y);
				break;
			}
		}
}
void GameRender(){
	switch (g_GameState)
	{
	case Start:
		startRender();
		break;
	case Loading:
		startRender();
		loading->Render();
		break;
	case Game:
		//渲染地图
		RenderMap();
		//渲染箱子
		for (int i=0;i<Box::box_count;i++)
		{
			box[i]->Render(map_off_x,map_off_y);
		}
		//渲染人物
		player->Render(map_off_x,map_off_y);
		//渲染按钮
		btn_restart->Render();
		btn_back->Render();
		break;
	}
}
bool RenderFunc()
{
	
	hge->Gfx_BeginScene();
	// Clear screen with black color
	hge->Gfx_Clear(100);
	
	GameRender();
	//渲染鼠标.
	sprite_point->Render(point_x,point_y);
	hge->Gfx_EndScene();
	return false;
}
void level_init() {  //关卡初始化
	Box::clear();
	//初始化地图
	if (step == 0) 
		for (int i = 0; i < map_height; i++) //记录第零步
			for (int j = 0; j < map_width; j++)
				map_back[step][i][j]= map[i][j];
	if (isBack) {
		if (step - 1 >= 0) {
			step--;
		for (int i = 0; i < map_height; i++)
			for (int j = 0; j < map_width; j++)
			{
				map[i][j] = map_back[step][i][j];
			}
		}
	}
	else  ReadMap(level);    //不是回退就读关卡地图是就读历史地图
	
	//构建对象
	Box::box_count = 0;
	for (int i = 0; i < map_height; i++)
		for (int j = 0; j < map_width; j++)
		{
				switch (map[i][j])
				{
				case MAP_PLAYER: //构建玩家	
					if (player != NULL) dir = player->getDir();
					player = new Player(tex_players, map_side);
					player->setDire(dir);         //关卡开始时玩家的方向
					player->setX(j);
					player->setY(i);
					map[i][j] = 0; //不用记录玩家位置
					break;
				case MAP_BOX: //构造箱子
					int count = Box::box_count;
					box[count] = new Box(sprite_box[0], sprite_box[1], sprite_box[2], map_side);
					box[Box::box_count - 1]->setX(j);
					box[Box::box_count - 1]->setY(i);
					break;
				}
		}
}
void init() { //初始化游戏系统

	//加载资源
	font = new hgeFont("res/font/font1.fnt");
	text = new hgeGUIText(0,10,10,10,10,font);
	font->SetColor(100);
	font->SetScale(0.2);
	tex_players = hge->Texture_Load("res/image/players.png");
	sprite_floor[0] = new hgeSprite(hge->Texture_Load("res/image/GroundGravel_Concrete.png"), 0, 0, 64, 64);
	sprite_floor[1] = new hgeSprite(hge->Texture_Load("res/image/GroundGravel_Dirt.png"), 0, 0, 64, 64);
	sprite_floor[2] = new hgeSprite(hge->Texture_Load("res/image/GroundGravel_Grass.png"), 0, 0, 64, 64);
	sprite_floor[3] = new hgeSprite(hge->Texture_Load("res/image/GroundGravel_Sand.png"), 0, 0, 64, 64);

	sprite_box[0] = new hgeSprite(hge->Texture_Load("res/image/Crate_Beige.png"), 0, 0, 64, 64);
	sprite_box[1] = new hgeSprite(hge->Texture_Load("res/image/CrateDark_Beige.png"), 0, 0, 64, 64);
	sprite_box[2] = new hgeSprite(hge->Texture_Load("res/image/Crate_Black.png"), 0, 0, 64, 64);
	sprite_box[4] = new hgeSprite(hge->Texture_Load("res/image/Crate_Blue.png"), 0, 0, 64, 64);
	sprite_box[5] = new hgeSprite(hge->Texture_Load("res/image/Crate_Brown.png"), 0, 0, 64, 64);

	sprite_wall[0] = new hgeSprite(hge->Texture_Load("res/image/Wall_Brown.png"), 0, 0, 64, 64);

	sprite_end_up[0] = new hgeSprite(hge->Texture_Load("res/image/EndPoint_Blue.png"), 0, 0, 64, 64);
	sprite_point = new hgeSprite(hge->Texture_Load("res/image/cur.png"), 0, 0, 32, 32);
	
	sprite_start = new hgeSprite(hge->Texture_Load("res/image/start.jpg"), 0, 0,768, 512);
	sprite_man = new hgeSprite(hge->Texture_Load("res/image/man.png"), 0, 0, 82, 130);
	//按钮加载
	btn_start_spr[0] = new hgeSprite(hge->Texture_Load("res/image/Wall_Brown.png"), 0, 0, 30, 60);
	btn_start_spr[1] = new hgeSprite(hge->Texture_Load(""), 0, 0, 30, 60);
	btn_start = new MyButton(200,450,btn_start_spr[0],btn_start_spr[1],start_click);
	
	btn_restart= new MyButton(600, 450, btn_start_spr[0], btn_start_spr[1], restart_click);
	btn_back = new MyButton(700, 450, btn_start_spr[0], btn_start_spr[1], back_click);

	sprite_box[3] = new hgeSprite(hge->Texture_Load("res/image/Crate_Blue.png"), 0, 0, 64, 64);
	tex_loadings = hge->Texture_Load("res/image/loading.png");
	sprite_loading[0] = new hgeSprite(tex_loadings, 45,40, 70, 70);
	sprite_loading[1] = new hgeSprite(tex_loadings, 45+70+2, 40, 70, 70);
	sprite_loading[2] = new hgeSprite(tex_loadings, 45, 40+70+5, 70, 70);
	sprite_loading[3] = new hgeSprite(tex_loadings, 45 +70 + 2, 40 + 70 + 5, 70, 70);
	sprite_loading[4] = new hgeSprite(tex_loadings, 45, 40 +70*2+12, 70, 70);
	sprite_loading[5] = new hgeSprite(tex_loadings, 45 +70+2, 40+70 * 2 + 15, 70, 70);
	loading = new LoadingUI(280,250,sprite_loading);
	g_GameState=Start;
	//读取关卡
	level = 1;
	level_init();
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
	hge->System_SetState(HGE_SCREENWIDTH, (map_width+3)*map_side);
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