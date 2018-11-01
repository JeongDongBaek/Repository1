#pragma once
#include "MyHero.h"

class image;
class animation;

class Fox : public MyHero
{
private:
	image * m_pImage[6];					//;
											//_Jump;
											//_Run;
											//_Hurt;
											//_Climb;
											//_Fall;

	animation * m_pAni[6];

public:
	virtual HRESULT init();
	virtual void update();
	virtual void release();
	virtual void render(HDC hdc);

	Fox();
	~Fox();
};
