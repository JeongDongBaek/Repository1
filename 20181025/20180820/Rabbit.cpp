#include "stdafx.h"
#include "Rabbit.h"
#include "animation.h"

HRESULT Rabbit::init()
{

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
	m_fSpeed = 4.0f;
	m_fJumpPower = 20.0f;
	m_fWeight = 4.5f;
	m_bIsJumped = false;
	m_bIsAlive = true;
	m_bIsGravity = true;
	m_rc = RectMake(m_fX, m_fY, RABBIT_WIDTH, RABBIT_HEIGHT);

	return S_OK;
}

void Rabbit::update()
{

	m_rc = RectMake(m_fX - SCROLL->GetX(), m_fY - SCROLL->GetY(), RABBIT_WIDTH, RABBIT_HEIGHT);

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
	}
 
	if (m_bIsChoosed != true)
	{
		m_eState = st_isIdle;
		return;
	} // 선택되지 않았을때 다음의 함수들을 건너뛴다.
	////////////////////
	KeyEvent();

	if (m_eState == st_isJump)
	{
		m_nJumpCount++;
		JumpEvent();
		m_fY -= m_fJumpTemp;

		if (m_fJumpTemp < 0) st_isIdle;
	}

	
}


void Rabbit::JumpEvent()
{
	if (m_nJumpCount >= 60)
	{
		m_fJumpTemp -= m_fWeight;
		m_nJumpCount++;
	}

}

void Rabbit::KeyEvent()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		m_fX -= m_fSpeed;
		m_eState = st_isRun;
		m_bIsRight = false;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
		m_eState = st_isIdle;
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		m_fX += m_fSpeed;
		m_eState = st_isRun;
		m_bIsRight = true;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
		m_eState = st_isIdle;
	if (KEYMANAGER->isStayKeyDown(VK_SPACE) && m_eState == st_isIdle)
	{
		m_eState = st_isJump;
		m_fJumpTemp = m_fJumpPower;
	}
	if (KEYMANAGER->isOnceKeyDown('H'))
	{
		m_bIsGravity = false;
		m_eState = st_isIdle;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_CONTROL))
	{

	}
	
	
}

void Rabbit::release()
{
}

void Rabbit::render(HDC hdc)
{

	if (m_bIsChoosed == true)
	{
		if (m_eState == st_isIdle)
		{
			if (m_bIsRight == false)
				m_pImage_left[0]->aniRender(hdc, m_rc.left - 48, m_rc.top - 65, m_pAni[0], PLAYER_RATIO, false, UNSELECTED_STATE);
			else
				m_pImage[0]->aniRender(hdc, m_rc.left - 48, m_rc.top - 65, m_pAni[0], PLAYER_RATIO, false, UNSELECTED_STATE);
		}
		else if (m_eState == st_isJump)
		{
			if (m_bIsRight == false)
				m_pImage_left[1]->aniRender(hdc, m_rc.left - 48, m_rc.top - 65, m_pAni[1], PLAYER_RATIO, false, UNSELECTED_STATE);
			else
				m_pImage[1]->aniRender(hdc, m_rc.left - 48, m_rc.top - 65, m_pAni[1], PLAYER_RATIO, false, UNSELECTED_STATE);
		}
		else if (m_eState == st_isRun)
		{
			if (m_bIsRight == false)
				m_pImage_left[2]->aniRender(hdc, m_rc.left - 48, m_rc.top - 65, m_pAni[2], PLAYER_RATIO, false, UNSELECTED_STATE);
			else
				m_pImage[2]->aniRender(hdc, m_rc.left - 48, m_rc.top - 65, m_pAni[2], PLAYER_RATIO, false, UNSELECTED_STATE);
		}
		else if (m_eState == st_isHurt)
		{
			if (m_bIsRight == false)
				m_pImage_left[3]->aniRender(hdc, m_rc.left - 48, m_rc.top - 65, m_pAni[3], PLAYER_RATIO, false, UNSELECTED_STATE);
			else
				m_pImage[3]->aniRender(hdc, m_rc.left - 48, m_rc.top - 65, m_pAni[3], PLAYER_RATIO, false, UNSELECTED_STATE);
		}
		else if (m_eState == st_isClimb)
		{
			if (m_bIsRight == false)
				m_pImage_left[4]->aniRender(hdc, m_rc.left - 48, m_rc.top - 65, m_pAni[4], PLAYER_RATIO, false, UNSELECTED_STATE);
			else
				m_pImage[4]->aniRender(hdc, m_rc.left - 48, m_rc.top - 65, m_pAni[4], PLAYER_RATIO, false, UNSELECTED_STATE);
		}
		else if (m_eState == st_isFall)
		{
			if (m_bIsRight == false)
				m_pImage_left[5]->aniRender(hdc, m_rc.left - 48, m_rc.top - 65, m_pAni[5], PLAYER_RATIO, false, UNSELECTED_STATE);
			else
				m_pImage[5]->aniRender(hdc, m_rc.left - 48, m_rc.top - 65, m_pAni[5], PLAYER_RATIO, false, UNSELECTED_STATE);
		}
	}
	else
	{
		if (m_eState == st_isIdle)
		{
			if (m_bIsRight == false)
				m_pImage_left[0]->aniRender(hdc, m_rc.left - 48, m_rc.top - 65, m_pAni[0], PLAYER_RATIO, true, UNSELECTED_STATE);
			else
				m_pImage[0]->aniRender(hdc, m_rc.left - 48, m_rc.top - 65, m_pAni[0], PLAYER_RATIO, true, UNSELECTED_STATE);
		}
		else if (m_eState == st_isJump)
		{
			if (m_bIsRight == false)
				m_pImage_left[1]->aniRender(hdc, m_rc.left - 48, m_rc.top - 65, m_pAni[1], PLAYER_RATIO, true, UNSELECTED_STATE);
			else
				m_pImage[1]->aniRender(hdc, m_rc.left - 48, m_rc.top - 65, m_pAni[1], PLAYER_RATIO, true, UNSELECTED_STATE);
		}
		else if (m_eState == st_isRun)
		{
			if (m_bIsRight == false)
				m_pImage_left[2]->aniRender(hdc, m_rc.left - 48, m_rc.top - 65, m_pAni[2], PLAYER_RATIO, true, UNSELECTED_STATE);
			else
				m_pImage[2]->aniRender(hdc, m_rc.left - 48, m_rc.top - 65, m_pAni[2], PLAYER_RATIO, true, UNSELECTED_STATE);
		}
		else if (m_eState == st_isHurt)
		{
			if (m_bIsRight == false)
				m_pImage_left[3]->aniRender(hdc, m_rc.left - 48, m_rc.top - 65, m_pAni[3], PLAYER_RATIO, true, UNSELECTED_STATE);
			else
				m_pImage[3]->aniRender(hdc, m_rc.left - 48, m_rc.top - 65, m_pAni[3], PLAYER_RATIO, true, UNSELECTED_STATE);
		}
		else if (m_eState == st_isClimb)
		{
			if (m_bIsRight == false)
				m_pImage_left[4]->aniRender(hdc, m_rc.left - 48, m_rc.top - 65, m_pAni[4], PLAYER_RATIO, true, UNSELECTED_STATE);
			else
				m_pImage[4]->aniRender(hdc, m_rc.left - 48, m_rc.top - 65, m_pAni[4], PLAYER_RATIO, true, UNSELECTED_STATE);
		}
		else if (m_eState == st_isFall)
		{
			if (m_bIsRight == false)
				m_pImage_left[5]->aniRender(hdc, m_rc.left - 48, m_rc.top - 65, m_pAni[5], PLAYER_RATIO, true, UNSELECTED_STATE);
			else
				m_pImage[5]->aniRender(hdc, m_rc.left - 48, m_rc.top - 65, m_pAni[5], PLAYER_RATIO, true, UNSELECTED_STATE);
		}
	}
	
}

Rabbit::Rabbit()
{

}


Rabbit::~Rabbit()
{
}
