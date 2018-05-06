#include"comment.h"



/*******************************************************************************
Function: void color();颜色控制函数
Description: 改变输出的字体和文本颜色
Calls:	#include<windows.h>
Input: const unsigned short COLor1正整数;0-15改变字体颜色，大于15改变（背景）文本颜色
Output: 字体和文本颜色改变
Return: 无
Others:
文字颜色对应值：
0=黑色	1=蓝色	2=绿色	3=湖蓝色	4=红色	5=紫色	6=黄色	7=白色	8=灰色
9=淡蓝色	10=淡绿色	11=淡浅绿色	12=浅红色	13=浅紫色	14=浅黄色	15=亮白色
底色对应值：
0*16=黑色	16*1=蓝色	16*2=绿色	16*3=湖蓝色	16*4=红色	16*5=紫色
16*6=黄色	16*7=白色	16*8=灰色	16*9=淡蓝色	16*10=淡绿色	16*11=淡浅绿色
16*12=浅红色	16*13=浅紫色	16*14=浅黄色	16*15=亮白色
最终颜色值：底色+文字颜色
*******************************************************************************/
/*-------------------------颜色控制函数begin----------------------------------*/
void color(const unsigned short COLor1)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLor1);
}





/*******************************************************************************
Function: void gotoxy();光标移动函数
Description: 控制光标的位置
Calls: #include<windows.h>
Input: int ROW行, int COL列
Output: 把控制台的光标设置到ROW，COL的位置，ROW代表行，COL代表列
Return: 无
Others: 对于COL进行了处理，光标向右移动的单位是2个字节
*******************************************************************************/
void gotoXY(int goRow, int goCol)
{
	COORD pos = { 2 * goCol, goRow };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}



//==================影藏光标函数
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}