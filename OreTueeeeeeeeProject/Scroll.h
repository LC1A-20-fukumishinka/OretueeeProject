#pragma once
extern const int WIN_WIDTH;
extern const int WIN_HEIGHT;
class Scroll
{
public:
	Scroll();
	void Init(double scrollMinX, double ScrollMinY, double ScrollMaxX, double ScrollMaxY);
	void Update();
	void SetScrollPos(double posX, double posY);
	double GetScrollX();
	double GetScrollY();
private:
	static double scrollMinX, scrollMaxX;
	static double scrollMinY, scrollMaxY;
	static double scrollPosX, scrollPosY;
	static double scrollX, scrollY;
};
