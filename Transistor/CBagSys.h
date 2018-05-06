/*
File Name : CBagSys.h
Function : Bag Manage Singleton
Updata time : 2017 11 11
*/

#ifndef CBAGSYS_H
#define CBAGSYS_H
#include "CSingleton.h"
#include "Game.h"
#include "CItem.h"
#include "comment.h"
#include "Mydefine.h"
#include "CRole.h"

class CBagSys :public CSingleton < CBagSys >
{
public:
	void init(char *_FileName);//游戏所有道具载入
	void showItem(int x,int y,ItemType _type);//展示商品    参数为控制台光标坐标和商品种类枚举
	void ctrlOfShop(int x, int y, ItemType _type);//控制（在商店界面）    参数为光标初始位置
	
	map<int, CItem> m_ItemContainer;
protected:
	//map<int, CItem> m_ItemContainer;
	GET_SET(CRole*, m_Player, Player);
	void printItemInfo(int x, int y, const map<int, CItem>::iterator _iter);//输出物品详细信息     参数为光标初始位置和迭代器
	void cleanItemInfo(int x, int y);//清理控制台物品详细信息     参数为光标初始位置
	void cleanShopInfo(int x, int y);//清理控制台物品详细信息      参数为光标初始位置
};

#endif