#include "CFightSys.h"
#include "comment.h"
#include "CMonster.h"
#include "CRole.h"
#include "CProcess.h"
#include "CCamerata.h"
#include "CBoss.h"
#include <mmstream.h>
#pragma comment(lib,"winmm.lib")

//打印战斗界面
void CFightSys::printFightUI()
{
	system("cls");
	int x = 2, y = 2;
	color(12);
	gotoXY(x++, y); cout << "╔═════════════════════════════╗";
	gotoXY(x++, y); cout << "║                                                          ║";
	gotoXY(x++, y); cout << "║                                                          ║";
	gotoXY(x++, y); cout << "║                                                          ║";
	gotoXY(x++, y); cout << "╚═════════════════════════════╝";
	color(15);

	x = 3, y = 3;
	gotoXY(x++, y); cout << "";
	gotoXY(x++, y); cout << "HP:";
	gotoXY(x++, y); cout << "MP:";

	x = 2, y = 47;
	color(11);
	gotoXY(x++, y); cout << "╔═════════════════════════════╗";
	gotoXY(x++, y); cout << "║                                                          ║";
	gotoXY(x++, y); cout << "║                                                          ║";
	gotoXY(x++, y); cout << "║                                                          ║";
	gotoXY(x++, y); cout << "╚═════════════════════════════╝";
	color(15);

	x = 3, y = 48;
	gotoXY(x++, y); cout << "";
	gotoXY(x++, y); cout << "HP:";
	gotoXY(x++, y); cout << "MP:";

	x = 2, y = 35;
	color(8);
	gotoXY(x++, y); cout << "┏━━━━━━━━┓";
	gotoXY(x++, y); cout << "┃  ※  攻击      ┃";
	gotoXY(x++, y); cout << "┣━━━━━━━━┫";
	gotoXY(x++, y); cout << "┃      技能      ┃";
	gotoXY(x++, y); cout << "┣━━━━━━━━┫";
	gotoXY(x++, y); cout << "┃      道具      ┃";
	gotoXY(x++, y); cout << "┣━━━━━━━━┫";
	gotoXY(x++, y); cout << "┃      逃跑      ┃";
	gotoXY(x++, y); cout << "┗━━━━━━━━┛";
	color(15);

}

//控制（在战斗中）      参数为怪物种类枚举
bool CFightSys::ctrlOfFight(MonsterType _MonsterType)
{
	if (0 == m_Player->getHP())
		return false;

	printFightUI();

	CMonster *pMonster = nullptr;	//定义一个怪物基类指针来控制与所有子类怪物的对战
	switch (_MonsterType)					//根据怪物种类生成子类
	{
		case MT_Process:pMonster = new CProcess; break;
		case MT_Camerata:pMonster = new CCamerata; break;
		case MT_Boss:pMonster = new CBoss;break;
		default:
			break;
	}

	upMonsterInfo(pMonster);

	gotoXY(SP_RnamePrintX, SP_RnamePrintY); color(14); cout << m_Player->getName(); color(15);
	m_Player->tubePrint(SP_PlayerTubeX, SP_PlayerTubeY);
	gotoXY(SP_MnamePrintX, SP_MnamePrintY); color(14); cout << pMonster->getName(); color(15);
	pMonster->tubePrint(SP_MonsterTubeX, SP_MonsterTubeY);
	pMonster->printStaticPicture(pMonster->m_MonsterPictureX, pMonster->m_MonsterPictureY);
	m_Player->printStaticPicture(m_Player->m_PlayerPictureX, m_Player->m_PlayerPictureY);

	int cursor = 3;
	char key = 0;
	//=======================战斗中的选择
	while (true)
	{
		key = _getch();

		switch (key)
		{
			case 's':
			case 'S':
			{
				gotoXY(cursor, 37); cout << "  ";
				cursor += 2;
				if (9 < cursor)
					cursor = 3;
				color(8); gotoXY(cursor, 37); cout << "※"; color(15);
			}break;

			case 'w':
			case 'W':
			{
				gotoXY(cursor, 37); cout << "  ";
				cursor -= 2;
				if (3 > cursor)
					cursor = 9;
				color(8); gotoXY(cursor, 37); cout << "※"; color(15);
			}break;

			//--------------------------------------战斗过程
			case ' ':
			{
				switch (cursor)
				{
					case FC_Atack://选择攻击
					{
						PaMvideo(pMonster);
						gotoXY(pMonster->m_MinfoPut_X, pMonster->m_MinfoPut_Y);
						color(12); cout << "-" << m_Player->atkAction(*pMonster); color(15);        //玩家攻击怪物数值计算
						_sleep(300);
						gotoXY(pMonster->m_MinfoPut_X, pMonster->m_MinfoPut_Y);
						cout << "            ";

						pMonster->tubePrint(SP_MonsterTubeX, SP_MonsterTubeY);		//怪物血条打印

						if (isMonsterDead(pMonster))		//怪物死亡
						{
							color(12);
							gotoXY(pMonster->m_MinfoPut_X, pMonster->m_MinfoPut_Y);
							cout << "挂  了";
							color(15);

							*m_Player + *pMonster;				//增加经验
							m_Player->upLevel();					//判断是否升级

							if (nullptr != pMonster)
								delete pMonster;							//释放内存
							_getch();
							return true;							//玩家胜利返回true
						}

						_sleep(500);							//****************************华丽的分割线

						MaPvideo(pMonster, _MonsterType);
						gotoXY(m_Player->m_RinfoPut_X, m_Player->m_RinfoPut_Y);
						color(12); cout << "-" << pMonster->atkAction(*m_Player); color(15);		 //怪物攻击玩家数值计算
						_sleep(300);
						gotoXY(m_Player->m_RinfoPut_X, m_Player->m_RinfoPut_Y);
						cout << "            ";

						m_Player->tubePrint(SP_PlayerTubeX, SP_PlayerTubeY);		//玩家血条打印

						if (isPlayerDead())			//玩家死亡
						{
							color(12);
							gotoXY(m_Player->m_RinfoPut_X, m_Player->m_RinfoPut_Y);
							cout << "挂  了";
							color(15);
							if (nullptr != pMonster)
								delete pMonster;							//释放内存
							_getch();
							return false;						//怪胜利返回false
						}

					}break;

					case FC_Skill://选择技能
					{
						int x = pMonster->m_MonsterPictureX - 3;
						int y = pMonster->m_MonsterPictureY;
						gotoXY(m_Player->m_RinfoPut_X, m_Player->m_RinfoPut_Y - 1);
						color(14); cout << "天 降 正 义"; color(15);
						PlaySound(TEXT("audio\\天降正义.wav"), NULL, SND_ASYNC);
						_sleep(500);
						gotoXY(m_Player->m_RinfoPut_X, m_Player->m_RinfoPut_Y - 2);
						cout << "                    ";

						//技能动画
						m_Player->printSkill1Picture(x, y);
						_sleep(300);
						m_Player->cleanSkill1Picture(x, y);
						_sleep(300);
						m_Player->printSkill1Picture(x + 4, y);
						_sleep(300);
						m_Player->cleanSkill1Picture(x + 4, y);
						_sleep(300);
						m_Player->printSkill1Picture(x + 8, y);
						_sleep(300);
						m_Player->cleanSkill1Picture(x + 8, y);
						pMonster->printStaticPicture(pMonster->m_MonsterPictureX, pMonster->m_MonsterPictureY);		//怪物图片复原

						gotoXY(pMonster->m_MinfoPut_X, pMonster->m_MinfoPut_Y); 
						color(12); cout << m_Player->skill1(*pMonster); color(15);
						_sleep(300);
						gotoXY(pMonster->m_MinfoPut_X, pMonster->m_MinfoPut_Y);
						cout << "            ";
						
						pMonster->tubePrint(SP_MonsterTubeX, SP_MonsterTubeY);		//怪物血条打印

						if (isMonsterDead(pMonster))		//怪物死亡
						{
							color(12);
							gotoXY(pMonster->m_MinfoPut_X, pMonster->m_MinfoPut_Y);
							cout << "挂  了";
							color(15);

							*m_Player + *pMonster;				//增加经验
							m_Player->upLevel();					//判断是否升级

							if (nullptr != pMonster)
								delete pMonster;							//释放内存
							_getch();
							return true;							//玩家胜利返回true
						}

						_sleep(500);							//****************************华丽的分割线

						MaPvideo(pMonster, _MonsterType);
						gotoXY(m_Player->m_RinfoPut_X, m_Player->m_RinfoPut_Y);
						color(12); cout << "-" << pMonster->atkAction(*m_Player); color(15);		 //怪物攻击玩家数值计算
						_sleep(300);
						gotoXY(m_Player->m_RinfoPut_X, m_Player->m_RinfoPut_Y);
						cout << "            ";

						m_Player->tubePrint(SP_PlayerTubeX, SP_PlayerTubeY);		//玩家血条打印

						if (isPlayerDead())			//玩家死亡
						{
							color(12);
							gotoXY(m_Player->m_RinfoPut_X, m_Player->m_RinfoPut_Y);
							cout << "挂  了";
							color(15);
							if (nullptr != pMonster)
								delete pMonster;							//释放内存
							_getch();
							return false;						//怪胜利返回false
						}
					}break;

					case FC_Item://选择背包
					{
						m_Player->m_Bag.printBag(SP_FightBagPrintX, SP_FightBagPrintY);
						m_Player->ctrlOfBagInFight(SP_FightBagPrintX, SP_FightBagPrintY);
					}break;

					case FC_Run://选择逃跑
					{
						int r = rand() % 100;
						if (60 >	r)						//60%几率逃跑
						{
							delete pMonster;							//释放内存
							system("cls");
							return false;
						}

						MaPvideo(pMonster, _MonsterType);
						gotoXY(m_Player->m_RinfoPut_X, m_Player->m_RinfoPut_Y);
						color(12); cout << "-" << pMonster->atkAction(*m_Player); color(15);		 //怪物攻击玩家数值计算
						_sleep(300);
						gotoXY(m_Player->m_RinfoPut_X, m_Player->m_RinfoPut_Y);
						cout << "            ";

						m_Player->tubePrint(SP_PlayerTubeX, SP_PlayerTubeY);		//玩家血条打印

						if (isPlayerDead())			//玩家死亡
						{
							color(12);
							gotoXY(m_Player->m_RinfoPut_X, m_Player->m_RinfoPut_Y);
							cout << "挂  了";
							color(15);
							if (nullptr != pMonster)
								delete pMonster;							//释放内存
							_getch();
							return false;						//怪胜利返回false
						}


					}break;
				}

			}break;
			//----------------------------------------------
		}
	}
	//===============================
}

//根据人物等级提升怪的属性
void CFightSys::upMonsterInfo(CMonster *_pMonster)
{
	int _level = m_Player->getLevel();
	if (1 == _level)
		return;

	_pMonster->setAtk(_pMonster->getAtk() + 20 * _level);
	_pMonster->setDef(_pMonster->getDef() + 5 * _level);
	_pMonster->setHP(_pMonster->getHP() + 300 * _level);
	_pMonster->setMP(_pMonster->getMP() + 50 * _level);
}

//判断怪是否死亡			死亡返回true
bool CFightSys::isMonsterDead(const CMonster *_monster)
{
	if (0 >= _monster->getHP())
		return true;

	return false;
}

//判断人物是否死亡        死亡返回true
bool CFightSys::isPlayerDead()
{
	if (0 >= m_Player->getHP())
		return true;

	return false;
}

//角色攻击怪动画
void CFightSys::PaMvideo(CMonster *pMonster)
{
	m_Player->cleanPixelPicture(m_Player->m_PlayerPictureX, m_Player->m_PlayerPictureY);    //先清除图片
	m_Player->printStaticPicture(pMonster->m_PattackM_X, pMonster->m_PattackM_Y);	//将人物挪过去
	_sleep(150);
	m_Player->printAttackPicture(pMonster->m_PattackM_X, pMonster->m_PattackM_Y);		//打印攻击图画
	PlaySound(TEXT("audio\\打击.wav"), NULL, SND_ASYNC);
	_sleep(200);
	m_Player->cleanPixelPicture(pMonster->m_PattackM_X, pMonster->m_PattackM_Y);		//清除图片
	_sleep(150);
	m_Player->printStaticPicture(m_Player->m_PlayerPictureX, m_Player->m_PlayerPictureY);		//人物归位
	pMonster->printStaticPicture(pMonster->m_MonsterPictureX, pMonster->m_MonsterPictureY);		//怪物图片复原
}

//怪攻击角色动画		参数为怪物指针
void CFightSys::MaPvideo(CMonster *pMonster,MonsterType _MonsterType)
{
	pMonster->cleanPixelPicture(pMonster->m_MonsterPictureX, pMonster->m_MonsterPictureY);		//先清除图片
	pMonster->printStaticPicture(pMonster->m_MattackP_X, pMonster->m_MattackP_Y);		//将怪物挪过去
	_sleep(150);
	pMonster->printAttackPicture(pMonster->m_MattackP_X, pMonster->m_MattackP_Y);		//打印攻击图画
	if (MT_Boss == _MonsterType)
		PlaySound(TEXT("audio\\喷火.wav"), NULL, SND_ASYNC);
	else
		PlaySound(TEXT("audio\\打击.wav"), NULL, SND_ASYNC);
	_sleep(200);
	pMonster->cleanPixelPicture(pMonster->m_MattackP_X, pMonster->m_MattackP_Y);		//	清除图片
	_sleep(150);
	pMonster->printStaticPicture(pMonster->m_MonsterPictureX, pMonster->m_MonsterPictureY);		//怪物归为
	m_Player->printStaticPicture(m_Player->m_PlayerPictureX, m_Player->m_PlayerPictureY);		//人物图片还原
}