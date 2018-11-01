#pragma once

class image;

class progressBar
{
private:
	RECT m_rc;
	
	float m_fWidth;
	float m_fHeight;
	float m_fX;
	float m_fY;

	bool m_isAlive;


	image * m_pImage_Top;
	image * m_pImage_Bottom;

public:
	HRESULT init(float x, float y, float width, float height);
	void release();
	void update();
	void render(HDC hdc);

	inline void setX(float x) { m_fX = x; }
	inline void setY(float y) { m_fY = y; }



	progressBar();
	~progressBar();
};

