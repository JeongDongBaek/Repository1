#pragma once
#include <vector>
#include "monster.h"
#include "animation.h"
#include "progressBar.h"

class effectManager;

class monsterManger
{
private:
	std::vector<monster*>				m_vecMonster;
	std::vector<monster*>::iterator		m_iter;

	effectManager * m_pEffMag;
	std::vector<std::string>	m_Monsterlist;

	tagMonInfo m_MonsterInfo[50];
	tagBulletInfo m_BulletInfo[50];
	int m_MaxMonster;

	//animation * m_monsterMove;
	//tagMonInfo m_tMonInfo;
	//image * m_monsterType;
public:

	HRESULT init(int vecMaxSize);
	void release();
	void update();
	void Regeneration(const char*strKey, int monNumber, tagMonInfo moninfo, bulletManger* bulletInfo, PlayerCharacter* playerInfo, tagBulletInfo tbulletInfo);
	void render(HDC hdc);

	int getIter() { return m_vecMonster.size(); }

	inline std::vector<monster*> getVecMons()
	{
		return m_vecMonster;
	}

	void setEffMagPoint(effectManager * effPoint) { m_pEffMag = effPoint; }

	monsterManger();
	~monsterManger();
};

