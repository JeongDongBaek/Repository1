#pragma once
#include "scene.h"

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

	tagTILE m_pTiles[TILE_MAX_COUNTX * TILE_MAX_COUNTY];
	tagSelectedCharacter mySelectedCh;

	Fox * m_pFox;
	Rabbit * m_pRabbit;
	Squirrel * m_pSquirrel;
	MyHero * m_pMyHero;

	image * m_pImg_TileSet;
	image * m_pMiniPlayer;
	image * m_pMiniEnemy;
	image * m_pImg_UI_top;
	image * m_pImg_UI_bottom;
	image * m_pImg_UI_char;
	image * m_pImg_Back;
	image * m_pImg_Middle[2];
	
	image * m_pImg_UIFox;
	image * m_pImg_UISquirrel;
	image * m_pImg_UIRabbit;
	image * m_pImg_UIMiniMap;

	int m_nNumberOfBlock;
	int m_nNumberOfTemp;

public:
	HRESULT init();
	void update();
	void KeyEvent();
	void ChangeCharacter();

	void FixedLoad();
	void CustomLoad();

	void release();
	void render(HDC hdc);


	StageScene();
	~StageScene();
};

