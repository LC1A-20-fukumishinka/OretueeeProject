#include "Game.h"
#include "Map.h"
Game::Game()
{
	isResultFlag = false;
	isSelectFlag = false;
	mapSize=32;
	sizeR = mapSize / 2;
}

void Game::Init()
{
	isResultFlag = false;
	isSelectFlag = false;
	player.Init(map.GetStartPosX() * mapSize + sizeR, map.GetStartPosY() * mapSize + sizeR, 100);
}

void Game::Update()
{
	player.Update();
	scroll.Update();
}

void Game::Draw()
{
	map.Draw();
	player.Draw();
}

bool Game::ChangeResultScene()
{
	return player.GetGoalFlag();
}

bool Game::ChangeSelectScene()
{
	return isSelectFlag;
}
