#pragma once
#include "EaseClass.h"
class EraseGraph
{
public:
	EraseGraph();
	void Init();
	void Update();
	void SetGraph(int Graph);
	void SetColor(int Color);
	void SetFlag(bool Flag);
	void SetErase(double DrawPosX, double DrawPosY, double width, double height, int timer);
	bool GetFinishFlag();
	void Draw();

private:
	double centerPosX;
	double centerPosY;
	double widthR;
	double heightR;
	double drawWidthR;
	double drawHeightR;
	bool isDrawFlag;
	bool isFinishFlag;
	Easing widthEase;
	Easing heightEase;
	int color;
	
	int timer;
	int graph;
};