#pragma once
#include "EraseGraph.h"
#include "SlashEffect.h"
class Warp
{
public:
	Warp();
	void Init(int WindowWidth, int WindowHeight);
	void Update();
	void Draw();
	void SetPos(double DrawPosX, double DrawPosY, double sizeX, double sizeY);
	void SetGraph(int Graph);
	void SetColor(int Color);
	void SetFlag(bool Flag);
	bool GetFinishFlag();
private:
	EraseGraph warpE;
	SlashEffect warpS;
	int graph;
	int color;
	bool isFinishFlag;
};
