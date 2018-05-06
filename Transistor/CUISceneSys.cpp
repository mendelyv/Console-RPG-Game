#include "CUISceneSys.h"

//初始化
void CUISceneSys::init()
{
	m_pGameMap = nullptr;
	m_MapName = MN_None;

	loadAllMap();
}

//载入所有地图
void CUISceneSys::loadAllMap()
{
	CMap *pM = nullptr;

	pM = new CMap;
	pM->setMapFromFile("map\\map1.txt");
	m_MapContainer.insert(make_pair(MN_Map1, pM));

	pM = new CMap;
	pM->setMapFromFile("map\\map2.txt");
	m_MapContainer.insert(make_pair(MN_Map2, pM));

	pM = new CMap;
	pM->setMapFromFile("map\\map3.txt");
	m_MapContainer.insert(make_pair(MN_Map3, pM));

	pM = new CMap;
	pM->setMapFromFile("map\\shop.txt");
	m_MapContainer.insert(make_pair(MN_Shop, pM));

	pM = new CMap;
	pM->setMapFromFile("map\\map4.txt");
	m_MapContainer.insert(make_pair(MN_Map4, pM));

	pM = new CMap;
	pM->setMapFromFile("map\\map5.txt");
	m_MapContainer.insert(make_pair(MN_Map5, pM));

	pM = new CMap;
	pM->setMapFromFile("map\\Boss.txt");
	m_MapContainer.insert(make_pair(MN_Boss, pM));
}

//获得地图
CMap* CUISceneSys::getMap(int _MapName)
{
	return m_MapContainer.at(_MapName);
}

//将玩家放入地图
void CUISceneSys::changeInMap(int _name, CRole* _player)
{
	CMap* pMap = m_MapContainer.at(_name);
	_player->setInMapName(_name);		
	pMap->setPlayer(_player);

	//判断地图是否可以设置怪物
	if (_name != MN_Map1 && _name != MN_Shop && _name != MN_Boss && _name != MN_None && _name != MN_Map2)
		setMonster(*pMap);
	
	pMap->ctrlOfMap();
}

//给地图散落怪物
void CUISceneSys::setMonster(CMap &_map)
{
	//去除地图中的所有怪    避免数量超标
	for (int i = 0; i < _map.getRow(); i++)
	{
		for (int j = 0; j < _map.getCol(); j++)
		{
			if (MT_Process == _map.m_pMap[i][j] || MT_Camerata == _map.m_pMap[i][j])
			{
				_map.m_pMap[i][j] = Road;
			}
		}
	}

	int monster_N = rand() % 4 + 9;		//普通怪的数量
	int monster_P = rand() % 3 + 2;		//精英怪的数量

	int i, j;//怪的坐标

	while (0 != monster_N)     //放置普通怪
	{
		i = rand() % 30;
		j = rand() % 30;

		if (Road == _map.m_pMap[i][j])
		{
			_map.m_pMap[i][j] = MT_Process;
			monster_N--;
		}
	}

	while (0 != monster_P)
	{
		i = rand() % 30;
		j = rand() % 30;

		if (Road == _map.m_pMap[i][j])
		{
			_map.m_pMap[i][j] = MT_Camerata;
			monster_P--;
		}
	}
}

//释放所有地图
void CUISceneSys::freeAllMap()
{
	map<int, CMap*>::iterator iter = m_MapContainer.begin();

	while (iter != m_MapContainer.end())
	{
		if (nullptr != iter->second)
		{
			delete iter->second;
			iter->second = nullptr;
		}
		iter++;
	}
}