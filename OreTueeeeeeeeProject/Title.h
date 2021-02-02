#pragma once
#include"egudai_ScreenTrans.h"
class Title
{
public:
	Title();
	void Init();
	void Update();
	void Draw();
	bool ChangeSelectScene();
private:
	bool isOutFlag,isSceneFlag;
	ScreenTrans fadeOut;
};