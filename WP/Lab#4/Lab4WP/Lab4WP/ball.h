#include <cmath>
#include <windows.h>

class Ball
{
public:
	POINT center;
	COLORREF color;
	int xVel, yVel;

	Ball(POINT, const int);
	bool accelerateBall(const int, const int);
	bool setColor(const COLORREF);
	bool onBorderImpact(const RECT);
	bool moveBall(const HDC, const RECT, HBRUSH);
};

bool checkBallCollision(Ball, Ball);
