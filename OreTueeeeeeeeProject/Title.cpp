#include "Title.h"
#include "Dxlib.h"
#include "input.h"

Title::Title()
{
	flag = false;
}

void Title::Init()
{
}

void Title::Update()
{
	if ((Input::IsPadATrigger()) ||
		(GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_8) ||
		(GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_1))
	{
		flag = true;
	}
	else
	{
		flag = false;
	}
}

void Title::Draw()
{
	DrawFormatString(0, 0, GetColor(0xFF, 0xFF, 0xFF), "SCENE:title");
	DrawFormatString(0, 20, GetColor(0xFF, 0xFF, 0xFF), "press A");
}

bool Title::ChangeSelectScene()
{
		return flag;
}
