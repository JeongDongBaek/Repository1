#pragma once
#include "MyHero.h"

class animation;
class image;

class Squirrel : public MyHero
{
private:
	image * m_pImage[6];
	
	image * m_pImage_left[6];

	animation * m_pAni[6];
	animation * m_pAni_left[6];

public:
	virtual HRESULT init();
	virtual void update();
	virtual void release();
	virtual void render(HDC hdc);

	Squirrel();
	~Squirrel();
};

