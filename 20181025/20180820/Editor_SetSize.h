#pragma once
#include "scene.h"

class button;
class image;

class Editor_SetSize : public scene
{
private:
	image * m_pImg_BG;
	int Enter_Number;

	int m_nTileCountX; // 최대 256까지
	int m_nTileCountY; // 최대 64까지

public:
	HRESULT init();
	void update();
	void KeyEvent();

	void release();
	void render(HDC hdc);



	Editor_SetSize();
	~Editor_SetSize();
};

