#pragma once

class Input
{
	Input();
	// �ŐV�̃L�[�{�[�h���p
	static char keys[];

	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
	static char oldkeys[];

	static bool ATrigger;
public:



	static void Update();
	
	static bool IsKey(int key);

	static bool IsKeyTrigger(int key);

	static bool IsPadA();

	static bool IsPadATrigger();
};