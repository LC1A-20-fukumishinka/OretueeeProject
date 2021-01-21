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
	isCursorFlag = false;
	isAcceleFlag = false;
	goalFlag = false;
	isScrollFlag = false;
	playerYSpeed = 0.1;
	playerXSpeed = 0;
	scrollDistanceX=0;
	scrollDistanceY=0;
	playerPosX = 0;
	playerPosY = 0;
	startPosX = 0;
	startPosY = 0;
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
	startPosX = PlayerPosX;
	startPosY = PlayerPosY;
	playerPosX = startPosX;
	playerPosY = startPosY;
	playerXSpeed = 0;
	playerYSpeed = 0.1;
	gravity = 0.49;

	warkMaxSpeed = 5;
	isCursorFlag = false;
	goalFlag = false;
	isScrollFlag = false;
	status = NORMAL;
	maxDistance = 100;
}

void Player::Update()
{
	Joypad();
	Normal();
	Setting();
	Accele();
	Dead();
	Collision();
	Move();
	scrollUpdate();
}

void Player::Draw()
{
	SetDrawPos();
	//自機の描画
	DrawBox(playerDrawPosX, playerDrawPosY, playerDrawPosX + playerR * 2, playerDrawPosY + playerR * 2, GetColor(0xAA, 0xAA, 0x00), TRUE);
	//床の描画
	//DrawBox(0, WIN_HEIGHT - Floor, WIN_WIDTH + 1, WIN_HEIGHT, GetColor(0xAA, 0xAA, 0xAA), TRUE);

	//デバッグ用のマップ判定描画
	for (int i = 0; i < PlayerChip; i++)
	{
		DrawBox(playerCollisionX[i] - 1 - scroll.GetScrollX(), playerCollisionY[i] - 1 - scroll.GetScrollY(), playerCollisionX[i] + 1 - scroll.GetScrollX(), playerCollisionY[i] + 1 - scroll.GetScrollY(), GetColor(0xFF, 0xFF, 0xFF), true);
	}
	//加速カーソルの描画
	if (isCursorFlag)
	{
		if (isAcceleFlag)
		{
			DrawLine(playerDrawPosX + playerR, playerDrawPosY + playerR, acceleDrawPosX, acceleDrawPosY, GetColor(0x22, 0xDD, 0xDD), 10);
			DrawCircle(acceleDrawPosX, acceleDrawPosY, 10, GetColor(0x22, 0xDD, 0xDD), TRUE);
		}
		else
		{
			DrawLine(playerDrawPosX + playerR, playerDrawPosY + playerR, acceleDrawPosX, acceleDrawPosY, GetColor(0xDD, 0x22, 0x22), 10);
			DrawCircle(acceleDrawPosX, acceleDrawPosY, 10, GetColor(0xDD, 0x22, 0x22), TRUE);
		}
	}
}

bool Player::GetGoalFlag()
{
	return goalFlag;
}

//入力
void Player::Joypad()
{
	GetJoypadAnalogInput(&inputX, &inputY, DX_INPUT_PAD1);
}

//通常状態
void Player::Normal()
{
	if (status != NORMAL)return;
	//ジャンプ入力
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_A) && (playerYSpeed == 0))
	{
		playerYSpeed = -10;
	}
	//歩き入力
	if ((inputX <= -100) && (playerXSpeed >= -warkMaxSpeed))
	{
		playerXSpeed -= warkSpeed;
	}
	if ((inputX >= 100) && (playerXSpeed <= warkMaxSpeed))
	{
		playerXSpeed += warkSpeed;
	}

	//加速入力
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_B)
	{
		status = SETTING;
		isCursorFlag = true;
	}

	//速度の自然減衰
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
	//自然落下
	playerYSpeed += gravity;


	Edit();


	accelePosX = playerPosX;
	accelePosY = playerPosY;

}

//加速設定状態
void Player::Setting()
{
	if (status != SETTING)return;
	//重力移動
	playerYSpeed += gravity / 10;

	//カーソル移動
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

	//速度減衰
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
	int pos = map.GetMapNumber(accelePosX, accelePosY);


	distanceX = accelePosX - playerPosX;
	distanceY = accelePosY - playerPosY;
	distance = sqrt((distanceX * distanceX) + (distanceY * distanceY));
	if (MapchipCollision(pos, Map::PILE))
	{
		isAcceleFlag = true;
	}
	else
	{
		isAcceleFlag = false;
	}

	//カーソル移動の終了
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_B) == 0)
	{
		//移動をキャンセルして通常状態に移行する

		//加速状態に移行する
		if (isAcceleFlag)
		{
			playerXSpeed = 0;
			playerYSpeed = 0;
			status = ACCELE;
			return;
		}
		isCursorFlag = false;
		status = NORMAL;
	}
}

//加速
void Player::Accele()
{
	if (status != ACCELE)return;

	distance = sqrt((distanceX * distanceX) + (distanceY * distanceY));
	playerXSpeed += (distanceX / distance) * acceleSpeed;
	playerYSpeed += (distanceY / distance) * acceleSpeed;
	Edit();



	//移動しきったら変更される
	if (((distanceX > 0) && (accelePosX - playerPosX <= 0)) ||
		((distanceY > 0) && (accelePosY - playerPosY <= 0)) ||
		((distanceX < 0) && (accelePosX - playerPosX >= 0)) ||
		((distanceY < 0) && (accelePosY - playerPosY >= 0)))
	{
		playerYSpeed += 0.001;
		isCursorFlag = false;
		status = NORMAL;
	}
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_X)
	{
		playerYSpeed += 0.001;
		isCursorFlag = false;
		status = NORMAL;
	}


}

void Player::Dead()
{
	if (status != DEAD)return;
	Init(startPosX, startPosY, maxDistance);
}

void Player::Move()
{
	if (status == SETTING)
	{
		//慣性移動
		if (!isAcceleFlag)
		{
			accelePosX += playerXSpeed / 10;
			accelePosY += playerYSpeed / 10;
		}
		playerPosX += playerXSpeed / 10;
		playerPosY += playerYSpeed / 10;
		return;
	}
	playerPosX += playerXSpeed;
	playerPosY += playerYSpeed;
}

void Player::SetDrawPos()
{
	//描画用の座標を決定する
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
		//	ブロックの当たり判定
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
				isCursorFlag = false;
			}
			if (status == NORMAL)
			{
				WallCollision(playerCollisionX[i], playerCollisionY[i]);
			}
		}
		//壁との判定
		if (MapchipCollision(map.GetMapNumber(playerCollisionX[i], playerCollisionY[i]), Map::WALL))
		{
			WallCollision(playerCollisionX[i], playerCollisionY[i]);
		}
		//ゴールとの判定
		if (MapchipCollision(map.GetMapNumber(playerCollisionX[i], playerCollisionY[i]), Map::GOAL))
		{
			goalFlag = true;
		}
		if (MapchipCollision(map.GetMapNumber(playerCollisionX[i], playerCollisionY[i]), Map::LAVA))
		{
			if (BoxCollision(playerPosX - playerR, playerPosY - playerR, playerPosX + playerR, playerPosY + playerR, (playerCollisionX[i] / 32) * 32, (playerCollisionY[i] / 32) * 32 + 16, (playerCollisionX[i] / 32 + 1) * 32, (playerCollisionY[i] / 32 + 1) * 32))
			{
				status = DEAD;
			}

		}
	}
}

void Player::WallCollision(double PosX, double PosY)
{
	//上下判定
	double heightAX = playerPosX - 10;
	double heightAY = playerPosY - playerR;
	double heightBX = playerPosX + 10;
	double heightBY = playerPosY + playerR;
	//左右判定
	double widthAX;
	double widthAY;
	double widthBX;
	double widthBY;
	if (playerYSpeed >= 0)
	{
		widthAX = playerPosX - playerR;
		widthAY = playerPosY - playerR;
		widthBX = playerPosX + playerR;
		widthBY = playerPosY;
	}
	else
	{
		widthAX = playerPosX - playerR;
		widthAY = playerPosY;
		widthBX = playerPosX + playerR;
		widthBY = playerPosY + playerR;
	}
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

//上限矯正
void Player::Edit()
{
	//落下速度
	if (playerYSpeed >= fallMaxSpeed)
	{
		playerYSpeed = fallMaxSpeed;
	}
	if (playerYSpeed <= -fallMaxSpeed)
	{
		playerYSpeed = -fallMaxSpeed;
	}
}

void Player::scrollUpdate()
{
	if (status == SETTING)
	{
		scroll.SetScrollPos(playerPosX + (distanceX / 2), playerPosY + (distanceY / 2));
		isScrollFlag = true;
		return;
	}
	if (isScrollFlag)
	{
		double scrollT = 1-easeScroll.EasingMaker(Easing::Out, Easing::Quad, 10);
		scroll.SetScrollPos(playerPosX + (distanceX / 2) * scrollT, playerPosY + (distanceY / 2) * scrollT);
		if (easeScroll.Finish())
		{
			isScrollFlag = false;
		}
		return;
	}
	scroll.SetScrollPos(playerPosX, playerPosY);
}
