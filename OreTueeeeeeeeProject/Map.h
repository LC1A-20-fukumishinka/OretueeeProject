#pragma once
#include "Scroll.h"
extern const int WIN_WIDTH;
extern const int WIN_HEIGHT;
class Map
{
public:
	static enum Size
	{
		width = 50,
		height = 20
	};
	static int mapSize;
	static int mainMap[height][width];

	static enum Status
	{
		NONE,
		WALL,
		BLOCK,
		START,
		GOAL,
		MapChip
	};
	Map();
	void Readmap(int MapNumber, int MapSize);
	int GetMapNumber(double PosX,double PosY);
	int GetStartPosX();
	int GetStartPosY();
	void ChangeMapNumber(double PosX, double PosY, int mapNumber);
	void Draw();
private:

	Scroll scroll;
	int mapChipGraph[MapChip];


	static int startPosX;
	static int startPosY;
	static int maxBlock;
	static int BlockCount;
};