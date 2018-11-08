#pragma once
class image;
class animation;



class Boomerang
{
private:
	animation * m_pAni;
	image * m_pImage;
	float tempAngle = 1.0f;
	SYNTHESIZE(RECT, m_rc, Rect);
	SYNTHESIZE(float, m_fX, X);
	SYNTHESIZE(float, m_fY, Y);
	SYNTHESIZE(float, m_fFiredX, FiredX);
	SYNTHESIZE(float, m_fFiredY, FiredY);
	SYNTHESIZE(float, m_fSpeed, Speed);
	SYNTHESIZE(float, m_fAngle, Angle);
	SYNTHESIZE(float, m_fAngle_Move, Angle_Move);
	SYNTHESIZE(float, m_fRange, Range );
	SYNTHESIZE(bool, m_bIsFire, IsFire );
	SYNTHESIZE(bool, m_bIsReturning, IsReturning);
	SYNTHESIZE(bool, m_bIsRight,IsRight);
	SYNTHESIZE(float, m_fAccuracy, Accuracy);



public:
	HRESULT init( float x, float y, float Player_Speed, float DestiX, float DestiY, float Accuracy);
	void Fire();
	void release();
	void update();
	void update_rotate();

	void render(HDC hdc);

	Boomerang();
	~Boomerang();
};

