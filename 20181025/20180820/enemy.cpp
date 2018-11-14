#include "stdafx.h"
#include "Enemy.h"
#include "animation.h"

HRESULT Enemy::init(int EnemyNum, tagEnemyPattern Pattern, int Upgrade)
{
	/*if (EnemyNum >= 8) return;
*/
	m_bIsMoving = true;
	m_bIsDown = true; // 밑으로 내려감
	m_pImage[1] = NULL;
	m_pAni[1] = NULL;

	m_pImage_left[1] = NULL;
	m_pAni_left[1] = NULL;
	m_bIsAlive = true;
	m_nEnemyNum = EnemyNum;
	m_fWeight = 1.0f;
	m_eState = st_isIdle_Enemy;
	m_nDetectNum = 240.0f;
	m_nUpgradeNum = Upgrade;
	m_ePattern = Pattern;
	m_fDef = 0.0f;
	m_nCountSteptemp = 50;
	m_nCountStep = 0;
	m_nStopCount = 0;
	m_bIsRight = false;

	switch (m_nEnemyNum)
	{
	case 0:
		m_nCurrectWidth = ANT_WIDTH;
		m_nCurrectHeight = ANT_HEIGHT;
		break;
	case 1:
		m_nCurrectWidth = BEE_WIDTH;
		m_nCurrectHeight = BEE_HEIGHT;
		break;
	case 2:
		m_nCurrectWidth = CROCOBIRD_WIDTH;
		m_nCurrectHeight = CROCOBIRD_HEIGHT;
		break;
	case 3:
		m_nCurrectWidth = GLASS_WIDTH;
		m_nCurrectHeight = GLASS_HEIGHT;
		break;
	case 4:
		m_nCurrectWidth = PLANT_WIDTH;
		m_nCurrectHeight = PLANT_HEIGHT;
		break;
	case 5:
		m_nCurrectWidth = EAGLE_WIDTH;
		m_nCurrectHeight = EAGLE_HEIGHT;
		break;
	case 6:
		m_nCurrectWidth = FROG_WIDTH;
		m_nCurrectHeight = FROG_HEIGHT;
		break;
	case 7:
		m_nCurrectWidth = OPOSUM_WIDTH;
		m_nCurrectHeight = OPOSUM_HEIGHT;
		break;
	case 8:
		m_nCurrectWidth = SLUG_WIDTH;
		m_nCurrectHeight = SLUG_HEIGHT;
		break;
	case 9:
		m_nCurrectWidth = DARK_SLUG_WIDTH;
		m_nCurrectHeight = DARK_SLUG_HEIGHT;
		break;
	
	}
	m_rc = RectMake(m_fX - SCROLL->GetX(), m_fY - SCROLL->GetY(), m_nCurrectWidth, m_nCurrectHeight);

	switch (m_nEnemyNum)
	{
	case 0:
		m_pImage[0] = IMAGEMANAGER->findImage("ant_idle");
		m_pImage_left[0] = IMAGEMANAGER->findImage("left_ant_idle");
		m_fHP = 2.0f ;
		m_fDamage = 1.0f;
		m_fSpeed = 1.3f;
		if (m_ePattern == Pattern_ofRule) m_ePattern = Pattern_moveStep;
		break;
	case 1:
		m_pImage[0] = IMAGEMANAGER->findImage("bee_idle");
		m_pImage_left[0] = IMAGEMANAGER->findImage("left_bee_idle");
		m_fHP = 5.0f;
		m_fDamage = 2.0f;
		m_fSpeed = 2.0f;
		if (m_ePattern == Pattern_ofRule) m_ePattern = Pattern_moveTileUpDown;
		break;
	case 2:
		m_pImage[0] = IMAGEMANAGER->findImage("crocodile_idle");
		m_pImage_left[0] = IMAGEMANAGER->findImage("left_crocodile_idle");
		m_fHP = 6.0f;
		m_fDamage = 3.0f;
		m_fSpeed = 2.4f;
		if (m_ePattern == Pattern_ofRule) m_ePattern = Pattern_moveFly;
		break;
	case 3:
		m_pImage[0] = IMAGEMANAGER->findImage("grasshopper_idle");
		m_pImage_left[0] = IMAGEMANAGER->findImage("left_grasshopper_idle");
		m_pImage[1] = IMAGEMANAGER->findImage("grasshopper_jump"); // 그냥 애니메이션
		m_pImage_left[1] = IMAGEMANAGER->findImage("left_grasshopper_jump"); // 그냥 애니메이션
		m_fHP = 3.0f;
		m_fDamage = 1.0f;
		m_fSpeed = 1.7f;
		if (m_ePattern == Pattern_ofRule) m_ePattern = Pattern_JumpOfGlass;
		break;
	case 4:
		m_pImage[0] = IMAGEMANAGER->findImage("monster_plant_idle");
		m_pImage[1] = IMAGEMANAGER->findImage("monster_plant_attack");
		m_pImage_left[0] = IMAGEMANAGER->findImage("left_monster_plant_idle");
		m_pImage_left[1] = IMAGEMANAGER->findImage("left_monster_plant_attack");
		m_fHP = 4.0f;
		m_fDamage = 1.0f;
		m_fSpeed = 0.0f;
		if (m_ePattern == Pattern_ofRule) m_ePattern = Pattern_Stop;
		break;
	case 5:
		m_pImage[0] = IMAGEMANAGER->findImage("eagle_idle");
		m_pImage_left[0] = IMAGEMANAGER->findImage("left_eagle_idle");
		m_fHP = 10.0f;
		m_fDamage = 4.0f;
		m_fSpeed = 3.5f;
		if (m_ePattern == Pattern_ofRule) m_ePattern = Pattern_moveFly;
		break;
	case 6:
		m_pImage[0] = IMAGEMANAGER->findImage("frog_idle");
		m_pImage[1] = IMAGEMANAGER->findImage("frog_jump");
		m_pImage_left[0] = IMAGEMANAGER->findImage("frog_idle");
		m_pImage_left[1] = IMAGEMANAGER->findImage("frog_jump");
		m_fHP = 5.0f;
		m_fDamage = 3.0f;
		m_fSpeed = 1.5f;
		if (m_ePattern == Pattern_ofRule) m_ePattern = Pattern_JumpOfFlog;
		break;
	case 7:
		m_pImage[0] = IMAGEMANAGER->findImage("oposum_idle");
		m_pImage_left[0] = IMAGEMANAGER->findImage("left_oposum_idle");
		m_fHP = 9.0f;
		m_fDamage = 3.0f;
		m_fSpeed = 2.1f;
		if (m_ePattern == Pattern_ofRule) m_ePattern = Pattern_moveNormal;
		break;
	case 8:
		m_bIsRight = true;
		m_pImage[0] = IMAGEMANAGER->findImage("slug_idle");
		m_pImage_left[0] = IMAGEMANAGER->findImage("left_slug_idle");
		m_fHP = 30.0f;
		m_fDamage = 3.0f;
		m_fSpeed = 1.8f;
		if (m_ePattern == Pattern_ofRule) m_ePattern = Pattern_Slug;
		break;
	case 9:
		m_bIsRight = true;
		m_pImage[0] = IMAGEMANAGER->findImage("dark_slug_idle");
		m_pImage_left[0] = IMAGEMANAGER->findImage("left_dark_slug_idle");
		m_fHP = 60.0f;
		m_fDamage = 3.0f;
		m_fSpeed = 2.4f;
		if (m_ePattern == Pattern_ofRule) m_ePattern = Pattern_Slug;
		break;
	}

	m_fHP += (m_fHP * 0.5) * Upgrade;
	m_fDamage += (m_fDamage * 0.5) * Upgrade;
	m_fSpeed += (m_fSpeed * 0.5) * Upgrade;
	m_fDef += (Upgrade * 0.5);	

	

	
	m_pAni[0] = new animation;
	m_pAni[0]->init(m_pImage[0]->getWidth(), m_pImage[0]->getHeight(),
		m_pImage[0]->getFrameWidth(), m_pImage[0]->getFrameHeight());
	m_pAni[0]->setDefPlayFrame(false, true);
	m_pAni[0]->setFPS(11);
	m_pAni[0]->start();

	if (m_pImage[1] != NULL)
	{
		m_pAni[1] = new animation;
		m_pAni[1]->init(m_pImage[1]->getWidth(), m_pImage[1]->getHeight(),
			m_pImage[1]->getFrameWidth(), m_pImage[1]->getFrameHeight());
		m_pAni[1]->setDefPlayFrame(false, true);
		m_pAni[1]->setFPS(11);
		m_pAni[1]->start();
	}


	m_pAni_left[0] = new animation;
	m_pAni_left[0]->init(m_pImage_left[0]->getWidth(), m_pImage_left[0]->getHeight(),
		m_pImage_left[0]->getFrameWidth(), m_pImage_left[0]->getFrameHeight());
	m_pAni_left[0]->setDefPlayFrame(false, true);
	m_pAni_left[0]->setFPS(11);
	m_pAni_left[0]->start();

	if (m_pImage_left[1] != NULL)
	{
		m_pAni_left[1] = new animation;
		m_pAni_left[1]->init(m_pImage_left[1]->getWidth(), m_pImage_left[1]->getHeight(),
			m_pImage_left[1]->getFrameWidth(), m_pImage_left[1]->getFrameHeight());
		m_pAni_left[1]->setDefPlayFrame(false, true);
		m_pAni_left[1]->setFPS(11);
		m_pAni_left[1]->start();
	}



	return S_OK;
}

void Enemy::update()
{
	if (!m_bIsAlive == true) return;

	m_rc = RectMake(m_fX - SCROLL->GetX(), m_fY - SCROLL->GetY(), m_nCurrectWidth, m_nCurrectHeight);

	if (m_nEnemyNum == 6)
	{
		if (m_eState == st_isJump_Enemy)
		{
			m_nCurrentFrame = 1;
			m_pImage[1]->setFrameX(m_nCurrentFrame);
			m_pImage_left[1]->setFrameX(m_nCurrentFrame);
		}
		else if (m_eState == st_isFall_Enemy)
		{
			m_nCurrentFrame = 2;
			m_pImage[1]->setFrameX(m_nCurrentFrame);
			m_pImage_left[1]->setFrameX(m_nCurrentFrame);
		}
	}

	m_pAni[0]->frameUpdate(TIMEMANAGER->getElapsedTime());
	if(m_nEnemyNum == 3 || m_nEnemyNum == 4 ) 
		m_pAni[1]->frameUpdate(TIMEMANAGER->getElapsedTime());

	m_pAni_left[0]->frameUpdate(TIMEMANAGER->getElapsedTime());
	if (m_nEnemyNum == 3 || m_nEnemyNum == 4)
		m_pAni_left[1]->frameUpdate(TIMEMANAGER->getElapsedTime());

	Pattern_move();
	
}
void Enemy::Pattern_move()
{
	switch (m_ePattern)
	{
	case Pattern_moveStep:
		if (m_bIsMoving == false)
		{
			m_nStopCount++;
			if (m_nStopCount > RANDOM->getFromIntTo(80, 100))
			{
				m_nStopCount = 0;
				m_bIsMoving = true;
			}
		}


		if (m_bIsMoving == true)
		{
			if (m_bIsRight == true)
				m_fX += m_fSpeed;
			else
				m_fX -= m_fSpeed;

			m_nCountStep++;
			if (m_nCountStep > m_nCountSteptemp)
			{
				m_nCountSteptemp = RANDOM->getFromIntTo(90, 120);
				m_nCountStep = 0;
				m_bIsMoving = false;
			}
		}

		
		break;
	case Pattern_moveNormal:
		if (m_bIsRight == true)
			m_fX += m_fSpeed;
		else
			m_fX -= m_fSpeed;
		break;
	case Pattern_moveTileUpDown:
		if (m_bIsDown)
			m_fY += m_fSpeed;
		else
			m_fY -= m_fSpeed;
		break;
	case Pattern_moveFly:
		break;
	case Pattern_Stop:
		break;
	case Pattern_Follow:
		break;
	case Pattern_JumpOfFlog:
		break;
	case Pattern_JumpOfGlass:
		break;
	case Pattern_Slug:
		break;
	}
}


void Enemy::release()
{
}

void Enemy::render(HDC hdc)
{

	if (g_saveData.gIsRectangleOn == true)
	{
		//EllipseMakeCenter(hdc, m_rc.left + m_nCurrectWidth / 2, m_rc.top + m_nCurrectHeight / 2 , m_nDetectNum * 2 , m_nDetectNum  * 2);
		Rectangle(hdc, m_rc.left , m_rc.top , m_rc.right, m_rc.bottom);

		char SzText2[64];
		RECT temp_rc = RectMake(
			m_rc.left + 58,
			m_rc.top + 1,
			m_rc.right + 58,
			m_rc.bottom + 1
		);

	
		sprintf_s(SzText2, "fY : %f", m_fY);
		DrawText(hdc, SzText2, strlen(SzText2), &temp_rc, DT_WORDBREAK);
		temp_rc = RectMake(
			m_rc.left + 55,
			m_rc.top + 35,
			m_rc.right + 55,
			m_rc.bottom + 35
		);
		sprintf_s(SzText2, "left : %ld", m_rc.left );
		DrawText(hdc, SzText2, strlen(SzText2), &temp_rc, DT_WORDBREAK);

		temp_rc = RectMake(
			m_rc.left + 55,
			m_rc.top + 66,
			m_rc.right + 55,
			m_rc.bottom + 66
		);
		sprintf_s(SzText2, "top : %ld", m_rc.top  );
		DrawText(hdc, SzText2, strlen(SzText2), &temp_rc, DT_WORDBREAK);
	}

	/*if (m_nEnemyNum == 3)
	{
	if (m_eState == st_isIdle_Enemy)
		m_pImage[0]->aniRender(hdc, m_rc.left - m_pImage[0]->getFrameWidth() / 2 , m_rc.top - 60 - m_pImage[0]->getFrameHeight() / 2, m_pAni[0], 4.0f, false, 100);
	else
		m_pImage[1]->aniRender(hdc, m_rc.left - 55, m_rc.top - 85, m_pAni[1], 4.0f, false, 100);
	}
	else if (m_nEnemyNum == 6)
	{
		if (m_eState == st_isIdle_Enemy)
			m_pImage[0]->aniRender(hdc, m_rc.left - m_pImage[0]->getFrameWidth() / 2, m_rc.top - 60 - m_pImage[0]->getFrameHeight() / 2, m_pAni[0], 4.0f, false, 100);
		else
			m_pImage[1]->frameRender(hdc, m_rc.left - 40, m_rc.top - 48, m_nCurrentFrame, 0, 4.0f);
	}
	else
		m_pImage[0]->aniRender(hdc, m_rc.left - m_pImage[0]->getFrameWidth() / 2, m_rc.top - 60 - m_pImage[0]->getFrameHeight() / 2, m_pAni[0], 4.0f, false, 100);
*/


	switch (m_nEnemyNum)
	{
	case 0:
		if(m_bIsRight == true)
			m_pImage[0]->aniRender(hdc, m_rc.left - 48, m_rc.top - 60, m_pAni[0], 4.0f, false ,100);
		else
			m_pImage_left[0]->aniRender(hdc, m_rc.left - 48, m_rc.top - 60, m_pAni_left[0], 4.0f, false, 100);
		break;
	case 1:
		if (m_bIsRight == true)
			m_pImage[0]->aniRender(hdc, m_rc.left - 43, m_rc.top - 60, m_pAni[0], 4.0f, false, 100);
		else
			m_pImage_left[0]->aniRender(hdc, m_rc.left - 43, m_rc.top - 60, m_pAni_left[0], 4.0f, false, 100);
		break;
	case 2:
		if (m_bIsRight == true)
			m_pImage[0]->aniRender(hdc, m_rc.left - 58, m_rc.top - 84, m_pAni[0], 4.0f, false, 100);
		else
			m_pImage_left[0]->aniRender(hdc, m_rc.left - 58, m_rc.top - 84, m_pAni_left[0], 4.0f, false, 100);
		break;
	case 3:
		if (m_bIsRight == true)
		{
			if (m_eState == st_isIdle_Enemy)
				m_pImage[0]->aniRender(hdc, m_rc.left - 60, m_rc.top - 60, m_pAni[0], 4.0f, false, 100);
			else
				m_pImage[1]->aniRender(hdc, m_rc.left - 55, m_rc.top - 85, m_pAni[1], 4.0f, false, 100);

		}
		else
		{
			if (m_eState == st_isIdle_Enemy)
				m_pImage_left[0]->aniRender(hdc, m_rc.left - 60, m_rc.top - 60, m_pAni_left[0], 4.0f, false, 100);
			else
				m_pImage_left[1]->aniRender(hdc, m_rc.left - 55, m_rc.top - 85, m_pAni_left[1], 4.0f, false, 100);
		}
		break;
	case 4:
		if (m_bIsRight == true)
			m_pImage[0]->aniRender(hdc, m_rc.left - 84, m_rc.top - 110, m_pAni[0], 4.0f, false, 100);
		else
			m_pImage_left[0]->aniRender(hdc, m_rc.left - 84, m_rc.top - 110, m_pAni_left[0], 4.0f, false, 100);
		break;
	case 5:
		if (m_bIsRight == true)
			m_pImage[0]->aniRender(hdc, m_rc.left - 40, m_rc.top - 60, m_pAni[0], 4.0f, false, 100);
		else
			m_pImage_left[0]->aniRender(hdc, m_rc.left - 40, m_rc.top - 60, m_pAni_left[0], 4.0f, false, 100);
		break;
	case 6:
		if (m_bIsRight == true)
		{
			if (m_eState == st_isIdle_Enemy)
				m_pImage[0]->aniRender(hdc, m_rc.left - 40, m_rc.top - 43, m_pAni[0], 4.0f, false, 100);
			else
				m_pImage[1]->frameRender(hdc, m_rc.left - 40, m_rc.top - 48, m_nCurrentFrame, 0, 4.0f);

		}
		else
		{
			if (m_eState == st_isIdle_Enemy)
				m_pImage_left[0]->aniRender(hdc, m_rc.left - 40, m_rc.top - 43, m_pAni_left[0], 4.0f, false, 100);
			else
				m_pImage_left[1]->frameRender(hdc, m_rc.left - 40, m_rc.top - 48, m_nCurrentFrame, 0, 4.0f);
		}
		break;
	case 7:
		if (m_bIsRight == true)
			m_pImage[0]->aniRender(hdc, m_rc.left - 36, m_rc.top - 44, m_pAni[0], 4.0f, false, 100);
		else
			m_pImage_left[0]->aniRender(hdc, m_rc.left - 36, m_rc.top - 44, m_pAni_left[0], 4.0f, false, 100);
		break;
	case 8:
		if (m_bIsRight == true)
			m_pImage[0]->aniRender(hdc, m_rc.left - 36, m_rc.top - 45, m_pAni[0], 1.7f, false, 100);
		else
			m_pImage_left[0]->aniRender(hdc, m_rc.left - 36, m_rc.top - 45, m_pAni_left[0], 1.7f, false, 100);
		break;
	case 9:
		if (m_bIsRight == true)
			m_pImage[0]->aniRender(hdc, m_rc.left - 36, m_rc.top - 45, m_pAni[0], 1.7f, false, 100);
		else
			m_pImage_left[0]->aniRender(hdc, m_rc.left - 36, m_rc.top - 45, m_pAni_left[0], 1.7f, false, 100);

		break;
	}

	
}











Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}
