/*
TODO : 有时间可以加入任务系统

*/

#include "CUISceneSys.h"
#include "CBagSys.h"
#include <windows.h>
#include <mmsyscom.h>
#pragma comment(lib,"winmm.lib")

void main()
{
	srand(time(NULL));
	HideCursor();//隐藏光标
	system("mode con cols=160 lines=37");//调整控制台界面尺寸

	//控制台播放背景音乐
	WCHAR mciCmd[] = TEXT("open audio\\WaterWall.mp3 alias BGM");
	mciSendString(mciCmd, 0, 0, 0);
	mciSendString(TEXT("play BGM"), 0, 0, 0);

	CUISceneSys *pUISceneSys = CUISceneSys::getInstance();//获得场景控制系统的单例指针
	pUISceneSys->init();//场景系统初始化
	CBagSys::getInstance()->init("init\\Item.xml");//游戏道具初始化

	int flag = CBeginScene::getInstance()->ctrlOfScene();		//返回值为玩家选项光标
	CBeginScene::getInstance()->action(flag);				//根据玩家选择做出行为
}