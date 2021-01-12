#pragma once

class Input
{
	Input();
	// 最新のキーボード情報用
	static char keys[];

	// 1ループ(フレーム)前のキーボード情報
	static char oldkeys[];

	static bool ATrigger;
public:



	static void Update();
	
	static bool IsKey(int key);

	static bool IsKeyTrigger(int key);

	static bool IsPadA();

	static bool IsPadATrigger();
};