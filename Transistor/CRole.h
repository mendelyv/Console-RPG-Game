/*
File Name : CRole.h
Function : Role Class
Updata time : 2017 11 16
*/

#ifndef CROLE_H
#define CROLE_H
#include "comment.h"
#include "Mydefine.h"
#include "CRoleBag.h"
#include "CEquip.h"

class CRoleBag;
class CEquip;
class CMonster;

class CRole
{
public:
	CRole();
	void move(int dx, int dy);//移动
	void setPosition(int _x, int _y);//设置角色坐标
	void print();//打印角色
	void getPosition(int &_x, int &_y);//获得人物坐标
	void setPlayerInfoFromXML(const char *_FileName);//从XML文件中读取人物初始信息
	void outputBag(int _x,int _y);//查看背包      参数为光标初始位置
	void ctrlOfBag(int _x, int _y);//控制（在背包中	非战状态）     参数为光标初始位置
	void ctrlOfBagInFight(int _x, int _y);//控制（在背包中		战斗状态）      参数为光标初始位置
	void outputEquip(int _x, int _y);//查看装备栏      参数为光标初始位置
	void ctrlOfEquip(int _x, int _y);//控制（在装备栏中）  参数为光标初始位置
	int atkAction(CMonster &);//攻击    返回值为伤害数值
	void beenAtkAction(int _hurt);//被攻击函数   参数为伤害值
	void tubePrint(int _x,int _y);//打印蓝条血条（参数：在控制台的位置）
	void upLevel();		//升级
	void upInfo();		//根据等级提升属性
	
	int skill1(CMonster &_monster);//技能1
	void printSkill1Picture(int x, int y);//打印技能1的图片     参数为控制台光标初始位置
	void cleanSkill1Picture(int x, int y);//清除技能图片     参数为控制台光标初始位置
	void printStaticPicture(int _x, int _y);//静止站立人物图片(参数:图片左上角控制台坐标)
	void printAttackPicture(int _x, int _y);//平a人物图片     参数为控制台光标初始位置
	void cleanPixelPicture(int _x, int _y);//清除人物图片(参数:图片左上角控制台坐标)

	int m_PlayerPictureX;				//角色图片打印位置
	int m_PlayerPictureY;

	int m_RinfoPut_X;					//角色相关数值输出点
	int m_RinfoPut_Y;

	friend CRole& operator+(CRole &_role, CMonster &_monster);		//重载+运算符  增加经验

	CRoleBag m_Bag;    //人物背包
	CEquip m_Equip;     //人物装备

protected:
	GET_SET(string, m_Name, Name);
	GET_SET(int, m_PositionX, PositionX);
	GET_SET(int, m_PositionY, PositionY);
	GET_SET(int, m_Golden, Golden);
	GET_SET(int, m_HP, HP);
	GET_SET(int, m_MP, MP);
	GET_SET(int, m_MaxHP, MaxHP);
	GET_SET(int, m_MaxMP, MaxMP);
	GET_SET(int, m_Atk, Atk);
	GET_SET(int, m_Def, Def);
	GET_SET(int, m_InMapName, InMapName);			//角色所在地图名字
	GET_SET(int, m_BagSize, BagSize);			//人物初始背包尺寸
	GET_SET(int, m_Level, Level);			//角色等级
	GET_SET(int, m_Experience, Experience);				//经验
	GET_SET(int, m_UpExperience, UpExperience);		//升级所需经验

	void maxInfoProtect();				//属性最大值保护
};

#endif;