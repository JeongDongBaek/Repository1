#include "stdafx.h"
#include "progressBar.h"


HRESULT progressBar::init(float x, float y, float width, float height)
{

	m_fX = x;
	m_fY = y;
	m_fWidth = width;
	m_fHeight = height;

	m_rc = RectMake(m_fX, m_fY, m_fWidth, m_fHeight);
	
	m_pImage_Top = IMAGEMANAGER->findImage("ui_bar_top");
	m_pImage_Bottom = IMAGEMANAGER->findImage("ui_bar_bottom");



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
	m_pImage_Top->render(hdc, m_fX, m_fY);
	m_pImage_Bottom->render(hdc, m_fX, m_fY);
}

progressBar::progressBar()
{
}


progressBar::~progressBar()
{
}
