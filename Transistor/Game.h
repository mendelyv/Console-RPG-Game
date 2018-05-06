/*
File Name : Game.h
Function : Game Element
Updata time : 2017 11 14
*/

#ifndef GAME_H
#define GAME_H

//地图名字
enum MapName
{
	MN_None,
	MN_Map1,
	MN_Map2,
	MN_Map3,
	MN_Map4,
	MN_Shop,
	MN_Map5,
	MN_Boss,
};

//开始界面玩家选择
enum PlayerChoose
{
	BeginGame = 26,
	LoadGame,//27
	GameExplain,//28
	Exit//29
};

//地图元素
enum MapElement
{
	None=-1,//地图中的空缺
	Road=0,//											0
	Border,//◇					                        1
	Roof_Red,//屋顶（红）■						2
	RoofTriangle1,//◤									3
	RoofTriangle2,//◥									4
	RoofTriangle3,//◣									5
	RoofTriangle4,//◢									6 
	Tree,//树												7
	Grass,//草												8
	Water,//≈												9
	Window,//田											10 
	Fence,//栅栏   ▓									11
	Body,//初始导向的尸体							12
	Wall,//建筑外墙										13
	Roof_Blue,//屋顶（蓝）							14
	Roof_White,//屋顶（白）						15
	Weapon_Person,//卖武器的					16
	Corselet_Person,//卖防具的					17
	Medicine_Person,//卖药的						18

	//地图传送点
	Map1ToMap2=100,
	
	Map2ToMap1,//101
	Map2ToMap3,
	Map2ToShop,
	ShopToMap2,

	Map3ToMap2,//105
	Map3ToMap4,

	Map4ToMap5,//107
	Map4ToMap3,

	Map5ToMap4,//109
	Map5ToBoss,

	BossToMap5,//111
};

//道具种类
enum ItemType
{
	IN_None=-1,
	IN_Medicine = 0,		//药物
	IN_Weapon,				//武器
	IN_Corselet,				//防具
	IN_Shoe,					//鞋子
	IN_Decoration			//饰品
};

//怪物种类
enum MonsterType
{
	MT_Process = 50,		//普通怪
	MT_Camerata,			//精英怪
	MT_Boss,					//BOSS
};

//玩家战斗中的选择
enum FightChoose
{
	FC_Atack = 3,			//攻击
	FC_Skill = 5,				//技能
	FC_Item = 7,				//背包
	FC_Run = 9,				//逃跑
};

//控制台特殊点
enum SpecialPoint
{
	//玩家血条打印坐标
	SP_PlayerTubeX = 4,
	SP_PlayerTubeY = 50,

	//怪物血条打印坐标
	SP_MonsterTubeX = 4,
	SP_MonsterTubeY = 5,

	//战斗中  背包的打印位置
	SP_FightBagPrintX = 12,
	SP_FightBagPrintY = 37,

	//角色打印名字光标坐标
	SP_RnamePrintX = 3,
	SP_RnamePrintY = 3,

	//怪物打印名字光标坐标
	SP_MnamePrintX = 3,
	SP_MnamePrintY = 48,
};

//按ESC玩家的选项
enum ESCchoose
{
	E_Continue=16,		//继续游戏
	E_Save,						//保存游戏
	E_Menu,					//回主选单
	E_Exit,						//退出游戏
};
#endif