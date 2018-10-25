#include "stdafx.h"
#include "bullet.h"
#include "animation.h"
#include "bulletManger.h"
#include "effectManager.h"

// 테스트

HRESULT bullet::init(const char * imageName, float posX, float posY, float angle, tagBulletInfo * bulletInfo, tagBulletInfo* bulletInfoSub, animation * pAni, effectManager * pEff, bulletManger*  bulletMagPoint)
{
	// 최초 초기화
	memset(&m_rc, NULL, sizeof(m_rc));
	m_pBulletMag = bulletMagPoint;

	// 이미지 초기화
	m_eff = pEff;

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
	m_bulletInfo.tImageType = bulletInfo->tImageType;
	switch (m_bulletInfo.tImageType)
	{
	case BULLET_IMAGE_TYPE::BULLET_IMAGE_NUM:
		m_pImg = IMAGEMANAGER->findImage("Bullet_Y");
		break;
	case BULLET_IMAGE_TYPE::COLOR_Y:
		m_pImg = IMAGEMANAGER->findImage("Bullet_Y");
		break;
	case BULLET_IMAGE_TYPE::COLOR_B:
		m_pImg = IMAGEMANAGER->findImage("Bullet_B");
		break;
	case BULLET_IMAGE_TYPE::COLOR_P:
		m_pImg = IMAGEMANAGER->findImage("Bullet_P");
		break;
	case BULLET_IMAGE_TYPE::COLOR_G:
		m_pImg = IMAGEMANAGER->findImage("Bullet_G");
		break;
	case BULLET_IMAGE_TYPE::COLOR_R:
		m_pImg = IMAGEMANAGER->findImage("Bullet_R");
		break;
	}
	m_pAni = pAni;
	m_pAni->init(m_pImg->getWidth(), m_pImg->getHeight(), m_pImg->getFrameWidth(), m_pImg->getFrameHeight());
	m_pAni->setDefPlayFrame(false, true);
	m_pAni->setFPS(30);
	m_pAni->start();



	// 멤버 초기화
	m_bulletInfo.tIsAlive = m_isAlive = bulletInfo->tIsAlive;
	m_bulletInfo.tAngle =  m_fAngle = bulletInfo->tAngle = angle -= (PI / 360.0f * RANDOM->getFromFloatTo(-(bulletInfo->tScatter),(bulletInfo->tScatter)));
	m_bulletInfo.tScale = bulletInfo->tScale;
	m_bulletInfo.tScaleMax = bulletInfo->tScaleMax;
	m_bulletInfo.tRadius = bulletInfo->tRadius;
	m_bulletInfo.tExpRadius = bulletInfo->tExpRadius;
	m_bulletInfo.tMoveSpeed = bulletInfo->tMoveSpeed;
	m_bulletInfo.tKnokBack = bulletInfo->tKnokBack;
	m_bulletInfo.tPosX = m_fSetPosX = bulletInfo->tPosX = posX;
	m_bulletInfo.tPosY = m_fSetPosY = bulletInfo->tPosY = posY;
	m_bulletInfo.tDmage = bulletInfo->tDmage;
	m_bulletInfo.tRange = bulletInfo->tRange;
	m_bulletInfo.tMoveActType = bulletInfo->tMoveActType;
	m_bulletInfo.tMoveType = bulletInfo->tMoveType;
	m_bulletInfo.tBulletBoom = bulletInfo->tBulletBoom;

	// 추가 폭발이 있다면
	m_bulletInfoSub = bulletInfoSub;

	m_ScaleCount = 0;

	m_fMoveAngle = 0.0f;
	m_fAngleRadius = 0.0f;
	tMoveTypeCount = 0;

	// RECT 초기화 (이미지 프레임 크기)
	m_rc = RectMakeCenter(m_bulletInfo.tPosX, m_bulletInfo.tPosY, m_pImg->getFrameWidth() * m_bulletInfo.tScale / 2, m_pImg->getFrameHeight() * m_bulletInfo.tScale / 2);

	switch (m_bulletInfo.tMoveType)
	{
	case BULLET_MOVE_TYPE::ONE_LINE:
		break;
	case BULLET_MOVE_TYPE::CENTER_CENTRIFUGAL:
		m_fMoveAngle = angle + 90.0f;
		break;
	case BULLET_MOVE_TYPE::MOVE_CENTRIFUGAL:
		break;
	case BULLET_MOVE_TYPE::MOVE_NUM:
		break;
	}

	return S_OK;
}

void bullet::release()
{
	SAFE_DELETE(m_pAni);
}

void bullet::update()
{
	if (!m_isAlive) return;

	movement();

	m_pAni->frameUpdate();
}

void bullet::render(HDC hdc)
{
	//EllipseMakeCenter(hdc, m_bulletInfo.tPosX - SCROLL->GetX(), m_bulletInfo.tPosY - SCROLL->GetY(), m_pImg->getFrameWidth() * m_bulletInfo.tScale, m_pImg->getFrameHeight() * m_bulletInfo.tScale);
	//Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);
	
	m_pImg->aniRender(hdc,
		(m_bulletInfo.tPosX - SCROLL->GetX()) - (m_pImg->getFrameWidth() / 2) * m_bulletInfo.tScale,
		(m_bulletInfo.tPosY - SCROLL->GetY()) - (m_pImg->getFrameHeight() / 2) * m_bulletInfo.tScale,
		m_pAni, m_bulletInfo.tScale, true, 255);
}

void bullet::movement()
{
	if (m_bulletInfo.tMoveSpeed == 0.0f || m_bulletInfo.tMoveSpeed == NULL) return;

	moveTypeAct(m_bulletInfo.tMoveType);

	m_rc = RectMakeCenter(m_bulletInfo.tPosX - SCROLL->GetX(), m_bulletInfo.tPosY - SCROLL->GetY(), m_pImg->getFrameWidth() * m_bulletInfo.tScale / 2, m_pImg->getFrameHeight() * m_bulletInfo.tScale / 2);

	switch (m_bulletInfo.tMoveActType)
	{
	case BULLET_MOVE_ACT_TYPE::SCALE_SIZE_UP:
		if (m_ScaleCount >= 10)
		{
			if (m_bulletInfo.tScale <= m_bulletInfo.tScaleMax)
			{
				m_bulletInfo.tScale += 0.1f;
			}
			else
			{
				m_bulletInfo.tScale = m_bulletInfo.tScaleMax;
			}
		}
		break;
	}
	m_ScaleCount++;


	// 거리만큼 이동하면 죽임
	if (m_bulletInfo.tRange < 0.0f)
	{
		m_eff->play(m_effName, m_bulletInfo.tPosX - (34 / 2), m_bulletInfo.tPosY - (30 / 2));

		m_isAlive = false;
		SecondBulletFire();
	}
}

void bullet::moveTypeAct(int moveType)
{
	if (m_bulletInfo.tMoveType == BULLET_MOVE_TYPE::MOVE_NUM) return;

	switch (m_bulletInfo.tMoveType)
	{
	case BULLET_MOVE_TYPE::ONE_LINE:
		m_fMoveAngle = 0.0f;

		m_bulletInfo.tPosX += cosf(m_fAngle) * m_bulletInfo.tMoveSpeed;
		m_bulletInfo.tPosY += -sinf(m_fAngle) * m_bulletInfo.tMoveSpeed;
		m_bulletInfo.tRange -= m_bulletInfo.tMoveSpeed;

		break;
	case BULLET_MOVE_TYPE::CENTER_CENTRIFUGAL:
		if (tMoveTypeCount >= 5)
		{
			m_fAngleRadius += 0.5f;
			m_fMoveAngle += 0.5f;
			tMoveTypeCount = 0;
		}
		if (m_fMoveAngle >= 360.0f)
		{
			m_fMoveAngle = 0.0f;
		}
		m_bulletInfo.tPosX = m_bulletInfo.tPosX + cosf(m_fMoveAngle) * m_fAngleRadius;
		m_bulletInfo.tPosY = m_bulletInfo.tPosY - sinf(m_fMoveAngle) * m_fAngleRadius;
		tMoveTypeCount++;

		m_bulletInfo.tRange -= m_fAngleRadius;
		

		break;
	case BULLET_MOVE_TYPE::MOVE_CENTRIFUGAL:
		if (tMoveTypeCount >= 5)
		{
			m_fMoveAngle += 1.0f;
			tMoveTypeCount = 0;
		}
		if (m_fMoveAngle >= 360.0f)
		{
			m_fMoveAngle = 0.0f;
		}
		m_bulletInfo.tPosX += cosf(m_fMoveAngle) * 10.0f;
		m_bulletInfo.tPosY += -sinf(m_fMoveAngle) * 10.0f;
		tMoveTypeCount++;

		m_bulletInfo.tPosX += cosf(m_fAngle) * m_bulletInfo.tMoveSpeed;
		m_bulletInfo.tPosY += -sinf(m_fAngle) * m_bulletInfo.tMoveSpeed;
		m_bulletInfo.tRange -= m_bulletInfo.tMoveSpeed;
		break;
	}
}

void bullet::HitEff()
{
	m_eff->play(m_effName, m_bulletInfo.tPosX - (34 / 2)  /** m_bulletInfo.tScale*/ , m_bulletInfo.tPosY - (30 / 2)  /** m_bulletInfo.tScale*/);
	SecondBulletFire();
	m_isAlive = false;
}

void bullet::SecondBulletFire()
{
	if (m_bulletInfo.tBulletBoom)
	{
		m_bulletInfoSub->tBulletBoom = false;
		float tempAngle;
		switch (m_bulletInfoSub->tBoomType)
		{
		case BULLET_BOOM_TYPE::ANGLE_LINE:
			m_bulletInfoSub->tAngle = tempAngle = m_fAngle;
			break;
		case BULLET_BOOM_TYPE::MOUSE_POINT:
			m_bulletInfoSub->tAngle = tempAngle = MY_UTIL::getMouseAngle(m_bulletInfo.tPosX, m_bulletInfo.tPosY);
			break;
		case BULLET_BOOM_TYPE::ANGLE_BOUNCE:
			m_bulletInfoSub->tAngle = tempAngle = -m_fAngle;
			break;
		case BULLET_BOOM_TYPE::ANGLE_RANDOM:
			m_bulletInfoSub->tAngle = tempAngle = RANDOM->getFloat(360.0f);
			break;
		case BULLET_BOOM_TYPE::ANGLE_REVERSE:
			m_bulletInfoSub->tAngle = tempAngle = m_fAngle + (180.0f);// + ((m_bulletInfoSub->tBulletSetNum - 1) * (PI / 180.0f * (30.0f)));
			break;
		}

		if (m_bulletInfoSub->tShootType == BULLET_SHOOT_TYPE::ONE_SHOOT)
		{
			if (m_bulletInfoSub->tBulletSetNum == 1)
			{
				m_pBulletMag->NextFire("임시", m_bulletInfo.tPosX, m_bulletInfo.tPosY, tempAngle, m_bulletInfoSub, m_bulletInfoSub);
			}
			else // 총알 개수 만큼 방향을 분리
			{
				for (int i = 0; i < m_bulletInfoSub->tBulletSetNum; i++)
				{
					m_pBulletMag->NextFire("임시", m_bulletInfo.tPosX, m_bulletInfo.tPosY, tempAngle - (i * (PI / 180.0f * (30.0f))) - ((PI / 180.0f) * tempAngle - ((m_bulletInfoSub->tBulletSetNum - 1) * (PI / 180.0f * (30.0f)))) / 2, m_bulletInfoSub, m_bulletInfoSub);
				}
			}
		}
		else if (m_bulletInfoSub->tShootType == BULLET_SHOOT_TYPE::CUFF_SHOOT)
		{
			if (m_bulletInfoSub->tBulletSetNum == 1)
			{
				m_pBulletMag->NextFire("임시", m_bulletInfo.tPosX, m_bulletInfo.tPosY, tempAngle, m_bulletInfoSub, m_bulletInfoSub);
			}
			else // 총알 개수 만큼 방향을 분리
			{
				for (int i = 0; i < m_bulletInfoSub->tBulletSetNum; i++)
				{
					m_pBulletMag->NextFire("임시", m_bulletInfo.tPosX, m_bulletInfo.tPosY, tempAngle + (i * (PI / 180.0f * (360.0f / m_bulletInfoSub->tBulletSetNum))), m_bulletInfoSub, m_bulletInfoSub);
				}
			}
		}
		else if (m_bulletInfoSub->tShootType == BULLET_SHOOT_TYPE::LINE_SHOOT)
		{
			if (m_bulletInfoSub->tBulletSetNum == 1)
			{
				m_pBulletMag->NextFire("임시", m_bulletInfo.tPosX, m_bulletInfo.tPosY, tempAngle, m_bulletInfoSub, m_bulletInfoSub);
			}
			else // 총알 개수 만큼 방향을 분리
			{
				for (int i = 0; i < m_bulletInfoSub->tBulletSetNum; i++)
				{
					m_pBulletMag->NextFire("임시", m_bulletInfo.tPosX, m_bulletInfo.tPosY, tempAngle, m_bulletInfoSub, m_bulletInfoSub);
				}
			}
		}

	}
}

bullet::bullet()
{
}


bullet::~bullet()
{
}
