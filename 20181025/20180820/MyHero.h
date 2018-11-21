#pragma once
#include "GameObject.h"

class Inventory;

class MyHero : public GameObject
{
protected:
	SYNTHESIZE(bool, m_bIsChoosed, IsChoosed);
	SYNTHESIZE(bool, m_bIsJumped, IsJumped);
	SYNTHESIZE(bool, m_bIsFloating, IsFloaing);
	SYNTHESIZE(bool, m_bIsFalling, IsFalling);
	SYNTHESIZE(bool, m_bIsRected, IsRected);
	SYNTHESIZE(bool, m_bHaveWand, haveWand);
	SYNTHESIZE(float, m_fMana, Mana);
	SYNTHESIZE(float, m_fMaxMana, MaxMana);
	SYNTHESIZE(float, m_fStamina, Stamina);
	SYNTHESIZE(float, m_fMaxStamina, MaxStamina);
	SYNTHESIZE(float, m_fJumpPower, JumpPower);
	SYNTHESIZE(float, m_fJumpTemp, JumpTemp);
	SYNTHESIZE(int, m_nCoolDown, CoolDown);
	SYNTHESIZE(int, m_nCoolDownTemp, CoolDownTemp);
	SYNTHESIZE(float, m_fAccrancy, Accrancy); // �������� ����
	SYNTHESIZE(int, m_CurrX, CurrX);
	SYNTHESIZE(int, m_CurrY, CurrY);
	SYNTHESIZE(int, m_nGravityTemp, GravityTemp);

	//RECT m_rc_Collide;
	SYNTHESIZE(tagCharacterState, m_eState, State);

	Inventory * m_pInven;

	int m_nJumpCount;

	SYNTHESIZE(RECT, m_rcLeft, rcLeft);
	SYNTHESIZE(RECT, m_rcRight, rcRight);
	SYNTHESIZE(RECT, m_rc_Collide, RectCollide);
	SYNTHESIZE(int, m_nHurtCount, HurtCount);
	SYNTHESIZE(int, m_nHurtCountTemp, HurtCountTemp);
	SYNTHESIZE(int, m_nFireDelay_Fireball, FireDelay_Fireball); // �������� ���� , ������	
	SYNTHESIZE(int, m_nFireDelayTemp_Fireball, FireDelayTemp_Fireball); // �������� ���� , �������� ��� ����ִ� ���� �������̴�.

public:

	virtual HRESULT init();
	virtual void update();
	virtual void release() ;
	virtual void render(HDC hdc);

	MyHero();
	~MyHero();
};

