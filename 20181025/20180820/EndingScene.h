#pragma once
#include "scene.h"

class image;
class animation;

class EndingScene : public scene
{
private:
	image * m_pImg_BG;
	image * m_pImg_Alice;
	animation * m_pAni;
	
public:

	HRESULT init();
	void update();
	void release();
	void render(HDC hdc);

	EndingScene();
	~EndingScene();
};

