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
	virtual void update();
	virtual void release();
	virtual void render(HDC hdc);

	Enemy();
	~Enemy();
};

