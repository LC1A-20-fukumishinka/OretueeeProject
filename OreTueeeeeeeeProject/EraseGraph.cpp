#include "EraseGraph.h"
#include "DxLib.h"
EraseGraph::EraseGraph()
{
	centerPosX = 0;
	centerPosY = 0;
	widthR = 0;
	heightR = 0;
	isDrawFlag = false;
	isFinishFlag = false;
	timer = 0;
	graph = -1;
	drawWidthR = 0;
	drawHeightR = 0;
	color = 0;
}

void EraseGraph::Init()
{
	centerPosX = 0;
	widthR = 0;
	heightR = 0;
	isDrawFlag = false;
	isFinishFlag = false;
	graph = -1;
	timer = 0;
	drawWidthR = 0;
	drawHeightR = 0;
	color = 0;
}

void EraseGraph::Update()
{
	if (!isDrawFlag)return;
	drawWidthR = widthR/3+(widthR * (1 - widthEase.EasingMaker(Easing::Out, Easing::Cubic, timer)));
	drawHeightR = (heightR * (1 - heightEase.EasingMaker(Easing::In, Easing::Back, timer)));
	//ââèoèIóπéûÇ…ï`âÊÇèIóπÇ∑ÇÈ
	if (!widthEase.Finish())return;
		heightEase.Finish();
		isFinishFlag = true;
		isDrawFlag = false;

}

void EraseGraph::SetGraph(int Graph)
{
	graph = Graph;
}

void EraseGraph::SetColor(int Color)
{
	color = Color;
}

void EraseGraph::SetFlag(bool Flag)
{
	if (!Flag)return;
	isDrawFlag = true;
}

void EraseGraph::SetErase(double DrawPosX, double DrawPosY, double width, double height, int Timer)
{
	if (isDrawFlag)return;
	centerPosX = DrawPosX + width / 2;
	centerPosY = DrawPosY + height / 2;
	widthR = (width*3 / 8);
	heightR = height / 2;
	timer = Timer;
	drawWidthR = heightR;
	drawHeightR = widthR;
}

bool EraseGraph::GetFinishFlag()
{
	if (!isFinishFlag)return false;
	isFinishFlag=false;
	return true;
}

void EraseGraph::Draw()
{
	if (!isDrawFlag)return;
	if (graph != -1)
	{
		DrawExtendGraph(centerPosX -drawWidthR,
			centerPosY - drawHeightR,
			centerPosX + drawWidthR,
			centerPosY + drawHeightR,
			graph, true);
	}
	else
	{
		DrawBox(centerPosX - drawWidthR,
			centerPosY - drawHeightR,
			centerPosX + drawWidthR,
			centerPosY + drawHeightR,
			color, TRUE);
	}
}
