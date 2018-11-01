#pragma once
#include "GameObject.h"

class image;
class animation;


class Enemy : public GameObject
{
private:
	tagEnemyPattern m_ePattern;
	int m_nEnemyNum;
	bool m_bIsMoving;
	image * m_pImage;

public:
	HRESULT init();
	void update();

	void release();
	void render(HDC hdc);

	HRESULT Editor_Create(int EnemyNumber);


	Enemy();
	~Enemy();
};

