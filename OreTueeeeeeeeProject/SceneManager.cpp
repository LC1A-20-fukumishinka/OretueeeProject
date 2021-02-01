#include "SceneManager.h"
#include "input.h"
SceneManager::SceneManager()
{
	//�ŏ��̃V�[���̓^�C�g���V�[��
	SceneStatus = TITLE;
	mapSize = 32;
}

//�S�̂̍X�V����
void SceneManager::Update()
{
	//����
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
		//�X�e�[�W�I���Ɉڍs
		if (title.ChangeSelectScene())SceneStatus = SELECT;
		break;
	case SELECT:
		//�Q�[���V�[���Ɉڍs
		if (select.ChangeGameScene())
		{
			SceneStatus = GAME;
			//�}�b�v�ǂݍ���
			map.Readmap(select.SetStageNum(), mapSize);
			game.Init();
		}
		break;
	case GAME:

		//���U���g�V�[���Ɉڍs����
		//if (game.ChangeResultScene())
		//{
		//	SceneStatus = RESULT;
		//	result.Init();
		//}
		//�X�e�[�W�I���Ɉڍs����
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
		//�X�e�[�W�I���Ɉڍs
		title.Update();
		break;
	case SELECT:
		//�Q�[���V�[���Ɉڍs
		select.Update();
		break;
	case GAME:
		//���U���g�V�[���Ɉڍs����
		game.Update();
		break;
	case RESULT:
		result.Update();
		break;
	default:
		break;
	}

}
