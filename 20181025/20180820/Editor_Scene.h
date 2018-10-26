#pragma once
#include "scene.h"


class image;
class button;
class animation;

class Editor_Scene : public scene
{
	image * m_pImg_EnemyBox;
	image * m_pImg_BG;
	image * m_pImg_tileset1;
	image * m_pImg_tileset1_div;
	image * m_pImg_UIopen;
	button * m_pButton_Terrains;
	button * m_pButton_Units;
	button * m_pButton_Else;

	image * m_pImg_Enemy[NUMBER_OF_KIND_UNITS];
	animation * m_pAni_Enemy[NUMBER_OF_KIND_UNITS];

	tagTILE m_pTiles[TILE_MAX_COUNTX * TILE_MAX_COUNTY];
	RECT m_rcSelectedTile;
	tagEDITOR_STATE m_editorState;

	bool m_bIsMiniMapOn;
	bool m_bIsHelpOn;
	bool m_bIsAutoOn;
	bool m_bIsUIOpen;
	bool m_bIsSel;
	bool m_bIsTextOn;
	bool m_bIsGridOn;
	static int m_editorStateNum;
	
	friend void button_func0(void);
	friend void button_func1(void);
	friend void button_func2(void);

public:
	HRESULT init();
	void init_image();
	void init_tileset();

	void update();
	void update_once();
	void KeyEvent();
	void buttonUpdate();

	void release();
	void render(HDC hdc);

	void ButtonEvent(HWND hWnd, UINT iMessage, WPARAM wParam);
	void SaveEvent();
	void LoadEvent();
	Editor_Scene();
	~Editor_Scene();
};

