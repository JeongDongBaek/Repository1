#pragma once
#include "Boomerang.h"


class BoomerangMgr

{
private:
	std::vector<Boomerang*> m_vecBoomerang;
	std::vector<Boomerang*>::iterator m_iter;

	SYNTHESIZE(int,m_nLimit, Limit);

public:
	HRESULT init(int limit);
	void Fire(float x, float y, float Player_Speed, float DestiX, float DestiY, float m_fAccuracy);
	void update();

	void release();
	void render(HDC hdc);

	BoomerangMgr();
	~BoomerangMgr();
};

