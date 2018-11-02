#pragma once
#include "MyHero.h"

class image;
class animation;

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

	animation * m_pAni[6];
	animation * m_pAni_left[6];

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