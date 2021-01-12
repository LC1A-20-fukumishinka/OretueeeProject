#include "Player.h"
#include "DxLib.h"
#include "input.h"
#include "collision.h"
#include <math.h>
using namespace collision;
Player::Player()
{


	warkSpeed = 0.6;
	playerR = 16;
	gravity = 0.49;
	warkMaxSpeed = 5;
	cancelDistance = 32;
	maxDistance = 100;
	fallMaxSpeed = 16;

	accelePosX = 0;
	accelePosY = 0;
	acceleFlag = false;
	goalFlag = false;
	playerYSpeed = 0;
	playerXSpeed = 0;
	playerPosX = 0;
	playerPosY = 0;
	inputX = 0;
	inputY = 0;

	oldFlag = 0;
	distanceX = 0;
	distanceY = 0;
	distance = 0;
	status = NORMAL;
	acceleSpeed = 1;

}

void Player::Init(double PlayerPosX, double PlayerPosY, double MaxDistance)
{
	playerPosX = PlayerPosX;
	playerPosY = PlayerPosY;
	playerXSpeed = 0;
	playerYSpeed = 0;
	gravity = 0.49;

	warkMaxSpeed = 5;
	acceleFlag = false;
	goalFlag = false;
	status = NORMAL;
	maxDistance = 100;
}

void Player::Update()
{
	Joypad();
	Normal();
	Setting();
	Accele();
	Collision();
	Move();
	scroll.SetScrollPos(playerPosX, playerPosY);
}

void Player::Draw()
{
	SetDrawPos();
	//���@�̕`��
	DrawBox(playerDrawPosX, playerDrawPosY, playerDrawPosX + playerR * 2, playerDrawPosY + playerR * 2, GetColor(0xAA, 0xAA, 0x00), TRUE);
	//���̕`��
	//DrawBox(0, WIN_HEIGHT - Floor, WIN_WIDTH + 1, WIN_HEIGHT, GetColor(0xAA, 0xAA, 0xAA), TRUE);

	for (int i = 0; i < PlayerChip; i++)
	{
		DrawBox(playerCollisionX[i] - 1 - scroll.GetScrollX(), playerCollisionY[i] - 1 - scroll.GetScrollY(), playerCollisionX[i] + 1 - scroll.GetScrollX(), playerCollisionY[i] + 1 - scroll.GetScrollY(), GetColor(0xFF, 0xFF, 0xFF), true);
	}
	//�����J�[�\���̕`��
	if (acceleFlag)
	{
		DrawLine(playerDrawPosX + playerR, playerDrawPosY + playerR, acceleDrawPosX, acceleDrawPosY, GetColor(0x00, 0xFF, 0xFF), 10);
		DrawCircle(acceleDrawPosX, acceleDrawPosY, 10, GetColor(0x0, 0xFF, 0xFF), TRUE);
	}
}

bool Player::GetGoalFlag()
{
	return goalFlag;
}

//����
void Player::Joypad()
{
	GetJoypadAnalogInput(&inputX, &inputY, DX_INPUT_PAD1);
}

//�ʏ���
void Player::Normal()
{
	if (status != NORMAL)return;
	//�W�����v����
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_A) && (playerYSpeed == 0))
	{
		playerYSpeed = -10;
	}
	//��������
	if ((inputX <= -100) && (playerXSpeed >= -warkMaxSpeed))
	{
		playerXSpeed -= warkSpeed;
	}
	if ((inputX >= 100) && (playerXSpeed <= warkMaxSpeed))
	{
		playerXSpeed += warkSpeed;
	}

	//��������
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_B)
	{
		status = SETTING;
		acceleFlag = true;
	}

	//���x�̎��R����
	if (playerXSpeed > 0)
	{
		playerXSpeed -= 0.3;
	}
	if (playerXSpeed < 0)
	{
		playerXSpeed += 0.3;
	}
	if ((playerXSpeed < 0.3) && (playerXSpeed > -0.3))
	{
		playerXSpeed = 0;
	}
	//���R����
	playerYSpeed += gravity;


	Edit();


	accelePosX = playerPosX;
	accelePosY = playerPosY;

}

//�����ݒ���
void Player::Setting()
{
	if (status != SETTING)return;
	//�d�͈ړ�
	playerYSpeed += gravity / 10;

	//�J�[�\���ړ�
	if (inputX <= -100)
	{
		accelePosX -= 5;
	}
	if (inputX >= 100)
	{
		accelePosX += 5;
	}
	if (inputY <= -100)
	{
		accelePosY -= 5;
	}
	if (inputY >= 100)
	{
		accelePosY += 5;
	}

	//���x����
	if (playerXSpeed > 0)
	{
		playerXSpeed -= 0.03;
	}
	if (playerXSpeed < 0)
	{
		playerXSpeed += 0.03;
	}
	if ((playerXSpeed < 0.03) && (playerXSpeed > -0.03))
	{
		playerXSpeed = 0;
	}

	Edit();



	//�J�[�\���ړ��̏I��
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_B) == 0)
	{

		distanceX = accelePosX - playerPosX;
		distanceY = accelePosY - playerPosY;
		distance = sqrt((distanceX * distanceX) + (distanceY * distanceY));
		//�ړ����L�����Z�����Ēʏ��ԂɈڍs����
		if (distance <= cancelDistance)
		{
			acceleFlag = false;
			status = NORMAL;
			return;
		}
		//������ԂɈڍs����
		playerXSpeed = 0;
		playerYSpeed = 0;
		status = ACCELE;
	}

}

//����
void Player::Accele()
{
	if (status != ACCELE)return;

	distance = sqrt((distanceX * distanceX) + (distanceY * distanceY));
	playerXSpeed += (distanceX / distance) * acceleSpeed;
	playerYSpeed += (distanceY / distance) * acceleSpeed;
	Edit();



	//�ړ�����������ύX�����
	if (((distanceX > 0) && (accelePosX - playerPosX <= 0)) ||
		((distanceY > 0) && (accelePosY - playerPosY <= 0)) ||
		((distanceX < 0) && (accelePosX - playerPosX >= 0)) ||
		((distanceY < 0) && (accelePosY - playerPosY >= 0)))
	{
		playerYSpeed += 0.001;
		acceleFlag = false;
		status = NORMAL;
	}
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_X)
	{
		playerYSpeed += 0.001;
		acceleFlag = false;
		status = NORMAL;
	}


}

void Player::Move()
{
	if (status == SETTING)
	{
		//�����ړ�
		accelePosX += playerXSpeed / 10;
		accelePosY += playerYSpeed / 10;
		playerPosX += playerXSpeed / 10;
		playerPosY += playerYSpeed / 10;
		return;
	}
	playerPosX += playerXSpeed;
	playerPosY += playerYSpeed;
}

void Player::SetDrawPos()
{
	//�`��p�̍��W�����肷��
	playerDrawPosX = playerPosX - scroll.GetScrollX() - playerR;
	playerDrawPosY = playerPosY - scroll.GetScrollY() - playerR;
	acceleDrawPosX = accelePosX - scroll.GetScrollX();
	acceleDrawPosY = accelePosY - scroll.GetScrollY();
}

void Player::Collision()
{

	playerCollisionX[LeftUp] = playerPosX + playerXSpeed - playerR;
	playerCollisionY[LeftUp] = playerPosY + playerYSpeed - playerR;

	playerCollisionX[RightUp] = playerPosX + playerXSpeed + playerR - 1;
	playerCollisionY[RightUp] = playerPosY + playerYSpeed - playerR;

	playerCollisionX[RightDown] = playerPosX + playerXSpeed + playerR - 1;
	playerCollisionY[RightDown] = playerPosY + playerYSpeed + playerR - 1;

	playerCollisionX[LeftDown] = playerPosX + playerXSpeed - playerR;
	playerCollisionY[LeftDown] = playerPosY + playerYSpeed + playerR - 1;

	for (int i = 0; i < PlayerChip; i++)
	{

		if ((MapchipCollision(map.GetMapNumber(playerCollisionX[i], playerCollisionY[i]), Map::BLOCK)))
		{
			if ((status == ACCELE))
			{
				map.ChangeMapNumber(playerCollisionX[i], playerCollisionY[i], Map::NONE);
				if (playerXSpeed < 0)
				{
					playerXSpeed = 2;
				}
				if (playerXSpeed > 0)
				{
					playerXSpeed = -2;
				}
				playerYSpeed = -5;
				status = NORMAL;
				acceleFlag = false;
			}
			if (status == NORMAL)
			{
				WallCollision(playerCollisionX[i], playerCollisionY[i]);
			}
		}
		if (MapchipCollision(map.GetMapNumber(playerCollisionX[i], playerCollisionY[i]), Map::WALL))
		{
			WallCollision(playerCollisionX[i], playerCollisionY[i]);
		}
		if (MapchipCollision(map.GetMapNumber(playerCollisionX[i], playerCollisionY[i]), Map::GOAL))
		{
			goalFlag = true;
		}
	}
}

void Player::WallCollision(double PosX, double PosY)
{
	//�㉺����
	double heightAX = playerPosX-10;
	double heightAY = playerPosY - playerR;
	double heightBX = playerPosX+10;
	double heightBY = playerPosY + playerR;
	//���E����
	double widthAX = playerPosX- playerR;
	double  widthAY = playerPosY-10;
	double widthBX = playerPosX+ playerR;
	double  widthBY = playerPosY;

	if (BoxCollision(heightAX, heightAY, heightBX, heightBY, (int)(PosX / 32) * 32, (int)(PosY / 32) * 32, (int)(PosX / 32 + 1) * 32, (int)(PosY / 32 + 1) * 32))
	{

			if (playerPosY < (int)(PosY / 32) * 32 + 16)
			{
				playerPosY = ((int)(PosY / 32) - 1) * 32 + 16;
				playerYSpeed = 0;
			}
			else
			{
				playerPosY = ((int)(PosY / 32) + 1) * 32 + 16;
				playerYSpeed = -0.01;
			}
	}
	if (BoxCollision(widthAX, widthAY, widthBX, widthBY, (int)(PosX / 32) * 32, (int)(PosY / 32) * 32, (int)(PosX / 32 + 1) * 32, (int)(PosY / 32 + 1) * 32))
	{
			if (playerPosX < (int)(PosX / 32) * 32 + 16)
			{
				playerPosX = ((int)(PosX / 32) - 1) * 32 + 16;
			}
			else
			{
				playerPosX = ((int)(PosX / 32) + 1) * 32 + 16;
			}
		playerXSpeed = 0;
	}
	//	double absX = fabs(playerXSpeed);
	//double absY = fabs(playerYSpeed);

	//if ((absX > absY) && (((int)(playerPosY / (playerR * 2)) == (int)(PosY / (playerR * 2))) && (playerXSpeed != 0) || (playerYSpeed == 0)))
	//{
	//	if (playerXSpeed >= 0)
	//	{
	//		playerPosX = ((int)(PosX / 32) - 1) * 32 + 16;
	//	}
	//	else
	//	{
	//		playerPosX = ((int)(PosX / 32) + 1) * 32 + 16;
	//	}
	//	playerXSpeed = 0;
	//	return;
	//}
	//if (((int)(playerPosX / (playerR * 2)) == (int)(PosX / (playerR * 2))) && (playerYSpeed != 0) || (playerXSpeed == 0))
	//{
	//	if (playerYSpeed >= 0)
	//	{
	//		playerPosY = ((int)(PosY / 32) - 1) * 32 + 16;
	//		playerYSpeed = 0;
	//	}
	//	else
	//	{
	//		playerPosY = ((int)(PosY / 32) + 1) * 32 + 16;
	//		playerYSpeed = -0.01;
	//	}

	//	return;
	//}

	//if (((int)(playerPosY / (playerR * 2)) == (int)(PosY / (playerR * 2))) && (playerXSpeed != 0) || (playerYSpeed == 0))
	//{
	//	if (playerXSpeed >= 0)
	//	{
	//		playerPosX = ((int)(PosX / 32) - 1) * 32 + 16;
	//	}
	//	else
	//	{
	//		playerPosX = ((int)(PosX / 32) + 1) * 32 + 16;
	//	}
	//	playerXSpeed = 0;
	//	return;
	//}

}

//�������
void Player::Edit()
{
	//�������x
	if (playerYSpeed >= fallMaxSpeed)
	{
		playerYSpeed = fallMaxSpeed;
	}
	if (playerYSpeed <= -fallMaxSpeed)
	{
		playerYSpeed = -fallMaxSpeed;
	}
}
