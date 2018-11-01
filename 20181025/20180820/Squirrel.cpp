#include "stdafx.h"
#include "Squirrel.h"
#include "animation.h"

HRESULT Squirrel::init()
{

	m_pImage[0] = IMAGEMANAGER->findImage("squirrel_idle");
	m_pImage[1]  = IMAGEMANAGER->findImage("squirrel_round") ; 	//_Jump
	m_pImage[2] = IMAGEMANAGER->findImage("squirrel_run");		//_Run 
	m_pImage[3]	 = IMAGEMANAGER->findImage("squirrel_hurt");	//	_Hurt
	//m_pImage[4]	 = IMAGEMANAGER->findImage("squirrel_round");	//	_Fall
	//m_pImage[5]	 = IMAGEMANAGER->findImage("squirrel_round");	//	_Round

	for (int i = 0; i < 4; ++i)
	{
		m_pAni[i] = new animation;
		m_pAni[i]->init(m_pImage[i]->getWidth(), m_pImage[i]->getHeight(),
			m_pImage[i]->getFrameWidth(), m_pImage[i]->getFrameHeight());
		m_pAni[i]->setDefPlayFrame(false, true);
		m_pAni[i]->setFPS(12);
		m_pAni[i]->start();
	}
	m_eState = st_isIdle;

	return S_OK;
}

void Squirrel::update()
{
	if (m_fX < 0) m_fX = 0;
	if (m_fX > g_saveData.gTileMaxCountX * TILESIZEX_STAGE) g_saveData.gTileMaxCountX * TILESIZEX_STAGE;
	if (m_fY < 0) m_fY = 0;
	if (m_fY > g_saveData.gTileMaxCountY * TILESIZEX_STAGE) g_saveData.gTileMaxCountY * TILESIZEX_STAGE;

	for (int i = 0; i < 4; ++i)
	{
		m_pAni[i]->frameUpdate(TIMEMANAGER->getElapsedTime());
	}
}

void Squirrel::release()
{
}

void Squirrel::render(HDC hdc)
{ //st_isHurt, st_isClimb, st_isIdle, st_isJump, st_isRun, st_round
	if (m_bIsAlive != true) return;

	if (m_bIsChoosed == true)
	{
		if (m_eState == st_isIdle)
		{
			m_pImage[0]->aniRender(hdc, m_fX, m_fY, m_pAni[0], PLAYER_RATIO, false, UNSELECTED_STATE);
		}
		else if (m_eState == st_isJump || m_eState == st_isFall || m_eState == st_isRound)
		{
			m_pImage[1]->aniRender(hdc, m_fX, m_fY, m_pAni[1], PLAYER_RATIO, false, UNSELECTED_STATE);
		}
		else if (m_eState == st_isRun)
		{
			m_pImage[2]->aniRender(hdc, m_fX, m_fY, m_pAni[2], PLAYER_RATIO, false, UNSELECTED_STATE);
		}
		else if (m_eState == st_isHurt)
		{
			m_pImage[3]->aniRender(hdc, m_fX, m_fY, m_pAni[3], PLAYER_RATIO, false, UNSELECTED_STATE);
		}
	}
	else
	{
		if (m_eState == st_isIdle)
		{
			m_pImage[0]->aniRender(hdc, m_fX, m_fY, m_pAni[0], PLAYER_RATIO, true, UNSELECTED_STATE);
		}
		else if (m_eState == st_isJump || m_eState == st_isFall || m_eState == st_isRound)
		{
			m_pImage[1]->aniRender(hdc, m_fX, m_fY, m_pAni[1], PLAYER_RATIO, true, UNSELECTED_STATE);
		}
		else if (m_eState == st_isRun)
		{
			m_pImage[2]->aniRender(hdc, m_fX, m_fY, m_pAni[2], PLAYER_RATIO, true, UNSELECTED_STATE);
		}
		else if (m_eState == st_isHurt)
		{
			m_pImage[3]->aniRender(hdc, m_fX, m_fY, m_pAni[3], PLAYER_RATIO, true, UNSELECTED_STATE);
		}
	}
}

Squirrel::Squirrel()
{
}


Squirrel::~Squirrel()
{
}
