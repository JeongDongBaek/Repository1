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

	for (m_iter = m_vec.begin(); m_iter != m_vec.end(); m_iter++) // 중간에 end가 바뀌면 안된다.
	{
		//(*m_iter)->release();
		delete (*m_iter);  // 공간은 두되 원소 개개인의 값을 초기화시킨다.
		// 자세히 설명하자면 : 포인터를 메모리 해제시킨다. 하지만 실제로 가리키는 클래스 변수에는 영향을 미치지 않는다.
		// 그리고 Limit변수에 따라 언제나 다시 메모리 할당을 할 수 있다.
	}
	m_vec.clear(); // 공간은 두되 원소들의 값을 초기화시킨다.
	
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
