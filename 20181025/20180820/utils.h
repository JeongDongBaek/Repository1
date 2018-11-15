#pragma once

namespace MY_UTIL
{
	float getDistance(float startX, float startY, float endX, float endY);
	float getAngle(float startX, float startY, float endX, float endY);
	float getMouseAngle(float startX, float startY);
	bool isScreenIn(float X, float Y);

	void FontOption(HDC hdc, int FontSize, int FontBold);
	void FontDelete(HDC hdc);
}

