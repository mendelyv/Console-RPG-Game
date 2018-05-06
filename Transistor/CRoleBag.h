/*
File Name : CRoleBag.h
Function : Bag Blongs Role
Updata time : 2017 11 16
*/

#ifndef CROLEBAG_H
#define CROLEBAG_H
#include "comment.h"
#include "CItem.h"

class CRoleBag
{
public:
	CRoleBag();
	void addItem(CItem &_Item);//添加物品进入背包
	int searchItem(int _ID);//从背包中查找物品，返回值为下标
	void printBag(int x,int y);//背包查看      参数为光标初始位置
	void setBagSize(int _size);//设置背包大小
	void printItemInfo(int x, int y, const vector<CItem>::iterator _iter);//输出物品详细信息     参数为光标初始位置和迭代器
	void cleanBagInfo(int x, int y);//清理控制台背包信息         参数为光标初始位置
	void cleanItemInfo(int x, int y);//清理控制台物品详细信息     参数为光标初始位置

	vector<CItem> m_BagContainer;


	int m_Size;//背包容量
	int m_MaxSize;//背包最大容量

};

#endif