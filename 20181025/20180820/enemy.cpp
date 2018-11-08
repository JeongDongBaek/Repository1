#include "stdafx.h"
#include "Enemy.h"
#include "animation.h"

HRESULT Enemy::init()
{
	/*if (EnemyNum >= 8) return;
*/
	m_pImage[1] = NULL;
	m_pAni[1] = NULL;
	m_bIsAlive = true;
	//m_nEnemyNum = EnemyNum;
	//m_fX = X;
	//m_fY = Y;
	m_fWeight = 1.0f;
	m_eState = st_isIdle_Enemy;

	switch (m_nEnemyNum)
	{
	case 0:
		m_pImage[0] = IMAGEMANAGER->findImage("ant_idle");
		m_fHP = 2.0f;
		m_fDamage = 1.0f;
		m_fSpeed = 1.3f;
		m_ePattern = Pattern_moveTile;
		m_rc = RectMake(m_fX - SCROLL->GetX(), m_fY - SCROLL->GetY(), ANT_WIDTH, ANT_HEIGHT);
		break;
	case 1:
		m_pImage[0] = IMAGEMANAGER->findImage("bee_idle");
		m_fHP = 5.0f;
		m_fDamage = 2.0f;
		m_fSpeed = 2.0f;
		m_ePattern = Pattern_moveTile;
		m_rc = RectMake(m_fX - SCROLL->GetX(), m_fY - SCROLL->GetY(), BEE_WIDTH, BEE_HEIGHT);
		break;
	case 2:
		m_pImage[0] = IMAGEMANAGER->findImage("crocodile_idle");
		m_fHP = 6.0f;
		m_fDamage = 3.0f;
		m_fSpeed = 2.4f;
		m_ePattern = Pattern_moveFly;
		m_rc = RectMake(m_fX - SCROLL->GetX(), m_fY - SCROLL->GetY(), CROCOBIRD_WIDTH, CROCOBIRD_HEIGHT);
		break;
	case 3:
		m_pImage[0] = IMAGEMANAGER->findImage("grasshopper_idle");
		m_pImage[1] = IMAGEMANAGER->findImage("grasshopper_jump"); // 그냥 애니메이션
		m_fHP = 3.0f;
		m_fDamage = 1.0f;
		m_fSpeed = 1.7f;
		m_ePattern = Pattern_moveTile;
		m_eState = st_isJump_Enemy;
		m_rc = RectMake(m_fX - SCROLL->GetX(), m_fY - SCROLL->GetY(), GLASS_WIDTH, GLASS_HEIGHT);
		break;
	case 4:
		m_pImage[0] = IMAGEMANAGER->findImage("monster_plant_idle");
		m_pImage[1] = IMAGEMANAGER->findImage("monster_plant_attack");
		m_fHP = 4.0f;
		m_fDamage = 1.0f;
		m_fSpeed = 0.0f;
		m_ePattern = Pattern_Stop;
		m_rc = RectMake(m_fX - SCROLL->GetX(), m_fY - SCROLL->GetY(), PLANT_WIDTH, PLANT_HEIGHT);
		break;
	case 5:
		m_pImage[0] = IMAGEMANAGER->findImage("eagle_idle");
		m_fHP = 10.0f;
		m_fDamage = 4.0f;
		m_fSpeed = 3.5f;
		m_ePattern = Pattern_moveFly;
		m_rc = RectMake(m_fX - SCROLL->GetX(), m_fY - SCROLL->GetY(), EAGLE_WIDTH, EAGLE_HEIGHT);

		break;
	case 6:
		m_pImage[0] = IMAGEMANAGER->findImage("frog_idle");
		m_pImage[1] = IMAGEMANAGER->findImage("frog_jump"); 
		m_fHP = 5.0f;
		m_fDamage = 3.0f;
		m_fSpeed = 1.5f;
		m_ePattern = Pattern_moveTile;
		//m_eState = st_isFall_Enemy;
		m_rc = RectMake(m_fX - SCROLL->GetX(), m_fY - SCROLL->GetY(), FROG_WIDTH, FROG_HEIGHT);

		break;
	case 7:
		m_pImage[0] = IMAGEMANAGER->findImage("oposum_idle");
		m_fHP = 9.0f;
		m_fDamage = 3.0f;
		m_fSpeed = 2.1f;
		m_ePattern = Pattern_moveTile;
		m_rc = RectMake(m_fX - SCROLL->GetX(), m_fY - SCROLL->GetY(), OPOSUM_WIDTH, OPOSUM_HEIGHT);

		break;
	}




	
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



	return S_OK;
}

void Enemy::update()
{
	if (!m_bIsAlive == true) return;

	switch (m_nEnemyNum)
	{
	case 0:
		m_rc = RectMake(m_fX - SCROLL->GetX(), m_fY - SCROLL->GetY(), ANT_WIDTH, ANT_HEIGHT);
		break;
	case 1:
		m_rc = RectMake(m_fX - SCROLL->GetX(), m_fY - SCROLL->GetY(), BEE_WIDTH, BEE_HEIGHT);
		break;
	case 2:
		m_rc = RectMake(m_fX - SCROLL->GetX(), m_fY - SCROLL->GetY(), CROCOBIRD_WIDTH, CROCOBIRD_HEIGHT);
		break;
	case 3:
		m_rc = RectMake(m_fX - SCROLL->GetX(), m_fY - SCROLL->GetY(), GLASS_WIDTH, GLASS_HEIGHT);

		break;
	case 4:
		m_rc = RectMake(m_fX - SCROLL->GetX(), m_fY - SCROLL->GetY(), PLANT_WIDTH, PLANT_HEIGHT);
		break;
	case 5:
		m_rc = RectMake(m_fX - SCROLL->GetX(), m_fY - SCROLL->GetY(), EAGLE_WIDTH, EAGLE_HEIGHT);
		break;
	case 6:
		m_rc = RectMake(m_fX - SCROLL->GetX(), m_fY - SCROLL->GetY(), FROG_WIDTH, FROG_HEIGHT);

		if (m_eState == st_isJump_Enemy)
			m_pImage[1]->setFrameX(0);
		else if (m_eState == st_isFall_Enemy)
			m_pImage[1]->setFrameX(1);

		break;
	case 7:
		m_rc = RectMake(m_fX - SCROLL->GetX(), m_fY - SCROLL->GetY(), OPOSUM_WIDTH, OPOSUM_HEIGHT);
		break;
	}

	m_pAni[0]->frameUpdate(TIMEMANAGER->getElapsedTime());
	if(m_nEnemyNum == 3 || m_nEnemyNum == 4 ) 
		m_pAni[1]->frameUpdate(TIMEMANAGER->getElapsedTime());
	
} 

void Enemy::release()
{
}

void Enemy::render(HDC hdc)
{

	switch (m_nEnemyNum)
	{
	case 0:

		m_pImage[0]->aniRender(hdc, m_rc.left - 48, m_rc.top - 60, m_pAni[0], 4.0f, false ,100);
		break;
	case 1:
		m_pImage[0]->aniRender(hdc, m_rc.left - 43, m_rc.top - 60, m_pAni[0], 4.0f, false, 100);
		break;
	case 2:
		m_pImage[0]->aniRender(hdc, m_rc.left - 58, m_rc.top - 84, m_pAni[0], 4.0f, false, 100);
		break;
	case 3:
		if (m_eState == st_isIdle_Enemy)
			m_pImage[0]->aniRender(hdc, m_rc.left - 60, m_rc.top - 60, m_pAni[0], 4.0f, false, 100);
		else
			m_pImage[1]->aniRender(hdc, m_rc.left - 55, m_rc.top - 85, m_pAni[1], 4.0f, false, 100);

		break;
	case 4:
		m_pImage[0]->aniRender(hdc, m_rc.left - 84, m_rc.top - 110, m_pAni[0], 4.0f, false, 100);
		break;
	case 5:
		m_pImage[0]->aniRender(hdc, m_rc.left - 40, m_rc.top - 60, m_pAni[0], 4.0f, false, 100);
		break;
	case 6:
		if (m_eState == st_isIdle_Enemy)
			m_pImage[0]->aniRender(hdc, m_rc.left - 40, m_rc.top - 43, m_pAni[0], 4.0f, false, 100);
		else
			m_pImage[1]->render(hdc, m_rc.left - 40, m_rc.top - 48, 4.0f);
		break;
	case 7:
		m_pImage[0]->aniRender(hdc, m_rc.left - 36, m_rc.top - 44, m_pAni[0], 4.0f, false, 100);
		break;
	}
}











Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}
