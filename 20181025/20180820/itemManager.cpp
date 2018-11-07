#include "stdafx.h"
#include "ItemManager.h"


HRESULT ItemManager::init(int MaxLimitNumber)
{
	m_nMaxLimitNumber = MaxLimitNumber;
	m_vecItem.reserve(m_nMaxLimitNumber);

	m_vecItemList = TXTDATA->txtLoad("ItemList.txt");

	m_nNumberofKindItem = atoi(m_vecItemList[0].c_str());
	for (int i = 0; i < m_nNumberofKindItem; ++i)
	{
		int temp = (i * 18) + 1;
		m_tItem[i].m_sItemName = atoi(m_vecItemList[temp++].c_str());
		m_tItem[i].m_nItemDivision = atoi(m_vecItemList[temp++].c_str());
		m_tItem[i].m_nItemFrameX = atoi(m_vecItemList[temp++].c_str());
		m_tItem[i].m_nItemFrameY = atoi(m_vecItemList[temp++].c_str());
		m_tItem[i].m_sItemName = m_vecItemList[temp++].c_str();
		m_tItem[i].m_sItemExpl1 = m_vecItemList[temp++].c_str();
		m_tItem[i].m_sItemExpl2 = m_vecItemList[temp++].c_str();
		m_tItem[i].m_fMaxHP = atof(m_vecItemList[temp++].c_str());
		m_tItem[i].m_fMaxMana = atof(m_vecItemList[temp++].c_str());
		m_tItem[i].m_fMaxStamina = atof(m_vecItemList[temp++].c_str());
		m_tItem[i].m_fAccuracy = atof(m_vecItemList[temp++].c_str());
		m_tItem[i].m_fSpeed = atof(m_vecItemList[temp++].c_str());
		m_tItem[i].m_fWeight = atof(m_vecItemList[temp++].c_str());
		m_tItem[i].m_fDef = atof(m_vecItemList[temp++].c_str());
		m_tItem[i].m_bCharacterChange = atoi(m_vecItemList[temp++].c_str());
		m_tItem[i].m_bFireball = atoi(m_vecItemList[temp++].c_str());
		m_tItem[i].m_fHP = atof(m_vecItemList[temp++].c_str());
		m_tItem[i].m_fMana = atof(m_vecItemList[temp++].c_str());
		m_tItem[i].m_fStamina = atof(m_vecItemList[temp++].c_str());


	}
	

	return S_OK;
}

void ItemManager::release()
{

	for (m_iter = m_vecItem.begin(); m_iter != m_vecItem.end(); m_iter++) // 중간에 end가 바뀌면 안된다.
	{
		delete (*m_iter);
	}
	m_vecItem.clear();
}

void ItemManager::update()
{
	if (g_saveData.gGamePause) return;

	for (m_iter = m_vecItem.begin(); m_iter != m_vecItem.end(); m_iter++) // 중간에 end가 바뀌면 안된다.
	{
		if((*m_iter)->getIsAlive() == true)
			(*m_iter)->update();
	}
}

void ItemManager::render(HDC hdc)
{

	for (m_iter = m_vecItem.begin(); m_iter != m_vecItem.end(); m_iter++) // 중간에 end가 바뀌면 안된다.
	{
		if ((*m_iter)->getIsAlive() == true)
			(*m_iter)->render(hdc);
	}
}

ItemManager::ItemManager()
{
}


ItemManager::~ItemManager()
{
}
