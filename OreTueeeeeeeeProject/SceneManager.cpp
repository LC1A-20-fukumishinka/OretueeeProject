#include "SceneManager.h"
#include "input.h"
SceneManager::SceneManager()
{
	//最初のシーンはタイトルシーン
	SceneStatus = TITLE;
	mapSize = 32;
}

//全体の更新処理
void SceneManager::Update()
{
	//入力
	Input::Update();
	SceneChange();
	SceneUpdate();
}

void SceneManager::Draw()
{
	switch (SceneStatus)
	{
	case TITLE:
		title.Draw();
		break;
	case SELECT:
		select.Draw();
		break;
	case GAME:
		game.Draw();
		break;
	case RESULT:
		result.Draw();
		break;
	default:
		break;
	}
}

void SceneManager::SceneChange()
{
	switch (SceneStatus)
	{
	case TITLE:
		//ステージ選択に移行
		if (title.ChangeSelectScene())SceneStatus = SELECT;
		break;
	case SELECT:
		//ゲームシーンに移行
		if (select.ChangeGameScene())
		{
			SceneStatus = GAME;
			//マップ読み込み
			map.Readmap(select.SetStageNum(), mapSize);
			game.Init();
		}
		break;
	case GAME:

		//リザルトシーンに移行する
		//if (game.ChangeResultScene())
		//{
		//	SceneStatus = RESULT;
		//	result.Init();
		//}
		//ステージ選択に移行する
		if ((game.ChangeSelectScene())||(game.ChangeResultScene()))
		{
			SceneStatus = SELECT;
			select.Init();
		}
		break;
	case RESULT:
		if (result.ChangeSelectScene())
		{
			SceneStatus = SELECT;
			select.Init();
		}
		break;
	default:
		break;
	}

}

void SceneManager::SceneUpdate()
{
	switch (SceneStatus)
	{
	case TITLE:
		//ステージ選択に移行
		title.Update();
		break;
	case SELECT:
		//ゲームシーンに移行
		select.Update();
		break;
	case GAME:
		//リザルトシーンに移行する
		game.Update();
		break;
	case RESULT:
		result.Update();
		break;
	default:
		break;
	}

}
