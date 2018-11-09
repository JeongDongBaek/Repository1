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
		if ((*m_iter)->getIsFire() == false)
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
	

}

void BoomerangMgr::update()
{
	if (g_saveData.gGamePause) return;

	for (m_iter = m_vecBoomerang.begin(); m_iter != m_vecBoomerang.end(); ++m_iter)
	{
		if (!(*m_iter)->getIsFire() == true)
			continue; // 다음반복실행 

		(*m_iter)->update();
	}
}

void BoomerangMgr::render(HDC hdc)
{
	for (m_iter = m_vecBoomerang.begin(); m_iter != m_vecBoomerang.end(); ++m_iter)
	{
		if (!(*m_iter)->getIsFire() == true)
			continue; // 다음반복실행

		//Rectangle(hdc, (*m_iter)->getRect().left, (*m_iter)->getRect().top, (*m_iter)->getRect().right, (*m_iter)->getRect().bottom);
		(*m_iter)->render(hdc);
	}

}


void BoomerangMgr::release()
{
	for (m_iter = m_vecBoomerang.begin(); m_iter != m_vecBoomerang.end(); ++m_iter)
	{
		delete(*m_iter); //  벡터안의 객체 주소를 m_iter안에 담아둔다. (임시적으로 )
		// m_iter는 포인터변수인데 *가 붙었으므로 원소 (객체) 자체를 없앤다.
	}
	m_vecBoomerang.clear(); // 원소 자체는 없지만 주소의 자리
	// 한번에 자리들을 없애주는것은 clear (위의 작업을 한번더한다. 자체함수로) , erase는 특정주소(자리) // 그냥 공허의공간으로 만들어버린다.  ( 12345 중에 3을 없앤다고 1234가 되지않는다.)
}

BoomerangMgr::BoomerangMgr()
{
}


BoomerangMgr::~BoomerangMgr()
{
}
