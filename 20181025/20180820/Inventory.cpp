#include "stdafx.h"
#include "Inventory.h"
#include "item.h"

HRESULT Inventory::init(int LimitItem)
{
	m_nLimitItem = LimitItem;

	m_nQuantity = 0;
	m_vecItemList = TXTDATA->txtLoad("ItemList.txt");

	m_nNumberofKindItem = atoi(m_vecItemList[0].c_str());
	for (int i = 0; i < m_nNumberofKindItem; ++i)
	{
		int temp = (i * 18) + 1;
		m_tItem[i].m_nItemNumber = atoi(m_vecItemList[temp++].c_str());
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
		m_tItem[i].m_nCharacterChange = atoi(m_vecItemList[temp++].c_str());
		m_tItem[i].m_bFireball = atoi(m_vecItemList[temp++].c_str());
		m_tItem[i].m_fHP = atof(m_vecItemList[temp++].c_str());
		m_tItem[i].m_fMana = atof(m_vecItemList[temp++].c_str());
		m_tItem[i].m_fStamina = atof(m_vecItemList[temp++].c_str());


	}



	m_vec.reserve(m_nLimitItem);

	return S_OK;
}

void Inventory::release()
{
	for (m_iter = m_vec.begin(); m_iter != m_vec.end(); m_iter++) // 중간에 end가 바뀌면 안된다.
	{
		delete (*m_iter);
	}
	m_vec.clear();

}

void Inventory::update()
{
	for (m_iter = m_vec.begin(); m_iter != m_vec.end(); m_iter++) // 중간에 end가 바뀌면 안된다.
	{
		if ((*m_iter)->getIsAlive() == true)
			(*m_iter)->update();
	}

}

void Inventory::AddItem(tagItemInfor ItemNumber)
{
	if (ItemNumber.m_nItemNumber >= 12) return;

	
	for (m_iter = m_vec.begin(); m_iter != m_vec.end(); m_iter++) // 중간에 end가 바뀌면 안된다.
	{
		if ((*m_iter)->getIsAlive() == false)
		{
			if (m_nQuantity <= 5)
				(*m_iter)->Inven_init(360 + (m_nQuantity * 100), 500 , ItemNumber, true);
			else
				(*m_iter)->Inven_init(360 + (m_nQuantity * 100)- 500, 600, ItemNumber, true);

			return;
		}
		
	}

	if (m_nLimitItem < m_vec.size()) return;

	item * m_pItem = new item;

	if(m_nQuantity <= 5)
		m_pItem->Inven_init(360 + (m_nQuantity * 100), 500, ItemNumber, true);
	else
		m_pItem->Inven_init(360 + (m_nQuantity * 100) - 600, 600, ItemNumber, true);


	m_vec.push_back(m_pItem);

}

void Inventory::render(HDC hdc)
{
	for (m_iter = m_vec.begin(); m_iter != m_vec.end(); ++m_iter)
	{
		if ((*m_iter)->getIsAlive() == true)
		{
			(*m_iter)->Inven_render(hdc);
		}

	}

}

Inventory::Inventory()
{
}


Inventory::~Inventory()
{
}
