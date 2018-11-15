#include "stdafx.h"
#include "progressBar.h"


HRESULT progressBar::init(float x, float y, float width, float height)
{

	m_fX = x;
	m_fY = y;
	m_fWidth_heal = width;
	m_fWidth_mana = width;
	m_fWidth_stamina = width;
	m_fHeight = height;

	m_rc = RectMake(m_fX, m_fY, m_fWidth_heal, m_fHeight);
	
	m_pImg_EmptyBar = IMAGEMANAGER->addImage("empty_bar", "image/ui/empty_bar.bmp", m_fWidth_heal, m_fHeight, true, RGB(255, 0, 255));
	m_pImg_HealthBar = IMAGEMANAGER->addImage("health_bar", "image/ui/health_bar.bmp", m_fWidth_heal, m_fHeight, true, RGB(255, 0, 255));
	m_pImg_StaminaBar = IMAGEMANAGER->addImage("stamina_bar", "image/ui/stamina_bar.bmp", m_fWidth_heal, m_fHeight, true, RGB(255, 0, 255));
	m_pImg_ManaBar = IMAGEMANAGER->addImage("mana_bar", "image/ui/mana_bar.bmp", m_fWidth_heal, m_fHeight, true, RGB(255, 0, 255));

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
	m_pImg_EmptyBar->render(hdc, m_fX, m_fY + 0);
	m_pImg_HealthBar->render(hdc, m_fX, m_fY + 0, 0, 0, m_fWidth_heal, m_fHeight);
	m_pImg_EmptyBar->render(hdc, m_fX, m_fY + 32);
	m_pImg_StaminaBar->render(hdc, m_fX, m_fY + 32, 0, 0, m_fWidth_stamina, m_fHeight);
	m_pImg_EmptyBar->render(hdc, m_fX, m_fY + 64);
	m_pImg_ManaBar->render(hdc, m_fX, m_fY + 64, 0,0, m_fWidth_mana, m_fHeight);



	
}

void progressBar::setGauge_heal(float CurrGauge, float MaxGauge)
{
	m_fWidth_heal = (CurrGauge / MaxGauge) * m_pImg_HealthBar->getWidth();
}

void progressBar::setGauge_mana(float CurrGauge, float MaxGauge)
{
	m_fWidth_mana = (CurrGauge / MaxGauge) * m_pImg_ManaBar->getWidth();
}

void progressBar::setGauge_stamina(float CurrGauge, float MaxGauge)
{
	m_fWidth_stamina = (CurrGauge / MaxGauge) * m_pImg_StaminaBar->getWidth();
}

progressBar::progressBar()
{
}


progressBar::~progressBar()
{
}
