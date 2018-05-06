#include "CESC.h"
#include "comment.h"
#include "Game.h"
#include "CBeginScene.h"
#include "CUISceneSys.h"

//打印界面
void CESC::print()
{
	int x = 15;
	int y = 30;

	gotoXY(x++, y); cout << "┏                              ┓";
	gotoXY(x++, y); cout << "            继 续 游 戏           ";
	gotoXY(x++, y); cout << "            保 存 游 戏           ";
	gotoXY(x++, y); cout << "            回 主 选 单           ";
	gotoXY(x++, y); cout << "            退 出 游 戏           ";
	gotoXY(x++, y); cout << "┗                              ┛";
}

//控制（在ESC场景中）
int CESC::ctrlOfSence()
{
	system("cls");

	print();

	int x = 16, y = 36;
	gotoXY(x, y); color(16 * 15 + 0); cout << "继 续 游 戏"; color(15);
	char key = 0;
	while (true)
	{
		key = _getch();
		switch (key)
		{
		case 'w':
		case 'W':
			switch (x)//靠光标所在行坐标判断选择
			{
			case 16:
				gotoXY(x, y); color(15); cout << "继 续 游 戏";
				x = 19;
				gotoXY(x, y); color(16 * 15 + 0); cout << "退 出 游 戏"; color(15);
				break;
			case 17:
				gotoXY(x, y); color(15); cout << "保 存 游 戏";
				x = 16;
				gotoXY(x, y); color(16 * 15 + 0); cout << "继 续 游 戏"; color(15);
				break;
			case 18:
				gotoXY(x, y); color(15); cout << "回 主 选 单";
				x = 17;
				gotoXY(x, y); color(16 * 15 + 0); cout << "保 存 游 戏"; color(15);
				break;
			case 19:
				gotoXY(x, y); color(15); cout << "退 出 游 戏";
				x = 18;
				gotoXY(x, y); color(16 * 15 + 0); cout << "回 主 选 单"; color(15);
				break;
			}
			break;

		case 's':
		case 'S':
			switch (x)//靠光标所在行坐标判断选择
			{
			case 16:
				gotoXY(x, y); color(15); cout << "继 续 游 戏";
				x = 17;
				gotoXY(x, y); color(16 * 15 + 0); cout << "保 存 游 戏"; color(15);
				break;
			case 17:
				gotoXY(x, y); color(15); cout << "保 存 游 戏";
				x = 18;
				gotoXY(x, y); color(16 * 15 + 0); cout << "回 主 选 单"; color(15);
				break;
			case 18:
				gotoXY(x, y); color(15); cout << "回 主 选 单";
				x = 19;
				gotoXY(x, y); color(16 * 15 + 0); cout << "退 出 游 戏"; color(15);
				break;
			case 19:
				gotoXY(x, y); color(15); cout << "退 出 游 戏";
				x = 16;
				gotoXY(x, y); color(16 * 15 + 0); cout << "继 续 游 戏"; color(15);
				break;
			}
			break;

		case '\r':
		case ' ':
			switch (x)//靠光标所在行坐标判断选择
			{
			case E_Continue: return E_Continue; break;
			case E_Save: return E_Save; break;
			case E_Menu: return E_Menu; break;
			case E_Exit: return E_Exit; break;
			}
			break;

		default:break;

		}
	}
}

//根据选择做出动作   参数为光标位置
void CESC::action(int cursor)
{
	switch (cursor)
	{
		case E_Continue:
		{
			return;
		}break;

		case E_Save:
		{
			saveInXML();
		}break;

		case E_Menu:
		{
			if (m_Player != nullptr)				//回主选单需要释放内存
			{
				delete m_Player;
				m_Player = nullptr;
			}
			int flag = CBeginScene::getInstance()->ctrlOfScene();
			CBeginScene::getInstance()->action(flag);
		}break;

		case E_Exit:
		{
			if (nullptr != m_Player)				//回主选单需要释放内存
			{
				delete m_Player;
				m_Player = nullptr;
			}
			CUISceneSys::getInstance()->freeAllMap();
			exit(NULL);
		}break;

		default:
			break;
	}
}

//存到XML文件中
void CESC::saveInXML()
{
	TiXmlDocument doc;
	//存放角色信息
	TiXmlElement *pRole = new TiXmlElement("Role");
	pRole->SetAttribute("Name", m_Player->getName().c_str());
	pRole->SetAttribute("HP", m_Player->getHP());
	pRole->SetAttribute("MP", m_Player->getMP());
	pRole->SetAttribute("Atk", m_Player->getAtk());
	pRole->SetAttribute("Def", m_Player->getDef());
	pRole->SetAttribute("Level", m_Player->getLevel());
	pRole->SetAttribute("MaxHP", m_Player->getMaxHP());
	pRole->SetAttribute("MaxMP", m_Player->getMaxMP());
	pRole->SetAttribute("Golden", m_Player->getGolden());
	pRole->SetAttribute("MapName", m_Player->getInMapName());
	pRole->SetAttribute("Experience", m_Player->getExperience());
	pRole->SetAttribute("UpExperience", m_Player->getUpExperience());
	pRole->SetAttribute("PositionX", m_Player->getPositionX());
	pRole->SetAttribute("PositionY", m_Player->getPositionY());
	pRole->SetAttribute("BagSize", m_Player->getBagSize());

	//存放背包信息
	for (int i = 0; i < m_Player->m_Bag.m_BagContainer.size();i++)
	{
		TiXmlElement *pItem = new TiXmlElement("Item");

		pItem->SetAttribute("Name", m_Player->m_Bag.m_BagContainer[i].m_Name.c_str());
		pItem->SetAttribute("Type", m_Player->m_Bag.m_BagContainer[i].m_Type);
		pItem->SetAttribute("Num", m_Player->m_Bag.m_BagContainer[i].m_Num);
		pItem->SetAttribute("ID", m_Player->m_Bag.m_BagContainer[i].m_ID);
		pItem->SetAttribute("HP", m_Player->m_Bag.m_BagContainer[i].m_HP);
		pItem->SetAttribute("MP", m_Player->m_Bag.m_BagContainer[i].m_MP);
		pItem->SetAttribute("Overly", m_Player->m_Bag.m_BagContainer[i].m_Overly);
		pItem->SetAttribute("Price", m_Player->m_Bag.m_BagContainer[i].m_Price);
		pItem->SetAttribute("Atk", m_Player->m_Bag.m_BagContainer[i].m_Atk);
		pItem->SetAttribute("Def", m_Player->m_Bag.m_BagContainer[i].m_Def);

		TiXmlText *pText = new TiXmlText(m_Player->m_Bag.m_BagContainer[i].m_Describe.c_str());
		pItem->LinkEndChild(pText);

		pRole->LinkEndChild(pItem);
	}

	//存放装备栏信息
	map<int, CItem>::iterator iter_2 = m_Player->m_Equip.m_EquipContainer.begin();
	while (iter_2 != m_Player->m_Equip.m_EquipContainer.end())
	{
		TiXmlElement *pEquip = new TiXmlElement("Equip");

		pEquip->SetAttribute("Name", iter_2->second.m_Name.c_str());
		pEquip->SetAttribute("Type", iter_2->second.m_Type);
		pEquip->SetAttribute("Num", iter_2->second.m_Num);
		pEquip->SetAttribute("ID", iter_2->second.m_ID);
		pEquip->SetAttribute("HP", iter_2->second.m_HP);
		pEquip->SetAttribute("MP", iter_2->second.m_MP);
		pEquip->SetAttribute("Overly", iter_2->second.m_Overly);
		pEquip->SetAttribute("Price", iter_2->second.m_Price);
		pEquip->SetAttribute("Atk", iter_2->second.m_Atk);
		pEquip->SetAttribute("Def", iter_2->second.m_Def);

		TiXmlText *pText = new TiXmlText(iter_2->second.m_Describe.c_str());
		pEquip->LinkEndChild(pText);

		pRole->LinkEndChild(pEquip);
		iter_2++;
	}

	doc.LinkEndChild(pRole);
	doc.SaveFile("save\\Role.xml");
}