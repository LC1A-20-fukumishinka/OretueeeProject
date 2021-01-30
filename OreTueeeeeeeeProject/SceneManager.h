#pragma once
#include "Title.h"
#include "Select.h"
#include "Game.h"
#include "Map.h"
#include "Result.h"
#include "egudai_ScreenTrans.h"
class SceneManager
{
public:
	SceneManager();
	void Update();
	void Draw();
private:
	enum Scene
	{
		TITLE,
		SELECT,
		GAME,
		RESULT,
	};
	int mapSize;
	int SceneStatus;
	Title title;
	Select select;
	Game game;
	Map map;
	Result result;
	void SceneChange();
	void SceneUpdate();

	ScreenTrans screenTrans;
};
