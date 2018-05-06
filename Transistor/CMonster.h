/*
File Name : CMonster.h
Function : Monster Class
Updata time : 2017 11 17
*/

#ifndef CMONSTER_H
#define CMONSTER_H
#include "Mydefine.h"
#include <string>
using namespace std;
class CRole;

class CMonster
{
public:
	virtual void tubePrint(int _x, int _y) = 0;//打印蓝条血条（参数：在控制台的位置）
	virtual int atkAction(CRole &) = 0;//攻击
	virtual void beenAtkAction(int) = 0;//被攻击
	virtual void printStaticPicture(int, int) = 0;//静止站立Process图片(参数:图片左上角控制台坐标)
	virtual void printAttackPicture(int, int) = 0;//平a  Process图片    参数为控制台光标初始坐标
	virtual void cleanPixelPicture(int, int) = 0;//清除Process图片(参数:图片左上角控制台坐标)

	//以下点用于控制台光标位置：
	int m_MonsterPictureX;			//怪物图片打印位置
	int m_MonsterPictureY;

	int m_PattackM_X;					//角色攻击怪物攻击动作位置
	int m_PattackM_Y;

	int m_MattackP_X;					//怪物攻击角色攻击动作位置
	int m_MattackP_Y;

	int m_MinfoPut_X;					//怪物相关数值输出点
	int m_MinfoPut_Y;

protected:
	GET_SET(string, m_Name, Name);
	GET_SET(int, m_HP, HP);
	GET_SET(int, m_MaxHP, MaxHp);//最大血量
	GET_SET(int, m_MP, MP);
	GET_SET(int, m_MaxMP, MaxMP);//最大蓝量
	GET_SET(int, m_Atk, Atk);
	GET_SET(int, m_Def, Def);
	GET_SET(int, m_ExperienceNum, ExperienceNum); //打死这个怪所给经验
	GET_SET(int, m_Golden, Golden);//打死这个怪所给金钱
};

#endif