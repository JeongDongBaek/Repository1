#include "stdafx.h"
#include "ScrollMgr.h"


HRESULT ScrollMgr::init()
{
	m_isFirst = true;

	return S_OK;
}

void ScrollMgr::release()
{
}

void ScrollMgr::update(float playerX, float playerY)
{
	if (m_isFirst)
	{
		m_fMaxofX = g_saveData.gTileMaxCountX * TILE_SIZEX;
		m_fMaxofY = g_saveData.gTileMaxCountY * TILE_SIZEY;

		m_fX = playerX - WINSIZEX / 2;
		m_fY = playerY - WINSIZEY / 2; // 플레이어는 항상 중심에 있으므로

		m_isFirst = false;
	}
	m_fX = playerX - WINSIZEX / 2;
	m_fY = playerY - WINSIZEY / 2; // 플레이어는 항상 중심에 있으므로

	// 플레이어 중심의 화면 (보이는화면)//
	m_rc.left = playerX - WINSIZEX / 2;
	m_rc.right = playerX + WINSIZEX / 2;
	m_rc.top = playerY - WINSIZEY / 2;
	m_rc.bottom = playerY + WINSIZEY / 2;

	if (m_fX < 0)
		m_fX = 0;
	if (m_fY < 0)
		m_fY = 0;
	if (m_fX > m_fMaxofX - WINSIZEX) m_fX = m_fMaxofX - WINSIZEX;
	if (m_fY > m_fMaxofY - WINSIZEY) m_fY = m_fMaxofY - WINSIZEY;

	
	/*if(playerX m-m_fMaxofX - WINSIZEX)*/
}

void ScrollMgr::render(HDC hdc)
{
}

ScrollMgr::ScrollMgr()
{
}


ScrollMgr::~ScrollMgr()
{
}
