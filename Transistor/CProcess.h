/*
File Name : CProcess.h
Function : Process Class
Updata time : 2017 11 3
*/

#ifndef CPROCESS_H
#define CPROCESS_H
#include "CMonster.h"
class CRole;

class CProcess:public CMonster
{	
public:
	CProcess();
	void tubePrint(int _x, int _y);//打印血条蓝条 （参数：图片左上角控制台坐标）
	int atkAction(CRole &);//攻击
	void beenAtkAction(int);//被攻击
	void printStaticPicture(int, int);//静止站立Process图片(参数：图片左上角控制台坐标)
	void cleanPixelPicture(int, int);//清除Process图片(参数：图片左上角控制台坐标)
	void printAttackPicture(int, int);//平a  Process图片    参数为控制台光标初始坐标
};

#endif