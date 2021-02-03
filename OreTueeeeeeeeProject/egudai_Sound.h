#pragma once

class Sound
{
public:
	/*サウンドハンドル*/
	static int bgm; //bgm
	static int wark; //歩き
	static int jump; //ジャンプ
	static int accele; //加速
	static int death; //死亡
	static int goal; //ゴール
	static int item; //アイテム
	static int decision; //決定
	static int select; //選択

	/*サウンドハンドル以外の変数*/
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
