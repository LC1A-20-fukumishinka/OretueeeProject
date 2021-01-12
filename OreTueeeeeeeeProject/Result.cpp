#include "Result.h"
#include "DxLib.h"
#include "input.h"
Result::Result()
{
}

void Result::Init()
{
}

void Result::Update()
{
}

bool Result::ChangeSelectScene()
{
	return (Input::IsPadATrigger());
}

void Result::Draw()
{
	DrawFormatString(0, 0, GetColor(0xFF, 0xFF, 0xFF), "SCENE RESULT");
	DrawFormatString(270, 200, GetColor(0xFF, 0xFF, 0xFF), "press A");
}
