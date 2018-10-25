#pragma once
#include "stdafx.h"
#include "scene.h"

class animation;
class button;

enum tagMOUSE_STATE
{
	MOUSE_IDLE1,
	MOUSE_UP1,
	MOUSE_DOWN1,
	MOUSE_NUM1
};

enum tagSELECTED_OBJ {
	isTerrain, isUnit
};

enum tagSELECTED_TILE {
	tileset1, tileset2, tileset3, tileset4
};

enum tagSELECTED_SIZE {
	x800 = 800, x1120 = 1120, x1440 = 1440, x1600 = 1600 // 25 35 45 50
};

enum tagSELECTED_VIEW {
	x1 = 1, x2 = 2, x3 = 3
};

struct tagSampleUnit
{

};

class editor : public scene
{
private:
	bool m_bIsSelectSize; // 메뉴창에서 선택가능
	bool m_bIsUnfold;
	bool m_isSel;
	bool m_bIsMiniMapOn;
	bool m_bIsTextOn;
	bool m_bIsNumberOn;
	bool m_bIsAutoOn;
	bool m_bIsStartingPoint;
	bool m_bIsHelpOn;

	int m_rcSelectedTileSampleNum;
	int MiniMap_Ratio;

	tagSpawnTile m_pSpawn;

	tagTile m_pTiles[TILE_MAXCOUNTX * TILE_MAXCOUNTY];  // 그려줄 타일의 정보 // 실제로 구성이 되는 타일의 정보
	//tagTile * m_pTiles[MAX_TILECOUNTX * MAX_TILECOUNTX];

	tagSampleTile m_pSampleTiles[SAMPLE_COUNTX * SAMPLE_COUNTY]; // 오른쪽의 타일정보들
	RECT m_rcSelectedTile;
	RECT m_rcSelectedUnit;
	tagSELECTED_TILE st_selTile;
	tagSELECTED_SIZE st_selSize;
	tagMOUSE_STATE st_mouse;
	tagSELECTED_OBJ st_obj;
	tagSELECTED_VIEW st_view;

	image* m_pTileSet[4]; // 총 4개
	image* m_pBox;
	image * m_pBG;
	image * m_pCursor;
	image * m_pTag;
	image * m_pTag2;
	image * m_pPlayer;

	image * m_pHelp;

	image * m_pEnemy[20];
	//animation * m_pAnimation[20];

	button * m_pBtnLspace;
	button * m_pBtnRspace;

public:
	static int m_nPreviewNum;
	static int m_nMonsterID;


	friend void SpaceFunc_left(void);
	friend void SpaceFunc_right(void);




	HRESULT init();
	void init_image();

	void tileReset();


	void release();


	void update();
	void SizeUpdate();
	void ButtonEvent(HWND hWnd, UINT iMessage, WPARAM wParam);
	void SaveEvent();
	void LoadEvent();
	void KeyEvent();
	void MouseEvent();

	void Unit_MouseEvent();

	void render(HDC hdc);
	void render_mapTile(HDC hdc);


	editor();
	~editor();
};


