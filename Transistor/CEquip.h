/*
File Name : CEquip.h
Function : Equipment Information
Updata time : 2017 11 15
*/

#ifndef CEQUIP_H
#define CEQUIP_H
#include "comment.h"
#include "Game.h"
#include "CItem.h"

class CEquip
{
public:
	void printUI(int x,int y);//打印装备栏    参数为控制台光标初始位置
	map<int, CItem> m_EquipContainer;
	void cleanEquipUI(int x, int y);//清理控制台      参数为控制台光标初始位置
	void printEquipInfo(int x, int y,const map<int,CItem>::iterator _iter);//打印装备详细信息      参数为控制台光标初始位置
	void cleanEquipInfo(int x, int y);//清理控制台       参数为控制台光标初始位置
};

#endif