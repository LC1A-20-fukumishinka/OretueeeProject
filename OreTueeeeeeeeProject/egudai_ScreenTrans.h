#pragma once

extern const int WIN_WIDTH;
extern const int WIN_HEIGHT;

class ScreenTrans
{
private:
	int graph; //•`‰æ‚³‚ê‚½•¨‚Ì•Û‘¶

	int size; //•ªŠ„‚µ‚½‚Ì‰æ‘œ‚Ì‘å‚«‚³(³•ûŒ`)
	double exRota; //Šg‘å—¦

	bool isEnd;

	void Updata(void);

public:
	ScreenTrans(void);

	void Init(int size);
	void Draw(void);

	bool GetFlag(void);
};
