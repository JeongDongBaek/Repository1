#include "stdafx.h"
#include "animation.h"
#include "PlayerCharacter.h"
#include "bulletManger.h"
#include "item.h"
#include "soundManager.h"

HRESULT PlayerCharacter::init(soundManager * soundPoint)
{
	m_pSoundMag = soundPoint;

	img_ItemUiBg = IMAGEMANAGER->findImage("Player_ItemUI");
	img_ItemUiBg->setX(WINSIZEX / 2 - img_ItemUiBg->getFrameWidth() / 2);
	img_ItemUiBg->setY(WINSIZEY / 2 - img_ItemUiBg->getFrameHeight() / 2);
	img_InfoIcon = IMAGEMANAGER->findImage("Player_InfoIcon");
	img_PlayerShadow = IMAGEMANAGER->findImage("Player_Shadow");

	for (int i = 0; i < 10; i++)
	{
		img_HpPoint[i] = IMAGEMANAGER->findImage("Player_HP_Point");
	}

	m_vecItem.reserve(30); // 가방 사이즈

	m_currHp = BAES_HP;
	m_currHpMax = m_currHp;
	m_isAlive = true;
	m_isItemUi = false;
	m_fPlayerScale = 1.0f;
	m_isRectCol = false;
	m_isIdle = true;
	m_isRun = false;

	// 조준점 (마우스 커서)
	img_CrossHair = IMAGEMANAGER->findImage("Player_CrossHair");
	ani_CrossHair = new animation;
	ani_CrossHair->init(img_CrossHair->getWidth(), img_CrossHair->getFrameHeight(),
		img_CrossHair->getFrameWidth(), img_CrossHair->getFrameHeight());
	ani_CrossHair->setDefPlayFrame(true, false);
	ani_CrossHair->setFPS(30);

	// 플레이어 이미지 초기화
	img_PlayerIdle = IMAGEMANAGER->findImage("Player_L_Idle");
	ani_PlayerIdle = new animation;
	ani_PlayerIdle->init(img_PlayerIdle->getWidth(), img_PlayerIdle->getFrameHeight(),
		img_PlayerIdle->getFrameWidth(), img_PlayerIdle->getFrameHeight());
	ani_PlayerIdle->setDefPlayFrame(false, true);
	ani_PlayerIdle->setFPS(15);
	ani_PlayerIdle->start();

	img_PlayerRun = IMAGEMANAGER->findImage("Player_L_Run");
	ani_PlayerRun = new animation;
	ani_PlayerRun->init(img_PlayerRun->getWidth(), img_PlayerRun->getFrameHeight(),
		img_PlayerRun->getFrameWidth(), img_PlayerRun->getFrameHeight());
	ani_PlayerRun->setDefPlayFrame(false, true);
	ani_PlayerRun->setFPS(15);
	ani_PlayerRun->start();


	// 정지수 시작
	memset(&m_rc, 0, sizeof(m_rc));
	memset(&m_TileRc, 0, sizeof(m_TileRc));


	m_fRadius = img_PlayerIdle->getFrameWidth() / 2;
	m_fSpeed = 2.0f;

	m_bulletDelayCount = 0;
	m_bulletDelayCountMax = BULLET_FIRST_DELAY;

	m_fCrossHairScaleMin = CROSSHAIR_MIN_SCALE;
	m_fCrossHairScale = m_fCrossHairScaleMin;
	m_fCrossHairScaleMax = CROSSHAIR_MAX_SCALE;

	m_itemNum = 0;
	m_itemNumY = 0;
	m_isHitState = false;
	m_HitDelayMax = PLAYER_HIT_DELAY;
	m_HitDelayCount = 0;
	m_HitAlphaValue = 255;

	// 정지수 끝

	// Player 기본 셋팅 (메인)
	memset(&m_tBulletInfo, 0, sizeof(m_tBulletInfo));

	m_tBulletInfo.tIsAlive = true;
	m_tBulletInfo.tBulletSetNum = 1;
	m_tBulletInfo.tScale = 1.0f;
	m_tBulletInfo.tScaleMax = m_tBulletInfo.tScale * 2.0f;
	m_tBulletInfo.tRadius = 0.5f;
	m_tBulletInfo.tExpRadius = 0.5f;
	m_tBulletInfo.tRange = 400.0f;
	m_tBulletInfo.tBulletBoom = false;

	m_tBulletInfo.tDmage = 5.0f;
	m_tBulletInfo.tKnokBack = 10.0f;
	m_tBulletInfo.tMoveSpeed = 10.0f;
	m_tBulletInfo.tScatter = m_fCrossHairScale * 10.0f;

	m_tBulletInfo.tBoomType = BULLET_BOOM_TYPE::ANGLE_LINE;
	m_tBulletInfo.tShootType = BULLET_SHOOT_TYPE::ONE_SHOOT;
	m_tBulletInfo.tMasterType = BULLET_MASTER_TYPE::PLAYER;
	m_tBulletInfo.tMoveActType = BULLET_MOVE_ACT_TYPE::BULLET_MOVE_ACT_NUM;
	m_tBulletInfo.tImageType = BULLET_IMAGE_TYPE::COLOR_Y;
	m_tBulletInfo.tMoveType = BULLET_MOVE_TYPE::ONE_LINE;

	m_tBulletInfoPoint = &m_tBulletInfo;

	// 서브 탄환 (이중 폭발)
	memset(&m_tBulletInfoSub, 0, sizeof(m_tBulletInfoSub));

	m_tBulletInfoSub.tIsAlive = true;
	m_tBulletInfoSub.tBulletSetNum = 1;
	m_tBulletInfoSub.tScale = m_tBulletInfo.tScale / 2;
	m_tBulletInfoSub.tScaleMax = m_tBulletInfo.tScale * 2.0f;
	m_tBulletInfoSub.tRadius = m_tBulletInfo.tRadius / 2;
	m_tBulletInfoSub.tExpRadius = m_tBulletInfo.tExpRadius / 2;
	m_tBulletInfoSub.tRange = m_tBulletInfo.tRange / 2;
	m_tBulletInfoSub.tBulletBoom = false;

	m_tBulletInfoSub.tDmage = m_tBulletInfo.tDmage / 2;
	m_tBulletInfoSub.tKnokBack = m_tBulletInfo.tKnokBack / 2;
	m_tBulletInfoSub.tMoveSpeed = m_tBulletInfo.tMoveSpeed / 2;
	m_tBulletInfoSub.tScatter = m_tBulletInfo.tScatter / 2;

	m_tBulletInfoSub.tBoomType = BULLET_BOOM_TYPE::ANGLE_LINE;
	m_tBulletInfoSub.tShootType = BULLET_SHOOT_TYPE::ONE_SHOOT;
	m_tBulletInfoSub.tMasterType = BULLET_MASTER_TYPE::PLAYER;
	m_tBulletInfoSub.tMoveActType = BULLET_MOVE_ACT_TYPE::BULLET_MOVE_ACT_NUM;
	m_tBulletInfoSub.tImageType = BULLET_IMAGE_TYPE::COLOR_P;
	m_tBulletInfoSub.tMoveType = BULLET_MOVE_TYPE::ONE_LINE;

	m_tBulletInfoSubPoint = &m_tBulletInfoSub;

	return S_OK;
}

void PlayerCharacter::release()
{
	SAFE_DELETE(ani_CrossHair);
	SAFE_DELETE(ani_PlayerIdle);
	SAFE_DELETE(ani_PlayerRun);
}

void PlayerCharacter::update()
{
	m_rc = RectMakeCenter(m_fX - SCROLL->GetX(), m_fY - SCROLL->GetY() + 10.0f, img_PlayerIdle->getFrameWidth() * m_fPlayerScale, img_PlayerIdle->getFrameHeight() * m_fPlayerScale);
	keyInput();
	HitState();

	if (m_bulletDelayCount > 0)
		m_bulletDelayCount--;

	if (m_fCrossHairScale > CROSSHAIR_MAX_SCALE)
		m_fCrossHairScale = CROSSHAIR_MAX_SCALE;

	if (m_fCrossHairScale > m_fCrossHairScaleMin)
		m_fCrossHairScale -= 0.1f;


	ani_CrossHair->frameUpdate();
	ani_PlayerIdle->frameUpdate();
	ani_PlayerRun->frameUpdate();
}

void PlayerCharacter::render(HDC hdc)
{
	//Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);
	//EllipseMakeCenter(hdc, (m_fX - SCROLL->GetX()), (m_fY - SCROLL->GetY()), img_PlayerIdle->getFrameWidth() * m_fPlayerScale, img_PlayerIdle->getFrameHeight() * m_fPlayerScale - 15);
	//Ellipse(hdc, m_rc.lef(m_fY - SCROLL->GetY())t,(m_fY - SCROLL->GetY()) m_rc.top, m_rc.right, m_rc.bottom);

	img_PlayerShadow->alphaRender(hdc,
		(m_fX - SCROLL->GetX()) - (img_PlayerIdle->getFrameWidth() / 2) * 1.5f,
		(m_fY - SCROLL->GetY()) + (img_PlayerIdle->getFrameHeight() / 2 - (5.0f * m_fPlayerScale)),
		150);

	// 캐릭터 이미지 랜더
	if (m_isIdle)
	{
		img_PlayerIdle->aniRender(hdc,
			(m_fX - SCROLL->GetX()) - (img_PlayerIdle->getFrameWidth() / 2) * m_fPlayerScale,
			(m_fY - SCROLL->GetY()) - (img_PlayerIdle->getFrameHeight() / 2) * m_fPlayerScale,
			ani_PlayerIdle, m_fPlayerScale, true, m_HitAlphaValue);
	}
	else
	{
		img_PlayerRun->aniRender(hdc,
			(m_fX - SCROLL->GetX()) - (img_PlayerRun->getFrameWidth() / 2) * m_fPlayerScale,
			(m_fY - SCROLL->GetY()) - (img_PlayerRun->getFrameHeight() / 2) * m_fPlayerScale,
			ani_PlayerRun, m_fPlayerScale, true, m_HitAlphaValue);
	}



	// 체력 하트 표기
	for (int i = 0; i < m_currHpMax / 2; i++)
	{
		if ((i + 1) * 2 <= m_currHp)
		{
			img_HpPoint[i]->frameRender(hdc,
				10 + i * (img_HpPoint[0]->getFrameWidth() + 10),
				(img_HpPoint[0]->getFrameHeight() / 2),
				2,
				0
			);
		}
		else if (((i + 1) * 2) - 1 == m_currHp)
		{
			img_HpPoint[i]->frameRender(hdc,
				10 + i * (img_HpPoint[0]->getFrameWidth() + 10),
				(img_HpPoint[0]->getFrameHeight() / 2),
				1,
				0
			);
		}
		else
		{
			img_HpPoint[i]->frameRender(hdc,
				10 + i * (img_HpPoint[0]->getFrameWidth() + 10),
				(img_HpPoint[0]->getFrameHeight() / 2),
				0,
				0
			);
		}
	}
	// TAP 아이콘
	img_InfoIcon->render(hdc, PLAYER_ICON_X - (img_InfoIcon->getFrameWidth() / 2), PLAYER_ICON_Y - (img_InfoIcon->getFrameHeight() / 2));
	// 가방 UI 표기
	if (m_isItemUi) // 가방 열기
	{
		IMAGEMANAGER->findImage("Player_UI_BG")->alphaRender(hdc, 0, 0, 155);

		img_ItemUiBg->render(hdc, (WINSIZEX / 2) - (img_ItemUiBg->getFrameWidth() / 2), (WINSIZEX / 2) - (img_ItemUiBg->getFrameHeight() / 2));
		PlayerInfoUi(hdc);
		itemUi(hdc);
	}
	// 조준점 UI 표기
	img_CrossHair->aniRender(hdc, g_ptMouse.x - (img_CrossHair->getFrameWidth() / 2) * m_fCrossHairScale, g_ptMouse.y - (img_CrossHair->getFrameHeight() / 2) * m_fCrossHairScale, ani_CrossHair, m_fCrossHairScale);

}

void PlayerCharacter::ColP2T()
{
	if (m_enumKey == 0)
	{
		m_fY += m_fSpeed + RECT_BOX;

		m_enumKey = -1;
	}
	if (m_enumKey == 1)
	{
		m_fY -= m_fSpeed + RECT_BOX;
		m_enumKey = -1;
	}
	if (m_enumKey == 2)
	{
		m_fX += m_fSpeed + RECT_BOX;
		m_enumKey = -1;
	}
	if (m_enumKey == 3)
	{
		m_fX -= m_fSpeed + RECT_BOX;
		m_enumKey = -1;
	}
}

void PlayerCharacter::getItem(tagItemInfo itemInfo)
{
	// 아이템 능력치 적용
	if (!itemInfo.tBulletType)
	{
		m_tBulletInfo.tBulletSetNum += itemInfo.tBulletSetNum;
		m_tBulletInfo.tRange += itemInfo.tRange;
		m_tBulletInfo.tScale += itemInfo.tBulletScale;
		m_tBulletInfo.tDmage += itemInfo.tDmage;
		m_tBulletInfo.tKnokBack += itemInfo.tKnokBack;
		m_tBulletInfo.tMoveSpeed += itemInfo.tMoveSpeed;

		if (itemInfo.tBoomType != (BULLET_BOOM_TYPE::BULLET_BOOM_NUM))
			m_tBulletInfo.tBoomType = itemInfo.tBoomType;
		if (itemInfo.tShootType != (BULLET_SHOOT_TYPE::BULLET_SHOOT_NUM))
			m_tBulletInfo.tShootType = itemInfo.tShootType;
		if (itemInfo.tMasterType != (BULLET_MASTER_TYPE::BULLET_MASTER_NUM))
			m_tBulletInfo.tMasterType = itemInfo.tMasterType;
		if (itemInfo.tMoveActType != (BULLET_BOOM_TYPE::BULLET_BOOM_NUM))
			m_tBulletInfo.tMoveActType = itemInfo.tMoveActType;
		if (itemInfo.tMoveType != (BULLET_MOVE_ACT_TYPE::BULLET_MOVE_ACT_NUM))
			m_tBulletInfo.tMoveType = itemInfo.tMoveType;
		if (itemInfo.tImageType != BULLET_IMAGE_TYPE::BULLET_IMAGE_NUM)
			m_tBulletInfo.tImageType = itemInfo.tImageType;
	}
	else
	{
		m_tBulletInfoSub.tBulletSetNum += itemInfo.tBulletSetNum;
		m_tBulletInfoSub.tRange += itemInfo.tRange;
		m_tBulletInfoSub.tScale += itemInfo.tBulletScale;
		m_tBulletInfoSub.tDmage += itemInfo.tDmage;
		m_tBulletInfoSub.tKnokBack += itemInfo.tKnokBack;
		m_tBulletInfoSub.tMoveSpeed += itemInfo.tMoveSpeed;

		if (itemInfo.tBoomType != (BULLET_BOOM_TYPE::BULLET_BOOM_NUM))
			m_tBulletInfoSub.tBoomType = itemInfo.tBoomType;
		if (itemInfo.tShootType != (BULLET_SHOOT_TYPE::BULLET_SHOOT_NUM))
			m_tBulletInfoSub.tShootType = itemInfo.tShootType;
		if (itemInfo.tMasterType != (BULLET_MASTER_TYPE::BULLET_MASTER_NUM))
			m_tBulletInfoSub.tMasterType = itemInfo.tMasterType;
		if (itemInfo.tMoveActType != (BULLET_BOOM_TYPE::BULLET_BOOM_NUM))
			m_tBulletInfoSub.tMoveActType = itemInfo.tMoveActType;
		if (itemInfo.tMoveType != (BULLET_MOVE_ACT_TYPE::BULLET_MOVE_ACT_NUM))
			m_tBulletInfoSub.tMoveType = itemInfo.tMoveType;
		if (itemInfo.tImageType != BULLET_IMAGE_TYPE::BULLET_IMAGE_NUM)
			m_tBulletInfoSub.tImageType = itemInfo.tImageType;
	}

	// 2차 폭발 여부
	if (itemInfo.tBulletBoom != 3)
		m_tBulletInfo.tBulletBoom = itemInfo.tBulletBoom;

	m_fSpeed += itemInfo.tPlayerSpeed;
	if (m_fSpeed < 0.0f)
		m_fSpeed = 0.3f;

	m_bulletDelayCountMax += itemInfo.tBulletDelayCountMax;
	m_fCrossHairScaleMin += itemInfo.tCrossHairScaleMax;

	m_currHpMax += itemInfo.tPlayerHpMax;
	m_currHp += itemInfo.tPlayerHpMax;
	m_fPlayerScale += itemInfo.tPlayerScale;

	m_pItemInfo = new item;
	itemInfo.tIsGet = true;

	m_itemNum++; // 아이템 개수 추가
	if (m_itemNum > 6)
	{
		m_itemNumY++;
		m_itemNum = 1;
	}

	m_pItemInfo->init("ItemObject", itemInfo, NULL);
	m_pItemInfo->setItemIdleCurrY(img_ItemUiBg->getY() + (ITEM_BAG_Y)+(m_itemNumY * ITEM_BAG_Size_Y));
	m_pItemInfo->setItemIdleY(img_ItemUiBg->getY() + (ITEM_BAG_Y)+(m_itemNumY * ITEM_BAG_Size_Y));
	m_pItemInfo->setX(img_ItemUiBg->getX() + (ITEM_BAG_X)+((m_itemNum - 1) * ITEM_BAG_Size_X));
	m_pItemInfo->setY(img_ItemUiBg->getY() + (ITEM_BAG_Y)+(m_itemNumY * ITEM_BAG_Size_Y));
	m_pItemInfo->ItemGetSetting();
	m_vecItem.push_back(m_pItemInfo);
}

void PlayerCharacter::PlayerDamage(int dam)
{
	//m_pSoundMag->play("sound/sound_playerHit.wav", g_saveData.gSeValue);

	m_currHp -= dam;
	if (m_currHp < 0)
	{
		m_isAlive = false;
	}

	if (!m_isHitState && m_HitDelayCount <= 0)
	{
		m_isHitState = true;
	}
}

void PlayerCharacter::itemUi(HDC hdc)
{
	for (m_iter = m_vecItem.begin(); m_iter != m_vecItem.end(); m_iter++)
	{
		if (!(*m_iter)->getIsAlive()) continue;

		(*m_iter)->render(hdc);
		(*m_iter)->update();
	}
}

void PlayerCharacter::PlayerInfoUi(HDC hdc)
{
	AddFontResourceA("BMHANNAAir_ttf.ttf");

	char szText[256];

	float TempYSize = 0.0f;
	// 이름 출력
	SetBkMode(hdc, TRANSPARENT);
	MY_UTIL::FontOption(hdc, 28, 0);
	SetTextColor(hdc, RGB(255, 255, 255));
	sprintf_s(szText, "[ 소녀 앨리스 ]");
	TextOut(hdc, img_ItemUiBg->getX() + PLAYER_STATE_X, img_ItemUiBg->getY() + PLAYER_STATE_Y, szText, strlen(szText));
	MY_UTIL::FontDelete(hdc);

	TempYSize = img_ItemUiBg->getY() + PLAYER_STATE_Y + 30.0f;

	// 캐릭터 능력치 출력
	MY_UTIL::FontOption(hdc, 18, 0);
	SetTextColor(hdc, RGB(255, 255, 255));
	sprintf_s(szText, "체력 : %d / %d", m_currHp, m_currHpMax);
	TextOut(hdc, img_ItemUiBg->getX() + PLAYER_STATE_X, TempYSize, szText, strlen(szText));

	TempYSize += 20.0f;
	sprintf_s(szText, "이동속도 : %.1f", m_fSpeed);
	TextOut(hdc, img_ItemUiBg->getX() + PLAYER_STATE_X, TempYSize, szText, strlen(szText));

	TempYSize += 20.0f;
	sprintf_s(szText, "크기 : %.1f", m_fPlayerScale);
	TextOut(hdc, img_ItemUiBg->getX() + PLAYER_STATE_X, TempYSize, szText, strlen(szText));

	// 블렛 능력치 출력
	sprintf_s(szText, "공격력 : %.1f", m_tBulletInfo.tDmage);
	TextOut(hdc, img_ItemUiBg->getX() + BULLET_STATE_X, img_ItemUiBg->getY() + BULLET_STATE_Y, szText, strlen(szText));
	TempYSize = img_ItemUiBg->getY() + BULLET_STATE_Y + 20.0f; // UI 위치 재정렬

	sprintf_s(szText, "발사개수 : %d", m_tBulletInfo.tBulletSetNum);
	TextOut(hdc, img_ItemUiBg->getX() + BULLET_STATE_X, TempYSize, szText, strlen(szText));
	TempYSize += 20.0f;

	sprintf_s(szText, "발사속도 : %d/s", m_bulletDelayCountMax);
	TextOut(hdc, img_ItemUiBg->getX() + BULLET_STATE_X, TempYSize, szText, strlen(szText));
	TempYSize += 20.0f;

	sprintf_s(szText, "마법속도 : %.1f", m_tBulletInfo.tMoveSpeed);
	TextOut(hdc, img_ItemUiBg->getX() + BULLET_STATE_X, TempYSize, szText, strlen(szText));
	TempYSize += 20.0f;

	sprintf_s(szText, "이동거리 : %.1f", m_tBulletInfo.tRange);
	TextOut(hdc, img_ItemUiBg->getX() + BULLET_STATE_X, TempYSize, szText, strlen(szText));
	TempYSize += 20.0f;

	sprintf_s(szText, "크기 : %.1f", m_tBulletInfo.tScale);
	TextOut(hdc, img_ItemUiBg->getX() + BULLET_STATE_X, TempYSize, szText, strlen(szText));
	TempYSize += 20.0f;

	sprintf_s(szText, "정확도 : %.1f", m_fCrossHairScaleMin);
	TextOut(hdc, img_ItemUiBg->getX() + BULLET_STATE_X, TempYSize, szText, strlen(szText));
	TempYSize += 20.0f;

	sprintf_s(szText, "넉백 : %.1f", m_tBulletInfo.tKnokBack);
	TextOut(hdc, img_ItemUiBg->getX() + BULLET_STATE_X, TempYSize, szText, strlen(szText));
	TempYSize += 20.0f;

	//sprintf_s(szText, "m_fX : %.1f", m_fX);
	//TextOut(hdc, img_ItemUiBg->getX() + BULLET_STATE_X, TempYSize, szText, strlen(szText));
	//TempYSize += 20.0f;

	//sprintf_s(szText, "CurrX : %.1f", m_fCurrX);
	//TextOut(hdc, img_ItemUiBg->getX() + BULLET_STATE_X, TempYSize, szText, strlen(szText));
	//TempYSize += 20.0f;



	MY_UTIL::FontDelete(hdc);
}

void PlayerCharacter::keyInput()
{

	if (KEYMANAGER->isOnceKeyDown(VK_TAB))
	{
		if (m_isItemUi)
		{
			m_isItemUi = false;
			g_saveData.gGamePause = false;
		}
		else
		{
			m_isItemUi = true;
			g_saveData.gGamePause = true;
		}
	}

	if (g_saveData.gGamePause) return;

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		if (m_bulletDelayCount == NULL)
		{
			//	m_pSoundMag->play("sound/sound_playerAtt.wav", g_saveData.gSeValue);
			if (m_fCrossHairScale < m_fCrossHairScaleMax)
			{
				m_fCrossHairScale += 0.1f;
				if (m_fCrossHairScale > m_fCrossHairScaleMax)
					m_fCrossHairScale = m_fCrossHairScaleMax;
				m_tBulletInfo.tScatter = m_fCrossHairScale * 10.0f;
			}
			ani_CrossHair->start();

			if (m_tBulletInfo.tShootType == BULLET_SHOOT_TYPE::ONE_SHOOT)
			{
				if (m_tBulletInfo.tBulletSetNum == 1)
				{
					(*m_pBulletMag)->fire("임시", m_fX, m_fY, MY_UTIL::getMouseAngle(m_fX - SCROLL->GetX(), m_fY - SCROLL->GetY()), m_tBulletInfoPoint, m_tBulletInfoSubPoint);
				}
				else // 총알 개수 만큼 방향을 분리
				{
					for (int i = 0; i < m_tBulletInfo.tBulletSetNum; i++)
					{
						(*m_pBulletMag)->fire("임시", m_fX, m_fY, MY_UTIL::getMouseAngle(m_fX - SCROLL->GetX(), m_fY - SCROLL->GetY()) - (i * (PI / 180.0f * (30.0f))) - ((PI / 180.0f) * MY_UTIL::getMouseAngle(m_fX, m_fY) - ((m_tBulletInfo.tBulletSetNum - 1) * (PI / 180.0f * (30.0f)))) / 2, m_tBulletInfoPoint, m_tBulletInfoSubPoint);
					}
				}
			}
			else if (m_tBulletInfo.tShootType == BULLET_SHOOT_TYPE::CUFF_SHOOT)
			{
				if (m_tBulletInfo.tBulletSetNum == 1)
				{
					(*m_pBulletMag)->fire("임시", m_fX, m_fY, MY_UTIL::getMouseAngle(m_fX - SCROLL->GetX(), m_fY - SCROLL->GetY()), m_tBulletInfoPoint, m_tBulletInfoSubPoint);
				}
				else // 총알 개수 만큼 방향을 분리
				{
					for (int i = 0; i < m_tBulletInfo.tBulletSetNum; i++)
					{
						(*m_pBulletMag)->fire("임시", m_fX, m_fY, MY_UTIL::getMouseAngle(m_fX - SCROLL->GetX(), m_fY - SCROLL->GetY()) + (i * (PI / 180.0f * (360.0f / m_tBulletInfo.tBulletSetNum))), m_tBulletInfoPoint, m_tBulletInfoSubPoint);
					}
				}
			}
			m_bulletDelayCount = m_bulletDelayCountMax;
		}
	}
	RECT temp_rc;

	m_isIdle = true;
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		m_isIdle = false;
		m_fY -= m_fSpeed;
		m_rc = RectMakeCenter(m_fX - SCROLL->GetX(), m_fY - SCROLL->GetY() + 10.0f, img_PlayerIdle->getFrameWidth() * m_fPlayerScale, img_PlayerIdle->getFrameHeight() * m_fPlayerScale);

		m_enumKey = 0;
	}

	if (KEYMANAGER->isStayKeyDown('S'))
	{
		m_isIdle = false;
		m_fY += m_fSpeed;
		m_rc = RectMakeCenter(m_fX - SCROLL->GetX(), m_fY - SCROLL->GetY() + 10.0f, img_PlayerIdle->getFrameWidth() * m_fPlayerScale, img_PlayerIdle->getFrameHeight() * m_fPlayerScale);

		m_enumKey = 1;
	}

	if (KEYMANAGER->isStayKeyDown('A'))
	{
		m_isIdle = false;
		m_fX -= m_fSpeed;
		m_rc = RectMakeCenter(m_fX - SCROLL->GetX(), m_fY - SCROLL->GetY() + 10.0f, img_PlayerIdle->getFrameWidth() * m_fPlayerScale, img_PlayerIdle->getFrameHeight() * m_fPlayerScale);

		m_enumKey = 2;
		img_PlayerRun = IMAGEMANAGER->findImage("Player_L_Run");
		img_PlayerIdle = IMAGEMANAGER->findImage("Player_L_Idle");

	}

	if (KEYMANAGER->isStayKeyDown('D'))
	{
		m_isIdle = false;
		m_fX += m_fSpeed;
		m_rc = RectMakeCenter(m_fX - SCROLL->GetX(), m_fY - SCROLL->GetY() + 10.0f, img_PlayerIdle->getFrameWidth() * m_fPlayerScale, img_PlayerIdle->getFrameHeight() * m_fPlayerScale);

		m_enumKey = 3;
		img_PlayerRun = IMAGEMANAGER->findImage("Player_R_Run");
		img_PlayerIdle = IMAGEMANAGER->findImage("Player_R_Idle");
	}

	//memset(&m_TileRc, 0, sizeof(m_TileRc));

}

void PlayerCharacter::HitState()
{
	if (!m_isHitState) return;

	m_HitDelayCount++;
	m_HitAlphaValue += 50;
	if (m_HitDelayCount >= m_HitDelayMax)
	{
		m_isHitState = false;
		m_HitAlphaValue = 255;
		m_HitDelayCount = 0;
	}

}

PlayerCharacter::PlayerCharacter()
{
}


PlayerCharacter::~PlayerCharacter()
{
}
