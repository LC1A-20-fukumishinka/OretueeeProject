#include "EaseClass.h"
#include<math.h>




Easing::Easing()
{
	maxTimer = 1;
	timer = 0;
}

double Easing::EasingMaker(int InOut, int type, int maxTimer)
{
	this->maxTimer = maxTimer;
	switch (InOut)
	{
	case In:
		switch (type)
		{
		case Sine:
			return easeInSine();
			break;
		case Quad:
			return easeInQuad();
			break;
		case Cubic:
			return easeInCubic();
			break;
		case Quart:
			return easeInQuart();
			break;
		case Quint:
			return easeInQuint();
			break;
		case Expo:
			return easeInExpo();
			break;
		case Circ:
			return easeInCirc();
			break;
		case Back:
			return easeInBack();
			break;
		case Elastic:
			return easeInElastic();
			break;
		case Bounce:
			return easeInBounce();
			break;
		default:
			break;
		}
		break;
	case Out:
		switch (type)
		{
		case Sine:
			return easeOutSine();
			break;
		case Quad:
			return easeOutQuad();
			break;
		case Cubic:
			return easeOutCubic();
			break;
		case Quart:
			return easeOutQuart();
			break;
		case Quint:
			return easeOutQuint();
			break;
		case Expo:
			return easeOutExpo();
			break;
		case Circ:
			return easeOutCirc();
			break;
		case Back:
			return easeOutBack();
			break;
		case Elastic:
			return easeOutElastic();
			break;
		case Bounce:
			return easeOutBounce();
			break;
		default:
			break;
		}
		break;
	case this->InOut:
		switch (type)
		{
		case Sine:
			return easeinOutSine();
			break;
		case Quad:
			return easeInOutQuad();
			break;
		case Cubic:
			return easeInOutCubic();
			break;
		case Quart:
			return easeInOutQuart();
			break;
		case Quint:
			return easeInOutQuint();
			break;
		case Expo:
			return easeInOutExpo();
			break;
		case Circ:
			return easeInOutCirc();
			break;
		case Back:
			return easeInOutBack();
			break;
		case Elastic:
			return easeInOutElastic();
			break;
		case Bounce:
			return easeInOutBounce();
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	return 0.0;
}

void Easing::Init()
{
	maxTimer = 1;
	timer = 0;
}

bool Easing::Finish()
{
	if (timer < maxTimer)	return false;
	timer = 0;
	return true;
}

double Easing::easeBasic()
{

	if (timer >= maxTimer) return 1.0;

	timer += 1;
	return (double)timer / maxTimer;

}

//Sine(1)
//easeInSine(ゆっくり→速い)
double Easing::easeInSine()
{
	//変化率
	double changeRate;
	double PI = 3.14159265;

	changeRate = easeBasic();
	return 1 - cos((changeRate * PI) / 2);
}

//easeOutSine(速い→ゆっくり)
double Easing::easeOutSine()
{
	//変化率
	double changeRate;
	double PI = 3.14159265;

	changeRate = easeBasic();
	return sin((changeRate * PI) / 2);

}

//easeInOutSine(ゆっくり→速い→ゆっくり)
double Easing::easeinOutSine()
{
	//変化率
	double changeRate;
	double PI = 3.14159265;

	changeRate = easeBasic();
	return -(cos(PI * changeRate) - 1) / 2;

}


//Quad(2乗)
//easeInQuad(ゆっくり→速い)
double Easing::easeInQuad()
{
	//変化率
	double changeRate;
	//ヌルチェック済み

	changeRate = easeBasic();
	return changeRate * changeRate;

}

//easeOutQuad(速い→ゆっくり)
double Easing::easeOutQuad()
{
	//変化率
	double changeRate;
	changeRate = easeBasic();
	return 1 - (1 - changeRate) * (1 - changeRate);

}

//easeInOutQuad(ゆっくり→速い→ゆっくり)
double Easing::easeInOutQuad()
{
	//変化率
	double changeRate;
	changeRate = easeBasic();
	return				 changeRate < 0.5 ?
		2 * changeRate * changeRate : 1 - pow(-2 * changeRate + 2, 2) / 2;
}


//Cubic(3乗)
//easeInCubic(ゆっくり→速い)
double Easing::easeInCubic()
{
	//変化率
	double changeRate;
	//ヌルチェック済み

	changeRate = easeBasic();
	return changeRate * changeRate * changeRate;

}

//easeOutCubic(速い→ゆっくり)
double Easing::easeOutCubic()
{
	//変化率
	double changeRate;

	changeRate = easeBasic();
	return 1 - pow(1 - changeRate, 3);

}

//easeInOutCubic(ゆっくり→速い→ゆっくり)
double Easing::easeInOutCubic()
{
	//変化率
	double changeRate;

	changeRate = easeBasic();
	return							  changeRate < 0.5 ?
		4 * changeRate * changeRate * changeRate : 1 - pow(-2 * changeRate + 2, 3) / 2;

}


//Quart(4乗)
//easeInQuart(ゆっくり→速い)
double Easing::easeInQuart()
{
	//変化率
	double changeRate;

	changeRate = easeBasic();
	return changeRate * changeRate * changeRate * changeRate;

}

//easeOutQuart(速い→ゆっくり)
double Easing::easeOutQuart()
{
	//変化率
	double changeRate;

	changeRate = easeBasic();
	return 1 - pow(1 - changeRate, 4);

}

//easeInOutQuart(ゆっくり→速い→ゆっくり)
double Easing::easeInOutQuart()
{
	//変化率
	double changeRate;
	//ヌルチェック済み

	changeRate = easeBasic();
	return										   changeRate < 0.5 ?
		8 * changeRate * changeRate * changeRate * changeRate : 1 - pow(-2 * changeRate + 2, 4) / 2;

}


//Quint(5乗)
//easeInQuint(ゆっくり→速い)
double Easing::easeInQuint()
{
	//変化率
	double changeRate;

	changeRate = easeBasic();
	return changeRate * changeRate * changeRate * changeRate * changeRate;

}

//easeOutQuint(速い→ゆっくり)
double Easing::easeOutQuint()
{
	//変化率
	double changeRate;

	changeRate = easeBasic();
	return 1 - pow(1 - changeRate, 5);

}

//easeInOutQuint(ゆっくり→速い→ゆっくり)
double Easing::easeInOutQuint()
{
	//変化率
	double changeRate;
	//ヌルチェック済み

	changeRate = easeBasic();
	return														 changeRate < 0.5 ?
		16 * changeRate * changeRate * changeRate * changeRate * changeRate : 1 - pow(-2 * changeRate + 2, 5) / 2;

}


//Expo(急カーブ)
//easeInExpo
double Easing::easeInExpo()
{
	//変化率
	double changeRate;

	changeRate = easeBasic();
	return changeRate == 0 ? 0 : pow(2, 10 * changeRate - 10);

}

//easeOutExpo
double Easing::easeOutExpo()
{
	//変化率
	double changeRate;

	changeRate = easeBasic();
	return changeRate == 1 ? 1 : 1 - pow(2, -10 * changeRate);

}

//easeInOutExpo
double Easing::easeInOutExpo()
{
	//変化率
	double changeRate;

	changeRate = easeBasic();
	return						changeRate == 0 ?
		0 : changeRate == 1 ?
		1 : changeRate < 0.5 ?
		pow(2, 20 * changeRate - 10) / 2 : (2 - pow(2, -20 * changeRate + 10)) / 2;

}


//Circ
//easeInCirc
double Easing::easeInCirc()
{
	//変化率
	double changeRate;

	changeRate = easeBasic();
	return 1 - sqrt(1 - pow(changeRate, 2));

}

//easeOutCirc
double Easing::easeOutCirc()
{
	//変化率
	double changeRate;

	changeRate = easeBasic();
	return sqrt(1 - pow(changeRate - 1, 2));

}

//easeInOutCirc
double Easing::easeInOutCirc()
{
	//変化率
	double changeRate;

	changeRate = easeBasic();
	return changeRate < 0.5
		? (1 - sqrt(1 - pow(2 * changeRate, 2))) / 2
		: (sqrt(1 - pow(-2 * changeRate + 2, 2)) + 1) / 2;

}


//Back
//easeInBack
double Easing::easeInBack()
{
	const double c1 = 1.70158;
	const double c3 = c1 + 1;
	//変化率
	double changeRate;

	changeRate = easeBasic();
	return c3 * changeRate * changeRate * changeRate - c1 * changeRate * changeRate;

}

//easeOutBack
double Easing::easeOutBack()
{
	const double c1 = 1.70158;
	const double c3 = c1 + 1;
	//変化率
	double changeRate;

	changeRate = easeBasic();
	return 1 + c3 * pow(changeRate - 1, 3) + c1 * pow(changeRate - 1, 2);

}

//easeInOutBack
double Easing::easeInOutBack()
{
	const double c1 = 1.70158;
	const double c2 = c1 * 1.525;
	//変化率
	double changeRate;

	changeRate = easeBasic();
	return changeRate < 0.5
		? (pow(2 * changeRate, 2) * ((c2 + 1) * 2 * changeRate - c2)) / 2
		: (pow(2 * changeRate - 2, 2) * ((c2 + 1) * (changeRate * 2 - 2) + c2) + 2) / 2;

}


//Elastic
//easeInElastic
double Easing::easeInElastic()
{
	double PI = 3.14159265;
	const double c4 = (2 * PI) / 3;
	//変化率
	double changeRate;

	changeRate = easeBasic();
	return changeRate == 0
		? 0
		: changeRate == 1
		? 1
		: -pow(2, 10 * changeRate - 10) * sin((changeRate * 10 - 10.75) * c4);

}

//easeOutElastic
double Easing::easeOutElastic()
{
	double PI = 3.14159265;
	const double c4 = (2 * PI) / 3;
	//変化率
	double changeRate;

	changeRate = easeBasic();
	return changeRate == 0
		? 0
		: changeRate == 1
		? 1
		: -pow(2, -10 * changeRate) * sin((changeRate * 10 - 0.75) * c4) + 1;

}

//easeInOutElastic
double Easing::easeInOutElastic()
{
	double PI = 3.14159265;
	const double c5 = (2 * PI) / 4.5;
	//変化率
	double changeRate;

	changeRate = easeBasic();
	return changeRate == 0
		? 0
		: changeRate == 1
		? 1
		: changeRate < 0.5
		? -(pow(2, 20 * changeRate - 10) * sin((20 * changeRate - 11.125) * c5)) / 2
		: (pow(2, -20 * changeRate + 10) * sin((20 * changeRate - 11.125) * c5)) / 2 + 1;

}


//Bounce
//easeInBounce
double Easing::easeInBounce()
{
	const double n1 = 7.5625;
	const double d1 = 2.75;
	//変化率
	double changeRate;

	changeRate = 1 - (easeBasic());
	if (changeRate < 1 / d1)
	{
		return 1 - (n1 * changeRate * changeRate);
	}
	else if (changeRate < 2 / d1)
	{
		return 1 - (n1 * (changeRate -= 1.5 / d1) * changeRate + 0.75);//0.11
	}
	else if (changeRate < 2.5 / d1)
	{
		return 1 - (n1 * (changeRate -= 2.25 / d1) * changeRate + 0.9375);//0.1111
	}
	else
	{
		return 1 - (n1 * (changeRate -= 2.625 / d1) * changeRate + 0.984375);//0.111111
	}

}

//easeOutBounce
double Easing::easeOutBounce()
{
	const double n1 = 7.5625;
	const double d1 = 2.75;
	//変化率
	double changeRate;

	changeRate = easeBasic();
	if (changeRate < 1 / d1)
	{
		return n1 * changeRate * changeRate;
	}
	else if (changeRate < 2 / d1)
	{
		return n1 * (changeRate -= 1.5 / d1) * changeRate + 0.75;//0.11
	}
	else if (changeRate < 2.5 / d1)
	{
		return n1 * (changeRate -= 2.25 / d1) * changeRate + 0.9375;//0.1111
	}
	else
	{
		return n1 * (changeRate -= 2.625 / d1) * changeRate + 0.984375;//0.111111
	}

}

//easeInOutBounce
double Easing::easeInOutBounce()
{
	const double n1 = 7.5625;
	const double d1 = 2.75;
	//変化率
	double changeRate;

	changeRate = easeBasic();
	if (changeRate < 0.5)
	{
		changeRate = (1 - 2 * changeRate);
		if (changeRate < 1 / d1)
		{
			return (1 - (n1 * changeRate * changeRate)) / 2;
		}
		else if (changeRate < 2 / d1)
		{
			return (1 - (n1 * (changeRate -= 1.5 / d1) * changeRate + 0.75)) / 2;//0.11
		}
		else if (changeRate < 2.5 / d1)
		{
			return (1 - (n1 * (changeRate -= 2.25 / d1) * changeRate + 0.9375)) / 2;//0.1111
		}
		else
		{
			return (1 - (n1 * (changeRate -= 2.625 / d1) * changeRate + 0.984375)) / 2;//0.111111
		}
	}
	else
	{
		changeRate = (2 * changeRate - 1);
		if (changeRate < 1 / d1)
		{
			return (1 + (n1 * changeRate * changeRate)) / 2;
		}
		else if (changeRate < 2 / d1)
		{
			return (1 + (n1 * (changeRate -= 1.5 / d1) * changeRate + 0.75)) / 2;//0.11
		}
		else if (changeRate < 2.5 / d1)
		{
			return (1 + (n1 * (changeRate -= 2.25 / d1) * changeRate + 0.9375)) / 2;//0.1111
		}
		else
		{
			return (1 + (n1 * (changeRate -= 2.625 / d1) * changeRate + 0.984375)) / 2;//0.111111
		}
	}

}