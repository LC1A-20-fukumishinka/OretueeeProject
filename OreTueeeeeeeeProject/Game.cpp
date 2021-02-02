#include "Game.h"
#include "Map.h"
#include "input.h"
#include "DxLib.h"
Game::Game()
{
	isResultFlag = false;
	isSelectFlag = false;
	isEndFlag = false;
	isInFlag = true;
	isDeadFlag = false;
	mapSize=32;
	sizeR = mapSize / 2;
	LoadDivGraph("playerDeath.png",3,3,1,32,32,deathGraph);

}

void Game::Init()
{
	isResultFlag = false;
	isSelectFlag = false;
	isEndFlag = false;
	isInFlag = true;
	isDeadFlag = false;
	player.Init(map.GetStartPosX()*mapSize+sizeR,map.GetStartPosY() * mapSize + sizeR,100);
	stageIn.Init(32, stageIn.In);
	clear.Init(32,clear.Out);
	dead.Init(32, dead.Out);
}

void Game::Update()
{
	player.Update();
	scroll.Update();
	if (player.GetDeathFlag()) //‚±‚±‚ÌğŒ®‚Íâ‘Î‚É•Ï‚¦‚Ä‚­‚¾‚³‚¢
	{
		if (!isDeadFlag)
		{
			if (death.GetFlag() == true)
			{
				death.Init(player.GetPosX(), player.GetPosY(), 16, deathGraph[2]); //’l‚Í“K“–‚Å‚·
			}
			death.Update();
			if (death.GetFlag() == true && death.GetOldFlag() == false)
			{
				/*€–S‚Ì‰Šú‰»*/
				map.Readmap(map.GetMapNumber(), mapSize);
				isDeadFlag = true;
			}
		}
		if (dead.GetFlag())
		{
			Init();
		}
	}
	if (stageIn.GetFlag())
	{
		isInFlag = false;
	}

}

void Game::Draw()
{
		map.DrawBack();
		player.Draw();
		death.Draw();
		map.DrawFront();
		if (isInFlag)
		{
			stageIn.Draw();
		}
		if ((player.GetGoalFlag()))
		{
			clear.Draw();
		}
		if (isDeadFlag)
		{
			dead.Draw();
		}
}

bool Game::ChangeResultScene()
{
	return clear.GetFlag();
}

bool Game::ChangeSelectScene()
{
	return player.GetReturnFlag();
}
