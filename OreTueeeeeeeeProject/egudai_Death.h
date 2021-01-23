#pragma once
#include "Scroll.h"

class Death
{
public:
	Death(void);
	//�S�̂̏�����
	void Init(double PlayerPosX, double PlayerPosY, int playerR, int playerGraph = -1);
	void Update(void);
	void Draw(void);
	bool GetFlag(void);
	bool GetOldFlag(void);
private:
	static const int fireNum = 100; //�p�[�e�B�N���̌�
	static const int interbal = 40; //���o�̎���

	bool isEnd; //���o���I���������ǂ����̃t���O
	bool oldIsEnd; //1�t���[���O��isEnd

	const double gravity = 0.49; //�d��

	double playerPosX, playerPosY; //�v���C���[�̍��W
	double playerSpeedY; //�v���C���[�̃X�s�[�h
	int playerR; //�v���C���[�̔��a

	int playerGraph; //�v���C���[�̉摜�f�[�^
	double playerDrawPosX, playerDrawPosY; //�v���C���[�̕`����W

	double firePosX[fireNum], firePosY[fireNum]; //�p�[�e�B�N���̍��W
	double fireSpeedY[fireNum]; //�p�[�e�B�N���̈ړ����x

	int particleGraph; //�p�[�e�B�N���̉摜�f�[�^
	int graphR; //�p�[�e�B�N����`�悷�鎞�̔��a
	int pal[fireNum]; //�p�[�e�B�N���̓����x

	bool isFireAlive[fireNum]; //�p�[�e�B�N���������Ă��邩�ǂ���
	bool isInit[fireNum]; //�p�[�e�B�N���̏������t���O

	Scroll scroll;
	void PlayerDraw(void);
};
