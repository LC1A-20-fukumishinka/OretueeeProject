#pragma once
#include "Scroll.h"

class Death
{
public:
	Death(void);
	//全体の初期化
	void Init(double PlayerPosX, double PlayerPosY, int playerR, int playerGraph = -1);
	void Update(void);
	void Draw(void);
	bool GetFlag(void);
	bool GetOldFlag(void);
private:
	static const int fireNum = 100; //パーティクルの個数
	static const int interbal = 40; //演出の時間

	bool isEnd; //演出が終了したかどうかのフラグ
	bool oldIsEnd; //1フレーム前のisEnd

	const double gravity = 0.49; //重力

	double playerPosX, playerPosY; //プレイヤーの座標
	double playerSpeedY; //プレイヤーのスピード
	int playerR; //プレイヤーの半径

	int playerGraph; //プレイヤーの画像データ
	double playerDrawPosX, playerDrawPosY; //プレイヤーの描画座標

	double firePosX[fireNum], firePosY[fireNum]; //パーティクルの座標
	double fireSpeedY[fireNum]; //パーティクルの移動速度

	int particleGraph; //パーティクルの画像データ
	int graphR; //パーティクルを描画する時の半径
	int pal[fireNum]; //パーティクルの透明度

	bool isFireAlive[fireNum]; //パーティクルが生きているかどうか
	bool isInit[fireNum]; //パーティクルの初期化フラグ

	Scroll scroll;
	void PlayerDraw(void);
};
