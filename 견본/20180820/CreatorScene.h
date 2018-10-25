#pragma once
#include "scene.h"

class image;
class button;

class CreatorScene : public scene
{
private:
	image * m_pImg_BG;
	button* m_pButton1;


	static bool buttonInput;
public:
	HRESULT init();
	void update();
	void release();
	void render(HDC hdc);

	friend void Func_button1(void);

	CreatorScene();
	~CreatorScene();
};

