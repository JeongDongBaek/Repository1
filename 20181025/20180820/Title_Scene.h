#pragma once

#include "scene.h"

class image;

class Title_Scene : public scene
{
	image * m_pImg_BG;
	image * m_pImg_Menu[5]; // 게임시작 / 에디트씬 / 옵션 / 만든이 / 나가기
	image * m_pImg_Parchment;

	int m_nindex_Scene;
	bool m_bIsOptionOn;
	bool m_bIsCreatorOn;

public:
	HRESULT init();
	void update();
	void KeyEvent();

	void release();
	void render(HDC hdc);

	Title_Scene();
	~Title_Scene();
};

