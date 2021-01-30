#pragma once

extern const int WIN_WIDTH;
extern const int WIN_HEIGHT;

class ScreenTrans
{
private:
	int graph; //�`�悳�ꂽ���̕ۑ�

	int size; //�����������̉摜�̑傫��(�����`)
	double exRota; //�g�嗦

	int mode;

	bool isEnd;

	void Updata(void);

public:
	enum Mode
	{
		In,
		Out
	};

	ScreenTrans(void);

	void Init(int size, int mode);
	void Draw(void);

	bool GetFlag(void);
};
