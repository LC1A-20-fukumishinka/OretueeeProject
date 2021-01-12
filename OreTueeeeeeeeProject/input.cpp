#include "input.h"
#include"DxLib.h"

char Input::keys[256] = { 0 };
char Input::oldkeys[256] = { 0 };
bool Input::ATrigger = false;


void Input::Update()
{
	for (int i = 0; i < 256; i++)
	{
		oldkeys[i] = keys[i];
	}
	GetHitKeyStateAll(keys);
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_A)return;
	ATrigger = false;
}

bool Input::IsKey(int key)
{
	return keys[key];
}

bool Input::IsKeyTrigger(int key)
{
	return keys[key]&&!oldkeys[key];
}

bool Input::IsPadA()
{
	ATrigger = true;
	return GetJoypadInputState(DX_INPUT_PAD1)&PAD_INPUT_A;
}

bool Input::IsPadATrigger()
{
	if ((!ATrigger) && (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_A))
	{
		ATrigger = true;
		return true;
	}
	return false;
}
