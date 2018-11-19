#include "stdafx.h"
#include "Rabbit.h"
#include "animation.h"
#include "BoomerangMgr.h"
#include "BulletManager.h"
#include "progressBar.h"


HRESULT Rabbit::init()
{
	m_pImage_boomerang = IMAGEMANAGER->findImage("boomerang");
	m_pBoomerang = new BoomerangMgr;
	m_pBoomerang->init(5);

	m_pBulletMgr = new BulletManager;
	m_pBulletMgr->init(5);

	m_pImage[0] = IMAGEMANAGER->findImage("rabbit_idle");
	m_pImage[1] = IMAGEMANAGER->findImage("rabbit_jump");
	m_pImage[2] = IMAGEMANAGER->findImage("rabbit_run");
	m_pImage[3] = IMAGEMANAGER->findImage("rabbit_hurt");
	m_pImage[4] = IMAGEMANAGER->findImage("rabbit_climb");
	m_pImage[5] = IMAGEMANAGER->findImage("rabbit_fall");
	
	m_pImage_left[0] = IMAGEMANAGER->findImage("left_rabbit_idle");
	m_pImage_left[1] = IMAGEMANAGER->findImage("left_rabbit_jump");
	m_pImage_left[2] = IMAGEMANAGER->findImage("left_rabbit_run");
	m_pImage_left[3] = IMAGEMANAGER->findImage("left_rabbit_hurt");
	m_pImage_left[4] = IMAGEMANAGER->findImage("left_rabbit_climb");
	m_pImage_left[5] = IMAGEMANAGER->findImage("left_rabbit_fall");

	for (int i = 0; i < 6; ++i)
	{
		m_pAni[i] = new animation;
		m_pAni[i]->init(m_pImage[i]->getWidth(), m_pImage[i]->getHeight(),
			m_pImage[i]->getFrameWidth(), m_pImage[i]->getFrameHeight());
		m_pAni[i]->setDefPlayFrame(false, true);
		m_pAni[i]->setFPS(12);
		m_pAni[i]->start();

		m_pAni_left[i] = new animation;
		m_pAni_left[i]->init(m_pImage_left[i]->getWidth(), m_pImage_left[i]->getHeight(),
			m_pImage_left[i]->getFrameWidth(), m_pImage_left[i]->getFrameHeight());
		m_pAni_left[i]->setDefPlayFrame(false, true);
		m_pAni_left[i]->setFPS(12);
		m_pAni_left[i]->start();
	}

	m_eState = st_isIdle;
	m_nHurtCount = 55;
	m_nHurtCountTemp = 0;
	m_fSpeed = 4.0f;
	m_fJumpPower = -21.2f;
	m_fWeight = 0.95f;
	m_fAccrancy = 0.15f; // 1레벨 0.15 2레벨 0.11f 3레벨 0.07f  //-0.04씩 줄어듬
	m_bIsBoomerangOn = true;
	m_bIsJumped = false;
	m_bHaveWand = false;
	m_bIsFloating = false;
	m_bIsRected = false;
	m_bIsFalling = false;
	m_bIsGravity = true;
	m_bIsRight = true;
	m_bIsAlive = true;
	m_bIsGravity = true;
	m_nFireDelay = 150; // 1레벨 150 2레벨 130 3레벨 110 
	m_nFireDelayTemp = m_nFireDelay;

	m_fDamage = 1.0f;
	m_fHP = m_fMaxHP = 5.0f;
	m_fStamina = m_fMaxStamina = 5.0f;
	m_fMana = m_fMaxMana = 5.0f;
	m_pProgressBar = new progressBar;
	m_pProgressBar->init(PROGRESSBAR_LOCX, PROGRESSBAR_LOCY, 440, 24);

	m_nFireDelay_Fireball = 55;
	m_nFireDelayTemp_Fireball = m_nFireDelay_Fireball;

	m_rc = RectMake(m_fX, m_fY, RABBIT_WIDTH, RABBIT_HEIGHT);

	m_rcLeft = RectMakeCenter(m_fX - 25, m_fY, 30, 30);
	m_rcLeft = RectMakeCenter(m_fX + 25, m_fY, 30, 30);

	return S_OK;
}

void Rabbit::update()
{
	if (g_saveData.gGamePause == true) return;

	if (m_fHP <= 0)
	{
		m_fHP = 0;
		m_bIsAlive = false;
	}

	//Gravity(GRAVITY);

	m_rc = RectMake(m_fX - SCROLL->GetX(), m_fY - SCROLL->GetY(), RABBIT_WIDTH, RABBIT_HEIGHT);
	m_rcLeft = RectMake(m_fX - RABBIT_WIDTH / 4 + 10 - SCROLL->GetX(), m_fY - SCROLL->GetY() + 20, 28, 5);
	m_rcRight = RectMake(m_fX + RABBIT_WIDTH / 2 + 15 - SCROLL->GetX(), m_fY - SCROLL->GetY() + 20, 28, 5);

	// getIsAlive가 없어도 되는것들
	if (m_fX < 0) m_fX = 0;
	if (m_fX > g_saveData.gTileMaxCountX * TILESIZEX_STAGE - RABBIT_WIDTH)
	{
		m_fX = g_saveData.gTileMaxCountX * TILESIZEX_STAGE- RABBIT_WIDTH;
	}
	if (m_fY < 0) m_fY = 0;
	if (m_fY > g_saveData.gTileMaxCountY * TILESIZEX_STAGE - RABBIT_HEIGHT)
	{
		m_fY = g_saveData.gTileMaxCountY * TILESIZEX_STAGE - RABBIT_HEIGHT;
	}
	

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

	if (m_bIsGravity == true)
	{
		m_nGravityTemp += 0.9f;
		m_fY += 2.8f + m_nGravityTemp;
	}
	else
		m_nGravityTemp = 0;



	if (m_nFireDelayTemp >= 0)
		m_nFireDelayTemp--;

	if (m_nFireDelayTemp_Fireball >= 0)
		m_nFireDelayTemp_Fireball--;

	if (m_pBoomerang)
		m_pBoomerang->update();

	if (m_pBulletMgr)
		m_pBulletMgr->update();
}


void Rabbit::Gravity(float Gravity)
{
	float gravity = 0;
	if (m_bIsGravity == false)
		gravity = 0;
	else
		gravity += Gravity;
	m_fY += gravity;
}

void Rabbit::Damaged(float damage)
{
	m_fHP -= damage;

	if (m_pProgressBar)
	{
		m_pProgressBar->setGauge_heal(m_fHP, m_fMaxHP);
	}

}

void Rabbit::KeyEvent()
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
		if(m_eState != st_isHurt)
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


	if (KEYMANAGER->isOnceKeyDown(VK_CONTROL))
	{
		if (m_bIsBoomerangOn == true && (m_eState == st_isIdle || m_eState == st_isRun) && m_nFireDelayTemp < 0 )
		{
			m_pBoomerang->Fire(m_fX, m_fY, (m_fSpeed - 2.0f), g_ptMouse.x, g_ptMouse.y, m_fAccrancy); // 
			m_nFireDelayTemp = m_nFireDelay;
		}
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

void Rabbit::release()
{
}

void Rabbit::render(HDC hdc)
{
	if (g_saveData.gGamePause == true) return;


	if (m_bIsChoosed == true)
	{
		if (m_eState == st_isIdle)
		{
			if (m_bIsRight == false)
				m_pImage_left[0]->aniRender(hdc, m_rc.left - 48, m_rc.top - 61, m_pAni[0], PLAYER_RATIO, false, UNSELECTED_STATE);
			else
				m_pImage[0]->aniRender(hdc, m_rc.left - 48, m_rc.top - 61, m_pAni[0], PLAYER_RATIO, false, UNSELECTED_STATE);
		}
		else if (m_eState == st_isJump)
		{
			if (m_bIsRight == false)
				m_pImage_left[1]->aniRender(hdc, m_rc.left - 48, m_rc.top - 61, m_pAni[1], PLAYER_RATIO, false, UNSELECTED_STATE);
			else
				m_pImage[1]->aniRender(hdc, m_rc.left - 48, m_rc.top - 61, m_pAni[1], PLAYER_RATIO, false, UNSELECTED_STATE);
		}
		else if (m_eState == st_isRun)
		{
			if (m_bIsRight == false)
				m_pImage_left[2]->aniRender(hdc, m_rc.left - 48, m_rc.top - 61, m_pAni[2], PLAYER_RATIO, false, UNSELECTED_STATE);
			else
				m_pImage[2]->aniRender(hdc, m_rc.left - 48, m_rc.top - 61, m_pAni[2], PLAYER_RATIO, false, UNSELECTED_STATE);
		}
		else if (m_eState == st_isHurt)
		{
			if (m_bIsRight == false)
				m_pImage_left[3]->aniRender(hdc, m_rc.left - 48, m_rc.top - 61, m_pAni[3], PLAYER_RATIO, false, UNSELECTED_STATE);
			else
				m_pImage[3]->aniRender(hdc, m_rc.left - 48, m_rc.top - 61, m_pAni[3], PLAYER_RATIO, false, UNSELECTED_STATE);
		}
		else if (m_eState == st_isClimb)
		{
			if (m_bIsRight == false)
				m_pImage_left[4]->aniRender(hdc, m_rc.left - 48, m_rc.top - 61, m_pAni[4], PLAYER_RATIO, false, UNSELECTED_STATE);
			else
				m_pImage[4]->aniRender(hdc, m_rc.left - 48, m_rc.top - 61, m_pAni[4], PLAYER_RATIO, false, UNSELECTED_STATE);
		}
		else if (m_eState == st_isFall)
		{
			if (m_bIsRight == false)
				m_pImage_left[5]->aniRender(hdc, m_rc.left - 48, m_rc.top - 61, m_pAni[5], PLAYER_RATIO, false, UNSELECTED_STATE);
			else
				m_pImage[5]->aniRender(hdc, m_rc.left - 48, m_rc.top - 61, m_pAni[5], PLAYER_RATIO, false, UNSELECTED_STATE);
		}
	}
	else
	{
		if (m_eState == st_isIdle)
		{
			if (m_bIsRight == false)
				m_pImage_left[0]->aniRender(hdc, m_rc.left - 48, m_rc.top - 61, m_pAni[0], PLAYER_RATIO, true, UNSELECTED_STATE);
			else
				m_pImage[0]->aniRender(hdc, m_rc.left - 48, m_rc.top - 61, m_pAni[0], PLAYER_RATIO, true, UNSELECTED_STATE);
		}
		else if (m_eState == st_isJump)
		{
			if (m_bIsRight == false)
				m_pImage_left[1]->aniRender(hdc, m_rc.left - 48, m_rc.top - 61, m_pAni[1], PLAYER_RATIO, true, UNSELECTED_STATE);
			else
				m_pImage[1]->aniRender(hdc, m_rc.left - 48, m_rc.top - 61, m_pAni[1], PLAYER_RATIO, true, UNSELECTED_STATE);
		}
		else if (m_eState == st_isRun)
		{
			if (m_bIsRight == false)
				m_pImage_left[2]->aniRender(hdc, m_rc.left - 48, m_rc.top - 61, m_pAni[2], PLAYER_RATIO, true, UNSELECTED_STATE);
			else
				m_pImage[2]->aniRender(hdc, m_rc.left - 48, m_rc.top - 61, m_pAni[2], PLAYER_RATIO, true, UNSELECTED_STATE);
		}
		else if (m_eState == st_isHurt)
		{
			if (m_bIsRight == false)
				m_pImage_left[3]->aniRender(hdc, m_rc.left - 48, m_rc.top - 61, m_pAni[3], PLAYER_RATIO, true, UNSELECTED_STATE);
			else
				m_pImage[3]->aniRender(hdc, m_rc.left - 48, m_rc.top - 61, m_pAni[3], PLAYER_RATIO, true, UNSELECTED_STATE);
		}
		else if (m_eState == st_isClimb)
		{
			if (m_bIsRight == false)
				m_pImage_left[4]->aniRender(hdc, m_rc.left - 48, m_rc.top - 61, m_pAni[4], PLAYER_RATIO, true, UNSELECTED_STATE);
			else
				m_pImage[4]->aniRender(hdc, m_rc.left - 48, m_rc.top - 61, m_pAni[4], PLAYER_RATIO, true, UNSELECTED_STATE);
		}
		else if (m_eState == st_isFall)
		{
			if (m_bIsRight == false)
				m_pImage_left[5]->aniRender(hdc, m_rc.left - 48, m_rc.top - 61, m_pAni[5], PLAYER_RATIO, true, UNSELECTED_STATE);
			else
				m_pImage[5]->aniRender(hdc, m_rc.left - 48, m_rc.top - 61, m_pAni[5], PLAYER_RATIO, true, UNSELECTED_STATE);
		}
	}
	
	if (m_pBoomerang)
		m_pBoomerang->render(hdc);

	if (m_pBulletMgr)
		m_pBulletMgr->render(hdc);


	if (g_saveData.gSelectedInven == 1)
	{
		IMAGEMANAGER->findImage("white2")->render(hdc, WINSIZEX / 2 - IMAGEMANAGER->findImage("white2")->getWidth() / 2, 220);
		m_pProgressBar->render(hdc);
	}
}

Rabbit::Rabbit()
{

}


Rabbit::~Rabbit()
{
}
