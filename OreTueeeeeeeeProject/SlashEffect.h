#pragma once
#include "EaseClass.h"
class SlashEffect
{
public:
	SlashEffect();
	void Init(int MaxThickness, int MaxTimer, int Color, int width, int height);
	void SetSlash( double AttackX, double AttackY, double HitX, double HitY);
	void SetFlag(bool Flag);
	void Update();
	void Draw();
	bool GetFinishFlag();

private:
	//斬撃のフラグ、描画のフラグ
	bool isSlashFlag;
	bool isDrawFlag;
	bool isFinishFlag;
	double maxThickness;
	double thickness;
	int color;
	int maxTimer;
	int timer;
	double vectorX;
	double vectorY;
	double vector;
	double normalVectorX;
	double normalVectorY;

	double size;
	double slashVectorX;
	double slashVectorY;
	double slashVector;
	double startPosX;
	double startPosY;
	double endPosX;
	double endPosY;
	Easing easeSlash;
	//関数
	void Normalize();
	void SetDrawPos();
	void SmallThickness();
	void Finish();
};