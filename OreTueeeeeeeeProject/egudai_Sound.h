#pragma once

class Sound
{
public:
	/*�T�E���h�n���h��*/
	static int bgm; //bgm
	static int wark; //����
	static int jump; //�W�����v
	static int accele; //����
	static int death; //���S
	static int goal; //�S�[��
	static int item; //�A�C�e��
	static int decision; //����
	static int select; //�I��

	/*�T�E���h�n���h���ȊO�̕ϐ�*/
	static bool isMuteBGM;
	static bool isMuteSE;

	static void Init(void);

	static void PlayBGM(int SoundHandle);
	static void StopBGM(void);
	static void MuteBGM(void);
	static void BGMVolumeUp(int volume);
	static int GetBGMVolume(void);

	static void PlaySE(int SoundHandle, bool loopFlag = false);
	static void StopSE(void);
	static void MuteSE(void);
	static void SEVolumeUp(int volume);
	static int GetSEVolume(void);

private:
	static const int maxBGMVolume;
	static const int maxWarkVolume;
	static const int maxJumpVolume;
	static const int maxAcceleVolume;
	static const int maxDeathVolume;
	static const int maxGoalVolume;
	static const int maxItemVolume;
	static const int maxDecisionVolume;
	static const int maxSelectVolume;

	static int bgmVolume;
	static int seVolume;

	Sound();
	static void ChangeBGMVolume(void);
	static void ChangeSEVolume(void);
};
