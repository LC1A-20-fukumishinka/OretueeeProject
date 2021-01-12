#include "Scroll.h"

double Scroll::scrollMinX, Scroll::scrollMaxX;
double Scroll::scrollMinY, Scroll::scrollMaxY;
double Scroll::scrollPosX, Scroll::scrollPosY;
double Scroll::scrollX, Scroll::scrollY;
Scroll::Scroll()
{
}

void Scroll::Init(double ScrollMinX, double ScrollMinY, double ScrollMaxX, double ScrollMaxY)
{
	scrollMinX = ScrollMinX;
	scrollMaxX = ScrollMaxX;
	scrollMinY = ScrollMinY;
	scrollMaxY = ScrollMaxY;

}

void Scroll::Update()
{
	scrollX = scrollPosX - (WIN_WIDTH / 2);
	scrollY = scrollPosY - (WIN_HEIGHT / 2);
	if (scrollPosX <= scrollMinX)
	{
		scrollX = 0;
	}
	else if (scrollPosX >= scrollMaxX)
	{
		scrollX = scrollMaxX - (WIN_WIDTH / 2);
	}
	if (scrollPosY <= scrollMinY)
	{
		scrollY = 0;
	}
	else if (scrollPosY >= scrollMaxY)
	{
		scrollY = scrollMaxY - (WIN_HEIGHT / 2);
	}
}

void Scroll::SetScrollPos(double posX, double posY)
{
	scrollPosX = posX;
	scrollPosY = posY;
}

double Scroll::GetScrollX()
{
	return scrollX;
}

double Scroll::GetScrollY()
{
	return scrollY;
}
