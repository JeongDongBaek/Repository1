#pragma once
#include "scene.h"
#include "stdafx.h"
#include "soundManager.h"

class button;
class image;
class PlayerCharacter;
class progressBar;
class bulletManger;
class effectManager;
class itemManager;
class monsterManger;
class animation;
class uiManager;

class stageScene : public scene
{
private:
	tagTile        m_pTiles[TILE_MAXCOUNTX * TILE_MAXCOUNTY];
	//tagTile        m_pTiles_Collide[100];

	button*        m_pButton1;
	button*       m_pButton2;

	image*        m_pImg_Black;
	image*		  m_pImg_rad[4];
	image*        m_pImage_checkBox;
	image*        m_pTileSet[4];
	image*		  m_pMiniPlayer;
	image*		  m_pMiniEnemy;
	

	RECT m_pTiles_Collide[TILE_MAXCOUNTX * TILE_MAXCOUNTY];

	int m_nTilesNumber;
	int m_nNumber;
	int m_nTempNumber;
	int MiniMap_Ratio;
	int MapSizeX;
	int MapSizeY;
	int m_nTileindex;
	bool m_bIsMiniMapOn;
	bool m_bIsCulling;
	bool m_bIsCameraTextOn;
	bool m_bIsFireOn;
	bool m_bIsScoreOn;

	static int buttonNum;
	static int buttonOK;

	bool m_isTest;


	// 타이틀 헤더 이동
	struct buttonSelect
	{
		RECT   m_rc;
		float   m_fX;
		float   m_fY;
		int      carrFrameX;
		int      carrFrameY;
		float   m_moveSpeed;
		bool   m_isMovement;
	};
	uiManager * m_pUiMag;

	PlayerCharacter* m_player;
	image* m_titleScene;
	image* m_button;
	buttonSelect m_tButtonInfo;
	bulletManger * m_pBulletMag;
	bulletManger * m_pBulletMagMons;
	itemManager * m_pItemMag;
	monsterManger * m_pMonsterMag;
	effectManager * m_pEffMagr;
	progressBar* m_pProgressBar;
	tagSpawnTile m_tSpawnTile;

	soundManager m_soundMag;

	tagSpawnTile tSpawnTile;
	tagMonInfo tMoninfo;

	tagBulletInfo m_tBulletInfo;

	int m_buttonSetX;
	int m_buttonSetY;
	int m_isCount;
	bool m_isSpawnCycle;
	int m_SpawnCount;
	int m_SpawnWorldTime;
	bool m_isMonLvUp;

	bool m_BGMreSet;

	//////몬스터 게이트
	int m_GateNum; // 게이트 번호  1 ~ 18 번
	int m_GateMonsterNum; // 게이트 동시 생성 마릿수
	int m_GateMonsterIndex; // 게이트 몬스터 종류 인덱스 1 ~ 18
	int m_stageNum;  // 스테이지
	int m_MaxSpawnNum; // 스테이지 최대 소환
	int m_ClearScore; // 스테이지 클리어 스코어

public:
	HRESULT init();
	void release();

	void update();
	void KeyEvent();

	void render(HDC hdc);
	void LoadEvent();
	void FixedLoadEvent();
	void MonSpawnCycle(int SpawnOfNumber, int MonNumber);

	void ColRc();
	bool getTileIsMove(int x) { return m_pTiles[x].isMove; }
	void SpawnGateTime();
	void ClearEvent();

	friend void Func_button1(void);
	friend void Func_button2(void);

	stageScene();
	~stageScene();
};