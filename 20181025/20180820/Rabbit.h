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

	animation * m_pAni[6];

public:
	virtual HRESULT init();
	virtual void update();
	virtual void release();
	virtual void render(HDC hdc);

	Rabbit();
	~Rabbit();
};

// 