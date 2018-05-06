#include "CBoss.h"
#include "comment.h"
#include "CRole.h"

CBoss::CBoss()
{
	m_Name = "Royce";
	m_HP = 20480;
	m_MP = 12000;
	m_Atk = 500;
	m_Def = 360;
	m_MaxHP = 20480;
	m_MaxMP = 12000;

	m_MonsterPictureX = 13;
	m_MonsterPictureY = 12;

	m_PattackM_X = 13;
	m_PattackM_Y = 28;

	m_MattackP_X = 13;
	m_MattackP_Y = 34;

	m_MinfoPut_X = 10;
	m_MinfoPut_Y = 19;

	m_ExperienceNum = 15000;

	m_Golden = 15000;
}


//打印血条蓝条 （参数：图片左上角控制台坐标）
void CBoss::tubePrint(int _x, int _y)
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


//静止站立Royce图片(参数:图片左上角控制台坐标)
void CBoss::printStaticPicture(int _PositionX, int _PositionY)
{
	int MonsterStatic_1[15][15] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 5, 0, 0, 0,      //1绿色  2白色   3黑色   4红色
		0, 0, 0, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 5, 0,     //5深绿色    6灰色    7深灰    8深红
		0, 0, 2, 3, 3, 2, 1, 1, 1, 2, 3, 2, 3, 7, 0,   //0无色
		0, 2, 3, 3, 3, 2, 1, 3, 2, 3, 2, 3, 2, 6, 0, 
		0, 2, 2, 3, 2, 1, 3, 1, 1, 1, 1, 1, 1, 5, 0,
		0, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 5, 0, 0,
		0, 4, 4, 4, 1, 1, 1, 1, 1, 1, 5, 0, 0, 0, 0,
		4, 4, 4, 4, 4, 4, 1, 1, 5, 0, 0, 0, 0, 0, 0,
		4, 8, 4, 8, 4, 1, 1, 1, 1, 5, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 5, 4, 8, 0,
		1, 5, 0, 0, 1, 1, 4, 1, 1, 1, 1, 5, 4, 8, 0,
		1, 1, 1, 1, 1, 1, 4, 1, 1, 1, 1, 4, 8, 0, 0,
		0, 1, 1, 1, 5, 4, 4, 4, 4, 8, 0, 4, 8, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	};

	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			gotoXY(_PositionX + i, _PositionY + j);
			switch (MonsterStatic_1[i][j])
			{
			case 0:cout << "  "; break;
			case 1:color(10); cout << "■"; break;
			case 2:color(15); cout << "■"; break;
			case 3:color(0); cout << "■"; break;
			case 4:color(12); cout << "■"; break;
			case 5:color(2); cout << "■"; break;
			case 6:color(7); cout << "■"; break;
			case 7:color(8); cout << "■"; break;
			case 8:color(4); cout << "■"; break;
			case 9:color(14); cout << "■"; break;
			case 10:color(6); cout << "■"; break;
			}
		}
		cout << endl;
	}
}

//平a  Royac图片    参数为控制台光标初始坐标
void CBoss::printAttackPicture(int _PositionX, int _PositionY)
{
	int MonsterStatic_2[15][20] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0,
		0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 5, 0, 0, 0, 0, 0, 10, 4, 8,		//1绿色  2白色   3黑色   4红色
		0, 0, 0, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 5, 0, 0, 9, 10, 4, 8,		//5深绿色    6灰色    7深灰    8深红
		0, 0, 2, 3, 3, 2, 1, 1, 1, 2, 3, 2, 3, 7, 0, 9, 9, 10, 4, 4,		//0无色
		0, 2, 3, 3, 3, 2, 1, 3, 2, 3, 2, 3, 2, 6, 0, 0, 0, 4, 4, 0, 
		0, 2, 2, 3, 2, 1, 3, 1, 1, 1, 1, 1, 1, 5, 0, 0, 0, 0, 0, 0,			//9浅黄    10黄
		0, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 5, 0, 0, 0, 0, 0, 0, 0,
		0, 4, 4, 4, 1, 1, 1, 1, 1, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		4, 4, 4, 4, 4, 4, 1, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		4, 8, 4, 8, 4, 1, 1, 1, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 5, 4, 8, 0, 0, 0, 0, 0, 0,
		1, 5, 0, 0, 1, 1, 4, 1, 1, 1, 1, 5, 4, 8, 0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 1, 4, 1, 1, 1, 1, 4, 8, 0, 0, 0, 0, 0, 0, 0,
		0, 1, 1, 1, 5, 4, 4, 4, 4, 8, 0, 4, 8, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};

	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			gotoXY(_PositionX + i, _PositionY + j);
			switch (MonsterStatic_2[i][j])
			{
				case 0:cout << "  "; break;
				case 1:color(10); cout << "■"; break;
				case 2:color(15); cout << "■"; break;
				case 3:color(0); cout << "■"; break;
				case 4:color(12); cout << "■"; break;
				case 5:color(2); cout << "■"; break;
				case 6:color(7); cout << "■"; break;
				case 7:color(8); cout << "■"; break;
				case 8:color(4); cout << "■"; break;
				case 9:color(14); cout << "■"; break;
				case 10:color(6); cout << "■"; break;
			}
		}
		cout << endl;
	}

}

//清除Process图片(参数：图片左上角控制台坐标)
void CBoss::cleanPixelPicture(int _PositionX, int _PositionY)
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			gotoXY(_PositionX + i, _PositionY + j);
			cout << "  ";
		}
		cout << endl;
	}
}

//攻击
int CBoss::atkAction(CRole &_Role)
{
	int hurt = m_Atk - _Role.getDef();

	if (hurt < 0)				//判断伤害是否未负数，强行破甲
		hurt = 1;

	_Role.beenAtkAction(hurt);

	return hurt;
}

//被攻击
void CBoss::beenAtkAction(int _hurt)
{
	m_HP -= _hurt;
}