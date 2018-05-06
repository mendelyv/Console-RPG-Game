#include "CEquip.h"


//打印装备栏    参数为控制台光标初始位置
void CEquip::printUI(int x,int y)
{
	int _x = x;
	int _y = y;
	map<int, CItem>::iterator iter = m_EquipContainer.begin();
	
	iter = m_EquipContainer.find(IN_Weapon);                   //寻找装备栏中的武器
	if (m_EquipContainer.end() != iter)
	{
		switch (iter->second.m_ID)
		{
			case 20000:gotoXY(x++, y); color(10); cout << "A"; color(15); break;
			case 20100:gotoXY(x++, y); color(10); cout << "B"; color(15); break;
			case 30000:gotoXY(x++, y); color(13); cout << "T"; color(15); break;
			default:
				break;
		}
	}
	else
	{
		gotoXY(x++, y); cout << "□";					//没找到输出一个空白框
	}

	iter = m_EquipContainer.find(IN_Corselet);					//寻找装备栏中的防具
	if (m_EquipContainer.end() != iter)
	{
		switch (iter->second.m_ID)
		{
			case 20000:gotoXY(x++, y); color(10); cout << "A"; color(15); break;
			case 20100:gotoXY(x++, y); color(10); cout << "B"; color(15); break;
			case 30000:gotoXY(x++, y); color(13); cout << "T"; color(15); break;
			default:
				break;
		}
	}
	else
	{
		gotoXY(x++, y); cout << "□";					//没找到输出一个空白框	
	}

	//**********************************************半完成
	iter = m_EquipContainer.find(IN_Shoe);					//寻找装备栏中的鞋子
	if (m_EquipContainer.end() != iter)
	{
		switch (iter->second.m_ID)
		{
		case 20000:gotoXY(x++, y); color(10); cout << "A"; color(15); break;
		case 20100:gotoXY(x++, y); color(10); cout << "B"; color(15); break;
		case 30000:gotoXY(x++, y); color(13); cout << "T"; color(15); break;
		default:
			break;
		}
	}
	else
	{
		gotoXY(x++, y); cout << "□";					//没找到输出一个空白框	
	}

	iter = m_EquipContainer.find(IN_Shoe);					//寻找装备栏中的饰品
	if (m_EquipContainer.end() != iter)
	{
		switch (iter->second.m_ID)
		{
		case 20000:gotoXY(x++, y); color(10); cout << "A"; color(15); break;
		case 20100:gotoXY(x++, y); color(10); cout << "B"; color(15); break;
		case 30000:gotoXY(x++, y); color(13); cout << "T"; color(15); break;
		default:
			break;
		}
	}
	else
	{
		gotoXY(x++, y); cout << "□";					//没找到输出一个空白框	
	}
	//****************************************************

	x = _x + 8;
	y = _y;

	iter = m_EquipContainer.begin();
	if (!m_EquipContainer.empty())					//如果装备栏不空    默认打印装备栏背包中的首元素信息
	{
		color(14);
		gotoXY(x++, y); cout << iter->second.m_Name;
		gotoXY(x, y); cout << iter->second.m_Describe;
		color(15);
	}
}

//清理控制台      参数为控制台光标初始位置
void CEquip::cleanEquipUI(int x, int y)
{
	for (int i = x; i < x+11; i++)
	{
		for (int j = y; j < y+9; j++)
		{
			gotoXY(i, j); cout << "  ";
		}
	}
}

//打印装备详细信息      参数为控制台光标初始位置
void CEquip::printEquipInfo(int x, int y, const map<int, CItem>::iterator _iter)
{
	color(14);
	gotoXY(x, y); cout << _iter->second.m_Name;
	gotoXY(x + 1, y); cout << _iter->second.m_Describe;
	color(15);
}

//清理控制台       参数为控制台光标初始位置
void CEquip::cleanEquipInfo(int x, int y)
{
	gotoXY(x++, y); cout << "                                                           ";
	gotoXY(x++, y); cout << "                                                           ";
}