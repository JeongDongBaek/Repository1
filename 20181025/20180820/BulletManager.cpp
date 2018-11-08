#include "stdafx.h"
#include "BulletManager.h"


HRESULT BulletManager::init(int limit)
{
	m_nLimit = limit;
	m_vecBullet.reserve(m_nLimit);

	return S_OK;
}

void BulletManager::Fire(const char * ImageName, float x, float y, float Speed, float Range, int RectType, bool isRight, bool istarget)
{
	for (m_iter = m_vecBullet.begin(); m_iter != m_vecBullet.end(); m_iter++)
	{
		if (!(*m_iter)->getIsFire() == true)
		{
			(*m_iter)->init(ImageName, x, y, Speed, Range, RectType, isRight, istarget);
			return;
		}
	}

	if (m_vecBullet.size() < m_nLimit) return;

	Bullet * bullet = new Bullet;
	bullet->init(ImageName, x, y, Speed, Range, RectType, isRight, istarget);
}

void BulletManager::update()
{
	for (m_iter = m_vecBullet.begin(); m_iter != m_vecBullet.end(); m_iter++)
	{
		if ((*m_iter)->getIsFire() == true) continue;

		(*m_iter)->update();
	}
}

void BulletManager::release()
{
	for (m_iter = m_vecBullet.begin(); m_iter != m_vecBullet.end(); m_iter++)
	{
		delete (*m_iter);
	}
	m_vecBullet.clear();
}

void BulletManager::render(HDC hdc)
{
	for (m_iter = m_vecBullet.begin(); m_iter != m_vecBullet.end(); m_iter++)
	{
		if ((*m_iter)->getIsFire() == true) continue;

		(*m_iter)->render(hdc);
	}
}

BulletManager::BulletManager()
{
}


BulletManager::~BulletManager()
{
}
