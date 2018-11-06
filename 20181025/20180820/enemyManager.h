#pragma once
#include <vector>
#include "Enemy.h"
#include "singletonBase.h"

class animation;
class Enemy;
class effectManager;

class EnemyManager : public singletonBase<EnemyManager>
{
private:
	int m_nMaxLimitNumber;

	effectManager * m_pEffectMgr;

	std::vector<std::string> m_vecEnemyList;

	std::vector<Enemy*>				m_vec;
	std::vector<Enemy*>::iterator	m_iter;

public:
	HRESULT init(int m_nMaxLimitNumber);
	void setEnemy(int m_nEnemyNum, float StartingX, float StartingY);
	
	void release();
	void update();
	void render(HDC hdc);

	int getIter() { return m_vec.size(); }
	inline std::vector<Enemy*> getVec()
	{
		return m_vec;
	}

	void SetEffectPoint(effectManager * effect) { m_pEffectMgr = effect; }



	EnemyManager();
	~EnemyManager();
};

