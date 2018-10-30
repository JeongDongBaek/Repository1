#pragma once
#include "GameObject.h"

class Squirrel : public GameObject
{
private:
	image * m_pImage_Jump;
	image * m_pImage_Run;
	image * m_pImage_Hurt;
	//image * m_pImage_Climb;
	image * m_pImage_Fall;
	image * m_pImage_Round;

public:
	virtual HRESULT init();
	virtual void update();
	virtual void release();
	virtual void render(HDC hdc);

	Squirrel();
	~Squirrel();
};

