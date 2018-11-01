#include "stdafx.h"
#include "ScrollMgr.h"


HRESULT ScrollMgr::init(float playerX, float playerY)
{
	m_fMaxofX = g_saveData.gTileMaxCountX * TILESIZEX_STAGE;
	m_fMaxofY = g_saveData.gTileMaxCountY * TILESIZEY_STAGE;

	m_fX = playerX - WINSIZEX / 2;
	m_fY = playerY - WINSIZEY / 2;

	return S_OK;
}

void ScrollMgr::release()
{
}

void ScrollMgr::update(float playerX, float playerY)
{


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
