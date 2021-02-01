#include "SlashEffect.h"
#include"DxLib.h"
#include<math.h>
SlashEffect::SlashEffect()
{
	isDrawFlag = false;
	maxThickness = 0;
	thickness = maxThickness;
	color = 0;
	maxTimer = 0;
	timer = maxTimer;
	size = 0;
	vectorX = 0;
	vectorY = 0;
	vector = 0;
	normalVectorX = 0;
	normalVectorY = 0;
	slashVectorX = 0;
	slashVectorY = 0;
	slashVector = 0;
	startPosX = 0;
	startPosY = 0;
	endPosX = 0;
	endPosY = 0;
	isFinishFlag = false;
}

void SlashEffect::Init(int MaxThickness, int MaxTimer, int Color, int width, int height)
{
	isDrawFlag = false;
	maxThickness = MaxThickness;
	thickness = maxThickness;
	color = Color;
	maxTimer = MaxTimer;
	timer = maxTimer;
	size = (sqrt(((double)width * width) + ((double)height * height)));
	vectorX = 0;
	vectorY = 0;
	vector = 0;
	normalVectorX = 0;
	normalVectorY = 0;
	slashVectorX = 0;
	slashVectorY = 0;
	slashVector = 0;
	startPosX = 0;
	startPosY = 0;
	endPosX = 0;
	endPosY = 0;
	isFinishFlag = false;
}

void SlashEffect::SetSlash(double AttackX, double AttackY, double HitX, double HitY)
{
	if (isDrawFlag)return;
	timer = maxTimer;
	thickness = maxThickness;
	vectorX = HitX - AttackX;
	vectorY = HitY - AttackY;
	vector = sqrt((vectorX * vectorX) + (vectorY * vectorY));
	startPosX = HitX;
	startPosY = HitY;
	endPosX = HitX;
	endPosY = HitY;
	isFinishFlag = false;
}

void SlashEffect::SetFlag(bool Flag)
{
	if (!Flag)return;
	isDrawFlag = true;
}

void SlashEffect::Update()
{
	if (!isDrawFlag)return;
	Normalize();
	SetDrawPos();
	SmallThickness();
	Finish();
}

void SlashEffect::Draw()
{
	if (!isDrawFlag)return;
	DrawLine(startPosX, startPosY, endPosX, endPosY, color, thickness);
}

bool SlashEffect::GetFinishFlag()
{
	return isFinishFlag;
}

void SlashEffect::Finish()
{
	if (!easeSlash.Finish())return;
	isFinishFlag = true;
	isDrawFlag = false;
}

void SlashEffect::Normalize()
{
	normalVectorX = vectorX / vector;
	normalVectorY = vectorY / vector;
}

void SlashEffect::SetDrawPos()
{
	slashVectorX = normalVectorX * size;
	slashVectorY = normalVectorY * size;
	startPosX += slashVectorX;
	startPosY += slashVectorY;
	endPosX -= slashVectorX;
	endPosY -= slashVectorY;

}

void SlashEffect::SmallThickness()
{
	if (isDrawFlag)
	{
		thickness = maxThickness * (1-easeSlash.EasingMaker(easeSlash.Out, easeSlash.Quart, maxTimer));;
	}
}
