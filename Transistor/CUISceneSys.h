/*
File Name : CUISceneSys.h
Function : UI Control System
Updata time : 2017 11 10
*/

#ifndef GUISCENESYS_H
#define GUISCENESYS_H
#include "CSingleton.h"
#include "CBeginScene.h"
#include "Game.h"
#include "CMap.h"
#include "comment.h"

class CUISceneSys :public CSingleton < CUISceneSys >
{
public:
	CBeginScene BeginScene;

	void init();//初始化
	void loadAllMap();//载入所有地图

	CMap* getMap(int _MapName);//获得地图

	void changeInMap(int _name, CRole* _player);//将玩家放入地图

	void setMonster(CMap &_map);//给地图散落怪物   参数为地图

	void freeAllMap();//释放所有地图

protected:
	map<int, CMap*> m_MapContainer;//用来存放游戏地图的容器

	CMap *m_pGameMap;//地图指针
	MapName m_MapName;//地图名字
};

#endif