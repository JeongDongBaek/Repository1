#pragma once
#include "scene.h"


class image;

class Editor_Scene : public scene
{
	image * m_pImg_tileset1;
	image * m_pImg_tileset1_div;

	tagTILE m_pTiles[TILE_MAX_COUNTX * TILE_MAX_COUNTY];
	RECT m_rcSelectedTile;

	bool m_bIsMiniMapOn;
	bool m_bIsHelpOn;
	bool m_bIsAutoOn;
	bool m_bIsUIOpen;
	bool m_bIsSel;
	bool m_bIsTextOn;
	


public:
	HRESULT init();
	void update();
	void update_once();

	void release();
	void render(HDC hdc);

	void ButtonEvent(HWND hWnd, UINT iMessage, WPARAM wParam);
	Editor_Scene();
	~Editor_Scene();
};

