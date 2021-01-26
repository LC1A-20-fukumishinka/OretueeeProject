#pragma once
#include "Map.h"
#include "Scroll.h"
#include "EaseClass.h"
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
	bool GetReturnFlag();
	bool GetItemFlag();

	static int playerWarkGraph[6];
	static int playerIdolGraph[2];
private:
	enum acceleStatus
	{
		NORMAL,
		SETTING,
		ACCELE,
		DEAD
	};
	enum animationStatus
	{
		IDOL,
		WARK,
		IDOL_TIMER=20,
		WARK_TIMER = 5
	};
	enum pauseStatus
	{
		RESUME,
		RETURN,
		menuEnd
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
	double scrollDistanceX;
	double scrollDistanceY;

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
	//�X�N���[���߂��`��t���O
	bool isScrollFlag;
	//�S�[���t���O
	bool goalFlag;
	//����
	int inputX,oldInputX;
	int inputY,oldInputY;

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

	//�A�j���[�V�����֌W�̃X�e�[�^�X
	int graphNum;
	int animationTimer;
	int animationStatus;
	int animationOldStatus;
	bool isTurnFlag;
	bool isItemFlag;

	//�|�[�Y���j���[
	bool isMenuFlag;
	bool isReturnFlag;
	bool isPauseFlag;
	int menuStatus;

	Map map;
	Scroll scroll;
	Easing easeScroll;
	void Joypad();
	void Normal();
	void Setting();
	void Accele();
	void Menu();
	void Dead();
	void Move();
	void SetDrawPos();
	void Collision();
	void WallCollision(double PosX, double PosY);
	void Edit();
	void scrollUpdate();
	void PlayerMapchipUpdate();
	void Animation();
};
