#include "CProcess.h"
#include "comment.h"
#include "CRole.h"

CProcess::CProcess()
{
	m_Name = "Process";
	m_HP = 1000;
	m_MP = 500;
	m_Atk = 80;
	m_Def = 30;
	m_MaxHP = 1000;
	m_MaxMP = 500;

	m_MonsterPictureX = 16;
	m_MonsterPictureY = 13;

	m_PattackM_X = 14;
	m_PattackM_Y = 24;

	m_MattackP_X = 16;
	m_MattackP_Y = 43;

	m_MinfoPut_X = 11;
	m_MinfoPut_Y = 17;

	m_ExperienceNum = 150;

	m_Golden = rand() % 100 + 100;
}

//打印血条蓝条 （参数：图片左上角控制台坐标）
void CProcess::tubePrint(int _x, int _y)
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
		default:break;
		}
	}
	color(15); cout << "  " << m_MP << "      ";
}

//静止站立Process图片(参数:图片左上角控制台坐标)
void CProcess::printStaticPicture(int _PositionX, int _PositionY)
{
	int MonsterStatic[8][11] = {
		0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0,
		1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1,
		1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1,
		1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
		0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0,
		0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0
	};

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			color(15);
			gotoXY(_PositionX + i, _PositionY + j);
			switch (MonsterStatic[i][j])
			{
				case 0:cout << "  "; break;
				case 1:cout << "■"; break;
			}
		}
		cout << endl;
	}
}

//平a  Process图片    参数为控制台光标初始坐标
void CProcess::printAttackPicture(int _PositionX, int _PositionY)
{
	int MonsterStaticArr_2[8][11] = {
		0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0,
		0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0,
		0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0,
		0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1,
		1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1,
		0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0
	};

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			color(15);
			gotoXY(_PositionX + i, _PositionY + j);
			switch (MonsterStaticArr_2[i][j])
			{
			case 0:cout << "  "; break;
			case 1:cout << "■"; break;
			}
		}
		cout << endl;
	}
}


//清除Process图片(参数:图片左上角控制台坐标)
void CProcess::cleanPixelPicture(int _PositionX, int _PositionY)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			gotoXY(_PositionX + i, _PositionY + j);
			cout << "  ";
		}
		cout << endl;
	}
}

//攻击
int CProcess::atkAction(CRole &_Role)
{
	int hurt = m_Atk - _Role.getDef();

	if (hurt < 0)				//判断伤害是否未负数，强行破甲
		hurt = 1;

	_Role.beenAtkAction(hurt);

	return hurt;
}

//被攻击
void CProcess::beenAtkAction(int _hurt)
{
	m_HP -= _hurt;
}