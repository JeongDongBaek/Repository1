#include "stdafx.h"
#include "monster.h"
#include "monsterManger.h"


HRESULT monsterManger::init(int vecMaxSize)
{
	m_vecMonster.reserve(vecMaxSize);
	m_Monsterlist = TXTDATA->txtLoad("Monsterlist.txt");

	m_MaxMonster = atoi(m_Monsterlist[0].c_str());
	for (int i = 0; i < m_MaxMonster; i++)
	{
		int temp = (i * 12) + 1;
		m_MonsterInfo[i].tMonsterNumber = atoi(m_Monsterlist[temp++].c_str());
		m_MonsterInfo[i].tHp = atof(m_Monsterlist[temp++].c_str());
		m_MonsterInfo[i].nScore = atoi(m_Monsterlist[temp++].c_str());
		m_MonsterInfo[i].tminGaugeSub = atof(m_Monsterlist[temp++].c_str());
		m_MonsterInfo[i].tminGaugeInfo = atoi(m_Monsterlist[temp++].c_str());
		m_MonsterInfo[i].tmaxGaugeSub = atof(m_Monsterlist[temp++].c_str());
		m_MonsterInfo[i].tmaxGaugeInfo = atoi(m_Monsterlist[temp++].c_str());
		m_MonsterInfo[i].tIslife = atoi(m_Monsterlist[temp++].c_str());
		m_MonsterInfo[i].tMoveType = atoi(m_Monsterlist[temp++].c_str());

		m_MonsterInfo[i].tMoveSpeed = atof(m_Monsterlist[temp++].c_str());
		m_MonsterInfo[i].tUnKnokBack = atof(m_Monsterlist[temp++].c_str());
		m_MonsterInfo[i].tFireDelay = atoi(m_Monsterlist[temp++].c_str());
	}


	return S_OK;
}

void monsterManger::release()
{
	for (m_iter = m_vecMonster.begin(); m_iter != m_vecMonster.end(); m_iter++)
	{
		delete (*m_iter);
	}
	m_vecMonster.clear();
}

void monsterManger::update()
{
	if (g_saveData.gGamePause) return;

	for (m_iter = m_vecMonster.begin(); m_iter != m_vecMonster.end(); m_iter++)
	{
		(*m_iter)->update();
	}
}

void monsterManger::Regeneration(const char*strKey, int monNumber, tagMonInfo moninfo, bulletManger* bulletInfo, PlayerCharacter* playerInfo, tagBulletInfo tbulletInfo)
{
	monNumber--;
	moninfo.tMonsterNumber = m_MonsterInfo[monNumber].tMonsterNumber;
	moninfo.tHp = m_MonsterInfo[monNumber].tHp;
	moninfo.nScore = m_MonsterInfo[monNumber].nScore;
	moninfo.tminGaugeSub = m_MonsterInfo[monNumber].tminGaugeSub;
	moninfo.tminGaugeInfo = m_MonsterInfo[monNumber].tminGaugeInfo;
	moninfo.tmaxGaugeSub = m_MonsterInfo[monNumber].tmaxGaugeSub;
	moninfo.tmaxGaugeInfo = m_MonsterInfo[monNumber].tmaxGaugeInfo;
	moninfo.tIslife = m_MonsterInfo[monNumber].tIslife;
	moninfo.tMoveType = m_MonsterInfo[monNumber].tMoveType;

	moninfo.tMoveSpeed = m_MonsterInfo[monNumber].tMoveSpeed;
	moninfo.tUnKnokBack = m_MonsterInfo[monNumber].tUnKnokBack;
	moninfo.tFireDelay = m_MonsterInfo[monNumber].tFireDelay;

	for (m_iter = m_vecMonster.begin(); m_iter != m_vecMonster.end(); m_iter++)
	{
		if (!(*m_iter)->getMonInfo().tIsAlive)
		{
			(*m_iter)->init(strKey, monNumber, moninfo, bulletInfo, playerInfo, m_pEffMag, tbulletInfo);
			return;
		}
	}
	monster * pMonster = new monster;

	pMonster->init(strKey, monNumber, moninfo, bulletInfo, playerInfo, m_pEffMag, tbulletInfo);
	m_vecMonster.push_back((pMonster));
	return;
}

void monsterManger::render(HDC hdc)
{
	for (m_iter = m_vecMonster.begin(); m_iter != m_vecMonster.end(); m_iter++)
	{
		if ((*m_iter)->getMonInfo().tIsAlive)
		{
			(*m_iter)->render(hdc);
		}
	}

}

monsterManger::monsterManger()
{
}


monsterManger::~monsterManger()
{
}
