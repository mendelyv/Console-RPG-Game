/*
File Name:CMap.h
Function:Map Class
Updata time:2017 11 16
*/

#ifndef CMAP_H
#define CMAP_H
#include  "CRole.h"

class CMap
{
public:
	CMap();
	~CMap();
	int **m_pMap;//存放地图元素的二级指针
	void setMapFromFile(char *);//从文件读入地图信息
	void print();//打印地图
	void ctrlOfMap();//控制（在地图中）
	int interactOfMap(int dx, int dy);//地图交互（返回值为地图元素）
	void printPlayerInfo();//在文本输出点打印角色信息
	void cleanRoleInfo();//清理在控制台输出的角色的各种信息

private:
	GET_SET(int, m_Row, Row);
	GET_SET(int, m_Col, Col);
	int m_textPositionX;//文本输出点行坐标
	int m_textPositionY;//文本输出点列坐标
	void initMemory();//开辟内存
	void interactOfMapElement(int dx, int dy);//接收偏移量做出相应工作
	void rePrint();//归还地图元素
	GET_SET(CRole*, m_Player, Player);//玩家指针
	bool m_isBody;//记录是否碰过尸体
	void collisionBody();//碰到导向尸体触发函数
};


#endif