#pragma once
#include "GameObject.h"

class image;
class animation;
class MyHero;
class BulletManager;


class Enemy : public GameObject
{
private:
	int m_nCurrentFrame;
	
	//int m_nEnemyNum;
	//float m_fDamage;
	image * m_pImage[2];
	animation * m_pAni[2];

	image * m_pImage_left[2];
	animation * m_pAni_left[2];
	MyHero * m_pMyHero;
	BulletManager * m_pBulletMgr;

	SYNTHESIZE(tagEnemyState, m_eState, State);

	float m_nDetectNum;
	SYNTHESIZE(RECT, m_rcMoveArea, rcMoveArea);

	
	SYNTHESIZE(int, m_nUpgradeNum, UpgradeNum);
	SYNTHESIZE(tagEnemyPattern, m_ePattern, Pattern);
	SYNTHESIZE(int, m_nEnemyNum, EnemyNumber);
	SYNTHESIZE(float, m_fFixedX, FixedX);
	SYNTHESIZE(float, m_fFixedY, FixedY);
	SYNTHESIZE(int, m_nCurrectWidth, CurrentWidth);
	SYNTHESIZE(int, m_nCurrectHeight, CurrectHeight);
	SYNTHESIZE(bool, m_bIsDown, IsDown);
	SYNTHESIZE(bool, m_bIsCollide, IsCollide);
	SYNTHESIZE(bool, m_bIsMoving, IsMoving);
	SYNTHESIZE(int, m_nFireDelay, FireDelay);
	SYNTHESIZE(int, m_nFireDelayTemp, FireDelayTemp);
	SYNTHESIZE(bool, m_bFollowOn, FollowOn);
	SYNTHESIZE(bool, m_bItemDrop, ItemDrop);

					

	// Pattern에 필요한 변수들
	int m_nCountStep;
	int m_nCountSteptemp;
	int m_nStopCount;

	SYNTHESIZE(RECT, m_rcCollide, rcCollide);

public:
	HRESULT init(int EnemyNum, tagEnemyPattern Pattern, int Upgrade);
	void update();
	void Pattern_move();
	void Damaged(float damageNum);

	void release();
	void render(HDC hdc);

	void DetectHero(MyHero * myHero);

	Enemy();
	~Enemy();
};

