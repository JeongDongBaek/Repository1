#pragma once
#include "GameObject.h"

class image;
class animation;


class Enemy : public GameObject
{
private:
	int m_nCurrentFrame;
	
	//int m_nEnemyNum;
	//float m_fDamage;
	image * m_pImage[2];
	animation * m_pAni[2];
	tagEnemyState m_eState;

	float m_nDetectNum;
	RECT m_rcMoveArea;

	SYNTHESIZE(int, m_nUpgradeNum, UpgradeNum);
	SYNTHESIZE(tagEnemyPattern, m_ePattern, Pattern);
	SYNTHESIZE(int, m_nEnemyNum, EnemyNumber);
	SYNTHESIZE(float, m_fDamage, Damage);
	SYNTHESIZE(int, m_nCurrectWidth, CurrentWidth);
	SYNTHESIZE(int, m_nCurrectHeight, CurrectHeight);


	// Pattern에 필요한 변수들
	int m_nCountStep;
	int m_nMaxCountStep;
	bool m_bIsMoving;

	SYNTHESIZE(RECT, m_rcCollide, rcCollide);

public:
	HRESULT init(int EnemyNum, tagEnemyPattern Pattern, int Upgrade);
	void update();
	void Pattern_move();

	void release();
	void render(HDC hdc);


	Enemy();
	~Enemy();
};

