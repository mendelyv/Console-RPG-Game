/*
File Name : CItem.h
Function : Item Class
Updata time : 2017 11 14
*/


#ifndef CITEM_H
#define CITEM_H
#include "Game.h"
#include "comment.h"
class CRole;

class CItem
{
public:
	CItem();

	string m_Name;
	int m_ID;//物品枚举名
	string m_Describe;//物品功效描述
	//=========增益属性
	int m_HP;//加血量
	int m_MP;//加蓝量
	int m_Atk;//增加攻击力
	int m_Def;//增加防御力

	//==========物品属性
	int m_Num;//数量
	int m_Overly;//叠加属性     1为可叠加    0为不可叠加
	int m_Price;//物品价格
	int m_Type;//物品种类

	friend CRole& operator+(CRole &_role, CItem &_item);     //重载 + 用于玩家属性值增加
	friend CRole& operator-(CRole &_role, CItem &_item);     //重载 - 用于玩家属性值增加
};

#endif