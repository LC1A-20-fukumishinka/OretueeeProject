#include "collision.h"

bool collision::CircileCollision(double x1, double y1, double x2, double y2, double r1, double r2)
{
	{
		double disX = x1 - x2;
		double disY = y1 - y2;
		double d = (disX * disX + disY * disY);
		double r = ((r1 + r2) * (r1 + r2));

		return d < r;
	}
}

bool collision::BoxCollision(double Ax1, double Ay1, double Ax2, double Ay2, double Bx1, double By1, double Bx2, double By2 )
{


	if ((Ax1 <= Bx2) && (Ay1 <= By2) && (Ax2 >= Bx1) && (Ay2 >= By1))
	{
		return true;
	}

	return false;
}

bool collision::SquareCollision(double x1, double y1, double x2, double y2, double r1, double r2)
{
	double AX1 = x1 - r1;
	double AX2 = x1 + r1;
	double AY1 = y1 - r1;
	double AY2 = y1 + r1;
	double BX1 = x2 - r2;
	double BX2 = x2 + r2;
	double BY1 = y2 - r2;
	double BY2 = y2 + r2;

	if ((AX1 <= BX2) && (AY1 <= BY2) && (AX2 >= BX1) && (AY2 >= BY1))
	{
		return true;
	}

	return false;
}

bool collision::MapchipCollision(int pointNumber, int checkNumber)
{
	if (pointNumber == checkNumber) return true;
	return false;
}
