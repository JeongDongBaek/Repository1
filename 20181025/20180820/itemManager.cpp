#include "stdafx.h"
#include "itemManager.h"


HRESULT itemManager::init(int vecMaxSize)
{
	m_vecItem.reserve(vecMaxSize);

	m_vecItemList = TXTDATA->txtLoad("ItemList.txt");

	m_itemMax = atoi(m_vecItemList[0].c_str());
	for (int i = 0; i < m_itemMax; i++) // 아이템의 전체 개수 파악
	{
		int temp = (i * 26) + 1;
		m_tItemInfo[i].tItemNumber = atoi(m_vecItemList[temp++].c_str());
		m_tItemInfo[i].tItemGrade = atoi(m_vecItemList[temp++].c_str());
		m_tItemInfo[i].tImageCurrX = atoi(m_vecItemList[temp++].c_str());
		m_tItemInfo[i].tImageCurrY = atoi(m_vecItemList[temp++].c_str());
		m_tItemInfo[i].tItemName = m_vecItemList[temp++].c_str();
		m_tItemInfo[i].tItemTxt = m_vecItemList[temp++].c_str();
		m_tItemInfo[i].tItemOption = m_vecItemList[temp++].c_str();
		m_tItemInfo[i].tBulletType = atoi(m_vecItemList[temp++].c_str());


		m_tItemInfo[i].tBulletSetNum = atoi(m_vecItemList[temp++].c_str());
		m_tItemInfo[i].tRange = atof(m_vecItemList[temp++].c_str());
		m_tItemInfo[i].tBulletScale = atof(m_vecItemList[temp++].c_str());
		m_tItemInfo[i].tDmage = atof(m_vecItemList[temp++].c_str());
		m_tItemInfo[i].tKnokBack = atof(m_vecItemList[temp++].c_str());
		m_tItemInfo[i].tMoveSpeed = atof(m_vecItemList[temp++].c_str());
		m_tItemInfo[i].tBulletBoom = atoi(m_vecItemList[temp++].c_str());

		m_tItemInfo[i].tBoomType = atoi(m_vecItemList[temp++].c_str());
		m_tItemInfo[i].tShootType = atoi(m_vecItemList[temp++].c_str());
		m_tItemInfo[i].tMasterType = atoi(m_vecItemList[temp++].c_str());
		m_tItemInfo[i].tMoveActType = atoi(m_vecItemList[temp++].c_str());
		m_tItemInfo[i].tMoveType = atoi(m_vecItemList[temp++].c_str());
		m_tItemInfo[i].tImageType = atoi(m_vecItemList[temp++].c_str());
		m_tItemInfo[i].tPlayerSpeed = atof(m_vecItemList[temp++].c_str());
		m_tItemInfo[i].tBulletDelayCountMax = atoi(m_vecItemList[temp++].c_str());
		m_tItemInfo[i].tCrossHairScaleMax = atof(m_vecItemList[temp++].c_str());
		m_tItemInfo[i].tPlayerHpMax = atoi(m_vecItemList[temp++].c_str());
		m_tItemInfo[i].tPlayerScale = atof(m_vecItemList[temp++].c_str());

	}

	return S_OK;
}

void itemManager::release()
{
	for (m_iter = m_vecItem.begin(); m_iter != m_vecItem.end(); m_iter++)
	{
		(*m_iter)->release();
	}
	m_vecItem.clear();
}

void itemManager::update()
{
	if (g_saveData.gGamePause) return;

	for (m_iter = m_vecItem.begin(); m_iter != m_vecItem.end(); m_iter++)
	{
		if ((*m_iter)->getIsAlive())
		{
			(*m_iter)->update();
		}
	}
}

void itemManager::render(HDC hdc)
{
	for (m_iter = m_vecItem.begin(); m_iter != m_vecItem.end(); m_iter++)
	{
		if ((*m_iter)->getIsAlive())
		{
			(*m_iter)->render(hdc);
		}
	}
}

void itemManager::itemDrop(const char * imageName, int itemNum, tagItemInfo itemInfo, effectManager * pEffMag)
{
	// 아이템에 따른 정보 갱신(초기화)
	itemNum--;
	itemInfo.tBulletType = m_tItemInfo[itemNum].tBulletType;
	itemInfo.tItemNumber = m_tItemInfo[itemNum].tItemNumber;
	itemInfo.tItemGrade = m_tItemInfo[itemNum].tItemGrade;
	itemInfo.tImageCurrX = m_tItemInfo[itemNum].tImageCurrX;
	itemInfo.tImageCurrY = m_tItemInfo[itemNum].tImageCurrY;
	itemInfo.tItemName = m_tItemInfo[itemNum].tItemName;
	itemInfo.tItemTxt = m_tItemInfo[itemNum].tItemTxt;
	itemInfo.tItemOption = m_tItemInfo[itemNum].tItemOption;

	// 아이템에 따른 옵션 갱신(초기화)
	itemInfo.tBulletSetNum = m_tItemInfo[itemNum].tBulletSetNum;
	itemInfo.tRange = m_tItemInfo[itemNum].tRange;

	itemInfo.tBulletScale = m_tItemInfo[itemNum].tBulletScale;
	itemInfo.tDmage = m_tItemInfo[itemNum].tDmage;
	itemInfo.tKnokBack = m_tItemInfo[itemNum].tKnokBack;
	itemInfo.tMoveSpeed = m_tItemInfo[itemNum].tMoveSpeed;
	itemInfo.tBulletBoom = m_tItemInfo[itemNum].tBulletBoom;
	itemInfo.tBoomType = m_tItemInfo[itemNum].tBoomType;
	itemInfo.tShootType = m_tItemInfo[itemNum].tShootType;
	itemInfo.tMasterType = m_tItemInfo[itemNum].tMasterType;
	itemInfo.tMoveActType = m_tItemInfo[itemNum].tMoveActType;
	itemInfo.tMoveType = m_tItemInfo[itemNum].tMoveType;
	itemInfo.tImageType = m_tItemInfo[itemNum].tImageType;

	itemInfo.tPlayerSpeed = m_tItemInfo[itemNum].tPlayerSpeed;
	itemInfo.tBulletDelayCountMax = m_tItemInfo[itemNum].tBulletDelayCountMax;
	itemInfo.tCrossHairScaleMax = m_tItemInfo[itemNum].tCrossHairScaleMax;
	itemInfo.tPlayerHpMax = m_tItemInfo[itemNum].tPlayerHpMax;
	itemInfo.tPlayerScale = m_tItemInfo[itemNum].tPlayerScale;

	for (m_iter = m_vecItem.begin(); m_iter != m_vecItem.end(); m_iter++)
	{
		if (!(*m_iter)->getIsAlive()) // 죽어있으면 재활용
		{
			(*m_iter)->init(imageName, itemInfo, pEffMag);
			return;
		}
	}

	item * pItem = new item;
	pItem->init(imageName, itemInfo, pEffMag);

	m_vecItem.push_back((pItem));
	return;
}

void itemManager::itemGet(const char * imageName, tagItemInfo itemInfo)
{
	for (m_iter = m_vecItem.begin(); m_iter != m_vecItem.end(); m_iter++)
	{
		if (!(*m_iter)->getIsAlive()) // 죽어있으면 재활용
		{
			(*m_iter)->init(imageName, itemInfo, NULL);

			return;
		}
	}
}

itemManager::itemManager()
{
}


itemManager::~itemManager()
{
}
