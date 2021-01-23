#include "egudai_Death.h"
#include <DxLib.h>
#include <stdlib.h>
#include <time.h>

Death::Death(void)
{
	isEnd = true;
	oldIsEnd = isEnd;

	playerPosX = 0;
	playerPosY = 0;
	playerSpeedY = 0;
	playerR = 16;
	playerGraph = -1;
	playerDrawPosX = 0;
	playerDrawPosY = 0;

	particleGraph = LoadGraph("particle.png");
	graphR = 12;

	for (int i = 0; i < fireNum; i++)
	{
		firePosX[i] = 0;
		firePosY[i] = 0;
		fireSpeedY[i] = 0;
		pal[i] = 0;
		isFireAlive[i] = false;
		isInit[i] = true;
	}

	srand(time(nullptr));
}

void Death::Init(double playerPosX, double playerPosY, int playerR, int playerGraph)
{
	isEnd = false;
	oldIsEnd = isEnd;

	this->playerPosX = playerPosX;
	this->playerPosY = playerPosY;
	playerSpeedY = -gravity * (interbal / 2);
	this->playerGraph = playerGraph;

	this->playerR = playerR;

	for (int i = 0; i < fireNum; i++)
	{
		fireSpeedY[i] = 0;
		pal[i] = fireNum;
		isFireAlive[i] = false;
		isInit[i] = true;
	}
}

void Death::Update(void)
{
	oldIsEnd = isEnd;
	if (isEnd == true) return;

	//重力による落下
	playerSpeedY += gravity;
	this->playerPosY += playerSpeedY;

	//1フレーム中に何回パーティクルを初期化したかのカウンタ
	int count = 0;

	for (int i = 0; i < fireNum; i++)
	{
		//パーティクルの更新処理
		if (isFireAlive[i] == true)
		{
			if (fireSpeedY[i] <= 1.5)
			{
				fireSpeedY[i] += gravity;
			}
			firePosY[i] += fireSpeedY[i];
			pal[i] -= 3;

			if (pal[i] <= 0)
			{
				pal[i] = 0;
				isFireAlive[i] = false;
			}

			//演出の終了
			if (i == interbal)
			{
				isEnd = true;
			}
		}
		//パーティクルの初期化
		else
		{
			if (count >= 1) continue; //1フレームにつき1個初期化
			if (isInit[i] == false) continue; //初期化の必要が無いものは飛ばす

			firePosX[i] = rand() % (int)((playerPosX + playerR) - (playerPosX - playerR) + 1) + (playerPosX - playerR);
			firePosY[i] = rand() % (int)((playerPosY + playerR) - (playerPosY - playerR) + 1) + (playerPosY - playerR);
			isFireAlive[i] = true;
			isInit[i] = false;

			count++;
		}
	}
}

void Death::Draw(void)
{
	if (isEnd == true) return;

	SetDrawBright(0xF4, 0x33, 0x33);

	for (int i = 0; i < fireNum; i++)
	{
		SetDrawBlendMode(DX_BLENDMODE_ADD, pal[i]);

		if (isFireAlive[i] == true)
		{
			//パーティクルの描画
			DrawExtendGraph(firePosX[i] - scroll.GetScrollX() - graphR, firePosY[i] - scroll.GetScrollY() - graphR,
				firePosX[i] - scroll.GetScrollX() + graphR, firePosY[i] - scroll.GetScrollY() + graphR, particleGraph, true);
		}
	}
	//プレイヤーの描画座標の計算
	playerDrawPosX = this->playerPosX - scroll.GetScrollX() - playerR;
	playerDrawPosY = this->playerPosY - scroll.GetScrollY() - playerR;

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0x80);
	SetDrawBright(0xFF, 0x60, 0x20);

	//プレイヤーの描画
	PlayerDraw();

	SetDrawBright(0xFF, 0xFF, 0xFF);
}

bool Death::GetFlag(void)
{
	return isEnd;
}

bool Death::GetOldFlag(void)
{
	return oldIsEnd;
}

void Death::PlayerDraw(void)
{
	if (playerGraph == -1)
	{
		DrawBox(playerDrawPosX, playerDrawPosY, playerDrawPosX + playerR * 2, playerDrawPosY + playerR * 2, GetColor(0xAA, 0xAA, 0x00), TRUE);
	}
	else
	{
		DrawGraph(playerDrawPosX, playerDrawPosY, playerGraph, true);
	}
}
