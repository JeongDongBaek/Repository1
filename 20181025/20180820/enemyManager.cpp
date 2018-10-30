#include "stdafx.h"
#include "EnemyManager.h"
#include "Enemy.h"

HRESULT EnemyManager::init(int m_nMaxLimitNumber)
{
	m_vec.reserve(m_nMaxLimitNumber); // Limit
	

	return S_OK;
}

void EnemyManager::release()
{
	if (g_saveData.gGamePause) false;

	for (m_iter = m_vec.begin(); m_iter != m_vec.end(); m_iter++) // �߰��� end�� �ٲ�� �ȵȴ�.
	{
		//(*m_iter)->release();
		delete (*m_iter);  // ������ �ε� ���� �������� ���� �ʱ�ȭ��Ų��.
		// �ڼ��� �������ڸ� : �����͸� �޸� ������Ų��. ������ ������ ����Ű�� Ŭ���� �������� ������ ��ġ�� �ʴ´�.
		// �׸��� Limit������ ���� ������ �ٽ� �޸� �Ҵ��� �� �� �ִ�.
	}
	m_vec.clear(); // ������ �ε� ���ҵ��� ���� �ʱ�ȭ��Ų��.
	
}

void EnemyManager::update()
{
	if (g_saveData.gGamePause) false;

	for (m_iter = m_vec.begin(); m_iter != m_vec.end(); m_iter++)
	{
		if((*m_iter)->getIsAlive() == true )
			(*m_iter)->update();
	}
}

void EnemyManager::render(HDC hdc)
{
	if (g_saveData.gGamePause) false;

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
