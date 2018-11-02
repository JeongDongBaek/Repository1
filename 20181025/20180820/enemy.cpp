#include "stdafx.h"
#include "Enemy.h"
#include "animation.h"

HRESULT Enemy::init()
{
	
	return S_OK;
}

void Enemy::update()
{
} 

void Enemy::release()
{
}

void Enemy::render(HDC hdc)
{

}














HRESULT Enemy::Editor_Create(int EnemyNumber)
{
	m_pImage[1] = NULL;
	m_nEnemyNum = EnemyNumber;

	switch (m_nEnemyNum)
	{
	case 0:
		m_pImage[0] = IMAGEMANAGER->findImage("ant_idle");
		break;
	case 1:
		m_pImage[0] = IMAGEMANAGER->findImage("bee_idle");
		break;
	case 2:
		m_pImage[0] = IMAGEMANAGER->findImage("crocodile_idle");
		break;
	case 3:
		m_pImage[0] = IMAGEMANAGER->findImage("grasshopper_idle");

		m_pImage[1] = IMAGEMANAGER->findImage("grasshopper_fly");
		break;
	case 4:
		m_pImage[0] = IMAGEMANAGER->findImage("monster_plant_idle");
		m_pImage[1] = IMAGEMANAGER->findImage("grasshopper_attack");
		break;
	case 5:
		m_pImage[0] = IMAGEMANAGER->findImage("eagle_idle");
		break;
	case 6:
		m_pImage[0] = IMAGEMANAGER->findImage("frog_idle");
		m_pImage[0] = IMAGEMANAGER->findImage("frog_jump");
		break;
	case 7:
		m_pImage[0] = IMAGEMANAGER->findImage("oposum_idle");
		break;
	}
	m_pAni[0] = new animation;
	m_pAni[0]->init(m_pImage[0]->getWidth(), m_pImage[0]->getHeight(), m_pImage[0]->getFrameWidth(), m_pImage[0]->getFrameHeight());
	m_pAni[0]->setDefPlayFrame(false, true);
	m_pAni[0]->setFPS(11);
	m_pAni[0]->start();
	if (m_pImage[1] != NULL)
	{
		m_pAni[1] = new animation;
		m_pAni[1]->init(m_pImage[1]->getWidth(), m_pImage[1]->getHeight(), m_pImage[1]->getFrameWidth(), m_pImage[1]->getFrameHeight());
		m_pAni[1]->setDefPlayFrame(false, true);
		m_pAni[1]->setFPS(11);
		m_pAni[1]->start();
	}


	return S_OK;
}





Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}
