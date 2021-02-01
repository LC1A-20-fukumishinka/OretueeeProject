#pragma once
#include "Player.h"
#include "Map.h"
#include "Scroll.h"
#include "egudai_Death.h"
#include "egudai_ScreenTrans.h"
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
	int deathGraph[3];
	int mapSize;
	int sizeR;
	bool isResultFlag;
	bool isSelectFlag;
	bool isEndFlag;
	bool isInFlag;
	bool isDeadFlag;

	Death death;
	ScreenTrans clear,stageIn,dead;
};
