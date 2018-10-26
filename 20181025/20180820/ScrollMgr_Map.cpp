#include "stdafx.h"
#include "ScrollMgr_Map.h"


HRESULT ScrollMgr_Map::init()
{
	m_fMaxofX = g_saveData.gTileMaxCountX * TILESIZEX;
	m_fMaxofY = g_saveData.gTileMaxCountY * TILESIZEY;

	m_fCenterX = WINSIZEX / 2;
	m_fCenterY = WINSIZEY / 2;

	m_fCameraSpeed = MAPCAMERA_SPEED;

	return S_OK;
}

void ScrollMgr_Map::release()
{
}

void ScrollMgr_Map::update()
{
	KeyEvent();


	m_fX = m_fCenterX - WINSIZEX / 2;
	m_fY = m_fCenterY - WINSIZEY / 2;

	if (m_fCenterX < WINSIZEX / 2) m_fCenterX = WINSIZEX / 2;
	if (m_fCenterX > m_fMaxofX - WINSIZEX / 2) m_fCenterX = m_fMaxofX - WINSIZEX / 2;
	if (m_fCenterY < WINSIZEY / 2) m_fCenterY = WINSIZEY / 2;
	if (m_fCenterY > m_fMaxofY - WINSIZEY / 2) m_fCenterY = m_fMaxofY - WINSIZEY / 2;



	if (m_fX < 0)
		m_fX = 0;
	if (m_fY < 0)
		m_fY = 0;
	if (m_fX > m_fMaxofX - WINSIZEX) m_fX = m_fMaxofX - WINSIZEX;
	if (m_fY > m_fMaxofY - WINSIZEY) m_fY = m_fMaxofY - WINSIZEY;

}

void ScrollMgr_Map::KeyEvent()
{
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		m_fCenterX -= m_fCameraSpeed;
	}

	if (KEYMANAGER->isStayKeyDown('D'))
	{
		m_fCenterX += m_fCameraSpeed;
	}

	if (KEYMANAGER->isStayKeyDown('W'))
	{
		m_fCenterY -= m_fCameraSpeed;
	}

	if (KEYMANAGER->isStayKeyDown('S'))
	{
		m_fCenterY += m_fCameraSpeed;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_PRIOR) && m_fCameraSpeed < 21)
	{
		m_fCameraSpeed += 1.0f;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_NEXT) && m_fCameraSpeed > 4)
	{
		m_fCameraSpeed -= 1.0f;
	}

}

void ScrollMgr_Map::render(HDC hdc)
{
}

ScrollMgr_Map::ScrollMgr_Map()
{
}


ScrollMgr_Map::~ScrollMgr_Map()
{
}
