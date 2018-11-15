#pragma once
#include "MyHero.h"

class image;
class animation;
class BoomerangMgr;
class BulletManager;
class progressBar;

//enum tagStandState
//{
//	stand_Tile, stand_Air_Up, Stand_Air_Down
//};

class Rabbit : public MyHero
{
private:
	image * m_pImage[6];
												//_Jump;
												//_Run;
												//_Fall;
												//_Hurt;
												//_Climb;
	image * m_pImage_left[6];
	image * m_pImage_boomerang;
	BoomerangMgr * m_pBoomerang;
	BulletManager * m_pBulletMgr;

	animation * m_pAni[6];
	animation * m_pAni_left[6];

	progressBar * m_pProgressBar;


	bool m_bIsBoomerangOn;

	// item ���밡�� ������
	
	/////// speed , MaxHP, MaxStamina, MaxMana, Damage, Def, JumpPower
	SYNTHESIZE(int, m_nFireDelay, FireDelay); // �������� ���� , ������	
	SYNTHESIZE(int, m_nFireDelayTemp, FireDelayTemp); // �������� ���� , �������� ��� ����ִ� ���� �������̴�.
	///////

public:
	HRESULT init();
	void update();
	void KeyEvent();
	void Gravity(float Gravity);
	void Damaged(float damage);

	void release();
	void render(HDC hdc);

	Rabbit();
	~Rabbit();
};

// 