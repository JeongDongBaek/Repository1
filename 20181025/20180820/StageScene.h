#pragma once
#include "scene.h"

class StageScene : public scene
{
public:
	HRESULT init();
	void update();
	void KeyEvent();
	void FixedLoad();
	void CustomLoad();

	void release();
	void render(HDC hdc);

	StageScene();
	~StageScene();
};

