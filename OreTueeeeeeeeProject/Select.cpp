#include "Select.h"
#include "DxLib.h"
#include "input.h"
#include "Map.h"
Select::Select()
{
	stageNum = 0;
	isOKFlag = false;
	stageMaxNum = (Map::mapNum)-1;
	joypadX = 0;
	joypadY = 0;
}

void Select::Init()
{
	isOKFlag = false;
	joypadX = 0;
	joypadY = 0;
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
}

bool Select::ChangeGameScene()
{
	return isOKFlag;
}

int Select::SetStageNum()
{
	return stageNum;
}
