/*
File name : CBeginScene.h
Function : Game Begin UI
Updata time : 2017 11 10
*/

#ifndef CBEGINSCENE_H
#define CBEGINSCENE_H
#include "CSingleton.h"

class CBeginScene:public CSingleton<CBeginScene>
{
public:
	void print();//打印场景
	int ctrlOfScene();//控制（在场景中）
	void action(int _flag);//根据选择做出动作   参数为光标位置

protected:
	void printGameExplain();//打印游戏提示
};

#endif