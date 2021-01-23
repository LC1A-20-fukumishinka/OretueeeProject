#pragma once
#include "Map.h"
#include "Scroll.h"
extern const int WIN_WIDTH;
extern const int WIN_HEIGHT;
extern const int Floor;
class Player
{
public:
	Player();
	void Init(double PlayerPosX, double PlayerPosY, double MaxDistance);
	void Update();
	void Draw();
	bool GetGoalFlag();
private:
	enum Status
	{
		NORMAL,
		SETTING,
		ACCELE,
		DEAD
	};
	enum playerPos
	{
		LeftUp,
		RightUp,
		RightDown,
		LeftDown,
		PlayerChip
	};
	//�v���C���[�̍��W
	double playerPosX;
	double playerPosY;
	double startPosX;
	double startPosY;
	double playerDrawPosX;
	double playerDrawPosY;

	//�}�b�v�`�b�v����p�̓����蔻��
	double playerCollisionX[PlayerChip];
	double playerCollisionY[PlayerChip];

	//�����X�s�[�h
	float warkSpeed;
	int playerR;

	//�d��
	float gravity;
	//���ۂ̈ړ����x
	double playerYSpeed;
	double playerXSpeed;

	//���x���
	int warkMaxSpeed;
	int fallMaxSpeed;

	//�����J�[�\���̍��W
	double accelePosX;
	double accelePosY;
	double acceleDrawPosX;
	double acceleDrawPosY;
	//�����t���O
	bool isCursorFlag;
	//�����\�t���O
	bool isAcceleFlag;
	//�S�[���t���O
	bool goalFlag;
	//����
	int inputX;
	int inputY;

	//�ЂƂO�̃t���[���̃t���O
	bool oldFlag;

	//���L�����Ɖ����J�[�\���̋���
	double distanceX;
	double distanceY;
	double distance;

	//���L�����̏��
	int status;

	//�����X�s�[�h
	double acceleSpeed;

	//���f
	double cancelDistance;
	//���E�̋���
	double maxDistance;


	Map map;
	Scroll scroll;
	void Joypad();
	void Normal();
	void Setting();
	void Accele();
	void Dead();
	void Move();
	void SetDrawPos();
	void Collision();
	void WallCollision(double PosX, double PosY);
	void Edit();
};
