#include "Warp.h"
#include "DxLib.h"
Warp::Warp()
{
	graph = -1;
}

void Warp::Init(int WindowWidth, int WindowHeight)
{
	warpS.Init(10, 10, GetColor(0xFF, 0xFF, 0xFF), WindowWidth, WindowHeight);
	warpE.Init();
}

void Warp::Update()
{
	warpS.SetFlag(warpE.GetFinishFlag());
	warpE.Update();
	warpS.Update();
}

void Warp::Draw()
{
	warpE.Draw();
	warpS.Draw();
}

void Warp::SetPos(double DrawPosX, double DrawPosY, double sizeX, double sizeY)
{
	warpE.SetErase(DrawPosX, DrawPosY, sizeX, sizeY, 15);
	warpS.SetSlash(DrawPosX+(sizeX/2) - 1, DrawPosY+(sizeY/2), DrawPosX + (sizeX / 2) , DrawPosY + (sizeY / 2));
}

void Warp::SetGraph(int Graph)
{
	warpE.SetGraph(Graph);
}

void Warp::SetColor(int Color)
{
	warpE.SetColor(Color);
}

void Warp::SetFlag(bool Flag)
{
	warpE.SetFlag(Flag);
}

bool Warp::GetFinishFlag()
{
	return warpS.GetFinishFlag();
}
