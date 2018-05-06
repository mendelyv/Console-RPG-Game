#include "BackGround.h"
#include"CMap.h"
#include "comment.h"
#include "Game.h"
#include "CUISceneSys.h"
#include "CBagSys.h"
#include "CFightSys.h"
#include "CESC.h"
#include "CBeginScene.h"

CMap::CMap()
{
	m_pMap = nullptr;
	m_Row = 0;
	m_Col = 0;
	m_isBody = false;
}

CMap::~CMap()
{
	if (nullptr == m_pMap)
		return;

	for (int i = 0; i < m_Row; i++)
	{
		if (nullptr != m_pMap[i])
		{
			delete[] m_pMap[i];
			m_pMap[i] = nullptr;
		}
	}

	delete[] m_pMap;
	m_pMap = nullptr;
}

//开辟内存
void CMap::initMemory()
{
	m_pMap = new int *[m_Row];
	if (nullptr == m_pMap)
	{
		return;
	}
	for (int i = 0; i < m_Row; i++)
	{
		m_pMap[i] = new int[m_Col];
	}
}

//从文件读入地图信息
void CMap::setMapFromFile(char *_FileName)
{
	FILE  *pf = fopen(_FileName, "r");
	fscanf(pf, "Row:%d Col:%d", &m_Row, &m_Col);
	initMemory();
	for (int i = 0; i < m_Row; i++)
	{
		for (int j = 0; j < m_Col; j++)
		{
			fscanf(pf, "%d,", &m_pMap[i][j]);
		}
		fscanf(pf, "\n");
	}

	fscanf(pf, "TX:%d TY:%d", &m_textPositionX, &m_textPositionY);

	fclose(pf);
}

//打印地图
void CMap::print()
{
	system("cls");

	for (int i = 0; i < m_Row; i++)
	{
		for (int j = 0; j < m_Col; j++)
		{
			switch (m_pMap[i][j])
			{
				case None:cout << "  "; break;
				case Road:cout << "  "; break;
				case Border:cout << "◇"; break;
				case Roof_Blue:color(9); cout << "■"; color(15); break;
				case Roof_Red:color(12); cout << "■"; color(15); break;
				case Roof_White:color(15); cout << "■"; break;
				case Wall:color(7); cout << "■"; color(15); break;
				case RoofTriangle3:color(4); cout << "◣"; color(15); break;
				case RoofTriangle4:color(12); cout << "◢"; color(15); break;
				case Tree:color(10); cout << "Ψ"; color(15); break;
				case Grass:color(2); cout << "ω"; color(15); break;
				case Water:color(9); cout << "≈"; color(15); break;
				case Window:color(11); cout << "田"; color(15); break;
				case Fence:color(6); cout << "▓"; color(15); break;
				case Body:color(9); cout << "♂"; color(15); break;
				case Weapon_Person:color(13); cout << "武"; color(15); break;
				case Medicine_Person:color(10); cout << "药"; color(15); break;
				case Corselet_Person:color(11); cout << "防"; color(15); break;

				case MT_Process:color(8); cout << "P "; color(15); break;
				case MT_Camerata:color(4); cout << "C "; color(15); break;
				case MT_Boss:color(12); cout << "B "; color(15); break;
					
				//地图上不可见的特殊点：

				//各种传送点
				case ShopToMap2:
				case Map3ToMap2:
				case Map3ToMap4:
				case Map2ToMap1:
				case Map2ToShop:
				case Map2ToMap3:
				case Map1ToMap2:cout << "  "; break;

				case BossToMap5:
				case Map4ToMap3:
				case Map5ToBoss:
				case Map4ToMap5:
				case Map5ToMap4:color(5); cout << "◎"; color(15); break;
				

				default:
					break;
			}
		}
		cout << endl;
	}
}

//控制（在地图中）
void CMap::ctrlOfMap()
{
	print();
	int x = 0, y = 0;

	m_Player->print();

	char key = 0;

	while (true)
	{
		key = _getch();
		switch (key)
		{
			case 'w':
			case 'W':interactOfMapElement(-1, 0);break;

			case 'a':
			case 'A':interactOfMapElement(0, -1); break;

			case 's':
			case 'S':interactOfMapElement(1, 0);break;

			case 'd':
			case 'D':interactOfMapElement(0, 1); break;

			case 'i':
			case 'I':									//按 I 打印人物信息    
				printPlayerInfo(); 
				if (_getch())						//按任意键清除人物信息
					cleanRoleInfo();
				break;

			case 'b':
			case 'B':								//按 B 查看背包
				m_Player->outputBag(m_textPositionX,m_textPositionY);
				m_Player->ctrlOfBag(m_textPositionX, m_textPositionY);
				break;

			case 'p':
			case 'P':								//按 P 查看装备栏
				m_Player->outputEquip(m_textPositionX, m_textPositionY); 
				m_Player->ctrlOfEquip(m_textPositionX, m_textPositionY);
				break;

			case '\r':								//后门，方便演示使用
			{
				char dad[30] = "whosyourdaddy";
				char money[30] = "show me the money";
				char sr[255] = { 0 };
				gotoXY(m_textPositionX, m_textPositionY);
				gets(sr);
				gotoXY(m_textPositionX, m_textPositionY); cout << "                              ";
				if (0 == strcmp(dad, sr))
				{
					m_Player->setAtk(1000000);
				}
				else if (0 == strcmp(money, sr))
				{
					m_Player->setGolden(m_Player->getGolden() + 10000);
				}
			}break;
				
			case 27:								//按 ESC 键退出游戏
			{
				system("cls");
				CESC::getInstance()->setPlayer(m_Player);			//将玩家放入ESC系统方便释放内存
				int flag = CESC::getInstance()->ctrlOfSence();
				CESC::getInstance()->action(flag);

				print();
				m_Player->print();
			}break;
		}
	}
}

//地图交互（返回值为地图元素）
int CMap::interactOfMap(int dx, int dy)
{
	int R_x, R_y;
	m_Player->getPosition(R_x, R_y);
	int _NewX = R_x + dx;
	int _NewY = R_y + dy;

	return m_pMap[_NewX][_NewY];
}

//接收返回值做出相应工作
void CMap::interactOfMapElement(int dx,int dy)
{
	//根据元素做出相应动作
	switch (interactOfMap(dx, dy))
	{
			//碰到可以移动的元素的行为
		case Grass:
		case Road:rePrint(); m_Player->move(dx, dy); m_Player->print(); break;

			//碰到导向尸体的行为
		case Body:
			collisionBody();
			print();
			m_Player->print();
			break;

			//碰撞商人触发行为
		case Weapon_Person:
		{
			CBagSys::getInstance()->setPlayer(m_Player);					//将玩家丢入背包系统
			CBagSys::getInstance()->showItem(m_textPositionX, m_textPositionY, IN_Weapon); 
		}break;

		case Medicine_Person:
		{
			CBagSys::getInstance()->setPlayer(m_Player);
			CBagSys::getInstance()->showItem(m_textPositionX, m_textPositionY, IN_Medicine); 
		} break;

		case Corselet_Person:
		{
			CBagSys::getInstance()->setPlayer(m_Player);
			CBagSys::getInstance()->showItem(m_textPositionX, m_textPositionY, IN_Corselet); 
		} break;

			//碰撞传送点触发行为
		case Map1ToMap2:m_Player->setPosition(10, 5); CUISceneSys::getInstance()->changeInMap(MN_Map2, m_Player); break;
		case Map2ToMap1:m_Player->setPosition(13, 4); CUISceneSys::getInstance()->changeInMap(MN_Map1, m_Player); break;
		case Map2ToMap3:m_Player->setPosition(1, 3); CUISceneSys::getInstance()->changeInMap(MN_Map3, m_Player); break;
		case Map3ToMap2:m_Player->setPosition(28, 22); CUISceneSys::getInstance()->changeInMap(MN_Map2, m_Player); break;
		case Map2ToShop:m_Player->setPosition(18, 12); CUISceneSys::getInstance()->changeInMap(MN_Shop, m_Player); break;
		case ShopToMap2:m_Player->setPosition(24, 11); CUISceneSys::getInstance()->changeInMap(MN_Map2, m_Player); break;
		case Map3ToMap4:m_Player->setPosition(15, 2); CUISceneSys::getInstance()->changeInMap(MN_Map4, m_Player); break;
		case Map4ToMap5:m_Player->setPosition(2, 28); CUISceneSys::getInstance()->changeInMap(MN_Map5, m_Player); break;
		case Map4ToMap3:m_Player->setPosition(26, 28); CUISceneSys::getInstance()->changeInMap(MN_Map3, m_Player); break;
		case Map5ToMap4:m_Player->setPosition(27, 11); CUISceneSys::getInstance()->changeInMap(MN_Map4, m_Player); break;
		case Map5ToBoss:m_Player->setPosition(2, 2); CUISceneSys::getInstance()->changeInMap(MN_Boss, m_Player); break;
		case BossToMap5:m_Player->setPosition(27, 1); CUISceneSys::getInstance()->changeInMap(MN_Map5, m_Player); break;

			//碰撞怪触发行为
		case MT_Process:
		{
			//CFightSys::getInstance()->printFightUI();
			CFightSys::getInstance()->setPlayer(m_Player);
			if (CFightSys::getInstance()->ctrlOfFight(MT_Process))
				m_pMap[m_Player->getPositionX() + dx][m_Player->getPositionY() + dy] = Road;
			print();
			m_Player->print();
		}break;

		case MT_Camerata:
		{
			//CFightSys::getInstance()->printFightUI();
			CFightSys::getInstance()->setPlayer(m_Player);
			if (CFightSys::getInstance()->ctrlOfFight(MT_Camerata))
				m_pMap[m_Player->getPositionX() + dx][m_Player->getPositionY() + dy] = Road;
			print();
			m_Player->print();
		}break;

		case MT_Boss:
		{
			//CFightSys::getInstance()->printFightUI();
			CFightSys::getInstance()->setPlayer(m_Player);
			if (1 == CFightSys::getInstance()->ctrlOfFight(MT_Boss))
				m_pMap[m_Player->getPositionX() + dx][m_Player->getPositionY() + dy] = Road;
			print();
			m_Player->print();
		}break;
	}
}

//归还地图元素
void CMap::rePrint()
{
	int x = 0, y = 0;
	m_Player->getPosition(x, y);
	switch (m_pMap[x][y])
	{
		case Road:gotoXY(x, y); cout << "  "; break;
		case Grass:gotoXY(x, y); color(2); cout << "ω"; color(15); break;
		case MT_Process:color(8); cout << "P "; color(15); break;
		case MT_Camerata:color(4); cout << "C "; color(15); break;
		case MT_Boss:color(12); cout << "B "; color(15); break;
		default:
			break;
	}
}

//在文本输出点打印角色信息
void CMap::printPlayerInfo()
{
	int x = m_textPositionX;
	int y = m_textPositionY;
	gotoXY(x++, y); color(15); cout <<"Name : "<< m_Player->getName();
	gotoXY(x++, y);
	gotoXY(x++, y); color(12); cout <<"HP : "<< m_Player->getHP() << "\\" << m_Player->getMaxHP();
	gotoXY(x++, y); color(9); cout << "MP : "<<m_Player->getMP() << "\\" << m_Player->getMaxMP();
	gotoXY(x++, y); 
	gotoXY(x++, y); color(13); cout << "Atk : " << m_Player->getAtk();
	gotoXY(x++, y); color(11); cout << "Def : " << m_Player->getDef();
	gotoXY(x++, y); color(3); cout << "Lv : " << m_Player->getLevel();
	gotoXY(x++, y); color(8); cout << "Exp : " << m_Player->getExperience() <<"\\"<< m_Player->getUpExperience();
	gotoXY(x++, y);
	gotoXY(x++, y); color(14); cout << "Golden : " << m_Player->getGolden(); color(15);
}

//清理在控制台输出的角色的各种信息
void CMap::cleanRoleInfo()
{
	for (int i = m_textPositionX; i < 30; i++)
	{
		for (int j = m_textPositionY; j < 50; j++)
		{
			gotoXY(i, j); cout << "  ";
		}
	}
}

//碰到导向尸体触发函数
void CMap::collisionBody()
{
	int x = 16;
	int y = 32;
	if (true == m_isBody)
		return;
	system("cls");
	gotoXY(x, y); cout << "Hi，不要伤心...";
	_getch();
	system("cls");
	gotoXY(x, y); cout << "快离开这个城市...";
	_getch();

	m_isBody = true;
	map<int, CItem>::iterator iter = CBagSys::getInstance()->m_ItemContainer.begin();
	while (30000 != iter->second.m_ID)
		iter++;

	m_Player->m_Bag.addItem(iter->second);
}