#pragma once

class image;

class progressBar
{
private:
	RECT m_rc;
	
	float m_fWidth_heal;
	float m_fWidth_mana;
	float m_fWidth_stamina;
	float m_fHeight;
	float m_fX;
	float m_fY;

	bool m_isAlive;

	image * m_pImg_EmptyBar;
	image * m_pImg_HealthBar;
	image * m_pImg_ManaBar;
	image * m_pImg_StaminaBar;


public:
	HRESULT init(float x, float y, float width, float height);
	void release();
	void update();
	void render(HDC hdc);
	void setGauge_heal (float CurrGauge, float MaxGauge);
	void setGauge_mana(float CurrGauge, float MaxGauge);
	void setGauge_stamina(float CurrGauge, float MaxGauge);

	inline void setX(float x) { m_fX = x; }
	inline void setY(float y) { m_fY = y; }



	progressBar();
	~progressBar();
};

