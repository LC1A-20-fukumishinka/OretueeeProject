#include "Title.h"
#include "Dxlib.h"
#include "input.h"
#include "egudai_Sound.h"

Title::Title()
{
	isOutFlag = false;
	isSceneFlag = false;
	fadeOut.Init(32, fadeOut.Out);
}

void Title::Init()
{
	isOutFlag = false;
	isSceneFlag = false;
	fadeOut.Init(32, fadeOut.Out);
}

void Title::Update()
{
	if ((Input::IsPadATrigger()) ||
		(GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_8) ||
		(GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_1))
	{
		isOutFlag = true;
		Sound::PlaySE(Sound::decision, false);
	}
}

void Title::Draw()
{
	DrawFormatString(0, 0, GetColor(0xFF, 0xFF, 0xFF), "SCENE:title");
	DrawFormatString(0, 20, GetColor(0xFF, 0xFF, 0xFF), "press A");
	if (isOutFlag)
	{
		fadeOut.Draw();
	}
}

bool Title::ChangeSelectScene()
{
		return fadeOut.GetFlag();
}
