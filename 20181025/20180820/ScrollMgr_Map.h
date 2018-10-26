#pragma once
#include "singletonBase.h"

class ScrollMgr_Map : public singletonBase<ScrollMgr_Map>
{
private:
	float m_fX;
	float m_fY;

	float m_fCenterX;
	float m_fCenterY;

	float m_fMaxofX;
	float m_fMaxofY;

	float m_fCameraSpeed;
	
	RECT m_rc;

public:
	HRESULT init();
	void release();
	void update();
	void KeyEvent();

	void render(HDC hdc);

	float GetX() { return m_fX; }
	void SetX(float fX) { m_fX = fX; }
	float GetY() { return m_fY; }
	void SetY(float fY) { m_fX = fY; }

	ScrollMgr_Map();
	~ScrollMgr_Map();
};

