#include "stdafx.h"
#include "BoomerangMgr.h"


HRESULT BoomerangMgr::init(int limit)
{
	m_nLimit = limit;
	m_vecBoomerang.reserve(m_nLimit);


	return S_OK;
}

void BoomerangMgr::Fire(float x, float y, float Player_Speed, float DestiX, float DestiY, float m_fAccuracy)
{
	for (m_iter = m_vecBoomerang.begin(); m_iter != m_vecBoomerang.end(); ++m_iter)
	{
		if (!(*m_iter)->getIsFire() == true)
		{
			(*m_iter)->init(x, y, Player_Speed, DestiX, DestiY, m_fAccuracy);
			(*m_iter)->Fire();
			return;
		}
	}

	if (m_vecBoomerang.size() > m_nLimit) return;
	
	//else
	Boomerang * m_pBoomerang = new Boomerang;

	m_pBoomerang->init( x, y, Player_Speed, DestiX, DestiY, m_fAccuracy);
	m_pBoomerang->Fire();
	m_vecBoomerang.push_back(m_pBoomerang);
	return;

}

void BoomerangMgr::update()
{
	for (m_iter = m_vecBoomerang.begin(); m_iter != m_vecBoomerang.end(); ++m_iter)
	{
		if (!(*m_iter)->getIsFire() == true)
			continue;

		(*m_iter)->update();
	}
}

void BoomerangMgr::render(HDC hdc)
{
	for (m_iter = m_vecBoomerang.begin(); m_iter != m_vecBoomerang.end(); ++m_iter)
	{
		if (!(*m_iter)->getIsFire() == true)
			continue;

		//Rectangle(hdc, (*m_iter)->getRect().left, (*m_iter)->getRect().top, (*m_iter)->getRect().right, (*m_iter)->getRect().bottom);
		(*m_iter)->render(hdc);
	}

}


void BoomerangMgr::release()
{
}

BoomerangMgr::BoomerangMgr()
{
}


BoomerangMgr::~BoomerangMgr()
{
}
