#include "egudai_Sound.h"
#include <DxLib.h>

int Sound::bgm = -1;
int Sound::wark = -1;
int Sound::jump = -1;
int Sound::accele = -1;
int Sound::death = -1;
int Sound::goal = -1;
int Sound::item = -1;
int Sound::decision = -1;
int Sound::select = -1;

const int Sound::maxBGMVolume = 0xB0;
const int Sound::maxWarkVolume = 0xFF;
const int Sound::maxJumpVolume = 0xC0;
const int Sound::maxAcceleVolume = 0xE0;
const int Sound::maxDeathVolume = 0x88;
const int Sound::maxGoalVolume = 0xFF;
const int Sound::maxItemVolume = 0xD0;
const int Sound::maxDecisionVolume = 0xD8;
const int Sound::maxSelectVolume = 0xFF;

int Sound::bgmVolume = 50;
int Sound::seVolume = 80;
bool Sound::isMuteBGM = false;
bool Sound::isMuteSE = false;

void Sound::Init(void)
{
	bgm = LoadSoundMem("./game.mp3");
	wark = LoadSoundMem("./wark.mp3");
	jump = LoadSoundMem("./jump.mp3");
	accele = LoadSoundMem("./accele.mp3");
	death = LoadSoundMem("./death.mp3");
	goal = LoadSoundMem("./goal.mp3");
	item = LoadSoundMem("./item.mp3");
	decision = LoadSoundMem("./decision.mp3");
	select = LoadSoundMem("./select.mp3");

	ChangeBGMVolume();
	ChangeSEVolume();
}

void Sound::PlayBGM(int SoundHandle)
{
	if (isMuteBGM == true)
	{
		if (CheckSoundMem(SoundHandle) == 1)
		{
			StopSoundMem(SoundHandle);
		}

		return;
	}

	if (CheckSoundMem(SoundHandle) == 0)
	{
		PlaySoundMem(SoundHandle, DX_PLAYTYPE_BACK);
	}
}

void Sound::StopBGM(void)
{
	StopSoundMem(bgm);
}

void Sound::MuteBGM(void)
{
	isMuteBGM = true;

	StopBGM();
}

void Sound::BGMVolumeUp(int volume)
{
	bgmVolume += volume;

	if (bgmVolume >= 100)
	{
		bgmVolume = 100;
	}
	if (bgmVolume <= 0)
	{
		bgmVolume = 0;
	}

	ChangeBGMVolume();
}

void Sound::BGMVolumeDown(int volume)
{
	bgmVolume -= volume;

	if (bgmVolume >= 100)
	{
		bgmVolume = 100;
	}
	if (bgmVolume <= 0)
	{
		bgmVolume = 0;
	}

	ChangeBGMVolume();
}

int Sound::GetBGMVolume(void)
{
	return bgmVolume;
}

void Sound::PlaySE(int SoundHandle, bool loopFlag)
{
	if (isMuteSE == true)
	{
		if (CheckSoundMem(SoundHandle) == 1)
		{
			StopSoundMem(SoundHandle);
		}

		return;
	}

	if (loopFlag == true)
	{
		if (CheckSoundMem(SoundHandle) == 0)
		{
			PlaySoundMem(SoundHandle, DX_PLAYTYPE_BACK);
		}
	}
	else
	{
		switch (CheckSoundMem(SoundHandle))
		{
		case 1:
			StopSoundMem(SoundHandle);
		case 0:
			PlaySoundMem(SoundHandle, DX_PLAYTYPE_BACK);
			break;
		default:
			break;
		}
	}
}

void Sound::StopSE(void)
{
	StopSoundMem(wark);
	StopSoundMem(jump);
	StopSoundMem(accele);
	StopSoundMem(death);
	StopSoundMem(goal);
	StopSoundMem(item);
	StopSoundMem(decision);
	StopSoundMem(select);
}

void Sound::MuteSE(void)
{
	isMuteSE = true;

	StopSE();
}

void Sound::SEVolumeUp(int volume)
{
	seVolume += volume;

	if (seVolume >= 100)
	{
		seVolume = 100;
	}
	if (seVolume <= 0)
	{
		seVolume = 0;
	}

	ChangeSEVolume();
}

void Sound::SEVolumeDown(int volume)
{
	seVolume -= volume;

	if (seVolume >= 100)
	{
		seVolume = 100;
	}
	if (seVolume <= 0)
	{
		seVolume = 0;
	}

	ChangeSEVolume();
}

int Sound::GetSEVolume(void)
{
	return seVolume;
}

void Sound::ChangeBGMVolume(void)
{
	ChangeVolumeSoundMem(maxBGMVolume * bgmVolume / 100, bgm);
}

void Sound::ChangeSEVolume(void)
{
	ChangeVolumeSoundMem(maxWarkVolume * seVolume / 100, wark);
	ChangeVolumeSoundMem(maxJumpVolume * seVolume / 100, jump);
	ChangeVolumeSoundMem(maxAcceleVolume * seVolume / 100, accele);
	ChangeVolumeSoundMem(maxDeathVolume * seVolume / 100, death);
	ChangeVolumeSoundMem(maxGoalVolume * seVolume / 100, goal);
	ChangeVolumeSoundMem(maxItemVolume * seVolume / 100, item);
	ChangeVolumeSoundMem(maxDecisionVolume * seVolume / 100, decision);
	ChangeVolumeSoundMem(maxSelectVolume * seVolume / 100, select);
}
