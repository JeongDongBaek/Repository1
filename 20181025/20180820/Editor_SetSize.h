#pragma once
#include "scene.h"

class button;
class image;

class Editor_SetSize : public scene
{
private:
	image * m_pImg_BG;
	int Enter_Number;

	int m_nTileCountX; // �ִ� 256����
	int m_nTileCountY; // �ִ� 64����

public:
	HRESULT init();
	void update();
	void KeyEvent();

	void release();
	void render(HDC hdc);



	Editor_SetSize();
	~Editor_SetSize();
};

