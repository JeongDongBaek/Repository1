#pragma once
#include "MyHero.h"

class image;
class animation;
class BulletManager;
class progressBar;
class effectManager;

enum tagFoxMode
{
	Mode_isFox, Mode_isBug 
};

class Fox : public MyHero
{
private:

	tagFoxMode FoxCurrMode;
	int m_nCurrentFrame;
	image * m_pImage[6];					//;
											//_Jump;
											//_Run;
											//_Hurt;
											//_Climb;
											//_Fall;

	image * m_pImage_left[6];

	image * m_pImage_Bug[2];
	image * left_m_pImage_Bug[2];

	animation * m_pAni_Bug[2];
	animation * left_m_pAni_Bug[2];

	BulletManager * m_pBulletMgr;
	animation * m_pAni[6];
	animation * m_pAni_left[6];

	progressBar * m_pProgressBar;
	effectManager * m_pEffectMgr;

public:
	HRESULT init();
	void update();
	void KeyEvent();
	void Gravity(float Gravity);
	void Damaged(float damage);

	void release();
	void render(HDC hdc);


	Fox();
	~Fox();
};
