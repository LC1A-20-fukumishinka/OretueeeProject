#include "egudai_ScreenTrans.h"
#include <DxLib.h>
#include <vector>

ScreenTrans::ScreenTrans()
{
	graph = MakeGraph(WIN_WIDTH, WIN_HEIGHT);

	size = 0;
	exRota = 1;

	isEnd = true;
}

void ScreenTrans::Init(int size)
{
	this->size = size;
	exRota = 1;

	isEnd = false;
}

void ScreenTrans::Updata(void)
{
	if (isEnd == true)
	{
		//‰æ–Ê‚ð‰æ‘œ‚Æ‚µ‚Ä•Û‘¶
		GetDrawScreenGraph(0, 0, WIN_WIDTH, WIN_HEIGHT, graph);

		return;
	}

	exRota -= 0.03;

	if (exRota < 0.5)
	{
		isEnd = true;
	}
}

void ScreenTrans::Draw(void)
{
	Updata();

	if (isEnd == true) return;

	for (int y = 0; y < WIN_HEIGHT / size; y++)
	{
		for (int x = 0; x < WIN_WIDTH / size; x++)
		{
			//‰æ‘œ‚Ì•”•ª“I‚ÈŠg‘åk¬
			DrawRectExtendGraph(x * size - size * (exRota - 1.0), y * size - size * (exRota - 1.0),
				(x + 1) * size + size * (exRota - 1.0), (y + 1) * size + size * (exRota - 1.0),
				x * size, y * size, size * exRota, size * exRota, graph, true);
		}
	}
}

bool ScreenTrans::GetFlag(void)
{
	return isEnd;
}
