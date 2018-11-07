#include "stdafx.h"
#include "Boomerang.h"
#include "Rabbit.h"

HRESULT Boomerang::init(float x, float y, float Player_Speed, float DestiX, float DestiY, float Accuracy)
{
	m_pImage = IMAGEMANAGER->findImage("boomerang");
	m_fFiredX = m_fX = x;
	m_fFiredY = m_fY = y;
	m_ntempDistance = 0;
	m_bIsReturning = false;
	m_bIsFire = false;
	m_fAccuracy = RANDOM->getFromFloatTo(0 - Accuracy, 0 + Accuracy);

	m_fAngle_Move = MY_UTIL::getAngle(x, y, DestiX, DestiY);
	m_rc = RectMakeCenter(m_fX - SCROLL->GetX(), m_fY - SCROLL->GetY(), 54, 42);
	m_fRange = 1000;
	m_fSpeed = 8.0f + Player_Speed;

	return S_OK;
}

void Boomerang::Fire()
{
	m_bIsFire = true;
}

void Boomerang::release()
{
}

void Boomerang::update()
{
	if (m_bIsFire)
	{
		update_rotate();

		m_fX += cosf(m_fAngle_Move + m_fAccuracy) * m_fSpeed;
		m_fY += -sinf(m_fAngle_Move + m_fAccuracy) * m_fSpeed;

		m_rc = RectMakeCenter(m_fX - SCROLL->GetX(), m_fY - SCROLL->GetY(),
			54, 42);

		if (m_fRange < MY_UTIL::getDistance(m_fFiredX, m_fFiredY, m_fX, m_fY) && m_bIsReturning == false)
		{
			m_bIsReturning = true;
		}
		if (MY_UTIL::getDistance(m_fFiredX, m_fFiredY, m_fX, m_fY) < 20 && m_bIsReturning == true)
		{
			m_bIsReturning = false;
			m_bIsFire = false;
		}
		
		/*if (m_fRange < MY_UTIL::getDistance(m_fFiredX, m_fFiredY, m_fX, m_fY))
		{
			m_bIsFire = false;
		}*/

	}
}

void Boomerang::update_rotate()
{
	if (m_bIsReturning == true)
	{
		m_fAngle_Move = MY_UTIL::getAngle(m_fX, m_fY, m_fFiredX, m_fFiredY);
		m_fAngle_Move += 0.22f;
	}

}

void Boomerang::render(HDC hdc)
{
	if (m_bIsFire)
	{
		tempAngle += 9.0f;
		m_pImage->rotateRender(hdc, tempAngle, m_rc.left + 22, m_rc.top + 10, 1.0f);

	}
}

Boomerang::Boomerang()
{
}


Boomerang::~Boomerang()
{
}
