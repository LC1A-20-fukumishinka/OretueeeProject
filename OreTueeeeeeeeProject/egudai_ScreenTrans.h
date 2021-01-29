#pragma once

extern const int WIN_WIDTH;
extern const int WIN_HEIGHT;

class ScreenTrans
{
private:
	int graph; //描画された物の保存

	int size; //分割した時の画像の大きさ(正方形)
	double exRota; //拡大率

	bool isEnd;

	void Updata(void);

public:
	ScreenTrans(void);

	void Init(int size);
	void Draw(void);

	bool GetFlag(void);
};
