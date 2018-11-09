#pragma once

class animation;
class image;


class Bullet
{
private :
	animation * m_pAni;
	animation * m_pAni_Left;
	image * m_pImage;
	image * m_pImage_left;
	SYNTHESIZE(RECT, m_rc, Rect);
	SYNTHESIZE(float, m_fX, X);
	SYNTHESIZE(float, m_fY, Y);
	SYNTHESIZE(float, m_fFiredX, FiredX);
	SYNTHESIZE(float, m_fFiredY, FiredY);
	SYNTHESIZE(float, m_fSpeed, Speed);
	SYNTHESIZE(float, m_fAngle, Angle);
	SYNTHESIZE(float, m_fRange, Range);
	SYNTHESIZE(bool, m_bIsFire, IsFire);
	SYNTHESIZE(bool, m_bIsRight, IsRight);

	SYNTHESIZE(int, m_nBulletType, BulletType);

public:
	HRESULT init(const char* ImageName, float x, float y, float Speed, float Range, int BulletType, bool isRight, bool istarget = false);
	void update();

	void release();
	void render(HDC hdc);

	Bullet();
	~Bullet();
};

