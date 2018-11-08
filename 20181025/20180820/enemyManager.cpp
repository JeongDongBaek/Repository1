#include "stdafx.h"
#include "EnemyManager.h"
#include "Enemy.h"

HRESULT EnemyManager::init(int MaxLimitNumber)
{
	
	m_nMaxLimitNumber = MaxLimitNumber;
	m_vec.reserve(m_nMaxLimitNumber); // Limit

	
	//for (m_iter = m_vec.begin(); m_iter != m_vec.end(); m_iter++) // �߰��� end�� �ٲ�� �ȵȴ�.
	//{
	//	(*m_iter)->init(m_nEnemyNum, StartingX, StartingY);  // ������ �ε� ���� �������� ���� �ʱ�ȭ��Ų��.
	//					   // �ڼ��� �������ڸ� : �����͸� �޸� ������Ų��. ������ ������ ����Ű�� Ŭ���� �������� ������ ��ġ�� �ʴ´�.
	//					   // �׸��� Limit������ ���� ������ �ٽ� �޸� �Ҵ��� �� �� �ִ�.
	//}

	return S_OK;
}

void EnemyManager::setEnemy(int m_nEnemyNum, float StartingX, float StartingY)
{
	for (m_iter = m_vec.begin(); m_iter != m_vec.end(); m_iter++)
	{	
		if (!(*m_iter)->getIsAlive() == true)
		{
			(*m_iter)->setEnemyNumber(m_nEnemyNum);
			(*m_iter)->setX(StartingX);
			(*m_iter)->setY(StartingY);
			(*m_iter)->init();
			return;
		}
		

	}


	if (m_nMaxLimitNumber < m_vec.size()) return;

	Enemy* pEnemy;
	pEnemy = new Enemy;

	pEnemy->setEnemyNumber(m_nEnemyNum);
	pEnemy->setX(StartingX);
	pEnemy->setY(StartingY);
	pEnemy->init();

	m_vec.push_back(pEnemy);
}

void EnemyManager::release()
{

	for (m_iter = m_vec.begin(); m_iter != m_vec.end(); m_iter++) // �߰��� end�� �ٲ�� �ȵȴ�.
	{
		delete (*m_iter);  // ������ �ε� ���� �������� ���� �ʱ�ȭ��Ų��.
	}
	m_vec.clear(); // ������ �ε� ���ҵ��� ���� �ʱ�ȭ��Ų��.
	
}

void EnemyManager::update()
{
	if (g_saveData.gGamePause) return;

	for (m_iter = m_vec.begin(); m_iter != m_vec.end(); m_iter++)
	{
		if((*m_iter)->getIsAlive() == true )
			(*m_iter)->update();
	}

}

void EnemyManager::render(HDC hdc)
{

	for (m_iter = m_vec.begin(); m_iter != m_vec.end(); m_iter++)
	{
		if ((*m_iter)->getIsAlive() == true)
			(*m_iter)->render(hdc);
	}
}

EnemyManager::EnemyManager()
{
}


EnemyManager::~EnemyManager()
{
}
