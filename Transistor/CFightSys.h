/*
File Name : CFightSys.h
Function : Fight Control System
Updata time : 2017 11 19
*/

#ifndef CFIGHTSYS_H
#define CFIGHTSYS_H

#include "CSingleton.h"
#include "Mydefine.h"
#include "Game.h"
class CRole;
class CMonster;

class CFightSys :public CSingleton < CFightSys >
{
public:
	void printFightUI();	//打印战斗界面
	bool ctrlOfFight(MonsterType _MonsterType);	//控制（在战斗中）参数为怪物种类枚举

protected:
	GET_SET(CRole*, m_Player, Player);	//玩家指针
	void upMonsterInfo(CMonster *);		//根据人物等级提升怪的属性
	bool isMonsterDead(const CMonster *_monster);					//判断怪是否死亡		死亡返回true
	bool isPlayerDead();			//判断人物是否死亡        死亡返回true
	void PaMvideo(CMonster *pMonster);			//角色攻击怪动画		参数为怪物指针
	void MaPvideo(CMonster *pMonster,MonsterType _MonsterType);			//怪攻击角色动画		参数为怪物指针和怪物种类
};

#endif