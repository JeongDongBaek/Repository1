#include "stdafx.h"
#include "MapCamera.h"
#include "editor.h"










HRESULT MapCamera::init()
{

	MiniMapRatioInit();

	return S_OK;
}

void MapCamera::MiniMapRatioInit()
{
	m_nMiniMap_LocationX = LOC_MINIMAPX_MAP;
	m_nMiniMap_LocationY = LOC_MINIMAPY_MAP;
	m_ptMoveCameraX = WINSIZEX / 2;
	m_ptMoveCameraY = WINSIZEY / 2;

	//m_rcCamera.left = 0;
	//m_rcCamera.right = WINSIZEX;
	//m_rcCamera.top = 0;
	//m_rcCamera.bottom = WINSIZEY;

	//m_rcMiniCamera.top = 0;
	//m_rcMiniCamera.bottom = WINSIZEY;


	m_ptCameraMiniX = LOC_MINIMAPX_MAP;
	m_ptCameraMiniY = LOC_MINIMAPY_MAP;
}

void MapCamera::release()
{
}

void MapCamera::update()
{
	if (m_ptMoveCameraX < WINSIZEX / 2) m_ptMoveCameraX = WINSIZEX / 2;
	if (m_ptMoveCameraX > (g_saveData.gTileMaxCountX * TILE_SIZEX - WINSIZEX / 2))
		m_ptMoveCameraX = (g_saveData.gTileMaxCountX * TILE_SIZEX - WINSIZEX / 2);
	if (m_ptMoveCameraY < WINSIZEY / 2) 
		m_ptMoveCameraY = WINSIZEY / 2;
	if (m_ptMoveCameraY > (g_saveData.gTileMaxCountY * TILE_SIZEX - WINSIZEY / 2)) 
		m_ptMoveCameraY = (g_saveData.gTileMaxCountY * TILE_SIZEY - WINSIZEY / 2);  // 1600기준으로 1200까지 (중심좌표)

	m_ptCameraX = m_ptMoveCameraX - WINSIZEX / 2; // 화면시작좌표
	if (m_ptCameraX < 0) m_ptCameraX = 0;
	if (m_ptCameraX > (g_saveData.gTileMaxCountX * TILE_SIZEX) - WINSIZEX) m_ptCameraX = (g_saveData.gTileMaxCountX * TILE_SIZEX) - WINSIZEX;

	m_ptCameraY = m_ptMoveCameraY - WINSIZEY / 2; // 윈도우 시작좌표
	if (m_ptCameraY < 0) m_ptCameraY = 0;
	if (m_ptCameraY > (g_saveData.gTileMaxCountY * TILE_SIZEY) - WINSIZEY) m_ptCameraY = (g_saveData.gTileMaxCountY * TILE_SIZEY) - WINSIZEY;

	// 미니맵
	//if (m_ptCameraMiniX < 0) m_ptCameraMiniX = 0; // 0보다 작을시 끝에 고정
	//if (m_ptCameraMiniX > LOC_MINIMAPX) m_ptCameraMiniX = LOC_MINIMAPX;  
	//if (m_ptCameraMiniY < 0) m_ptCameraMiniY = 0; 
	//if (m_ptCameraMiniY > LOC_MINIMAPY) m_ptCameraMiniY = LOC_MINIMAPY;

	//m_ptMiniCameraX = m_ptCameraMiniX - LOC_MINIMAPX;
	//if (m_ptMiniCameraX < 0) m_ptMiniCameraX = 0;
	//if (m_ptMiniCameraX > WINSIZEX - LOC_MINIMAPX) m_ptMiniCameraX = WINSIZEX - LOC_MINIMAPX;

	//m_ptMiniCameraY = m_ptCameraMiniY - LOC_MINIMAPY;
	//if (m_ptMiniCameraY < 0) m_ptMiniCameraY = 0;
	//if (m_ptMiniCameraY > WINSIZEY - LOC_MINIMAPY) m_ptMiniCameraY = WINSIZEY - LOC_MINIMAPY;

}

void MapCamera::keyUpdate()
{
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		m_ptMoveCameraX -= 10.0f;
		m_ptCameraMiniX -= 10.0f;
	}

	if (KEYMANAGER->isStayKeyDown('D'))
	{
		m_ptMoveCameraX += 10.0f;
		m_ptCameraMiniX += 10.0f;
	}

	if (KEYMANAGER->isStayKeyDown('W'))
	{
		m_ptMoveCameraY -= 10.0f;
		m_ptCameraMiniY -= 10.0f;
	}

	if (KEYMANAGER->isStayKeyDown('S'))
	{
		m_ptMoveCameraY += 10.0f;
		m_ptCameraMiniY += 10.0f;
	}

}

void MapCamera::render(HDC hdc)
{
}

MapCamera::MapCamera()
{
}


MapCamera::~MapCamera()
{
}

