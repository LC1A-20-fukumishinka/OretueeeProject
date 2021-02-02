#include "Map.h"
#include "DxLib.h"
#include "egudai_Load.h"

int Map::mapSize;
int Map::mainMap[Map::height][Map::width];
int Map::startPosX;
int Map::startPosY;
int Map::scrollMinX;
int Map::scrollMinY;
int Map::scrollMaxX;
int Map::scrollMaxY;
int Map::maxBlock;
int Map::BlockCount;
int Map::mapNum;
Map::Map()
{
	LoadDivGraph("mapchip.png", MapChipGraph, MapChipGraph, 1, 32, 32, mapChipGraph);
	mapSize = 0;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			mainMap[y][x] = 0;
		}
	}
}

void Map::Readmap(int MapNumber, int MapSize)
{
	mapSize = MapSize;
	mapNum = MapNumber;
	maxBlock = 0;
	BlockCount = 0;
	scrollMinX = 0;
	scrollMinY = 0;
	scrollMaxX = width;
	scrollMaxY = height;
	int Map[height][width] = { 0 };
	switch (mapNum)
	{
	case 0:
		LoadCSV(Map, "./map1.csv");
		break;
	case 1:
		LoadCSV(Map, "./map2.csv");
		break;
	case 2:
		LoadCSV(Map, "./map3.csv");
		break;
	case 3:
		LoadCSV(Map, "./map4.csv");
		break;
	case 4:
		LoadCSV(Map, "./map5.csv");
		break;
	case 5:
		LoadCSV(Map, "./map6.csv");
		break;
	case 6:
		LoadCSV(Map, "./map7.csv");
		break;
	case 7:
		LoadCSV(Map, "./map8.csv");
		break;
	case 8:
		LoadCSV(Map, "./map9.csv");
		break;
	default:
		break;
	}
	//LoadCSV(Map, "./tamesi.csv"); //./tamesi.csv縺ｯ隱ｭ縺ｿ霎ｼ縺ｿ縺ｮ遒ｺ隱咲畑縺ｫ驕ｩ蠖薙↓菴懊▲縺溘・繝・・

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{

			mainMap[y][x] = Map[y][x];
			//繝励Ξ繧､繝､繝ｼ縺ｮ蛻晄悄蠎ｧ讓吶・繝槭ャ繝励メ繝・・繧堤匱隕九☆繧・
			if (mainMap[y][x] == START)
			{
				startPosX = x;
				startPosY = y;
				mainMap[y][x] = NONE;
			}
			if (mainMap[y][x] == BLOCK)
			{
				maxBlock++;
			}
			if (mainMap[y][x] == SCROLL_MIN)
			{
				scrollMinX = x + 1;
				scrollMinY = y + 1;
				mainMap[y][x] = WALL;
			}
			if (mainMap[y][x] == SCROLL_MAX)
			{
				scrollMaxX = x;
				scrollMaxY = y;
				mainMap[y][x] = WALL;
			}
		}
	}
	scroll.Init(scrollMinX * mapSize + WIN_WIDTH / 2, scrollMinY * mapSize + WIN_HEIGHT / 2, scrollMaxX * mapSize - WIN_WIDTH / 2, scrollMaxY * mapSize - WIN_HEIGHT / 2);
}

//繝槭ャ繝励メ繝・・縺ｮ逡ｪ蜿ｷ繧貞女縺大叙繧・
int Map::GetMapNumber(double PosX, double PosY)
{
	return mainMap[(int)(PosY / mapSize)][(int)(PosX / mapSize)];
}

//繧ｹ繧ｿ繝ｼ繝亥慍轤ｹ縺ｮX蠎ｧ讓吶ｒ霑斐☆
int Map::GetStartPosX()
{
	return startPosX;
}

//繧ｹ繧ｿ繝ｼ繝亥慍轤ｹ縺ｮY蠎ｧ讓吶ｒ霑斐☆
int Map::GetStartPosY()
{
	return startPosY;
}

//繝槭ャ繝礼分蜿ｷ繧貞､画峩縺吶ｋ
void Map::ChangeMapNumber(double PosX, double PosY, int mapNumber)
{
	if ((mainMap[(int)(PosY / mapSize)][(int)(PosX / mapSize)] == BLOCK) && (mapNumber == NONE))
	{
		BlockCount++;
	}
	mainMap[(int)(PosY / mapSize)][(int)(PosX / mapSize)] = mapNumber;
}

void Map::DrawBack()
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (mainMap[y][x] == LAVA)continue;
			DrawGraph(x * mapSize - scroll.GetScrollX(), y * mapSize - scroll.GetScrollY(), mapChipGraph[mainMap[y][x]], true);
		}
	}
	//DrawFormatString(0, 0, GetColor(0xFF, 0xFF, 0xFF), "BLOCK %d/%d", BlockCount, maxBlock);
}

void Map::DrawFront()
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (mainMap[y][x] != LAVA)continue;
			DrawGraph(x * mapSize - scroll.GetScrollX(), y * mapSize - scroll.GetScrollY(), mapChipGraph[mainMap[y][x]], true);
		}
	}
}

int Map::GetMapNumber()
{
	return mapNum;
}
