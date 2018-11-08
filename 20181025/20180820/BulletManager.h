#pragma once
#include "Bullet.h"

class BulletManager
{
private:
	std::vector<Bullet*>			m_vecBullet;
	std::vector<Bullet*>::iterator  m_iter;

	SYNTHESIZE(int, m_nLimit, Limit);

public:

	HRESULT init(int limit);
	void Fire(const char* ImageName, float x, float y, float Speed, float Range, int RectType, bool isRight, bool istarget = false);
	void update();

	void release();
	void render(HDC hdc);


	BulletManager();
	~BulletManager();
};

