#pragma once
#include "MyHero.h"

class image;
class animation;
class BoomerangMgr;

class Rabbit : public MyHero
{
private:
	image * m_pImage[6];
												//_Jump;
												//_Run;
												//_Fall;
												//_Hurt;
												//_Climb;
	image * m_pImage_left[6];
	image * m_pImage_boomerang;
	BoomerangMgr * m_pBoomerang;

	animation * m_pAni[6];
	animation * m_pAni_left[6];

	bool m_bIsBoomerangOn;
	float m_fAccrancy;

public:
	HRESULT init();
	void update();
	void KeyEvent();
	void JumpEvent();

	void release();
	void render(HDC hdc);

	Rabbit();
	~Rabbit();
};

// 