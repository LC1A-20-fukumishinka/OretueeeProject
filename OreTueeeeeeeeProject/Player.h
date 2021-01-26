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
	//プレイヤーの座標
	double playerPosX;
	double playerPosY;
	double startPosX;
	double startPosY;
	double playerDrawPosX;
	double playerDrawPosY;

	//マップチップ判定用の当たり判定
	double playerCollisionX[PlayerChip];
	double playerCollisionY[PlayerChip];

	//歩くスピード
	float warkSpeed;
	int playerR;

	//重力
	float gravity;
	//実際の移動速度
	double playerYSpeed;
	double playerXSpeed;
	double scrollDistanceX;
	double scrollDistanceY;

	//速度上限
	int warkMaxSpeed;
	int fallMaxSpeed;

	//加速カーソルの座標
	double accelePosX;
	double accelePosY;
	double acceleDrawPosX;
	double acceleDrawPosY;
	//加速フラグ
	bool isCursorFlag;
	//加速可能フラグ
	bool isAcceleFlag;
	//スクロール戻し描画フラグ
	bool isScrollFlag;
	//ゴールフラグ
	bool goalFlag;
	//入力
	int inputX,oldInputX;
	int inputY,oldInputY;

	//ひとつ前のフレームのフラグ
	bool oldFlag;

	//自キャラと加速カーソルの距離
	double distanceX;
	double distanceY;
	double distance;

	//自キャラの状態
	int status;

	//加速スピード
	double acceleSpeed;

	//中断
	double cancelDistance;
	//限界の距離
	double maxDistance;

	//アニメーション関係のステータス
	int graphNum;
	int animationTimer;
	int animationStatus;
	int animationOldStatus;
	bool isTurnFlag;
	bool isItemFlag;

	//ポーズメニュー
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
