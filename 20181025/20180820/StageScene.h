#pragma once
#include "scene.h"

class soundManager;
class effectManager;
class animation;
class image;
class Fox;
class Squirrel;
class Rabbit;
class MyHero;


enum tagSelectedCharacter
{
	sel_rabbit,
	sel_Fox,
	sel_Squirrel
};


class StageScene : public scene
{
private:

	tagHouse m_House;
	tagTILE m_pTiles[TILE_MAX_COUNTX * TILE_MAX_COUNTY];
	
	RECT m_Collide_Tiles[(TILE_MAX_COUNTX * TILE_MAX_COUNTY) / 2 ];

	tagSelectedCharacter mySelectedCh;
	int m_nYipeeCount;
	bool m_bYipeeOn;

	int m_nochCount;
	bool m_bochOn;

	Fox * m_pFox;
	Rabbit * m_pRabbit;
	Squirrel * m_pSquirrel;
	MyHero * m_pMyHero;

	effectManager * m_pEffectMgr;
	soundManager * m_pSoundMgr;

	image * m_pImg_MapUI;

	image * m_pImg_TileSet;
	image * m_pMiniPlayer;
	image * m_pMiniEnemy;
	image * m_pImg_UI_top;
	image * m_pImg_UI_bottom;
	image * m_pImg_UI_char;
	image * m_pImg_Back;
	image * m_pImg_Middle[2];
	image * m_pImg_itemBox[5];
	image * m_pImg_House;
	image * m_pImg_Pixel;

	image * m_pImg_UIFox;
	image * m_pImg_UISquirrel;
	image * m_pImg_UIRabbit;
	image * m_pImg_UIMiniMap;
	image * m_pImg_UIinventory;

	RECT m_rcUIcharacter[3];
	tagMOUSE_STATE st_mouse;

	int m_nNumberOfBlock;
	int m_nNumberOfTemp;
	
	int m_nSelectedInven;
	float m_fUIscaleUp;

	bool m_bMiniMapOn;
	bool m_bInvenOn;
	bool m_bIsPixelOn;
	bool m_bIsHelpON;
	
public:
	HRESULT init();
	void update();
	void KeyEvent();
	void ChangeCharacter();
	void UI_Click();
	void Item_Collide();
	void Unit_TileCollide();
	void Character_UnitCollide();

	void FixedLoad();
	void CustomLoad();

	void release();
	void render(HDC hdc);


	StageScene();
	~StageScene();
};

