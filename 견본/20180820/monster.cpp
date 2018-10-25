#include "stdafx.h"
#include "animation.h"
#include "monster.h"
#include "PlayerCharacter.h"
#include "bulletManger.h"
#include "PlayerCharacter.h"
#include "progressBar.h"
#include "effectManager.h"
#include "soundManager.h"
#include "itemManager.h"

HRESULT monster::init(const char * strKey, int monNumber, tagMonInfo monInfo, bulletManger* bulletP, PlayerCharacter* playerPoint, effectManager* effMagPoint, tagBulletInfo tBulletInfo)
{
	m_pBulletMag = bulletP;
	m_PlayerCharPoint = playerPoint;
	m_pEffMag = effMagPoint;

	// Monster Bullet 기본 셋팅 (메인)
	memset(&m_tBulletInfo, 0, sizeof(m_tBulletInfo));

	m_tBulletInfo.tIsAlive = true;
	m_tBulletInfo.tBulletSetNum = tBulletInfo.tBulletSetNum;
	m_tBulletInfo.tScale = tBulletInfo.tScale;
	m_tBulletInfo.tScaleMax = m_tBulletInfo.tScale * 2.0f;
	m_tBulletInfo.tRadius = tBulletInfo.tRadius;
	m_tBulletInfo.tExpRadius = tBulletInfo.tExpRadius;
	m_tBulletInfo.tRange = tBulletInfo.tRange;
	m_tBulletInfo.tBulletBoom = tBulletInfo.tBulletBoom;

	m_tBulletInfo.tDmage = tBulletInfo.tDmage + m_tMonInfo.tDamageSub;
	m_tBulletInfo.tKnokBack = tBulletInfo.tKnokBack;
	m_tBulletInfo.tMoveSpeed = tBulletInfo.tMoveSpeed;
	m_tBulletInfo.tScatter = tBulletInfo.tScatter;


	m_tBulletInfo.tBoomType = tBulletInfo.tBoomType;
	m_tBulletInfo.tShootType = tBulletInfo.tShootType;
	m_tBulletInfo.tMasterType = BULLET_MASTER_TYPE::MONSTER;
	m_tBulletInfo.tMoveActType = tBulletInfo.tMoveActType;
	m_tBulletInfo.tImageType = tBulletInfo.tImageType;
	m_tBulletInfo.tMoveType = tBulletInfo.tMoveType;

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
	m_tBulletInfoSub.tMasterType = BULLET_MASTER_TYPE::MONSTER;
	m_tBulletInfoSub.tMoveActType = BULLET_MOVE_ACT_TYPE::BULLET_MOVE_ACT_NUM;
	m_tBulletInfoSub.tImageType = BULLET_IMAGE_TYPE::COLOR_R;
	m_tBulletInfoSub.tMoveType = BULLET_MOVE_TYPE::MOVE_NUM;

	m_tBulletInfoSubPoint = &m_tBulletInfoSub;

	m_monsterType = IMAGEMANAGER->findImage(strKey);
	m_monsterMove = new animation;
	m_monsterMove->init(m_monsterType->getWidth(), m_monsterType->getHeight(),
		m_monsterType->getFrameWidth(), m_monsterType->getFrameHeight());

	// 몬스터 정보 초기화
	memset(&m_tMonInfo.m_rc, 0, sizeof(m_tMonInfo.m_rc));
	memset(&m_tMonInfo, 0, sizeof(m_tMonInfo));

	m_tMonInfo.m_rc = RectMakeCenter(m_tMonInfo.tPosX, m_tMonInfo.tPosY, 50, 50);
	m_tMonInfo.tIsAlive = monInfo.tIsAlive;
	m_tMonInfo.tHp = monInfo.tHp;
	m_tMonInfo.tHpMax = monInfo.tHpMax;
	m_tMonInfo.tPosX = monInfo.tPosX;
	m_tMonInfo.tPosY = monInfo.tPosY;
	m_tMonInfo.tFireCount = monInfo.tFireCount;
	m_tMonInfo.tFireDelay = monInfo.tFireDelay;
	m_tMonInfo.tFireAngle = monInfo.tFireAngle;
	m_tMonInfo.tMoveAngle = monInfo.tMoveAngle;
	m_tMonInfo.tRadius = 30.0f;
	m_tMonInfo.tScale = monInfo.tScale;
	m_tMonInfo.tScaleMax = monInfo.tScaleMax;
	m_tMonInfo.tUnKnokBack = monInfo.tUnKnokBack;
	m_tMonInfo.tMoveSpeed = monInfo.tMoveSpeed;

	m_tMonInfo.tHealingCount = monInfo.tHealingCount = 1;
	m_tMonInfo.tWidth = monInfo.tWidth;
	m_tMonInfo.tHeight = monInfo.tHeight;
	m_tMonInfo.tHp = monInfo.tHp;
	m_tMonInfo.tIsBoom = monInfo.tIsBoom;
	m_tMonInfo.tDamageSub = monInfo.tDamageSub;
	m_tMonInfo.tDef = monInfo.tDef = 0.0f;
	m_tMonInfo.tHealing = monInfo.tHealing;
	m_tMonInfo.tMoveType = monInfo.tMoveType;
	m_tMonInfo.tScore = monInfo.tScore;
	m_tMonInfo.tMonsterNumber = monNumber;
	m_tMonInfo.tMonsterBoss = monInfo.tMonsterBoss = 1.0f;


	m_monsterMove->setDefPlayFrame(false, true);
	m_monsterMove->setFPS(10);
	m_monsterMove->start();

	m_HealingCount = 0;
	m_count = 0;
	m_isHealing = false;
	m_isMove = false;
	m_SubDamgeAdd = 5.0f;

	return S_OK;
}

void monster::release()
{
	SAFE_DELETE(m_monsterMove);
}

void monster::Move(int m_moveTypeNum)//int m_moveTypeNum)
{
	if (!m_tMonInfo.tIsAlive) return;
	{
		m_tMonInfo.m_rc = RectMakeCenter(m_tMonInfo.tPosX - SCROLL->GetX(), m_tMonInfo.tPosY - SCROLL->GetY(), 50, 50);
		m_tMonInfo.tMoveAngle = MY_UTIL::getAngle(m_tMonInfo.tPosX , m_tMonInfo.tPosY, m_PlayerCharPoint->getX(), m_PlayerCharPoint->getY());
	}

	switch (m_moveTypeNum)
	{
	case MONSTER_MOVE::MONSTER_CRAWL:
		if (m_tMonInfo.m_rc.left + 70 < m_PlayerCharPoint->getRect().left
			|| m_tMonInfo.m_rc.right - 70 > m_PlayerCharPoint->getRect().right
			|| m_tMonInfo.m_rc.bottom + 70 < m_PlayerCharPoint->getRect().bottom
			|| m_tMonInfo.m_rc.top - 70 > m_PlayerCharPoint->getRect().top)
		{
			if (m_isMove)
			{
				m_tMonInfo.tPosX += cosf(m_tMonInfo.tMoveAngle) * (m_tMonInfo.tMoveSpeed);
				m_tMonInfo.tPosY += -sinf(m_tMonInfo.tMoveAngle) * (m_tMonInfo.tMoveSpeed);
				m_monsterMove->setFPS(10);
			}
			m_count++;
			if (m_count >= 20)
			{
				m_count = 0;
				m_isMove = RANDOM->getInt(2);
				m_monsterMove->setFPS(0);
			}
		}
		break;
	case MONSTER_MOVE::MONSTER_FLY:
		if (m_tMonInfo.m_rc.left + 150 < m_PlayerCharPoint->getRect().left
			|| m_tMonInfo.m_rc.right - 150 > m_PlayerCharPoint->getRect().right
			|| m_tMonInfo.m_rc.bottom + 150 < m_PlayerCharPoint->getRect().bottom
			|| m_tMonInfo.m_rc.top - 150 > m_PlayerCharPoint->getRect().top)
		{
			if (m_Follow)
			{
				m_tMonInfo.tPosX += cosf(m_tMonInfo.tMoveAngle) * (m_tMonInfo.tMoveSpeed + RANDOM->getFromFloatTo(0, 5));
				m_tMonInfo.tPosY += -sinf(m_tMonInfo.tMoveAngle) * (m_tMonInfo.tMoveSpeed + RANDOM->getFromFloatTo(0, 5));
			}
		}
		else
		{
			m_Follow = false;
		}
		if (!(m_tMonInfo.m_rc.left + 300 < m_PlayerCharPoint->getRect().left
			|| m_tMonInfo.m_rc.right - 300 > m_PlayerCharPoint->getRect().right
			|| m_tMonInfo.m_rc.bottom + 300 < m_PlayerCharPoint->getRect().bottom
			|| m_tMonInfo.m_rc.top - 300 > m_PlayerCharPoint->getRect().top) && !m_Follow)
		{
			m_tMonInfo.tPosX -= cosf(m_tMonInfo.tMoveAngle) * (m_tMonInfo.tMoveSpeed + RANDOM->getFromFloatTo(0, 5));
			m_tMonInfo.tPosY -= -sinf(m_tMonInfo.tMoveAngle) * (m_tMonInfo.tMoveSpeed + RANDOM->getFromFloatTo(0, 5));
		}
		else
		{
			m_Follow = true;
		}
		break;
	case MONSTER_MOVE::MONSTER_RUN:

		if (m_tMonInfo.m_rc.left + 250 < m_PlayerCharPoint->getRect().left
			|| m_tMonInfo.m_rc.right - 250 > m_PlayerCharPoint->getRect().right
			|| m_tMonInfo.m_rc.bottom + 250 < m_PlayerCharPoint->getRect().bottom
			|| m_tMonInfo.m_rc.top - 250 > m_PlayerCharPoint->getRect().top)
		{
			if (m_Follow)
			{
				m_monsterMove->setFPS(10);
				m_tMonInfo.tPosX += cosf(m_tMonInfo.tMoveAngle) * (m_tMonInfo.tMoveSpeed);
				m_tMonInfo.tPosY += -sinf(m_tMonInfo.tMoveAngle) * (m_tMonInfo.tMoveSpeed);
			}
		}
		else
		{
			m_Follow = false;
		}
		if (!(m_tMonInfo.m_rc.left + 300 < m_PlayerCharPoint->getRect().left
			|| m_tMonInfo.m_rc.right - 300 > m_PlayerCharPoint->getRect().right
			|| m_tMonInfo.m_rc.bottom + 300 < m_PlayerCharPoint->getRect().bottom
			|| m_tMonInfo.m_rc.top - 300 > m_PlayerCharPoint->getRect().top) && !m_Follow)
		{
			m_tMonInfo.tPosX -= cosf(m_tMonInfo.tMoveAngle) * (m_tMonInfo.tMoveSpeed);
			m_tMonInfo.tPosY -= -sinf(m_tMonInfo.tMoveAngle) * (m_tMonInfo.tMoveSpeed);
			if (m_isMove)
			{
				m_monsterMove->setFPS(60);
				for (int i = 0; i < 10; i++)
				{
					m_tMonInfo.tMoveAngle += i * 36.0f;
					m_tMonInfo.tPosX += cosf(m_tMonInfo.tMoveAngle) * (m_tMonInfo.tMoveSpeed * 1.3f);
					m_tMonInfo.tPosY += -sinf(m_tMonInfo.tMoveAngle) * (m_tMonInfo.tMoveSpeed * 1.3f);
					if (i == 10)
					{
						i = 0;
					}
				}
			}


		}
		else
		{
			m_Follow = true;
		}
		m_count++;
		if (m_count >= 10)
		{
			m_count = 0;
			m_isMove = RANDOM->getInt(2);
			m_monsterMove->setFPS(10);
		}
		break;
		
	case MONSTER_MOVE::MONSTER_WALK :
		if (m_tMonInfo.m_rc.left + 70 < m_PlayerCharPoint->getRect().left
			|| m_tMonInfo.m_rc.right - 70 > m_PlayerCharPoint->getRect().right
			|| m_tMonInfo.m_rc.bottom + 70 < m_PlayerCharPoint->getRect().bottom
			|| m_tMonInfo.m_rc.top - 70 > m_PlayerCharPoint->getRect().top)
		{
			if (m_Follow)
			{

				m_tMonInfo.tPosX += -1.0f + RANDOM->getFromFloatTo(0.0f, 2.0f);
				m_monsterMove->setFPS(10);
				m_tMonInfo.tPosX += cosf(m_tMonInfo.tMoveAngle) * (m_tMonInfo.tMoveSpeed / 2);
				m_tMonInfo.tPosY += -sinf(m_tMonInfo.tMoveAngle) * (m_tMonInfo.tMoveSpeed / 2);

			}
		}
		else
		{
			m_Follow = false;
		}
		if (!(m_tMonInfo.m_rc.left + 100 < m_PlayerCharPoint->getRect().left
			|| m_tMonInfo.m_rc.right - 100 > m_PlayerCharPoint->getRect().right
			|| m_tMonInfo.m_rc.bottom + 100 < m_PlayerCharPoint->getRect().bottom
			|| m_tMonInfo.m_rc.top - 100 > m_PlayerCharPoint->getRect().top) && !m_Follow)
		{
			m_monsterMove->setFPS(10);
			m_tMonInfo.tPosX -= cosf(m_tMonInfo.tMoveAngle) * (m_tMonInfo.tMoveSpeed / 2);
			m_tMonInfo.tPosY -= -sinf(m_tMonInfo.tMoveAngle) * (m_tMonInfo.tMoveSpeed / 2);
		}
		else
		{
			m_Follow = true;
		}


		break;
	}
}

void monster::fireAtk()
{
	if (!m_tMonInfo.tIsAlive) return;

	if (m_tMonInfo.tFireCount == 0)
	{
		if (m_tBulletInfo.tShootType == BULLET_SHOOT_TYPE::ONE_SHOOT)
		{
			if (m_tBulletInfo.tBulletSetNum == 1)
			{
				m_pBulletMag->fire("임시", m_tMonInfo.tPosX, m_tMonInfo.tPosY, m_tMonInfo.tFireAngle, &m_tBulletInfo, &m_tBulletInfoSub);
			}
			else // 총알 개수 만큼 방향을 분리
			{
				for (int i = 0; i < m_tBulletInfo.tBulletSetNum; i++)
				{
					m_pBulletMag->fire("임시", m_tMonInfo.tPosX, m_tMonInfo.tPosY,
						m_tMonInfo.tFireAngle - (i * (PI / 180.0f * (30.0f))) - ((PI / 180.0f) * m_tMonInfo.tFireAngle - ((m_tBulletInfo.tBulletSetNum - 1) * (PI / 180.0f * (30.0f)))) / 2
						, &m_tBulletInfo, &m_tBulletInfoSub);
				}
			}
		}
		else if (m_tBulletInfo.tShootType == BULLET_SHOOT_TYPE::CUFF_SHOOT)
		{
			if (m_tBulletInfo.tBulletSetNum == 1)
			{
				m_pBulletMag->fire("임시", m_tMonInfo.tPosX, m_tMonInfo.tPosY, m_tMonInfo.tFireAngle, &m_tBulletInfo, &m_tBulletInfoSub);
			}
			else // 총알 개수 만큼 방향을 분리
			{
				for (int i = 0; i < m_tBulletInfo.tBulletSetNum; i++)
				{
					m_pBulletMag->fire("임시", m_tMonInfo.tPosX, m_tMonInfo.tPosY,
						m_tMonInfo.tFireAngle + (i * (PI / 180.0f * (360.0f / m_tBulletInfo.tBulletSetNum)))
						, &m_tBulletInfo, &m_tBulletInfoSub);
				}
			}
		}
		m_tMonInfo.tFireCount = m_tMonInfo.tFireDelay;
	}
	m_tMonInfo.tFireCount--;

}

void monster::knokback(float playerkuokback, float monsterHitRecovery, float bulletAngle)
{
	playerkuokback -= monsterHitRecovery;
	if (playerkuokback > 0.0f)
	{
		m_Follow = false;
		m_tMonInfo.tPosX += cosf(bulletAngle) * ((m_tMonInfo.tMoveSpeed) + playerkuokback);
		m_tMonInfo.tPosY += -sinf(bulletAngle) * ((m_tMonInfo.tMoveSpeed) + playerkuokback);
		m_Follow = true;
	}

}

void monster::Damge(float dam, soundManager * soundMagPoint, itemManager * itemMagPoint)
{
	// 데미지가 받을때 방어력 적용

	int tempItemValue = itemMagPoint->getItemMax();
	tagItemInfo ItemInfo;
	ItemInfo.tScale = 1.0f;
	ItemInfo.tTimer = 1000;
	ItemInfo.tRadius = 1.5f;
	ItemInfo.posX = m_tMonInfo.tPosX;
	ItemInfo.posY = m_tMonInfo.tPosY;

	dam -= m_tMonInfo.tDef;
	if (m_isHealing)
	{
		m_SubDamgeAdd += dam;
	}
	else
	{
		m_SubDamgeAdd = 0.0f;
	}
	m_tMonInfo.tHp -= dam;

	if (m_tMonInfo.tHp < 0.0f) // 사망처리
	{
		m_tMonInfo.tIsAlive = false;
		m_tMonInfo.tDef = 5.0f;
		m_pEffMag->play("Monster_die", m_tMonInfo.tPosX - (512 / 4 / 2), m_tMonInfo.tPosY - (384 / 3 / 2));
		m_tMonInfo.tScore += RANDOM->getInt(4);

		int tempItem = RANDOM->getFromIntTo(1, tempItemValue + 30);

		if (tempItem <= tempItemValue)
		{
			itemMagPoint->itemDrop("ItemObject", tempItem, ItemInfo, m_pEffMag);
		}

		// 사망 사운드
		switch (RANDOM->getFromIntTo(0, 6))
		{
		case 0:
			soundMagPoint->play("sound/EnemyDead0.wav", g_saveData.gSeValue);
			break;
		case 1:
			soundMagPoint->play("sound/EnemyDead1.wav", g_saveData.gSeValue);
			break;
		case 2:
			soundMagPoint->play("sound/EnemyDead2.wav", g_saveData.gSeValue);
			break;
		case 3:
			soundMagPoint->play("sound/EnemyDead3.wav", g_saveData.gSeValue);
			break;
		case 4:
			soundMagPoint->play("sound/EnemyDead4.wav", g_saveData.gSeValue);
			break;
		case 5:
			soundMagPoint->play("sound/EnemyDead0.wav", g_saveData.gSeValue);
			break;
		}
	}
}

void monster::TypeSub(float minGague, float maxGauge, int minSubInfo, int maxSubInfo, bool isTrance, int life)
{
	m_tMonInfo.tTrance = isTrance;
	m_tMonInfo.tIslife = life;
	m_tMonInfo.tminGaugeSub = minGague;
	m_tMonInfo.tmaxGaugeSub = maxGauge;
	m_tMonInfo.tminGaugeInfo = minSubInfo;
	m_tMonInfo.tmaxGaugeInfo = maxSubInfo;
	if (m_isHealing && m_HealingCount <= m_tMonInfo.tHealingCount)
	{
		if (m_tMonInfo.tHp <= m_tMonInfo.tHpMax)
		{
			m_count++;
			if (m_count >= 10)
			{
				m_count = 0;
				m_tMonInfo.tHealing = 5.0f;
				if (!(m_tMonInfo.tHp > m_tMonInfo.tHpMax - m_SubDamgeAdd))
				{
					m_tMonInfo.tHp += m_tMonInfo.tHealing;
				}
				else
				{
					m_isHealing = false;
					m_HealingCount++;
				}
			}
		}
	}
	if (m_tMonInfo.tHp <= m_tMonInfo.tminGaugeSub)
	{
		switch (minSubInfo)
		{
		case MONSTER_SUB::MONSTER_ATT_UP:
			m_tMonInfo.tDamageSub = 1.0f;
			break;
		case MONSTER_SUB::MONSTER_DEF_UP:
			m_tMonInfo.tDef = 4.0f;
			break;
		case MONSTER_SUB::MONSTER_SPEED_UP:
			m_tMonInfo.tMoveSpeed = 1.0f;
			break;
		case MONSTER_SUB::MONSTER_POWER_UP:
			m_tMonInfo.tDamageSub += 10.0f;
			m_tMonInfo.tHp -= 5.0f;
			break;
		}
	}
	if (m_tMonInfo.tHp <= m_tMonInfo.tmaxGaugeSub)
	{
		switch (maxSubInfo)
		{
		case MONSTER_SUB::MONSTER_HP_HEALING:
			m_isHealing = true;
			break;
		case MONSTER_SUB::MONSTER_RESURRECTION:
			if (m_tMonInfo.tTrance == true)
			{
				if (m_tMonInfo.tIsAlive == false && m_lifeCount == 0)
				{
					m_lifeCount++;
					m_tMonInfo.tIsAlive = true;
					m_tMonInfo.tHp = 100.0f;
				}
				else
					m_tMonInfo.tIsAlive = false;
			}
			else if (m_tMonInfo.tIsAlive == false && m_lifeCount <= m_tMonInfo.tIslife)
			{
				m_lifeCount++;
				m_tMonInfo.tIsAlive = true;
				m_tMonInfo.tHp = 100.0f;
			}
			break;
		case MONSTER_SUB::MONSTER_NOMAL:
			// 능력이 없는 상태
			break;
		}
	}
}

void monster::update()
{

	if (!m_tMonInfo.tIsAlive) return;

	m_tMonInfo.tFireAngle = MY_UTIL::getAngle(m_tMonInfo.tPosX, m_tMonInfo.tPosY, m_PlayerCharPoint->getX(), m_PlayerCharPoint->getY());
	Move(m_tMonInfo.tMoveType);
	fireAtk();
	m_monsterMove->frameUpdate();
}

void monster::Enemy_LevelUp(int type)
{


}

void monster::render(HDC hdc)
{
	//Rectangle(hdc, m_tMonInfo.m_rc.left, m_tMonInfo.m_rc.top, m_tMonInfo.m_rc.right, m_tMonInfo.m_rc.bottom);
	//EllipseMakeCenter(hdc, m_tMonInfo.tPosX - SCROLL->GetX(), m_tMonInfo.tPosY -SCROLL->GetY() , 30, 30);

	m_monsterType->aniRender(hdc,
		(m_tMonInfo.tPosX - SCROLL->GetX()) - (m_monsterType->getFrameWidth() / 2) * m_tMonInfo.tScale*m_tMonInfo.tMonsterBoss,
		(m_tMonInfo.tPosY - SCROLL->GetY()) - (m_monsterType->getFrameHeight() / 2) * m_tMonInfo.tScale*m_tMonInfo.tMonsterBoss,
		m_monsterMove, m_tMonInfo.tScale*m_tMonInfo.tMonsterBoss, true, 255);
}

void monster::rectNotMove(RECT rRc)
{
	if (rRc.left < m_tMonInfo.m_rc.right && rRc.left > m_tMonInfo.m_rc.left)
	{
		m_tMonInfo.tPosX -= m_tMonInfo.tMoveSpeed + RECT_SIZE;
	}
	
	if (rRc.right > m_tMonInfo.m_rc.left && rRc.right < m_tMonInfo.m_rc.right)
	{
		m_tMonInfo.tPosX += m_tMonInfo.tMoveSpeed + RECT_SIZE;
	}

	if (rRc.top < m_tMonInfo.m_rc.bottom && rRc.top > m_tMonInfo.m_rc.top)
	{
		m_tMonInfo.tPosY -= m_tMonInfo.tMoveSpeed + RECT_SIZE;
	}

	if (rRc.bottom > m_tMonInfo.m_rc.top && rRc.bottom < m_tMonInfo.m_rc.bottom)
	{
		m_tMonInfo.tPosY += m_tMonInfo.tMoveSpeed + RECT_SIZE;
	}
}

monster::monster()
{
}


monster::~monster()
{
}
