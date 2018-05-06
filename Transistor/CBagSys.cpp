#include "CBagSys.h"
#include "comment.h"

//游戏所有道具载入
void CBagSys::init(char *_FileName)
{
	TiXmlDocument doc;
	if (false == doc.LoadFile(_FileName))
	{
		return;
	}

	TiXmlElement *pItem = doc.FirstChildElement();

	while (nullptr != pItem)
	{
		CItem item;
		item.m_Name = pItem->Attribute("Name");
		item.m_Describe = pItem->Attribute("Describe");
		pItem->Attribute("HP", &item.m_HP);
		pItem->Attribute("MP", &item.m_MP);
		pItem->Attribute("Atk", &item.m_Atk);
		pItem->Attribute("Def", &item.m_Def);
		pItem->Attribute("Overly", &item.m_Overly);
		pItem->Attribute("Price", &item.m_Price);
		pItem->Attribute("ID", &item.m_ID);
		pItem->Attribute("Type", &item.m_Type);
		pItem->Attribute("Num", &item.m_Num);
		//将Item装入容器
		m_ItemContainer.insert(make_pair(item.m_ID, item));
		//偏向下一个标签
		pItem = pItem->NextSiblingElement();
	}
}

//展示商品    参数为控制台光标坐标和商品种类枚举
void CBagSys::showItem(int x, int y, ItemType _type)
{
	int _x = x;
	int _y = y;

	int count = 0;
	map<int, CItem>::iterator iter = m_ItemContainer.begin();
	map<int, CItem>::iterator iter_end = m_ItemContainer.end();


	for (int i = 0; i < 20; i++)
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
	for (; iter != m_ItemContainer.end() && count < 20; iter++)
	{
		if (0 == count % 5 && 0 != count)
		{
			gotoXY(x++, _y);
			y = _y;
		}
		switch (_type)
		{
		case IN_Medicine:
		{
			if (IN_Medicine == iter->second.m_Type)
			{
				switch (iter->second.m_ID)
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
		}break;

		case IN_Weapon:
		{
			if (IN_Weapon == iter->second.m_Type)
			{
				switch (iter->second.m_ID)
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
		}break;

		case IN_Corselet:
		{
			if (IN_Corselet == iter->second.m_Type)
			{
				switch (iter->second.m_ID)
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
		}break;
		}
	}

	ctrlOfShop(_x, _y,_type);
}

//控制（在商店界面）
void CBagSys::ctrlOfShop(int x, int y,ItemType _type)
{
	int _x = x + 8;
	int _y = y;
	int index = 0;//记录玩家光标所在下标
	int maxIndex = m_ItemContainer.size();//记录容器最大下标

	map<int, CItem>::iterator iter = m_ItemContainer.begin();
	
	char key = 0;
	//=============打印各类商品的第一个Item类
	switch (_type)				
	{
		case IN_Medicine:
		{
			while(IN_Medicine != iter->second.m_Type)
			{
				iter++;
			}
			printItemInfo(_x, _y, iter);
		}break;

		case IN_Corselet:
		{
			while (IN_Corselet != iter->second.m_Type)
			{
				iter++;
			}
			printItemInfo(_x, _y, iter);
		}break;

		case IN_Weapon:
		{
			while (IN_Weapon != iter->second.m_Type)
			{
				iter++;
			}
			printItemInfo(_x, _y, iter);
		}break;
	}
	//=============================
	while (true)
	{
		key = _getch();
		switch (key)
		{
			case 'd':
			case 'D':
			{
				iter++;
				if (iter == m_ItemContainer.end())
				{
					iter--;                                      //迭代器归位，否则会  CRASH    !!!!!!!
					break;
				}
				if (_type != iter->second.m_Type)
					iter--;
				cleanItemInfo(_x, _y);
				printItemInfo(_x, _y, iter);
			}break;

			case 'a':
			case 'A':
			{
				if (iter == m_ItemContainer.begin())
					break;
				iter--;
				if (_type != iter->second.m_Type)
					iter++;
				cleanItemInfo(_x, _y);
				printItemInfo(_x, _y, iter);
			}break;

			//==========================买装备
			case ' ':					//按空格买选中的物品
			{

				if (0 > m_Player->getGolden() - iter->second.m_Price)		//判断金钱是否足够
				{
					color(14); gotoXY(_x + 6, y); cout << "木钱了！"; color(15);
					if (_getch())
						gotoXY(_x + 6, y); cout << "                      ";
					break;
				}

				if (m_Player->m_Bag.m_MaxSize == m_Player->m_Bag.m_Size)   //判断背包是否足够
				{
					color(14); gotoXY(_x + 6, y); cout << "拿不过来了！"; color(15);
					if (_getch())
						gotoXY(_x + 6, y); cout << "                      ";
					break;
				}
					
				m_Player->m_Bag.addItem(iter->second);
				m_Player->setGolden(m_Player->getGolden() - iter->second.m_Price);

				color(14); gotoXY(_x + 6, y); cout << "诺，拿着！"; color(15);
				if (_getch())
					gotoXY(_x + 6, y); cout << "                     ";
			}break;
			//=============================

			case 27:
				cleanShopInfo(x, y); return;
		}
	}
}

//输出物品详细信息     参数为光标初始位置和背包下标
void CBagSys::printItemInfo(int x, int y, const map<int, CItem>::iterator _iter)
{
	color(14);
	gotoXY(x, y); cout << _iter->second.m_Name;
	gotoXY(x + 1, y); cout << _iter->second.m_Describe;
	gotoXY(x + 3, y); cout <<"价格："<< _iter->second.m_Price;
	gotoXY(x + 4, y); cout << "按空格键买入";
	color(15);
}

//清理控制台物品详细信息     参数为光标初始位置
void CBagSys::cleanItemInfo(int x, int y)
{
	gotoXY(x++, y); cout << "                                                                  ";
	gotoXY(x, y); cout << "                                                                         ";
}

//清理控制台物品详细信息      参数为光标初始位置
void CBagSys::cleanShopInfo(int x, int y)
{
	for (int i = x; i < 30; i++)
	{
		for (int j = y; j < 50; j++)
		{
			gotoXY(i, j); cout << "  ";
		}
	}
}