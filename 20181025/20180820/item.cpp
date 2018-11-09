#include "stdafx.h"
#include "item.h"


HRESULT item::init(float x, float y, tagItemInfor itemNumber, bool persisting)
{
	m_bIsAlive = true;
	m_fX = x;
	m_fY = y;
	m_bItemPersisting = persisting;
	m_nAlphaBlendNum = 22; // 높을수록 투명
	m_fItemfloppingNum = 0;
	m_nTwinkleNum = 0;
	m_nCountTemp = 0;
	m_bItemfloppingUpDown = false; // 트루면 위로
	m_bAlpahBlendUpDown = false;
	m_pImg_item = IMAGEMANAGER->findImage("item");
	m_tItemInfor = itemNumber;
	m_rc = RectMake(m_fX - SCROLL->GetX(), m_fY - SCROLL->GetY(), ITEM_WIDTH, ITEM_HEIGHT);

	return S_OK;
}

void item::release()
{
}

void item::update()
{
	if (!m_bIsAlive == true) return;

	m_rc = RectMake(m_fX - SCROLL->GetX(), m_fY - SCROLL->GetY(), ITEM_WIDTH, ITEM_HEIGHT);
	flopping();
	twinkle();

}





void item::flopping()
{
	if (m_fItemfloppingNum >= 5.0f)
		m_bItemfloppingUpDown = false;
	if (m_fItemfloppingNum <= -5.0f)
		m_bItemfloppingUpDown = true;

	if (m_bItemfloppingUpDown == true)
		m_fItemfloppingNum += 0.2f;
	else
		m_fItemfloppingNum -= 0.2f;

}

void item::twinkle()
{
	if (! (m_bItemPersisting == false)) return;
 
	m_nCountTemp++;
	if (m_nCountTemp >= 250 )
	{
		m_nCountTemp = 0;
		m_nTwinkleNum += 40;
	}
	if (m_nTwinkleNum > 160)
		m_bIsAlive = false;

	if (m_nAlphaBlendNum >= 80 + m_nTwinkleNum)
		m_bAlpahBlendUpDown = false;
	if (m_nAlphaBlendNum <= 25 + m_nTwinkleNum)
		m_bAlpahBlendUpDown = true;

	if (m_bAlpahBlendUpDown == true)
	{
		if (m_nTwinkleNum >= 80)
			m_nAlphaBlendNum += 3;
		else
			m_nAlphaBlendNum += 1;
	}
	else
	{
		if (m_nTwinkleNum >= 80)
			m_nAlphaBlendNum -= 3;
		else
			m_nAlphaBlendNum -= 1;
	}

}

void item::render(HDC hdc)
{
	if (!m_bIsAlive == true) return;
	
	if (g_saveData.gIsRectangleOn == true)
	{
		Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);
	}

	m_pImg_item->frameAlphaRender(hdc, m_rc.left, (m_rc.top-8) + m_fItemfloppingNum, m_tItemInfor.m_nItemFrameX, m_tItemInfor.m_nItemFrameY, 1.0f, m_nAlphaBlendNum);
}

item::item()
{
}


item::~item()
{
}
