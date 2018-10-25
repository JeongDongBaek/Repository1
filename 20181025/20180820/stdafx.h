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
#include <commdlg.h>

using namespace std;

///////////////////// 쓰는거/////////////////////////

#define MINIMAP_RATIO 8
#define MAPCAMERA_SPEED 5

#define TILE_MAX_COUNTX 256 // 8192
#define TILE_MAX_COUNTY 64 // 2048
#define TILESIZEX 32
#define TILESIZEY 32

#define MAX_SAMPLEX 128
#define MAX_SAMPLEY 1

#define TILE_DIV_NUM 32 // 4개씩 나옴 

#define PI 3.141592f
////////////////////////////////////////////////////


///////////////////// 쓰는거/////////////////////////
enum tagTITLE_SELECT
{
	SC_GAMESTART, SC_EDIT, SC_OPTION, SC_QUIT
};

enum TERRAIN
{
	xx800 = 25, xx1120 = 35, xx1440 = 45, xx1600 = 50, TR_WALL = 0
};

struct tagTILE
{
	TERRAIN terrain;
	int terrainFrameX; // 타일이 가지고 있는 지형정보
	int terrainFrameY;
	RECT rc;
};

struct tagSAMPLETILE
{
	RECT rc;
	int frameX;
	int frameY;
};

enum tagMOUSE_STATE
{
	st_MouseDown,
	st_MouseUp,
	st_MouseIdle,
	st_MouseNum
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

typedef struct tagSaveData
{
	int	selected_player_id;
	int score;
	int gTileMaxCountX;
	int gTileMaxCountY;

	float gMainBGMValue = 1.0f;
	float gSeValue = 1.0f;

	bool gGamePause = false;

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
	#define WINSTARTY 50
	#define WINSIZEX 1200	
	#define WINSIZEY 900
#endif





#define RANDOM randomFunction::getSingleton()
#define KEYMANAGER keyManager::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()
#define TIMEMANAGER timeManager::getSingleton()
#define TXTDATA txtData::getSingleton()
#define SCENEMANAGER sceneManager::getSingleton()
#define SCROLL ScrollMgr::getSingleton()
#define SCROLL_MAP ScrollMgr_Map::getSingleton()

extern HINSTANCE	g_hInstance;
extern HWND			g_hWnd;
extern HFONT		g_hFont;
extern HFONT		g_OldFont;
extern SAVE_DATA	g_saveData;
extern POINT		g_ptMouse;
