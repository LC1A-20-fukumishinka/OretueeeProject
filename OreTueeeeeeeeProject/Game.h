#pragma once
#include "Player.h"
#include "Map.h"
#include "Scroll.h"
//ゲームシーン
class Game
{
public:
	Game();
	void Init();
	void Update();
	void Draw();
	//リザルトシーン移行する
	bool ChangeResultScene();
	//ステージ選択に移行する
	bool ChangeSelectScene();
private:
	Scroll scroll;
	Player player;
	Map map;
	int mapSize;
	int sizeR;
	bool isResultFlag;
	bool isSelectFlag;
};
