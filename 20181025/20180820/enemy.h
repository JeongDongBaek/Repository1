#pragma once
#include "GameObject.h"

class image;
class animation;


class Enemy : public GameObject
{
private:
	tagEnemyPattern m_ePattern;
	//int m_nEnemyNum;
	//float m_fDamage;
	bool m_bIsMoving;
	image * m_pImage[2];
	animation * m_pAni[2];

	SYNTHESIZE(int, m_nEnemyNum, EnemyNumber);
	SYNTHESIZE(float, m_fDamage, Damage);


public:
	HRESULT init();
	void update();

	void release();
	void render(HDC hdc);

	HRESULT Editor_Create(int EnemyNumber);


	Enemy();
	~Enemy();
};

