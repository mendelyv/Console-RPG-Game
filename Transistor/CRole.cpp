#include "CRole.h"
#include "CMonster.h"
#include "CBagSys.h"

CRole::CRole()
{
	m_Bag.setBagSize(m_BagSize);

	m_PlayerPictureX = 14;
	m_PlayerPictureY = 53;

	m_RinfoPut_X = 10;
	m_RinfoPut_Y = 61;

	m_Level = 1;

	m_Experience = 0;
	m_UpExperience = 300;

	m_InMapName = MN_None;
}

//移动
void CRole::move(int dx, int dy)
{
	int _NewX = m_PositionX + dx;
	int _NewY = m_PositionY + dy;

	m_PositionX = _NewX;
	m_PositionY = _NewY;
}

//设置角色坐标
void CRole::setPosition(int _x, int _y)
{
	m_PositionX = _x;
	m_PositionY = _y;
}

//打印角色
void CRole::print()
{
	color(14);
	gotoXY(m_PositionX, m_PositionY); cout << "♀";
	color(15);
}

//获得人物坐标
void CRole::getPosition(int &_x,int &_y)
{
	_x = m_PositionX;
	_y = m_PositionY;
}

//从XML文件中读取人物初始信息
void CRole::setPlayerInfoFromXML(const char *_FileName)
{
	TiXmlDocument doc;
	if (doc.LoadFile(_FileName))
	{
		//读入角色信息
		TiXmlElement *pRole = doc.FirstChildElement("Role");
		m_Name = pRole->Attribute("Name");
		pRole->Attribute("HP", &m_HP);
		pRole->Attribute("MP", &m_MP);
		pRole->Attribute("MaxHP", &m_MaxHP);
		pRole->Attribute("MaxMP", &m_MaxMP);
		pRole->Attribute("Atk", &m_Atk);
		pRole->Attribute("Def", &m_Def);
		pRole->Attribute("BagSize", &m_BagSize);
		pRole->Attribute("Golden", &m_Golden);
		pRole->Attribute("MapName", &m_InMapName);
		pRole->Attribute("Experience", &m_Experience);
		pRole->Attribute("UpExperience", &m_UpExperience);
		pRole->Attribute("PositionX", &m_PositionX);
		pRole->Attribute("PositionY", &m_PositionY);

		m_Bag.setBagSize(m_BagSize);
		//读取背包信息
		TiXmlElement *pItem = pRole->FirstChildElement("Item");
		while (pItem != nullptr)
		{
			CItem item;
			item.m_Name = pItem->Attribute("Name");
			item.m_Describe = pItem->GetText();
			pItem->Attribute("HP", &item.m_HP);
			pItem->Attribute("MP", &item.m_MP);
			pItem->Attribute("Atk", &item.m_Atk);
			pItem->Attribute("Def", &item.m_Def);
			pItem->Attribute("Overly", &item.m_Overly);
			pItem->Attribute("Price", &item.m_Price);
			pItem->Attribute("ID", &item.m_ID);
			pItem->Attribute("Type", &item.m_Type);
			//将Item装入背包
			m_Bag.addItem(item);
			//偏向下一个标签
			pItem = pItem->NextSiblingElement("Item");
		}


		//读取装备信息
		TiXmlElement *pEquip = pRole->FirstChildElement("Equip");
		while (pEquip != nullptr)
		{
			CItem item;
			item.m_Name = pEquip->Attribute("Name");
			item.m_Describe = pEquip->GetText();
			pEquip->Attribute("HP", &item.m_HP);
			pEquip->Attribute("MP", &item.m_MP);
			pEquip->Attribute("Atk", &item.m_Atk);
			pEquip->Attribute("Def", &item.m_Def);
			pEquip->Attribute("Overly", &item.m_Overly);
			pEquip->Attribute("Price", &item.m_Price);
			pEquip->Attribute("ID", &item.m_ID);
			pEquip->Attribute("Type", &item.m_Type);
			//将item装入装备栏
			m_Equip.m_EquipContainer.insert(make_pair(item.m_Type, item));
			//偏向下一个标签
			pEquip = pEquip->NextSiblingElement("Equip");
		}
	}
}


//查看背包
void CRole::outputBag(int _x,int _y)
{
	m_Bag.printBag(_x, _y);
}

//查看装备栏
void CRole::outputEquip(int _x, int _y)
{
	m_Equip.printUI(_x, _y);
}

//控制（在背包中）  参数为光标初始位置
void CRole::ctrlOfBag(int x, int y)
{
	int _x = x + 8;
	int _y = y;

	vector<CItem>::iterator iter = m_Bag.m_BagContainer.begin();

	char key = 0;

	while (true)
	{
		if (m_Bag.m_BagContainer.empty())
		{
			if (_getch())
			{
				m_Bag.cleanBagInfo(x, y);
				return;
			}
		}
		key = _getch();
		switch (key)
		{
		case 'd':
		case 'D':
		{
			iter++;
			if (m_Bag.m_BagContainer.end() == iter)
			{
				iter--;                           //迭代器归位，否则会  CRASH    !!!!!!!
				break;
			}
			m_Bag.cleanItemInfo(_x, _y);
			m_Bag.printItemInfo(_x, _y, iter);
		}break;

		case 'a':
		case 'A':
		{
			if (m_Bag.m_BagContainer.begin() == iter)
				break;
			iter--;
			m_Bag.cleanItemInfo(_x, _y);
			m_Bag.printItemInfo(_x, _y, iter);
		}break;

		//=============================使用物品
		case ' ':
		{
			//--------------------------------------------------使用消耗品
			if (1 == iter->m_Overly && 1 < iter->m_Num)     //物品可以叠加并且物品的数目不为1的时候    
			{
				*this + *iter;

				maxInfoProtect();												//属性最大值保护

				iter->m_Num--;												  //物品的数量直接-1
				gotoXY(_x + 4, _y); cout << "使用成功";
				if (_getch())
				{
					m_Bag.cleanItemInfo(_x, _y);
					gotoXY(_x + 4, _y); cout << "                    ";
					m_Bag.printItemInfo(_x, _y, iter);
				}
				break;
			}
			else if (1 == iter->m_Overly && 1 == iter->m_Num)
			{
				*this + *iter;
				m_Bag.m_BagContainer.erase(iter);
				m_Bag.m_Size--;
				iter = m_Bag.m_BagContainer.begin();                          //迭代器归位
				gotoXY(_x + 4, _y); cout << "使用成功";
				if (_getch())
				{
					gotoXY(_x + 4, _y); cout << "                    ";
					m_Bag.printBag(x, y);														//重新打印背包界面
				}
				break;
			}
			//------------------------------------------------------------

			//--------------------------------------------------使用装备
			if (m_Equip.m_EquipContainer.find(iter->m_Type) != m_Equip.m_EquipContainer.end())  //找到同类装备
				break;																															//直接跳出

			m_Equip.m_EquipContainer.insert(make_pair(iter->m_Type, *iter));         //将装备塞进装备栏
			*this + *iter;

			m_Bag.m_BagContainer.erase(iter);				//将物品栏中的装备erase
			m_Bag.m_Size--;												//物品栏物品数量减少
			iter = m_Bag.m_BagContainer.begin();                          //迭代器归位
			gotoXY(_x + 4, _y); cout << "使用成功";
			if (_getch())
			{
				gotoXY(_x + 4, _y); cout << "                    ";
				m_Bag.printBag(x, y);														//重新打印背包界面
			}
			//------------------------------------------------------------

		}break;//===============================

		case 27:
		case 'b':                            //关闭背包
		case 'B':m_Bag.cleanBagInfo(x, y); return;
		}
	}
}

//控制（在背包中		战斗状态）      参数为光标初始位置
void CRole::ctrlOfBagInFight(int x, int y)
{
	int _x = x + 8;
	int _y = y;

	vector<CItem>::iterator iter = m_Bag.m_BagContainer.begin();

	char key = 0;

	while (true)
	{
		if (m_Bag.m_BagContainer.empty())
		{
			if (_getch())
			{
				m_Bag.cleanBagInfo(x, y);
				return;
			}
		}
		key = _getch();
		switch (key)
		{
		case 'd':
		case 'D':
		{
			iter++;
			if (m_Bag.m_BagContainer.end() == iter)
			{
				iter--;                           //迭代器归位，否则会  CRASH    !!!!!!!
				break;
			}
			m_Bag.cleanItemInfo(_x, _y);
			m_Bag.printItemInfo(_x, _y, iter);
		}break;

		case 'a':
		case 'A':
		{
			if (m_Bag.m_BagContainer.begin() == iter)
				break;
			iter--;
			m_Bag.cleanItemInfo(_x, _y);
			m_Bag.printItemInfo(_x, _y, iter);
		}break;

		//=============================使用物品
		case ' ':
		{
			//--------------------------------------------------使用消耗品
			if (1 == iter->m_Overly && 1 < iter->m_Num)     //物品可以叠加并且物品的数目不为1的时候    
			{
				*this + *iter;

				maxInfoProtect();												//属性最大值保护

				iter->m_Num--;												  //物品的数量直接-1
				gotoXY(_x + 4, _y); cout << "吃  药";
				if (_getch())
				{
					m_Bag.cleanItemInfo(_x, _y);
					gotoXY(_x + 4, _y); cout << "                    ";
					m_Bag.printItemInfo(_x, _y, iter);
					tubePrint(SP_PlayerTubeX, SP_PlayerTubeY);
				}
				break;
			}
			else if (1 == iter->m_Overly && 1 == iter->m_Num)     //物品可以叠加并且物品的数目为1的时候
			{
				*this + *iter;
				m_Bag.m_BagContainer.erase(iter);
				m_Bag.m_Size--;
				iter = m_Bag.m_BagContainer.begin();                          //迭代器归位
				gotoXY(_x + 4, _y); cout << "吃  药";
				if (_getch())
				{
					gotoXY(_x + 4, _y); cout << "                    ";
					m_Bag.printBag(x, y);														//重新打印背包界面
					tubePrint(SP_PlayerTubeX, SP_PlayerTubeY);
				}
				break;
			}
			//------------------------------------------------------------

			//--------------------------------------------------使用装备
			else if(0 == iter->m_Overly)
			{
				gotoXY(_x + 4, _y); cout << "专心打架";
				if (_getch())
				{
					gotoXY(_x + 4, _y); cout << "                  ";
					m_Bag.printBag(x, y);
				}
				break;
			}
			//------------------------------------------------------------

		}break;//===============================

		case 27:
		case 'b':                            //关闭背包
		case 'B':m_Bag.cleanBagInfo(x, y); return;
		}
	}
}

//控制（在装备栏中）  参数为光标初始位置
void CRole::ctrlOfEquip(int x, int y)
{
	{
		int _x = x + 8;
		int _y = y;
		map<int, CItem>::iterator iter = m_Equip.m_EquipContainer.begin();
		char key = 0;

		while (true)
		{
			if (m_Equip.m_EquipContainer.empty())
			{
				if (_getch())
				{
					m_Equip.cleanEquipUI(x, y);
					return;
				}
			}

			key = _getch();

			switch (key)
			{
				case 's':
				case 'S':
				{
					iter++;
					if (iter == m_Equip.m_EquipContainer.end())
					{
						iter--;                                      //将迭代器送回，避免越界！！！！
						break;
					}
					m_Equip.cleanEquipInfo(_x, _y);
					m_Equip.printEquipInfo(_x, _y, iter);

				}break;

				case 'w':
				case 'W':
				{
					if (iter == m_Equip.m_EquipContainer.begin())
						break;
					iter--;
					m_Equip.cleanEquipInfo(_x, _y);
					m_Equip.printEquipInfo(_x, _y, iter);
				}break;

				case 'p':
				case 'P':m_Equip.cleanEquipUI(x, y); return;

				//==========================脱装备
				case ' ':
				{
					m_Bag.addItem(iter->second);       //往背包中添加一个装备
					*this - iter->second;						//属性值减少

					m_Equip.m_EquipContainer.erase(iter);       //装备栏装备清除

					iter = m_Equip.m_EquipContainer.begin();      //迭代器归位

					m_Equip.cleanEquipUI(x, y);
					m_Equip.printUI(x, y);

				}break;
				//==============================
			}
		}
	}
}

//属性最大值保护
void CRole::maxInfoProtect()
{
	if (m_MaxHP < m_HP)
		m_HP = m_MaxHP;

	if (m_MaxMP < m_MP)
		m_MP = m_MaxMP;
}

//攻击行为      参数为攻击的怪物     返回值为伤害数值
int CRole::atkAction(CMonster &_monster)
{
	int hurt = m_Atk - _monster.getDef();

	if (hurt < 0)				//判断伤害是否未负数，强行破甲
		hurt = 1;

	_monster.beenAtkAction(hurt);

	return hurt;
}

//被攻击    参数为伤害值
void CRole::beenAtkAction(int _hurt)
{
	m_HP -= _hurt;
}

//打印蓝条血条（参数：在控制台的位置）
void CRole::tubePrint(int _x, int _y)
{
	int FallHPCell = m_MaxHP / 20;//得出一格血的量
	int FallMPCell = m_MaxMP / 20;//得出一格蓝的量
	int HPTubeArr[20] = { 0 };//用来存放血条的数组，5%为一格，0代表有血
	int MPTubeArr[20] = { 0 };//用来存放蓝条的数组，5%为一格，0代表有蓝

	if (0 > m_HP)
	{
		m_HP = 0;//血量保护
		for (int i = 19; i >= 0; i--)
			HPTubeArr[i] = 1;
	}

	for (int i = 19; i > (0 == m_HP%FallHPCell ? m_HP / FallHPCell - 1 : m_HP / FallHPCell); i--)
	{
		HPTubeArr[i] = 1;
	}

	gotoXY(_x++, _y); color(4);
	for (int i = 0; i < sizeof(HPTubeArr) / 4; i++)
	{
		switch (HPTubeArr[i])
		{
		case 0:cout << "■"; break;
		case 1:cout << "□"; break;
		default:break;
		}
	}

	color(15); cout << "  " << m_HP << "      ";

	if (0 > m_MP)
	{
		m_MP = 0;//蓝量保护
		for (int i = 19; i >= 0; i--)
			MPTubeArr[i] = 1;
	}

	for (int i = 19; i > (0 == m_MP%FallMPCell ? m_MP / FallMPCell - 1 : m_MP / FallMPCell); i--)
	{
		MPTubeArr[i] = 1;
	}

	gotoXY(_x, _y); color(1);
	for (int i = 0; i < sizeof(MPTubeArr) / 4; i++)
	{
		switch (MPTubeArr[i])
		{
		case 0:cout << "■"; break;
		case 1:cout << "□";  break;
		default:
			break;
		}
	}
	color(15); cout << "  " << m_MP << "      ";

}

//静止站立人物图片(参数:图片左上角控制台坐标)
void CRole::printStaticPicture(int _PositionX, int _PositionY)
{
	int PlayerStatic[14][16] = {
		0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 5, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 5, 0, 0,
		0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 5, 0,    //1浅灰色   2蓝色  3黑色  4红色
		0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5,    //5深灰色   6深蓝色   7深红色
		0, 0, 0, 0, 2, 2, 3, 2, 3, 2, 2, 2, 1, 1, 1, 5,    //0无色
		0, 0, 0, 0, 2, 2, 3, 2, 3, 2, 2, 2, 1, 1, 1, 5,
		0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 5,
		0, 0, 0, 4, 7, 0, 1, 1, 1, 1, 1, 2, 2, 6, 0, 0,
		0, 0, 4, 4, 7, 1, 1, 1, 1, 1, 1, 2, 2, 1, 5, 0,
		0, 4, 4, 4, 4, 4, 4, 4, 2, 2, 2, 2, 4, 4, 4, 7,
		0, 0, 4, 4, 7, 1, 1, 1, 2, 2, 2, 1, 1, 5, 0, 0,
		0, 0, 0, 4, 7, 0, 1, 1, 1, 1, 1, 1, 1, 1, 5, 0,
		0, 0, 0, 0, 0, 0, 0, 1, 1, 5, 0, 0, 1, 1, 5, 0,
		0, 0, 0, 0, 0, 1, 1, 1, 1, 5, 1, 1, 1, 1, 5, 0
	};

	for (int i = 0; i < 14; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			gotoXY(_PositionX + i, _PositionY + j);
			switch (PlayerStatic[i][j])
			{
			case 0:cout << "  "; break;
			case 1:color(7); cout << "■"; break;
			case 2:color(9); cout << "■"; break;
			case 3:color(0); cout << "■"; break;
			case 4:color(12); cout << "■"; break;
			case 5:color(8); cout << "■"; break;
			case 6:color(1); cout << "■"; break;
			case 7:color(4); cout << "■"; break; color(15);
			}
		}
		cout << endl;
	}

}

//平a人物图片     参数为控制台光标初始位置
void CRole::printAttackPicture(int _x, int _y)
{
	int PlayerFight[14][16] = {
		0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 5, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 5, 0, 0,
		0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 5, 0,    //1浅灰色   2蓝色  3黑色  4红色
		0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5,    //5深灰色   6深蓝色   7深红色
		0, 0, 0, 0, 2, 2, 3, 2, 3, 2, 2, 2, 1, 1, 1, 5,    //0无色
		0, 0, 0, 0, 2, 2, 3, 2, 3, 2, 2, 2, 1, 1, 1, 5,
		0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 5,
		0, 0, 4, 7, 0, 0, 1, 1, 1, 1, 1, 2, 2, 6, 0, 0,
		0, 4, 4, 7, 0, 1, 1, 1, 1, 1, 2, 2, 1, 1, 5, 0,
		4, 4, 4, 4, 4, 4, 4, 2, 2, 2, 2, 4, 4, 4, 7, 0,
		0, 4, 4, 7, 0, 1, 1, 2, 2, 2, 1, 1, 1, 5, 0, 0,
		0, 0, 4, 7, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 5, 0,
		0, 0, 0, 0, 0, 0, 0, 1, 1, 5, 0, 0, 1, 1, 5, 0,
		0, 0, 0, 0, 0, 1, 1, 1, 1, 5, 1, 1, 1, 1, 5, 0
	};

	for (int i = 0; i < 14; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			gotoXY(_x + i, _y + j);
			switch (PlayerFight[i][j])
			{
			case 0:cout << "  "; break;
			case 1:color(7); cout << "■"; break;
			case 2:color(9); cout << "■"; break;
			case 3:color(0); cout << "■"; break;
			case 4:color(12); cout << "■"; break;
			case 5:color(8); cout << "■"; break;
			case 6:color(1); cout << "■"; break;
			case 7:color(4); cout << "■"; break; color(15);
			}
		}
		cout << endl;
	}

}

//清除人物图片(参数:图片左上角控制台坐标)
void CRole::cleanPixelPicture(int _x, int _y)
{
	for (int i = 0; i < 14; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			gotoXY(_x + i, _y + j);
			cout << "  ";
		}
		cout << endl;
	}
}

//升级
void CRole::upLevel()
{
	if (m_Experience < m_UpExperience)				//给予递归退出条件
		return;

	m_Experience -= m_UpExperience;				//首先减去升级所需经验
	m_Level++;													//等级提升
	upInfo();														//提升人物属性
	m_UpExperience = m_UpExperience + 125 * m_Level;		//提升升级所需经验，原数据加上125乘人物等级

	upLevel();			//递归，用于连续升级
}

//根据等级提升属性
void CRole::upInfo()
{
	if (1 == m_Level)			//1级时退出
		return;

	m_MaxHP = m_MaxHP + 200 * m_Level;
	m_MaxMP = m_MaxMP + 90 * m_Level;
	m_Atk = m_Atk + 15 * m_Level;
	m_Def = m_Def + 5 * m_Level;
}

//重载+运算符  增加经验和金钱
CRole& operator+(CRole &_role, CMonster &_monster)
{
	_role.m_Experience += _monster.getExperienceNum();
	_role.m_Golden += _monster.getGolden();

	return _role;
}

//技能1
int CRole::skill1(CMonster &_monster)
{
	int hurt = m_Atk*3 - _monster.getDef();
	m_MP -= 150;

	if (hurt < 0)				//判断伤害是否未负数，强行破甲
		hurt = 1;

	_monster.beenAtkAction(hurt);

	return hurt;
}

//打印技能1的图片     参数为控制台光标初始位置
void CRole::printSkill1Picture(int x, int y)
{
	int Skill1Arr[9][10] = {
		0, 0, 1, 1, 1, 1, 2, 2, 0, 0,//0无色   1黄色   2红色
		0, 2, 2, 1, 1, 1, 2, 2, 2, 0,
		2, 2, 2, 1, 1, 1, 1, 2, 2, 1,
		1, 1, 1, 1, 2, 2, 1, 1, 1, 1,
		2, 1, 1, 1, 2, 2, 1, 1, 1, 1,
		2, 1, 1, 1, 1, 1, 1, 2, 2, 1,
		2, 1, 3, 4, 3, 3, 4, 3, 2, 1,//3是白色    4是黑色
		0, 0, 3, 4, 3, 3, 4, 3, 0, 0,
		0, 0, 3, 3, 3, 3, 3, 3, 0, 0
	};

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			gotoXY(x + i, y + j);
			switch (Skill1Arr[i][j])
			{
			case 0:color(0); cout << "  "; break;
			case 1:color(14); cout << "■"; break;
			case 2:color(12); cout << "■"; break;
			case 3:color(15); cout << "■"; break;
			case 4:color(0); cout << "■"; break;
			}
		}
		cout << endl; color(15);
	}
}

//清除技能图片     参数为控制台光标初始位置
void CRole::cleanSkill1Picture(int x, int y)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			gotoXY(x + i, y + j);
			cout << "  ";
		}
	}
}