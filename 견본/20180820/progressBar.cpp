#include "stdafx.h"
#include "progressBar.h"

HRESULT progressBar::init(float x, float y, float width, float height)
{
	m_isBoom = false;
	m_fX = x;
	m_fY = y;
	m_tMonInfo.tHp = width;
	m_fWidth = m_tMonInfo.tHp;
	m_fHeight = height;
	
	m_rc = RectMake(m_fX, m_fY, m_fWidth, m_fHeight);

	m_imgTop = IMAGEMANAGER->addImage("barTop", 
		"image/resources/UI_image/Progress_Bar/hpBarTop.BMP", m_fWidth, m_fHeight, true, RGB(255, 0, 255));
	m_imgBottom = IMAGEMANAGER->addImage("barBottom",
		"image/resources/UI_image/Progress_Bar/hpBarBottom.BMP", m_fWidth, m_fHeight, true, RGB(255, 0, 255));

	return S_OK;
}

void progressBar::release()
{
}

void progressBar::update()
{
}

void progressBar::render(HDC hdc)
{
	IMAGEMANAGER->findImage("barBottom")->render(hdc, m_fX, m_fY);
	IMAGEMANAGER->findImage("barTop")->render(hdc, m_fX, m_fY,
		0, 0, m_fWidth, m_imgTop->getHeight());
}

void progressBar::setGauge(float currGauge, float maxGauge)
{
	m_tMonInfo.tHpMax = maxGauge;
	m_tMonInfo.tHp = currGauge;
	m_fWidth = (m_tMonInfo.tHp / m_tMonInfo.tHpMax) * m_imgTop->getWidth();
}


progressBar::progressBar()
{
}


progressBar::~progressBar()
{
}
