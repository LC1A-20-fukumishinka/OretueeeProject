#pragma once

namespace collision
{
	bool CircileCollision(double x1, double y1, double x2, double y2, double r1, double r2);

	bool BoxCollision(double Ax1, double Ay1, double Ax2, double Ay2, double Bx1, double By1, double Bx2, double By2);

	bool SquareCollision(double x1, double y1, double x2, double y2, double r1, double r2);

	bool MapchipCollision(int pointNumber, int checkNumber);
}


//class Collision
//{
//private:
//	Collision();
//public:
//	static bool CircileCollision(double x1, double y1, double x2, double y2, double r1, double r2)
//	{
//		double disX = x1 - x2;
//		double disY = y1 - y2;
//		double d = (disX * disX + disY * disY);
//		double r = ((r1 + r2)* (r1 + r2));
//
//		if (d < r)
//		{
//			return true;
//		}
//		return false;
//	}
//};