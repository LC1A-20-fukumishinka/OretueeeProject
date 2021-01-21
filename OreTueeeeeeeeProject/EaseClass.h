#pragma once
class Easing
{
private:
	int timer;
	int maxTimer;

	double easeBasic();

	double easeInSine();

	double easeOutSine();

	double easeinOutSine();

	double easeInQuad();

	double easeOutQuad();

	double easeInOutQuad();

	double easeInCubic();

	double  easeOutCubic();

	double easeInOutCubic();

	double easeInQuart();

	double easeOutQuart();

	double easeInOutQuart();

	double easeInQuint();

	double easeOutQuint();

	double easeInOutQuint();

	double easeInExpo();

	double easeOutExpo();

	double easeInOutExpo();

	double easeInCirc();

	double easeOutCirc();

	double easeInOutCirc();

	double easeInBack();

	double easeOutBack();

	double easeInOutBack();

	double easeInElastic();

	double easeOutElastic();

	double easeInOutElastic();

	double easeInBounce();

	double easeOutBounce();

	double easeInOutBounce();

public:
	static const enum InOut
	{
		In,
		Out,
		InOut
	};

	static const enum Type
	{
		Sine,
		Quad,
		Cubic,
		Quart,
		Quint,
		Expo,
		Circ,
		Back,
		Elastic,
		Bounce
	};
	Easing();

	double EasingMaker(int InOut, int type, int maxTimer);
	void Init();

	bool Finish();
};