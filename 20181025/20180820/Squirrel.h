#pragma once
#include "MyHero.h"

class BulletManager;
class animation;
class image;
class progressBar;


class Squirrel : public MyHero
{
private:
	image * m_pImage[6];
	
	image * m_pImage_left[6];

	animation * m_pAni[6];
	animation * m_pAni_left[6];
	BulletManager * m_pBulletMgr;

	progressBar * m_pProgressBar;

public:
	HRESULT init();
	void update();
	void KeyEvent();
	void Gravity(float Gravity);
	void Damaged(float damage);

	void release();
	void render(HDC hdc);



	Squirrel();
	~Squirrel();
};

