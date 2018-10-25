#pragma once

#include "scene.h"

class image;

class Title_Scene : public scene
{
	image * m_pImg_BG;
	image * m_pImg_Menu[5]; // ���ӽ��� / ����Ʈ�� / �ɼ� / ������ / ������
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

