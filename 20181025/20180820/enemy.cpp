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
	m_nEnemyNum = EnemyNumber;

	switch (m_nEnemyNum)
	{
	case 0:
		m_pImage = IMAGEMANAGER->findImage("ant_idle");
		m_pAni = new animation;
		m_pAni->init(m_pImage->getWidth(), m_pImage->getHeight(), m_pImage->getFrameWidth(), m_pImage->getFrameHeight());
		
		break;
	case 1:
		m_pImage = IMAGEMANAGER->findImage("bee_idle");
		break;
	case 2:
		m_pImage = IMAGEMANAGER->findImage("crocodile_idle");
		break;
	case 3:
		m_pImage = IMAGEMANAGER->findImage("grasshopper_idle");
		break;
	case 4:
		m_pImage = IMAGEMANAGER->findImage("monster_plant_idle");
		break;
	case 5:
		m_pImage = IMAGEMANAGER->findImage("eagle_idle");
		break;
	case 6:
		m_pImage = IMAGEMANAGER->findImage("frog_idle");
		break;
	case 7:
		m_pImage = IMAGEMANAGER->findImage("oposum_idle");
		break;
	}

	return S_OK;
}








Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}
