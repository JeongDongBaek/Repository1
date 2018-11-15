#include "stdafx.h"
#include "Fox.h"
#include "image.h"
#include "animation.h"
#include "BulletManager.h"
#include "progressBar.h"


HRESULT Fox::init()
{

	m_pImage[0] = IMAGEMANAGER->findImage("fox_idle");
	m_pImage[1] = IMAGEMANAGER->findImage("fox_jump"); // 
	m_pImage[2] = IMAGEMANAGER->findImage("fox_fall"); // 
	m_pImage[3] = IMAGEMANAGER->findImage("fox_run"); // 
	m_pImage[4] = IMAGEMANAGER->findImage("fox_hurt"); // 
	m_pImage[5] = IMAGEMANAGER->findImage("fox_climb"); // 

	m_pImage_left[0] = IMAGEMANAGER->findImage("left_fox_idle");
	m_pImage_left[1] = IMAGEMANAGER->findImage("left_fox_jump"); // 
	m_pImage_left[2] = IMAGEMANAGER->findImage("left_fox_fall"); // 
	m_pImage_left[3] = IMAGEMANAGER->findImage("left_fox_run"); // 
	m_pImage_left[4] = IMAGEMANAGER->findImage("left_fox_hurt"); // 
	m_pImage_left[5] = IMAGEMANAGER->findImage("left_fox_climb"); // 

	for (int i = 0; i < 6; ++i)
	{
		m_pAni[i] = new animation;
		m_pAni[i]->init(m_pImage[i]->getWidth(), m_pImage[i]->getHeight(), m_pImage[i]->getFrameWidth(), m_pImage[i]->getFrameHeight());
		m_pAni[i]->setDefPlayFrame(false, true);
		m_pAni[i]->setFPS(12);
		m_pAni[i]->start();

		m_pAni_left[i] = new animation;
		m_pAni_left[i]->init(m_pImage_left[i]->getWidth(), m_pImage_left[i]->getHeight(), m_pImage_left[i]->getFrameWidth(), m_pImage_left[i]->getFrameHeight());
		m_pAni_left[i]->setDefPlayFrame(false, true);
		m_pAni_left[i]->setFPS(12);
		m_pAni_left[i]->start();
	}
	m_eState = st_isIdle;

	m_pBulletMgr = new BulletManager;
	m_pBulletMgr->init(5);

	m_eState = st_isIdle;
	m_nHurtCount = 55;
	m_nHurtCountTemp = 0;
	m_fSpeed = 4.0f;
	m_fJumpPower = -20.5f;
	m_fWeight = 0.95f;
	m_bIsJumped = false;
	m_bHaveWand = true;
	m_bIsFloating = false;
	m_bIsRight = true;
	m_bIsRected = false;
	m_bIsFalling = false;
	m_bIsGravity = true;
	m_bIsAlive = true;
	m_bIsGravity = true;


	m_fHP = m_fMaxHP = 5.0f;
	m_fStamina = m_fMaxStamina = 5.0f;
	m_fMana = m_fMaxMana = 5.0f;
	m_pProgressBar = new progressBar;
	m_pProgressBar->init(PROGRESSBAR_LOCX, PROGRESSBAR_LOCY, 440, 24);


	m_nFireDelay_Fireball = 180;
	m_nFireDelayTemp_Fireball = m_nFireDelay_Fireball;

	m_rc = RectMake(m_fX, m_fY, FOX_WIDTH, FOX_HEIGHT);


	return S_OK;
}

void Fox::update()
{
	m_rc = RectMake(m_fX - SCROLL->GetX(), m_fY - SCROLL->GetY(), FOX_WIDTH, FOX_HEIGHT);

	if (m_fX < 0) m_fX = 0;
	if (m_fX > g_saveData.gTileMaxCountX * TILESIZEX_STAGE) g_saveData.gTileMaxCountX * TILESIZEX_STAGE;
	if (m_fY < 0) m_fY = 0;
	if (m_fY > g_saveData.gTileMaxCountY * TILESIZEX_STAGE) g_saveData.gTileMaxCountY * TILESIZEX_STAGE;

	for (int i = 0; i < 6; ++i)
	{
		m_pAni[i]->frameUpdate(TIMEMANAGER->getElapsedTime());
		m_pAni_left[i]->frameUpdate(TIMEMANAGER->getElapsedTime());
	}




	if (m_bIsChoosed != true)
	{
		m_eState = st_isIdle;
		return;
	} // 선택되지 않았을때 다음의 함수들을 건너뛴다.
	////////////////////

	KeyEvent();



	//////////////////////// 점프이미지  및  하강이미지 ////////////////////
	if (m_bIsFloating == true)
	{
		m_eState = st_isJump;
		m_fY += m_fJumpTemp;
		m_fJumpTemp += m_fWeight;

		if (m_fJumpTemp >= 19)
			m_fJumpTemp = 20;

		if (m_fJumpTemp > 0)
		{
			m_bIsJumped = false;
			m_eState = st_isFall;
		}

		if (m_bIsRected == true)
		{
			m_bIsFalling = false;
			m_bIsFloating = false;
			m_eState = st_isIdle;
		}
	}/////////////////////////////////////////////////////


	if (m_eState == st_isHurt) ////////// 데미지 이미지에서 아이들로 /////
	{

		if (m_nHurtCount > m_nHurtCountTemp)
		{
			m_nHurtCountTemp++;
		}
		else
		{
			m_eState = st_isIdle;
			m_nHurtCountTemp = 0;
		}
	}/////////////////////////////







	if (m_nFireDelayTemp_Fireball >= 0)
		m_nFireDelayTemp_Fireball--;

	if (m_pBulletMgr)
		m_pBulletMgr->update();
}

void Fox::KeyEvent()
{
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		if (m_eState != st_isClimb && m_eState != st_isHurt)
		{
			if (m_eState != st_isRun)
			{
				m_eState = st_isRun;
				m_pAni[2]->start();
				m_pAni[2]->setFPS(13 + m_fSpeed);
			}
			m_fX += m_fSpeed;
			m_bIsRight = true;
		}

	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		if (m_eState != st_isHurt)
			m_eState = st_isIdle;
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		if (m_eState != st_isClimb && m_eState != st_isHurt)
		{
			if (m_eState != st_isRun)
			{
				m_eState = st_isRun;
				m_pAni[2]->start();
				m_pAni[2]->setFPS(13 + m_fSpeed);
			}
			m_fX -= m_fSpeed;
			m_bIsRight = false;
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		if (m_eState != st_isHurt)
			m_eState = st_isIdle;
	}







	if (KEYMANAGER->isStayKeyDown(VK_SPACE) && m_bIsRight == false && m_bIsFloating == false)
	{
		if (m_eState != st_isJump && m_eState != st_isFall)
		{
			m_eState = st_isJump;
			m_pAni_left[1]->start();
			m_pAni_left[1]->setFPS(12);
			m_bIsJumped = true;
		}
		m_bIsJumped = true;
		m_bIsRected = false;
		m_bIsFloating = true;
		m_fJumpTemp = m_fJumpPower;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_SPACE) && m_bIsRight == false && m_bIsJumped == true)
	{
		if (m_fJumpTemp < -6.0f)
			m_fJumpTemp = -4.0f;
	}




	if (KEYMANAGER->isStayKeyDown(VK_SPACE) && m_bIsRight == true && m_bIsFloating == false)
	{
		if (m_eState != st_isJump || m_eState != st_isFall)
		{
			m_eState = st_isJump;
			m_pAni[1]->start();
			m_pAni[1]->setFPS(12);
			m_bIsJumped = true;
		}
		m_bIsJumped = true;
		m_bIsFloating = true;
		m_bIsRected = false;

		m_fJumpTemp = m_fJumpPower;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_SPACE) && m_bIsRight == true && m_bIsJumped == true)
	{
		if (m_fJumpTemp < -4.0f)
			m_fJumpTemp = -4.0f;
	}




	if (KEYMANAGER->isStayKeyDown('Z'))
	{
		if (!m_bHaveWand == true) return;

		if ((m_eState == st_isIdle || m_eState == st_isRun) && m_nFireDelayTemp_Fireball <= 0)
		{
			m_pBulletMgr->Fire("fireball", m_fX, m_fY, FIREBALL_SPEED, FIREBALL_RANGE, 1, m_bIsRight, false);
			m_nFireDelayTemp_Fireball = m_nFireDelay_Fireball;
		}

	}


}

void Fox::Gravity(float Gravity)
{
}

void Fox::Damaged(float damage)
{
	m_fHP -= damage;
	if (m_fHP <= 0)
	{
		m_fHP = 0;
		m_bIsAlive = false;
	}

	if (m_pProgressBar)
	{
		m_pProgressBar->setGauge_heal(m_fHP, m_fMaxHP);
	}

}

void Fox::release()
{
}

void Fox::render(HDC hdc)
{
	if (m_bIsChoosed == true)
	{
		if (m_eState == st_isIdle)
		{
			if(m_bIsRight == true)
				m_pImage[0]->aniRender(hdc, m_rc.left - 40, m_rc.top - 59, m_pAni[0], PLAYER_RATIO, false, UNSELECTED_STATE);
			else
				m_pImage_left[0]->aniRender(hdc, m_rc.left - 45, m_rc.top - 59, m_pAni_left[0], PLAYER_RATIO, false, UNSELECTED_STATE);
		}
		else if (m_eState == st_isJump)
		{
			if (m_bIsRight == true)
				m_pImage[1]->frameAlphaRender(hdc, m_rc.left - 40, m_rc.top - 59, 0, 0, PLAYER_RATIO, 0);
			else
				m_pImage_left[1]->frameAlphaRender(hdc, m_rc.left - 45, m_rc.top - 59, 0, 0, PLAYER_RATIO, 0);
		}
		else if (m_eState == st_isFall)
		{
			if (m_bIsRight == true)
				m_pImage[2]->frameAlphaRender(hdc, m_rc.left - 40, m_rc.top - 59, 0,0, PLAYER_RATIO, 0);
			else
				m_pImage_left[2]->frameAlphaRender(hdc, m_rc.left - 45, m_rc.top - 59, 0, 0, PLAYER_RATIO, 0);
		}
		else if (m_eState == st_isRun)
		{
			if (m_bIsRight == true)
				m_pImage[3]->aniRender(hdc, m_rc.left - 40, m_rc.top - 59, m_pAni[3], PLAYER_RATIO, false, UNSELECTED_STATE);
			else
				m_pImage_left[3]->aniRender(hdc, m_rc.left - 45, m_rc.top - 59, m_pAni_left[3], PLAYER_RATIO, false, UNSELECTED_STATE);
		}
		else if (m_eState == st_isHurt)
		{
			if (m_bIsRight == true)
				m_pImage[4]->aniRender(hdc, m_rc.left - 40, m_rc.top - 59, m_pAni[4], PLAYER_RATIO, false, UNSELECTED_STATE);
			else
				m_pImage_left[4]->aniRender(hdc, m_rc.left - 45, m_rc.top - 59, m_pAni_left[4], PLAYER_RATIO, false, UNSELECTED_STATE);
		}
		else if (m_eState == st_isClimb)
		{
			if (m_bIsRight == true)
				m_pImage[5]->aniRender(hdc, m_rc.left - 40, m_rc.top - 59, m_pAni[5], PLAYER_RATIO, false, UNSELECTED_STATE);
			else
				m_pImage_left[5]->aniRender(hdc, m_rc.left - 45, m_rc.top - 59, m_pAni_left[5], PLAYER_RATIO, false, UNSELECTED_STATE);
		}
	}
	else
	{
		if (m_eState == st_isIdle)
		{
			if(m_bIsRight)
				m_pImage[0]->aniRender(hdc, m_rc.left - 40, m_rc.top - 59, m_pAni[0], PLAYER_RATIO, true, UNSELECTED_STATE);
			else
				m_pImage_left[0]->aniRender(hdc, m_rc.left - 45, m_rc.top - 59, m_pAni_left[0], PLAYER_RATIO, true, UNSELECTED_STATE);
		}
		else if (m_eState == st_isJump)
		{
			if (m_bIsRight)
				m_pImage[1]->frameAlphaRender(hdc, m_rc.left - 40, m_rc.top - 59, 0, 0, PLAYER_RATIO, UNSELECTED_STATE);
			else
				m_pImage_left[1]->frameAlphaRender(hdc, m_rc.left - 45, m_rc.top - 59, 0, 0, PLAYER_RATIO, UNSELECTED_STATE);
		}
		else if (m_eState == st_isFall)
		{
			if (m_bIsRight)
				m_pImage[2]->frameAlphaRender(hdc, m_rc.left - 40, m_rc.top - 59, 0, 0, PLAYER_RATIO, UNSELECTED_STATE);
			else
				m_pImage_left[2]->frameAlphaRender(hdc, m_rc.left - 45, m_rc.top - 59, 0, 0, PLAYER_RATIO, UNSELECTED_STATE);
		}
		else if (m_eState == st_isRun)
		{
			if (m_bIsRight)
				m_pImage[3]->aniRender(hdc, m_rc.left - 40, m_rc.top - 59, m_pAni[3], PLAYER_RATIO, true, UNSELECTED_STATE);
			else
				m_pImage_left[3]->aniRender(hdc, m_rc.left - 45, m_rc.top - 59, m_pAni_left[3], PLAYER_RATIO, true, UNSELECTED_STATE);

		}
		else if (m_eState == st_isHurt)
		{
			if (m_bIsRight)
				m_pImage[4]->aniRender(hdc, m_rc.left - 40, m_rc.top - 59, m_pAni[4], PLAYER_RATIO, true, UNSELECTED_STATE);
			else
				m_pImage_left[4]->aniRender(hdc, m_rc.left - 45, m_rc.top - 59, m_pAni_left[4], PLAYER_RATIO, true, UNSELECTED_STATE);
		}
		else if (m_eState == st_isClimb)
		{
			if(m_bIsRight)
				m_pImage[5]->aniRender(hdc, m_rc.left - 40, m_rc.top - 59, m_pAni[5], PLAYER_RATIO, true, UNSELECTED_STATE);
			else
				m_pImage_left[5]->aniRender(hdc, m_rc.left - 45, m_rc.top - 59, m_pAni_left[5], PLAYER_RATIO, true, UNSELECTED_STATE);
		}
	}

	m_pBulletMgr->render(hdc);

	if (g_saveData.gSelectedInven == 0)
	{
		IMAGEMANAGER->findImage("white2")->render(hdc, WINSIZEX / 2 - IMAGEMANAGER->findImage("white2")->getWidth() / 2, 220);
		m_pProgressBar->render(hdc);
	}
}



Fox::Fox()
{
}

Fox::~Fox()
{
}