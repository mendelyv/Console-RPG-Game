/*
File Name : CCamerata.h
Function : Camerata Class
Updata time : 2017 11 16
*/

#ifndef CCAMERATA_H
#define CCAMERATA_H

#include "CMonster.h"

class CCamerata :public CMonster
{
public:
	CCamerata();
	void tubePrint(int _x, int _y);//打印血条蓝条 （参数：图片左上角控制台坐标）
	int atkAction(CRole &);//攻击
	void beenAtkAction(int);//被攻击
	void printStaticPicture(int, int);//静止站立Process图片(参数：图片左上角控制台坐标)
	void cleanPixelPicture(int, int);//清除Process图片(参数：图片左上角控制台坐标)
	void printAttackPicture(int, int);//平a  Process图片    参数为控制台光标初始坐标
};

#endif