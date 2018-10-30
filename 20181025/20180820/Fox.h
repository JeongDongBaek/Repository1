#pragma once
#include "GameObject.h"

class image;
class animation;

class Fox : public GameObject
{
private:
	image * m_pImage_Jump;
	image * m_pImage_Run;
	image * m_pImage_Hurt;
	image * m_pImage_Climb;
	image * m_pImage_Fall;

public:
	virtual HRESULT init();
	virtual void update();
	virtual void release();
	virtual void render(HDC hdc);

	Fox();
	~Fox();
};
