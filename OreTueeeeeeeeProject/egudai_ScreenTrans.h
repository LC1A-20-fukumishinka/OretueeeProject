#pragma once

extern const int WIN_WIDTH;
extern const int WIN_HEIGHT;

class ScreenTrans
{
private:
	int graph; //�`�悳�ꂽ���̕ۑ�

	int size; //�����������̉摜�̑傫��(�����`)
	double exRota; //�g�嗦

	bool isEnd;

	void Updata(void);

public:
	ScreenTrans(void);

	void Init(int size);
	void Draw(void);

	bool GetFlag(void);
};
