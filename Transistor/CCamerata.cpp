#include "CCamerata.h"
#include "comment.h"
#include "CRole.h"

CCamerata::CCamerata()
{
	m_Name = "Camerata";
	m_HP = 2200;
	m_MP = 800;
	m_Atk = 140;
	m_Def = 45;
	m_MaxHP = 2200;
	m_MaxMP = 800;

	m_MonsterPictureX = 14;
	m_MonsterPictureY = 12;

	m_PattackM_X = 14;
	m_PattackM_Y = 28;

	m_MattackP_X = 14;
	m_MattackP_Y = 38;

	m_MinfoPut_X = 10;
	m_MinfoPut_Y = 19;

	m_ExperienceNum = 350;

	m_Golden = rand() % 200 + 300;
}

//打印血条蓝条 （参数：图片左上角控制台坐标）
void CCamerata::tubePrint(int _x, int _y)
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
void CCamerata::printStaticPicture(int _PositionX, int _PositionY)
{
	int MonsterStatic_1[14][15] = {
		0, 0, 0, 0, 0, 1, 1, 1, 1, 4, 0, 0, 0, 0, 0,  //1红色  2白色   3蓝色
		0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 4, 0, 0, 0,  //4深红色  5深蓝色   6灰色
		0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 0, 0,  //0无色
		0, 1, 1, 1, 2, 2, 1, 1, 1, 1, 2, 2, 1, 4, 0,
		0, 1, 1, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 6, 0,
		0, 1, 1, 2, 2, 3, 3, 1, 1, 2, 2, 3, 3, 5, 0,
		1, 1, 1, 2, 2, 3, 3, 1, 1, 2, 2, 3, 3, 1, 4,
		1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 2, 2, 1, 1, 4,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4,
		1, 1, 1, 1, 4, 1, 1, 1, 1, 4, 1, 1, 1, 1, 4,
		0, 1, 1, 4, 0, 0, 1, 1, 4, 0, 0, 1, 1, 4, 0
	};

	for (int i = 0; i < 14; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			gotoXY(_PositionX + i, _PositionY + j);
			switch (MonsterStatic_1[i][j])
			{
				case 0:cout << "  "; break;
				case 1:color(12); cout << "■"; break;
				case 2:color(15); cout << "■"; break;
				case 3:color(9); cout << "■"; break;
				case 4:color(4); cout << "■"; break;
				case 5:color(1); cout << "■"; break;
				case 6:color(8); cout << "■"; break;
			}
		}
		cout << endl;
	}

}

//平a  Process图片    参数为控制台光标初始坐标
void CCamerata::printAttackPicture(int _PositionX, int _PositionY)
{
	int MonsterStatic_2[14][15] = {
		0, 0, 0, 0, 0, 1, 1, 1, 1, 4, 0, 0, 0, 0, 0,  //1红色  2白色   3蓝色
		0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 4, 0, 0, 0,  //4深红色  5深蓝色   6灰色
		0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 0, 0,  //0无色
		0, 1, 1, 1, 2, 2, 1, 1, 1, 1, 2, 2, 1, 4, 0,
		0, 1, 1, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 6, 0,
		0, 1, 1, 2, 2, 3, 3, 1, 1, 2, 2, 3, 3, 5, 0,
		1, 1, 1, 2, 2, 3, 3, 1, 1, 2, 2, 3, 3, 1, 4,
		1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 2, 2, 1, 1, 4,
		1, 1, 1, 1, 1, 1, 1, 1, 4, 1, 1, 1, 1, 1, 4,
		1, 1, 1, 1, 1, 1, 1, 4, 0, 0, 1, 1, 1, 1, 4,
		1, 1, 1, 1, 1, 1, 1, 1, 4, 1, 1, 1, 1, 1, 4,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4,
		1, 1, 1, 1, 4, 1, 1, 1, 1, 4, 1, 1, 1, 1, 4,
		0, 0, 1, 1, 1, 0, 1, 1, 4, 0, 1, 1, 1, 0, 0
	};

	for (int i = 0; i < 14; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			gotoXY(_PositionX + i, _PositionY + j);
			switch (MonsterStatic_2[i][j])
			{
			case 0:cout << "  "; break;
			case 1:color(12); cout << "■"; break;
			case 2:color(15); cout << "■"; break;
			case 3:color(9); cout << "■"; break;
			case 4:color(4); cout << "■"; break;
			case 5:color(1); cout << "■"; break;
			case 6:color(8); cout << "■"; break;
			}
		}
		cout << endl;
	}

}

//清除Process图片(参数：图片左上角控制台坐标)
void CCamerata::cleanPixelPicture(int _PositionX, int _PositionY)
{
	for (int i = 0; i < 14; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			gotoXY(_PositionX + i, _PositionY + j);
			cout << "  ";
		}
		cout << endl;
	}
}

//攻击
int CCamerata::atkAction(CRole &_Role)
{
	int hurt = m_Atk - _Role.getDef();

	if (hurt < 0)				//判断伤害是否未负数，强行破甲
		hurt = 1;

	_Role.beenAtkAction(hurt);

	return hurt;
}

//被攻击
void CCamerata::beenAtkAction(int _hurt)
{
	m_HP -= _hurt;
}