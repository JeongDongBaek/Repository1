#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet()
{
}
Bullet::~Bullet()
{
}






HRESULT Bullet::init(const char * ImageName, float x, float y, float Speed, float Range, int BulletType, bool isRight, bool istarget)
{
	m_pImage = IMAGEMANAGER->findImage(ImageName);
	m_fFiredX = m_fX = x;
	m_fFiredY = m_fY = y;
	m_bIsFire = true;
	if (m_bIsRight)
		m_fAngle = (PI / 180) * 0;
	else 
		m_fAngle = (PI / 180) * 180;

	switch (BulletType)
	{
	case 0:
		m_rc = RectMakeCenter(m_fX - SCROLL->GetX(), m_fY - SCROLL->GetY(), 32, 32);
		break;
	case 1:
		m_rc = RectMakeCenter(m_fX - SCROLL->GetX(), m_fY - SCROLL->GetY(), 48, 48);
		break;
	case 2:
		m_rc = RectMakeCenter(m_fX - SCROLL->GetX(), m_fY - SCROLL->GetY(), 64, 64);
		break;
	}
	m_fRange = Range;
	m_fSpeed = Speed;
	
	//if (istarget)

	return S_OK;
}

void Bullet::update()
{

}

void Bullet::release()
{
}

void Bullet::render(HDC hdc)
{
}
