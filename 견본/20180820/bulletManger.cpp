#include "stdafx.h"
#include "bulletManger.h"
#include "animation.h"
#include "effectManager.h"


HRESULT bulletManger::init(int vecMaxSize, effectManager * pBulletMag)
{
	for (int i = 0; i < vecMaxSize; i++)
	{
		memset(&m_tBulletInfo, 0, sizeof(m_tBulletInfo));

		m_pAni = new animation;
		m_tBulletInfo.tIsAlive = false;

		m_pEffMag = pBulletMag;

		bullet * pBullet = new bullet;
		pBullet->init("임시", 0, 0, 0, &m_tBulletInfo, &m_tBulletInfo, m_pAni, m_pEffMag, this);
		m_vecBullet.push_back((pBullet));
		m_vecNextFire.push_back((pBullet));
	}

	m_vecBullet.reserve(vecMaxSize);
	

	return S_OK;
}

void bulletManger::release()
{
	for (m_iter = m_vecBullet.begin(); m_iter != m_vecBullet.end(); m_iter++)
	{
		delete (*m_iter);
	}

	m_vecBullet.clear();
}

void bulletManger::update()
{
	if (g_saveData.gGamePause) return;

	for (m_iter = m_vecBullet.begin(); m_iter != m_vecBullet.end(); m_iter++)
	{
		if (!(*m_iter)->getIsAlive()) continue;

		(*m_iter)->update();
	}
}

void bulletManger::render(HDC hdc)
{
	for (m_iter = m_vecBullet.begin(); m_iter != m_vecBullet.end(); m_iter++)
	{
		if (!(*m_iter)->getIsAlive()) continue;

		(*m_iter)->render(hdc);
	}
}

void bulletManger::fire(const char * imageName, float posX, float posY, float angle, tagBulletInfo * bulletInfo, tagBulletInfo* bulletInfoSub)
{
	for (m_iter = m_vecBullet.begin(); m_iter != m_vecBullet.end(); m_iter++)
	{
		if (!(*m_iter)->getIsAlive()) // 죽어있으면 재활용
		{
			(*m_iter)->init(imageName, posX, posY, angle, bulletInfo, bulletInfoSub, m_pAni, m_pEffMag, this);
			return;
		}
	}

	bullet * pBullet = new bullet;
	pBullet->init(imageName, posX, posY, angle, bulletInfo, bulletInfoSub, m_pAni, m_pEffMag,this);
	m_vecBullet.push_back((pBullet));
	return;
}

void bulletManger::NextFire(const char * imageName, float posX, float posY, float angle, tagBulletInfo * bulletInfo, tagBulletInfo* bulletInfoSub)
{
	for (m_NextIter = m_vecNextFire.begin(); m_NextIter != m_vecNextFire.end(); m_NextIter++)
	{
		if (!(*m_NextIter)->getIsAlive()) // 죽어있으면 재활용
		{
			(*m_NextIter)->init(imageName, posX, posY, angle, bulletInfo, bulletInfoSub, m_pAni, m_pEffMag, this);
			return;
		}
	}

	bullet * pBullet = new bullet;
	pBullet->init(imageName, posX, posY, angle, bulletInfo, bulletInfoSub, m_pAni, m_pEffMag, this);
	m_vecNextFire.push_back((pBullet));
	return;
}

bulletManger::bulletManger()
{
}


bulletManger::~bulletManger()
{
}
