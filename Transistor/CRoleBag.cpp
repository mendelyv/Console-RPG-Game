#include "CRoleBag.h"

CRoleBag::CRoleBag()
{
	m_Size = 0;
}

//添加物品进入背包
void CRoleBag::addItem(CItem &_Item)
{
	if (m_MaxSize <= m_Size)
		return;
	int index = searchItem(_Item.m_ID);
	if (-1 != index&&_Item.m_Overly == 1)
	{
		m_BagContainer[index].m_Num++;
		return;
	}
	//如果背包中不存在物品或者物品无法叠加，添加一个进入背包
	m_BagContainer.push_back(_Item);
	m_Size++;
}

//从背包中查找物品，返回值为下标
int CRoleBag::searchItem(int _ID)
{
	vector<CItem>::iterator i;
	int index = 0;
	//遍历容器找Item
	for (vector<CItem>::iterator i = m_BagContainer.begin(); i != m_BagContainer.end(); i++,index++)
	{
		if (i->m_ID == _ID)
			return index;//找到返回下标
	}
	return -1;//未找到返回-1
}

//背包查看（参数为背包左上角控制台位置）
void CRoleBag::printBag(int x, int y)
{
	int _x = x;//用一个变量存x的初始位置
	int _y = y;

	int count = 0;
	vector<CItem>::iterator iter = m_BagContainer.begin();

	for (int i = 0; i < m_MaxSize; i++)
	{
		if (0 == count % 5 && 0 != count)
		{
			gotoXY(x++, _y);
			y = _y;
		}
		gotoXY(x, y++); color(15); cout << "□"; count++;
	}

	x = _x;
	y = _y;
	count = 0;
	for (; iter != m_BagContainer.end() && count <= m_MaxSize; iter++)
	{
		if (0 == count % 5 && 0 != count)
		{
			gotoXY(x++, _y);
			y = _y;
		}
		switch (iter->m_ID)
		{
			case 10000:gotoXY(x, y++); color(12); cout << "药"; count++; break;
			case 15000:gotoXY(x, y++); color(9); cout << "药"; count++; break;
			case 20000:gotoXY(x, y++); color(10); cout << "A"; count++; break;
			case 20100:gotoXY(x, y++); color(10); cout << "B"; count++; break;
			case 30000:gotoXY(x, y++); color(13); cout << "T"; count++; break;
			default:
				break;
		}
	}
	
	x = _x + 8;
	y = _y;

	iter = m_BagContainer. begin();
	if (m_BagContainer.empty())      //如果背包不是空   默认打印第一个Item的信息
	{
		cleanItemInfo(x, y);
		return;
	}
	else
	{
		cleanBagInfo(x, y);
		printItemInfo(x, y, iter);
	}

}

//设置背包大小
void CRoleBag::setBagSize(int _size)
{
	m_MaxSize = _size;
}

//清理控制台背包信息
void CRoleBag::cleanBagInfo(int x, int y)
{
	for (int i = x; i < x + 11; i++)
	{
		for (int j = y; j < y + 9; j++)
		{
			gotoXY(i, j); cout << "  ";
		}
	}
}

//输出物品详细信息     参数为光标初始位置和迭代器
void CRoleBag::printItemInfo(int x, int y, const vector<CItem>::iterator _iter)
{
	color(14);
	gotoXY(x, y); cout << _iter->m_Name << "  ×" << _iter->m_Num;
	gotoXY(x + 1, y); cout << _iter->m_Describe;
	color(15);
}

//清理控制台物品详细信息     参数为光标初始位置
void CRoleBag::cleanItemInfo(int x, int y)
{
	gotoXY(x++, y); cout << "                     ";
	gotoXY(x, y); cout << "                          ";
}