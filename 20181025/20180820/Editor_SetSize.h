#pragma once
#include "scene.h"

class Editor_SetSize : public scene
{
public:
	HRESULT init();
	void update();
	void release();
	void render(HDC hdc);

	Editor_SetSize();
	~Editor_SetSize();
};

