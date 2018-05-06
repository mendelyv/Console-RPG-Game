/*
FIle Name : CESC.h
Function : ESC choose UI
Updata time : 2017 11 17
*/

#ifndef CESC_H
#define CESC_H
#include "CSingleton.h"
#include "Mydefine.h"
#include "CRole.h"

class CESC :public CSingleton < CESC >
{
public:
	void print();//打印界面
	int ctrlOfSence();//控制（在ESC场景中）
	void action(int cursor);//根据选择做出动作   参数为光标位置
	void saveInXML();//存到XML文件中
	GET_SET(CRole*, m_Player, Player);
};

#endif