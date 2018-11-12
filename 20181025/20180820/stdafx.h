// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <vector>
#include <map>
#include <algorithm>
#include <commdlg.h>

using namespace std;

///////////////////// 쓰는거/////////////////////////
#define NULL_CLICK 3

#define ITEM_WIDTH 46
#define ITEM_HEIGHT 46

#define FIREBALL_SPEED 8.0f
#define FIREBALL_RANGE 600.0f

#define UNIT_NULL 99
#define UNSELECTED_STATE 150
#define PLAYER_RATIO 4.2f
#define GRAVITY 9.8f

#define RABBIT_WIDTH 72
#define RABBIT_HEIGHT 78

#define SQUIRREL_WIDTH 72
#define SQUIRREL_HEIGHT 78

#define FOX_WIDTH 72
#define FOX_HEIGHT 78


#define ANT_WIDTH 70
#define ANT_HEIGHT 70

#define BEE_WIDTH 70
#define BEE_HEIGHT 70

#define CROCOBIRD_WIDTH 70
#define CROCOBIRD_HEIGHT 70

#define GLASS_WIDTH 70
#define GLASS_HEIGHT 70

#define PLANT_WIDTH 70
#define PLANT_HEIGHT 70

#define EAGLE_WIDTH 70
#define EAGLE_HEIGHT 70

#define FROG_WIDTH 70
#define FROG_HEIGHT 70

#define OPOSUM_WIDTH 70
#define OPOSUM_HEIGHT 70

#define SLUG_WIDTH 190
#define SLUG_HEIGHT 175

#define DARK_SLUG_WIDTH 186
#define DARK_SLUG_HEIGHT 166

//////////////////////// Pattern에 필요한것////////////////////

#define MOVE_STEP_COUNT 250




/////////////////////////////////////////////////////


#define MINIMAP_RATIO 8
#define MAPCAMERA_SPEED 8

#define TILE_MAX_COUNTX 128     // 4096
#define TILE_MAX_COUNTY 64		// 2048
#define TILESIZEX 32
#define TILESIZEY 32

#define TILESIZEX_STAGE 64
#define TILESIZEY_STAGE 64

#define MAX_SAMPLEX 132
#define MAX_SAMPLEY 1

#define TILE_DIV_NUM 33 // 4개씩 나옴 

#define PI 3.141592f

#define NUMBER_OF_KIND_UNITS 12

#define NUMBER_OF_KIND_BOSS 2

#define NUMBER_OF_KIND_ELSE 4
////////////////////////////////////////////////////


///////////////////// 쓰는거/////////////////////////

enum tagEnemyState
{
	st_isIdle_Enemy, is_isAttack_Enemy, st_isJump_Enemy, st_isFall_Enemy
};

struct tagItemInfor
{
	int m_nItemNumber;
	int m_nItemDivision;
	int m_nItemFrameX;
	int m_nItemFrameY;
	string m_sItemName;
	string m_sItemExpl1;
	string m_sItemExpl2;
	float m_fMaxHP;
	float m_fMaxMana;
	float m_fMaxStamina;
	float m_fAccuracy;
	float m_fSpeed;
	float m_fWeight;
	float m_fDef;
	int m_nCharacterChange;
	bool m_bFireball;
	float m_fHP;
	float m_fMana;
	float m_fStamina;
	
};


enum tagTITLE_SELECT
{
	SC_GAMESTART, SC_EDIT, SC_OPTION, SC_QUIT
};

enum tagCharacterState
{
	st_isHurt, st_isClimb, st_isIdle, st_isJump, st_isFall,  st_isRun, st_isRound,
}; // idle, jump, down, move, hurt ,climb

enum tagEnemyPattern
{
	Pattern_moveStep, // 개미
	Pattern_moveNormal, // 쥐
	Pattern_moveTileUpDown, // 벌
	Pattern_moveFly, // 악어새 , 독수리 (행동반경(m_rcMoveArea) 안에서 계속 움직임 - 플레이어 좌표가 반경안에 있을경우 따라가서 공격)
	Pattern_Stop, // 식물
	Pattern_Follow, // 독수리 - 행동반경 안에 있을경우 그때부터 계속 따라다님
	Pattern_JumpOfFlog, // 개구리 점프를 앞으로 많이
	Pattern_JumpOfGlass, // 베짱이 점프를 위로 많이
	Pattern_Slug, // 달팽이 랜덤확률로 앞으로돌진
	Pattern_ofRule
	/*Pattern_
	Pattern_

	Pattern_
	Pattern_ */
};

enum TERRAIN
{ // isGround는 안쓰는걸로
	isGround, isBlock, isEmpty, isladder, isUpHill1, isUpHill2, isUpHill3, isDownHill1, isDownHill2, isDownHill3
};

struct tagTILE
{
	TERRAIN terrain;
	int terrainFrameX; // 타일이 가지고 있는 지형정보
	int terrainFrameY;
	int	unitID;
	RECT rc;
};

struct tagSampleTile
{
	TERRAIN terrain;
	int frameX;
	int frameY;
	int unitID;
	RECT rc;
};
enum tagMOUSE_STATE
{
	st_MouseDown,
	st_MouseUp,
	st_MouseIdle,
	st_MouseNum
};

enum tagEDITOR_STATE
{
	st_Terrains = 0,
	st_Units = 1,
	st_else = 2
};


//////////////////////////////////////////////

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
//파일 경로 수정
//#include <shlwapi.h> #pragma comment(lib, "shlwapi")

#define SAFE_DELETE(p)	{ if (p) delete p; p = NULL; }

#define SYNTHESIZE(varType, varName, funcName)\
protected: varType varName;\
public: varType get##funcName() { return varName; }\
public: void set##funcName(varType var) { varName = var; }


#include "txtData.h"
#include "timeManager.h"
#include "keyManager.h"
#include "imageManager.h"
#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "sceneManager.h"
#include "utils.h"
#include "MapCamera.h"
#include "ScrollMgr.h"
#include "ScrollMgr_Map.h"
#include "EnemyManager.h"
#include "ItemManager.h"

typedef struct tagSaveData
{
	int stageMode;
	int	selected_player_id;
	int score;
	int gTileMaxCountX;
	int gTileMaxCountY;
	int gColiideCount;
	int gItemIndex = 0;

	float gMainBGMValue = 1.0f;
	float gSeValue = 1.0f;

	bool gGamePause = false;
	bool bIsCustomGame;
	bool gSortButtonOn = false;
	bool gIsRectangleOn;

} SAVE_DATA;

#define  WINDOW_SCREEN	// FULL_SCREEN, WINDOW_SCREEN, MAP_TOOL

#ifdef FULL_SCREEN
	#define WINSTARTX 0
	#define WINSTARTY 0
	#define WINSIZEX GetSystemMetrics(SM_CXSCREEN)
	#define WINSIZEY GetSystemMetrics(SM_CYSCREEN)
#elif defined MAP_TOOL
	#define WINSTARTX 50
	#define WINSTARTY 50
	#define WINSIZEX 1600
	#define WINSIZEY 800
#else
	#define WINSTARTX 50
	#define WINSTARTY 20
	#define WINSIZEX 1280	
	#define WINSIZEY 960
#endif





#define RANDOM randomFunction::getSingleton()
#define KEYMANAGER keyManager::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()
#define TIMEMANAGER timeManager::getSingleton()
#define TXTDATA txtData::getSingleton()
#define SCENEMANAGER sceneManager::getSingleton()
#define SCROLL ScrollMgr::getSingleton()
#define SCROLL_MAP ScrollMgr_Map::getSingleton()
#define ENEMYMANAGER EnemyManager::getSingleton()
#define ITEMMANAGER ItemManager::getSingleton()

extern HINSTANCE	g_hInstance;
extern HWND			g_hWnd;
extern HFONT		g_hFont;
extern HFONT		g_OldFont;
extern SAVE_DATA	g_saveData;
extern POINT		g_ptMouse;
