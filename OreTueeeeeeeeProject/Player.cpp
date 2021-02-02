#include "Player.h"
#include "DxLib.h"
#include "input.h"
#include "collision.h"
#include <math.h>
#include "egudai_Sound.h"
using namespace collision;

int Player::playerIdolGraph[] = { 0 };
int Player::playerWarkGraph[] = { 0 };
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
	isGoalFlag = false;
	isScrollFlag = false;
	playerYSpeed = 0.1;
	playerXSpeed = 0;
	scrollDistanceX = 0;
	scrollDistanceY = 0;
	playerPosX = 0;
	playerPosY = 0;
	startPosX = 0;
	startPosY = 0;
	inputX = 0;
	inputY = 0;
	oldInputX = 0;
	oldInputY = 0;
	oldFlag = 0;
	distanceX = 0;
	distanceY = 0;
	distance = 0;
	status = NORMAL;
	acceleSpeed = 1;

	graphNum = 0;
	animationTimer = 0;;
	animationStatus = IDOL;
	animationOldStatus = IDOL;
	LoadDivGraph("playerIdol.png", 2, 2, 1, 32, 32, playerIdolGraph);
	LoadDivGraph("playerWark.png", 7, 7, 1, 32, 32, playerWarkGraph);
	isTurnFlag = false;

	isMenuFlag = false;
	isReturnFlag = false;
	isPauseFlag = false;
	isItemFlag = false;
	menuStatus = RESUME;

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
	isGoalFlag = false;
	isScrollFlag = false;
	status = NORMAL;
	maxDistance = 100;

	graphNum = 0;
	animationTimer = 0;;
	animationStatus = IDOL;
	animationOldStatus = IDOL;
	isMenuFlag = false;
	isReturnFlag = false;
	isPauseFlag = false;
	isItemFlag = false;
	menuStatus = RESUME;
	clear.Init(WIN_WIDTH, WIN_HEIGHT);
	clear.SetColor(GetColor(0xFF, 0xFF, 0xFF));
}

void Player::Update()
{
	Joypad();
	Menu();
	if (isMenuFlag)return;
	Normal();
	Setting();
	Accele();
	Collision();
	Animation();
	Move();
	if (!isGoalFlag)
	{
		scrollUpdate();
	}
	clear.Update();
}

void Player::Draw()
{
	SetDrawPos();
	if (isGoalFlag)
	{
		clear.SetGraph(playerIdolGraph[graphNum]);
		clear.Draw();
	}
	else
	{
		if (GetDeathFlag())return;
		switch (animationStatus)
		{
		case IDOL:
			DrawRotaGraph(playerDrawPosX + playerR, playerDrawPosY + playerR, 1.0, 0, playerIdolGraph[graphNum], TRUE, isTurnFlag);
			/*DrawGraph(playerDrawPosX, playerDrawPosY, playerIdolGraph[graphNum], TRUE);*/
			break;
		case WARK:
			DrawRotaGraph(playerDrawPosX + playerR, playerDrawPosY + playerR, 1.0, 0, playerWarkGraph[graphNum], TRUE, isTurnFlag);
			break;
		default:
			break;
		}

	}
	//デバッグ用のマップ判定描画(白点)
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
	DrawFormatString(0, 0, GetColor(0xBB, 0xBB, 0xBB), "ITEM %d/1", isItemFlag);


	if (isMenuFlag)
	{
		int mainPosX = WIN_WIDTH / 2 - 40, mainPosY = WIN_HEIGHT / 2;
		DrawBox(WIN_WIDTH / 2 - 100, WIN_HEIGHT / 2 - 75, WIN_WIDTH / 2 + 100, WIN_HEIGHT / 2 + 75, GetColor(0x33, 0x33, 0x33), true);
		DrawFormatString(mainPosX, mainPosY, GetColor(0xBB, 0xBB, 0xBB), "RESUME");
		DrawFormatString(mainPosX, mainPosY + 25, GetColor(0xBB, 0xBB, 0xBB), "SELECT");

		DrawTriangle(mainPosX - 5, mainPosY + 8 + (menuStatus * 25), mainPosX - 10, mainPosY + 3 + (menuStatus * 25), mainPosX - 10, mainPosY + 13 + (menuStatus * 25),
			GetColor(0xBB, 0xBB, 0xBB), true);
	}
}

double Player::GetPosX()
{
	return playerPosX;
}

double Player::GetPosY()
{
	return playerPosY;
}

bool Player::GetGoalFlag()
{
	return clear.GetFinishFlag();
}

bool Player::GetReturnFlag()
{
	return isReturnFlag;
}

bool Player::GetItemFlag()
{
	return isItemFlag;
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
		Sound::PlaySE(Sound::jump, false);
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

	//歩きの音声
	if (playerYSpeed == 0 && playerXSpeed != 0)
	{
		Sound::PlaySE(Sound::wark, true);
	}
	else
	{
		StopSoundMem(Sound::wark);
	}

	//加速入力
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_B)
	{
		status = SETTING;
		isCursorFlag = true;
		Sound::StopSE();
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
		StopSoundMem(Sound::wark);
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

	Sound::PlaySE(Sound::accele, true);
}

void Player::Menu()
{
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_8)
	{
		if (!isPauseFlag)
		{
			if (isMenuFlag)
			{
				isMenuFlag = false;
			}
			else
			{
				isMenuFlag = true;
				menuStatus = RESUME;
			}
		}
		Sound::PlaySE(Sound::decision, false);
	}
	isPauseFlag = GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_8;
	if (!isMenuFlag)return;
	if ((inputY >= 100) && (oldInputY < 100))
	{
		menuStatus++;
		if (menuStatus >= menuEnd)
		{
			menuStatus = RESUME;
		}
		Sound::PlaySE(Sound::select, false);
	}
	if ((inputY <= -100) && (oldInputY > -100))
	{
		menuStatus--;
		if (menuStatus <= -1)
		{
			menuStatus = menuEnd - 1;
		}
		Sound::PlaySE(Sound::select, false);
	}
	if (Input::IsPadATrigger())
	{
		switch (menuStatus)
		{
		case RESUME:
			isMenuFlag = false;
			break;
		case RETURN:
			isReturnFlag = true;
			break;
		default:
			break;
		}
		Sound::PlaySE(Sound::decision, false);
	}
	oldInputX = inputX;
	oldInputY = inputY;

}

bool Player::GetDeathFlag()
{
	if (status != DEAD)return false;
	return true;
}

void Player::Move()
{
	if (GetDeathFlag())return;
	if (isGoalFlag)return;
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

	PlayerMapchipUpdate();
	for (int i = 0; i < PlayerChip; i++)
	{
		//	ブロックの当たり判定
		if ((MapchipCollision(map.GetMapNumber(playerCollisionX[i], playerCollisionY[i]), Map::BLOCK)))
		{
			map.ChangeMapNumber(playerCollisionX[i], playerCollisionY[i], Map::NONE);
			isItemFlag = true;
			Sound::PlaySE(Sound::item, false);
		}
		//壁との判定
		if (MapchipCollision(map.GetMapNumber(playerCollisionX[i], playerCollisionY[i]), Map::WALL))
		{
			int a = map.GetMapNumber(playerCollisionX[i], playerCollisionY[i]);
			WallCollision(playerCollisionX[i], playerCollisionY[i]);
			PlayerMapchipUpdate();
		}
		//ゴールとの判定
		if (MapchipCollision(map.GetMapNumber(playerCollisionX[i], playerCollisionY[i]), Map::GOAL))
		{
			if (isGoalFlag)return;
			playerPosX = (int)(playerCollisionX[i] / 32) * 32+16;
			playerPosY = (int)(playerCollisionY[i] / 32) * 32+16;
			SetDrawPos();
			clear.SetPos(playerDrawPosX, playerDrawPosY, playerR * 2, playerR * 2);
			clear.SetFlag(true);
			isGoalFlag = true;
			Sound::PlaySE(Sound::goal, false);
		}
		if (MapchipCollision(map.GetMapNumber(playerCollisionX[i], playerCollisionY[i]), Map::LAVA))
		{
			if (BoxCollision(playerPosX - playerR, playerPosY - playerR, playerPosX + playerR, playerPosY + playerR, (playerCollisionX[i] / 32) * 32, (playerCollisionY[i] / 32) * 32 + 16, (playerCollisionX[i] / 32 + 1) * 32, (playerCollisionY[i] / 32 + 1) * 32))
			{
				status = DEAD;
				Sound::PlaySE(Sound::death, true);
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

	//縦
	if (BoxCollision(heightAX, heightAY, heightBX, heightBY, (int)(PosX / 32) * 32, (int)(PosY / 32) * 32, (int)(PosX / 32 + 1) * 32, (int)(PosY / 32 + 1) * 32))
	{

		if (playerYSpeed > 0)
		{
			playerPosY = ((int)(PosY / 32) - 1) * 32 + 16;
			playerYSpeed = 0;
		}
		else if (playerYSpeed < 0)
		{
			playerPosY = ((int)(PosY / 32) + 1) * 32 + 16;
			playerYSpeed = 0.1;
		}
	}

	//横
	if (BoxCollision(widthAX, widthAY, widthBX, widthBY, (int)(PosX / 32) * 32, (int)(PosY / 32) * 32, (int)(PosX / 32 + 1) * 32, (int)(PosY / 32 + 1) * 32))
	{
		if (playerXSpeed > 0)
		{
			playerPosX = ((int)(PosX / 32) - 1) * 32 + 16;
		}
		else if (playerXSpeed < 0)
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
		double scrollT = 1 - easeScroll.EasingMaker(Easing::Out, Easing::Quad, 30);
		scroll.SetScrollPos(playerPosX + (distanceX / 2) * scrollT, playerPosY + (distanceY / 2) * scrollT);
		if (easeScroll.Finish())
		{
			isScrollFlag = false;
		}
		return;
	}
	scroll.SetScrollPos(playerPosX, playerPosY);
}

void Player::PlayerMapchipUpdate()
{
	playerCollisionX[LeftUp] = playerPosX + playerXSpeed - playerR;
	playerCollisionY[LeftUp] = playerPosY + playerYSpeed - playerR;

	playerCollisionX[RightUp] = playerPosX + playerXSpeed + playerR;
	playerCollisionY[RightUp] = playerPosY + playerYSpeed - playerR;

	playerCollisionX[RightDown] = playerPosX + playerXSpeed + playerR;
	playerCollisionY[RightDown] = playerPosY + playerYSpeed + playerR;

	playerCollisionX[LeftDown] = playerPosX + playerXSpeed - playerR;
	playerCollisionY[LeftDown] = playerPosY + playerYSpeed + playerR;
}

void Player::Animation()
{
	if (playerXSpeed > 0)
	{
		isTurnFlag = false;
	}
	else if (playerXSpeed < 0)
	{
		isTurnFlag = true;
	}
	switch (animationStatus)
	{
	case IDOL:
		if ((playerXSpeed != 0) && (!isGoalFlag))
		{
			animationStatus = WARK;
			graphNum = 0;
			animationTimer = WARK_TIMER;
		}

		//アニメーション進行
		if (animationTimer <= 0)
		{
			animationTimer = IDOL_TIMER;
			if (graphNum == 1)
			{
				graphNum = 0;
			}
			else
			{
				graphNum++;
			}
		}
		--animationTimer;
		break;
	case WARK:
		if ((playerXSpeed == 0) || (isGoalFlag))
		{
			animationStatus = IDOL;
			graphNum = 0;
			animationTimer = IDOL_TIMER;
		}
		//アニメーション進行
		if (animationTimer <= 0)
		{
			animationTimer = WARK_TIMER;
			if (graphNum == 6)
			{
				graphNum = 0;
			}
			else
			{
				graphNum++;
			}
		}
		--animationTimer;
		break;
	default:
		break;
	}


}
