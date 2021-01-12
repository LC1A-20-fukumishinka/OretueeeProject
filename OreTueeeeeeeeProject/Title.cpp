#include "Title.h"
#include "Dxlib.h"
#include "input.h"

Title::Title()
{
}

void Title::Init()
{
}

void Title::Update()
{
}

void Title::Draw()
{
	DrawFormatString(0, 0, GetColor(0xFF, 0xFF, 0xFF), "SCENE:title");
	DrawFormatString(300, 250, GetColor(0xFF, 0xFF, 0xFF), "press A");
}

bool Title::ChsngeSelectScene()
{
	if ((Input::IsPadATrigger()) ||
		(GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_8)||
		(GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_1))
	{
		return true;
	}

}
