#include "Select.h"
#include "DxLib.h"
#include "input.h"
#include "Map.h"
Select::Select()
{
	stageNum = 0;
	isOKFlag = false;
	isInFlag = true;
	stageMaxNum = (Map::mapMaxNum)-1;
	joypadX = 0;
	joypadY = 0;
	fadeIn.Init(32,fadeIn.In);
	fadeOut.Init(32,fadeOut.Out);
}

void Select::Init()
{
	isOKFlag = false;
	isInFlag = true;
	joypadX = 0;
	joypadY = 0;
	fadeIn.Init(32, fadeIn.In);
	fadeOut.Init(32, fadeOut.Out);
}

void Select::Update()
{
	oldpadX = joypadX;
	oldpadY = joypadY;
	GetJoypadAnalogInput(&joypadX, &joypadY, DX_INPUT_PAD1);

	if ((joypadX >= 300)&&(oldpadX<300))
	{
		stageNum++;
		isSelectFlag = true;
	}
	else if ((joypadX <= -300) && (oldpadX > -300))
	{
		stageNum--;
		isSelectFlag = true;

	}
	else
	{
		isSelectFlag = false;
	}

	if (stageNum < 0)
	{
		stageNum = 0;
	}
	if (stageNum >= stageMaxNum)
	{
		stageNum = stageMaxNum;
	}

	if (Input::IsPadATrigger())
	{
		isOKFlag = true;
	}
}

void Select::Draw()
{
	DrawFormatString(0, 0, GetColor(0xFF, 0xFF, 0xFF), "SCENE:select");
	DrawFormatString(0, 20, GetColor(0xFF, 0xFF, 0xFF), "Stage %d", stageNum + 1);
	DrawFormatString(0, 40, GetColor(0xFF, 0xFF, 0xFF), "PRESS A");
	if (isInFlag)
	{
		fadeIn.Draw();
	}if (isOKFlag)
	{
		fadeOut.Draw();
	}
}

bool Select::ChangeGameScene()
{
	return fadeOut.GetFlag();
}

int Select::SetStageNum()
{
	return stageNum;
}
