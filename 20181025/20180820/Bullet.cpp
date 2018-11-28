#include "stdafx.h"
#include "Bullet.h"
#include "animation.h"
#include "effectManager.h"

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
	m_bIsRight = isRight;
	if (m_bIsRight)
		m_fAngle = (PI / 180) * 0;
	else 
		m_fAngle = (PI / 180) * 180;

	m_nBulletType = BulletType;
	switch (m_nBulletType)
	{
	case 0:
		m_rc = RectMakeCenter(m_fX - SCROLL->GetX(), m_fY - SCROLL->GetY(), 32, 32);
		break;
	case 1: // fireball
		m_rc = RectMakeCenter(m_fX - SCROLL->GetX(), m_fY - SCROLL->GetY(), 48, 48);
		m_pAni = new animation;
		m_pAni->init(m_pImage->getWidth(), m_pImage->getHeight(), m_pImage->getFrameWidth(), m_pImage->getFrameHeight());
		m_pAni->setDefPlayFrame(false, true);
		m_pAni->setFPS(10);
		m_pAni->start();
		
		m_pImage_left = IMAGEMANAGER->findImage("fireball_left");
		m_pAni_Left = new animation;
		m_pAni_Left->init(m_pImage_left->getWidth(), m_pImage_left->getHeight(), m_pImage_left->getFrameWidth(), m_pImage_left->getFrameHeight());
		m_pAni_Left->setDefPlayFrame(false, true);
		m_pAni_Left->setFPS(10);
		m_pAni_Left->start();
		break;
	case 2:
		m_rc = RectMakeCenter(m_fX - SCROLL->GetX(), m_fY - SCROLL->GetY(), 64, 64);
		break;
	}
	m_fRange = Range;
	m_fSpeed = Speed;

	switch (RANDOM->getFromIntTo(1, 4))
	{
	case 1:
		m_effName = "Bullet_End_0";
		break;
	case 2:
		m_effName = "Bullet_End_1";
		break;
	case 3:
		m_effName = "Bullet_End_2";
		break;
	case 4:
		m_effName = "Bullet_End_3";
		break;
	}

	m_pEffectMgr = new effectManager;
	//if (istarget)

	return S_OK;
}

void Bullet::update()
{
	if (!m_bIsFire == true) return;

	m_fX += cosf(m_fAngle) * m_fSpeed;
	m_fY += -sinf(m_fAngle) * m_fSpeed;

	switch (m_nBulletType)
	{
	case 0:
		m_rc = RectMakeCenter(m_fX - SCROLL->GetX(), m_fY - SCROLL->GetY(), 32, 32);
		break;
	case 1:
		m_rc = RectMakeCenter(m_fX - SCROLL->GetX(), m_fY - SCROLL->GetY(), 48, 48);
		m_pAni->frameUpdate(TIMEMANAGER->getElapsedTime());
		m_pAni_Left->frameUpdate(TIMEMANAGER->getElapsedTime());
		break;
	case 2:
		m_rc = RectMakeCenter(m_fX - SCROLL->GetX(), m_fY - SCROLL->GetY(), 64, 64);
		break;
	}

	if (MY_UTIL::getDistance(m_fFiredX, m_fFiredY, m_fX, m_fY) > m_fRange)
	{
		m_bIsFire = false;
	}

}

void Bullet::HitEff()
{
	m_pEffectMgr->play(m_effName, m_rc.left, m_rc.top);
	m_bIsFire = false;
}

void Bullet::release()
{
}

void Bullet::render(HDC hdc)
{
	if (!m_bIsFire == true) return;

	switch (m_nBulletType)
	{
	case 0:
		break;
	case 1:
		//Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);

		if(m_bIsRight == true)
			m_pImage->aniRender(hdc, m_rc.left - 8, m_rc.top - 11, m_pAni, 1.2f, false, 100);
		else
			m_pImage_left->aniRender(hdc, m_rc.left - 8, m_rc.top - 11, m_pAni_Left, 1.2f, false, 100);
		break;
	case 2:
		break;
	}
}
