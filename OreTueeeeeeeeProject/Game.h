#pragma once
#include "Player.h"
#include "Map.h"
#include "Scroll.h"
//�Q�[���V�[��
class Game
{
public:
	Game();
	void Init();
	void Update();
	void Draw();
	//���U���g�V�[���ڍs����
	bool ChangeResultScene();
	//�X�e�[�W�I���Ɉڍs����
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
