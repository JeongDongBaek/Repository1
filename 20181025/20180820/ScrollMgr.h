#pragma once
#include "singletonBase.h"

//화면은 WINSIZEX 와 WINSIZEY
// 처음 좌표는 0, 0

class ScrollMgr : public singletonBase<ScrollMgr>
{
private:
	bool m_isFirst;
	float m_fX;
	float m_fY;
	float m_fMaxofX;
	float m_fMaxofY;

	RECT m_rc;
	
public:
	HRESULT init();

	void release();
	void update(float playerX, float playerY);

	void render(HDC hdc);


	float GetX() { return m_fX; }
	void SetX(float fX) { m_fX = fX; }
	float GetY() { return m_fY; }
	void SetY(float fY) { m_fX = fY; }


	RECT GetRC() { return m_rc; }

	ScrollMgr();
	~ScrollMgr();
};

