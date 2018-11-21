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
	m_pImg_Text = IMAGEMANAGER->findImage("text2");
	m_tItemInfor = itemNumber;
	m_rc = RectMake(m_fX - SCROLL->GetX(), m_fY - SCROLL->GetY(), ITEM_WIDTH, ITEM_HEIGHT);

	return S_OK;
}

void item::Inven_init(float x, float y, tagItemInfor itemNumber, bool persisting)
{
	m_bIsAlive = true;
	Inven_m_fX = x;
	Inven_m_fY = y;
	m_bItemPersisting = persisting;
	m_nAlphaBlendNum = 22; // 높을수록 투명
	m_fItemfloppingNum = 0;
	m_nTwinkleNum = 0;
	m_nCountTemp = 0;
	m_bItemfloppingUpDown = false; // 트루면 위로
	m_bAlpahBlendUpDown = false;
	m_pImg_item = IMAGEMANAGER->findImage("item");
	m_pImg_Text = IMAGEMANAGER->findImage("text2");
	m_tItemInfor = itemNumber;
	m_rc = RectMake(Inven_m_fX, Inven_m_fY , ITEM_WIDTH, ITEM_HEIGHT);

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

void item::Inven_update()
{
	if (!m_bIsAlive == true) return;

	m_rc = RectMake(Inven_m_fX, Inven_m_fY, ITEM_WIDTH, ITEM_HEIGHT);
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
	if (m_nCountTemp >= 280 )
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

	if (PtInRect(&m_rc, g_ptMouse))
	{
		m_pImg_Text->render(hdc, m_rc.left - 120, m_rc.top + 15);

		char SzText2[64];
		RECT temp_rc = RectMake(
			m_rc.left - 97,
			m_rc.top + 78,
			m_rc.right - 97,
			m_rc.bottom + 78
		);
		
		MY_UTIL::FontOption(hdc, 29, 0);
		SetTextColor(hdc, RGB(240, 245, 225));
		sprintf_s(SzText2, m_tItemInfor.m_sItemName.c_str());
		DrawText(hdc, SzText2, strlen(SzText2), &temp_rc, DT_WORDBREAK);

		temp_rc = RectMake(
			m_rc.left - 110,
			m_rc.top + 113,
			m_rc.right - 110,
			m_rc.bottom + 113
		);
		MY_UTIL::FontOption(hdc, 25, 0);
		SetTextColor(hdc, RGB(220, 244, 221));
		sprintf_s(SzText2, m_tItemInfor.m_sItemExpl1.c_str());
		DrawText(hdc, SzText2, strlen(SzText2), &temp_rc, DT_WORDBREAK);

		temp_rc = RectMake(
			m_rc.left - 110,
			m_rc.top + 155,
			m_rc.right - 110,
			m_rc.bottom + 155
		);
		sprintf_s(SzText2, m_tItemInfor.m_sItemExpl2.c_str());
		DrawText(hdc, SzText2, strlen(SzText2), &temp_rc, DT_WORDBREAK);
	}

	m_pImg_item->frameAlphaRender(hdc, m_rc.left, (m_rc.top-8) + m_fItemfloppingNum, m_tItemInfor.m_nItemFrameX, m_tItemInfor.m_nItemFrameY, 1.0f, m_nAlphaBlendNum);
}

void item::Inven_render(HDC hdc)
{
	if (!m_bIsAlive == true) return;

	m_pImg_item->frameAlphaRender(hdc, Inven_m_fX, Inven_m_fY + m_fItemfloppingNum, m_tItemInfor.m_nItemFrameX, m_tItemInfor.m_nItemFrameY, 1.0f, m_nAlphaBlendNum);

}

item::item()
{
}


item::~item()
{
}
