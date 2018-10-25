#include "stdafx.h"
#include "item.h"
#include "animation.h"
#include "effectManager.h"

HRESULT item::init(const char * imageName, tagItemInfo itemInfo, effectManager * pEffItem)
{
	// 최초 초기화
	memset(&m_rc, NULL, sizeof(m_rc));

	// 이미지 초기화
	m_pImg = IMAGEMANAGER->findImage(imageName);
	m_pImgShadow = IMAGEMANAGER->findImage("ItemShadow");
	m_pItemPopupUi = IMAGEMANAGER->findImage("Player_ItemPopupUI");

	// 멤버 초기화
	m_tItemInfo.tScale = itemInfo.tScale;
	m_tItemInfo.tRadius = (m_pImg->getFrameWidth() / 2) * itemInfo.tScale;

	m_tItemInfo.tTimer = itemInfo.tTimer;
	m_tItemInfo.tTimerMax = m_tItemInfo.tTimer;
	m_tItemInfo.tImageCurrX = itemInfo.tImageCurrX;
	m_tItemInfo.tImageCurrY = itemInfo.tImageCurrY;
	m_tItemInfo.tSkillType = itemInfo.tSkillType;

	m_tItemInfo.posX = itemInfo.posX;
	m_tItemInfo.posY = m_fItemIdleY = itemInfo.posY;
	m_tItemInfo.tItemTimerAlpha = 0;

	m_tItemInfo.tBulletType = itemInfo.tBulletType;

	m_tItemInfo.tItemNumber = itemInfo.tItemNumber;
	m_tItemInfo.tItemGrade = itemInfo.tItemGrade;
	m_tItemInfo.tItemName = itemInfo.tItemName;
	m_tItemInfo.tItemTxt = itemInfo.tItemTxt;
	m_tItemInfo.tItemOption = itemInfo.tItemOption;

	m_tItemInfo.tIsGet = itemInfo.tIsGet;
	m_fItemIdleCurrY = m_tItemInfo.posY;

	m_tItemInfo.tBulletSetNum = itemInfo.tBulletSetNum;
	m_tItemInfo.tRange = itemInfo.tRange;

	m_tItemInfo.tBulletScale = itemInfo.tBulletScale;
	m_tItemInfo.tDmage = itemInfo.tDmage;
	m_tItemInfo.tKnokBack = itemInfo.tKnokBack;
	m_tItemInfo.tMoveSpeed = itemInfo.tMoveSpeed;
	m_tItemInfo.tBulletBoom = itemInfo.tBulletBoom;

	m_tItemInfo.tBoomType = itemInfo.tBoomType;
	m_tItemInfo.tShootType = itemInfo.tShootType;
	m_tItemInfo.tMasterType = itemInfo.tMasterType;
	m_tItemInfo.tMoveActType = itemInfo.tMoveActType;
	m_tItemInfo.tMoveType = itemInfo.tMoveType;
	m_tItemInfo.tImageType = itemInfo.tImageType;

	m_tItemInfo.tPlayerSpeed = itemInfo.tPlayerSpeed;
	m_tItemInfo.tBulletDelayCountMax = itemInfo.tBulletDelayCountMax;
	m_tItemInfo.tCrossHairScaleMax = itemInfo.tCrossHairScaleMax;
	m_tItemInfo.tPlayerHpMax = itemInfo.tPlayerHpMax;
	m_tItemInfo.tPlayerScale = itemInfo.tPlayerScale;

	m_isItemIdle = true;
	m_ItemAlphaNum = 0;
	// RECT 초기화 (이미지 프레임 크기)
	m_rc = RectMakeCenter(m_tItemInfo.posX - SCROLL->GetX(), m_tItemInfo.posY - SCROLL->GetY(), m_pImg->getFrameWidth(), m_pImg->getFrameHeight());

	m_isAlive = true;
	m_pEffMag = pEffItem;

	return S_OK;
}

void item::release()
{
}

void item::update()
{
	if (!m_isAlive) return;

	if (m_isItemIdle)
	{
		m_ItemAlphaNum += 2;
		if (m_ItemAlphaNum > 155)
			m_ItemAlphaNum = 155;

		if (m_fItemIdleY < m_fItemIdleCurrY - ITEM_IDLE_Y_SIZE)
		{
			m_isItemIdle = false;
		}

		m_fItemIdleY -= 0.1f;
	}
	else
	{
		m_ItemAlphaNum -= 2;
		if (m_ItemAlphaNum < 0)
			m_ItemAlphaNum = 0;

		if (m_fItemIdleY > m_fItemIdleCurrY + ITEM_IDLE_Y_SIZE)
		{
			m_isItemIdle = true;
		}


		m_fItemIdleY += 0.1f;
	}

	if (!m_tItemInfo.tIsGet)
	{
		if (m_tItemInfo.tTimer <= 0)
		{
			m_isAlive = false;
			m_pEffMag->play("Item_Get1",
				m_tItemInfo.posX - ((320 / 4) / 2),
				m_tItemInfo.posY - (31 / 2) + 10.0f);
		}
		m_tItemInfo.tTimer--;
	}

	if (!m_tItemInfo.tIsGet)
	{
		m_rc = RectMakeCenter(
			m_tItemInfo.posX - SCROLL->GetX(),
			m_tItemInfo.posY - SCROLL->GetY(),
			(m_pImg->getFrameWidth() * m_tItemInfo.tScale),
			(m_pImg->getFrameHeight() * m_tItemInfo.tScale));
	}
	else
	{
		m_rc = RectMakeCenter(
			m_tItemInfo.posX,
			m_tItemInfo.posY,
			(m_pImg->getFrameWidth() * m_tItemInfo.tScale),
			(m_pImg->getFrameHeight() * m_tItemInfo.tScale));
	}


}

void item::render(HDC hdc)
{
	if (!m_isAlive) return;
	//Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);
	//Ellipse(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);
	//EllipseMakeCenter(hdc, m_fX, m_fY, m_pImg->getFrameWidth() + 5, m_pImg->getFrameHeight() + 5);

	if (!m_tItemInfo.tIsGet)
	{
		m_pImgShadow->frameAlphaRender(hdc,
			(m_tItemInfo.posX - SCROLL->GetX()) - (m_pImgShadow->getFrameWidth() / 2 * m_tItemInfo.tScale),
			(m_tItemInfo.posY - SCROLL->GetY()) - (m_pImgShadow->getFrameHeight() / 2 * m_tItemInfo.tScale) + 20.0f,
			m_tItemInfo.tImageCurrX,
			m_tItemInfo.tImageCurrY,
			m_tItemInfo.tScale,
			m_ItemAlphaNum);

		m_pImg->frameAlphaRender(hdc,
			(m_tItemInfo.posX - SCROLL->GetX()) - (m_pImg->getFrameWidth() / 2 * m_tItemInfo.tScale),
			(m_fItemIdleY - SCROLL->GetY()) - (m_pImg->getFrameHeight() / 2 * m_tItemInfo.tScale),
			m_tItemInfo.tImageCurrX,
			m_tItemInfo.tImageCurrY,
			m_tItemInfo.tScale,
			m_tItemInfo.tItemTimerAlpha);
	}
	else
	{
		m_pImgShadow->frameAlphaRender(hdc,
			m_fItemX - (m_pImgShadow->getFrameWidth() / 2 * m_tItemInfo.tScale),
			m_fItemY - (m_pImgShadow->getFrameHeight() / 2 * m_tItemInfo.tScale) + 20.0f,
			m_tItemInfo.tImageCurrX,
			m_tItemInfo.tImageCurrY,
			m_tItemInfo.tScale,
			m_ItemAlphaNum);

		m_pImg->frameAlphaRender(hdc,
			m_fItemX - (m_pImg->getFrameWidth() / 2 * m_tItemInfo.tScale),
			m_fItemIdleY - (m_pImg->getFrameHeight() / 2 * m_tItemInfo.tScale),
			m_tItemInfo.tImageCurrX,
			m_tItemInfo.tImageCurrY,
			m_tItemInfo.tScale,
			m_tItemInfo.tItemTimerAlpha);
	}



	if (!m_tItemInfo.tIsGet)
	{
		// 아이템 반짝임
		if (m_tItemInfo.tTimer < (m_tItemInfo.tTimerMax / 4))
		{
			m_tItemInfo.tItemTimerAlpha += 20;
		}
		else if (m_tItemInfo.tTimer < (m_tItemInfo.tTimerMax / 3))
		{
			m_tItemInfo.tItemTimerAlpha += 15;
		}
		else if (m_tItemInfo.tTimer < (m_tItemInfo.tTimerMax / 2))
		{
			m_tItemInfo.tItemTimerAlpha += 5;
		}


		//char szText[256];

		//// TRANSPARENT : 투명, OPAQUE : 불투명
		//SetBkMode(hdc, TRANSPARENT);

		//SetTextColor(hdc, RGB(255, 0, 255));

		//sprintf_s(szText, "m_fX : %f / m_fY : %f",
		//	m_tItemInfo.posX, m_tItemInfo.posY);
		//TextOut(hdc, 200, 100, szText, strlen(szText));

		//sprintf_s(szText, "tImageCurrX / Y : %d, %d",
		//	m_tItemInfo.tImageCurrX, m_tItemInfo.tImageCurrY);
		//TextOut(hdc, 200, 120, szText, strlen(szText));

		//sprintf_s(szText, "tMoveTypeCount : %f",
		//	m_tItemInfo.tScale);
		//TextOut(hdc, 200, 140, szText, strlen(szText));

		//sprintf_s(szText, "tTimer : %d",
		//	m_tItemInfo.tTimer);
		//TextOut(hdc, 200, 160, szText, strlen(szText));

		//sprintf_s(szText, "tRadius : %f",
		//	m_tItemInfo.tRadius);
		//TextOut(hdc, 200, 180, szText, strlen(szText));
	}
	else
	{
		ItemPopup(hdc);
	}
}

void item::ItemGetSetting()
{
	m_tItemInfo.tScale = m_tItemInfo.tScale * 1.5f;
	m_tItemInfo.tRadius = (m_pImg->getFrameWidth() / 2) * m_tItemInfo.tScale;
}

void item::ItemPopup(HDC hdc)
{
	AddFontResourceA("BMHANNAAir_ttf.ttf");

	if (g_ptMouse.x > m_rc.left && g_ptMouse.x < m_rc.right &&
		g_ptMouse.y > m_rc.top && g_ptMouse.y < m_rc.bottom)
	{
		m_pItemPopupUi->render(hdc, m_fItemX - (m_pItemPopupUi->getFrameWidth() / 2), m_fItemY - (m_pItemPopupUi->getFrameHeight() + 20.0f));
		m_pItemPopupUi->setX(m_fItemX - (m_pItemPopupUi->getFrameWidth() / 2) + 15.0f);
		m_pItemPopupUi->setY(m_fItemY - (m_pItemPopupUi->getFrameHeight() / 2) - 20.0f);


		char szText[256];
		const char * tempItemName = m_tItemInfo.tItemName.c_str();
		const char * tempItemTxt = m_tItemInfo.tItemTxt.c_str();
		const char * tempItemOption = m_tItemInfo.tItemOption.c_str();
		string TempItemGrade;

		SetBkMode(hdc, TRANSPARENT);
		MY_UTIL::FontOption(hdc, 24, 0);
		switch (m_tItemInfo.tItemGrade) // 등급별 색상 초기화
		{
		case 0:
			TempItemGrade = "일반";
			SetTextColor(hdc, RGB(180, 180, 180));
			break;
		case 1:
			TempItemGrade = "고급";
			SetTextColor(hdc, RGB(0, 255, 0));
			break;
		case 2:
			TempItemGrade = "전설";
			SetTextColor(hdc, RGB(255, 0, 0));
			break;
		}
		const char * tempItemGrade = TempItemGrade.c_str();

		TextOut(hdc,
			m_tItemInfo.posX - (m_pItemPopupUi->getFrameWidth() / 2) + 200.0f,
			m_tItemInfo.posY - (m_pItemPopupUi->getFrameHeight() / 2) - 65.0f, szText, strlen(szText));
		MY_UTIL::FontDelete(hdc);


		MY_UTIL::FontOption(hdc, 32, 0);
		sprintf_s(szText, "[%s] : %s", tempItemGrade, tempItemName);
		TextOut(hdc,
			m_tItemInfo.posX - (m_pItemPopupUi->getFrameWidth() / 2) + 15.0f,
			m_tItemInfo.posY - (m_pItemPopupUi->getFrameHeight() / 2) - 70.0f, szText, strlen(szText));
		MY_UTIL::FontDelete(hdc);

		MY_UTIL::FontOption(hdc, 20, 0);
		SetTextColor(hdc, RGB(255, 255, 255));
		sprintf_s(szText, "기능 : %s", tempItemOption);
		TextOut(hdc,
			m_tItemInfo.posX - (m_pItemPopupUi->getFrameWidth() / 2) + 15.0f,
			m_tItemInfo.posY - (m_pItemPopupUi->getFrameHeight() / 2) - 40.0f, szText, strlen(szText));

		RECT rcTextArea = {
			m_pItemPopupUi->getX(),
			m_pItemPopupUi->getY(),
			m_pItemPopupUi->getX() + m_pItemPopupUi->getFrameWidth() - 20.0f,
			m_pItemPopupUi->getY() + m_pItemPopupUi->getFrameHeight() };
		SetTextColor(hdc, RGB(255, 255, 255));
		sprintf_s(szText, "내용 : %s", tempItemTxt);
		DrawText(hdc, szText, strlen(szText), &rcTextArea, DT_WORDBREAK);
		MY_UTIL::FontDelete(hdc);
	}

}

item::item()
{
}


item::~item()
{
}
