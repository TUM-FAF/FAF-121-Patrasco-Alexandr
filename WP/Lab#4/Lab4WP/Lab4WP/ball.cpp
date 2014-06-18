#include "ball.h"

Ball::Ball(POINT pt, const int velocity)
{
	this->center = pt;
	this->xVel	 = velocity;
	this->yVel	 = velocity;
	this->color	 = RGB(128, 128, 128);
}

bool Ball::accelerateBall(const int dXVel, const int dYVel)
{
	xVel = dXVel;
	yVel = dYVel;
	return true;
}

bool Ball::setColor(const COLORREF clr)
{
	color = clr;
	return true;
}

bool Ball::onBorderImpact(const RECT rct)
{
	if(center.x + 25 > rct.right - 1){xVel = -abs(xVel); setColor(RGB(center.x%127 + center.y%128, center.x%255, center.y%255));}
	if(center.x - 25 < rct.left + 1){xVel = abs(xVel); setColor(RGB(center.x%127 + center.y%128, center.x%255, center.y%255));}
	if(center.y + 25 > rct.bottom - 1){yVel = -abs(yVel); setColor(RGB(center.x%127 + center.y%128, center.x%255, center.y%255));}
	if(center.y - 25 < rct.top + 1){yVel = abs(yVel); setColor(RGB(center.x%127 + center.y%128, center.x%255, center.y%255));}
	return true;
}

bool Ball::moveBall(const HDC hDC, const RECT rct, HBRUSH hBrush)
{
	hBrush = CreateSolidBrush(color);
	SelectObject(hDC, hBrush);

	onBorderImpact(rct);
	center.x += xVel;
	center.y += yVel;

	Ellipse(hDC, center.x - 50, center.y - 50, center.x + 50, center.y + 50);
	SelectObject(hDC, GetStockObject(LTGRAY_BRUSH));
	DeleteObject(hBrush);
	return true;
}

bool checkBallCollision(Ball b1, Ball b2)
{
	float dist;
	POINT accumVel;

	dist = sqrt(pow(b1.center.x - b2.center.x, 2) + pow(b1.center.y - b2.center.y, 2));

	if(dist < 105)
	{
		accumVel.x = (abs(b1.xVel) + abs(b2.xVel)) / 2;
		accumVel.y = (abs(b1.yVel) + abs(b2.yVel)) / 2;

		b1.accelerateBall(-b1.xVel * accumVel.x / abs(b1.xVel), -b1.yVel * accumVel.y / abs(b1.yVel));
		b2.accelerateBall(-b2.xVel * accumVel.x / abs(b2.xVel), -b2.yVel * accumVel.y / abs(b2.yVel));
		b1.setColor(RGB(accumVel.x%255, accumVel.x*20%255, accumVel.x*15%255));
	}
	return true;
}