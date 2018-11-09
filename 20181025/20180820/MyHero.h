#pragma once
#include "GameObject.h"

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
	SYNTHESIZE(float, m_fAccrancy, Accrancy); // 작을수록 좋다

	//RECT m_rc_Collide;
	tagCharacterState m_eState;
	int m_nJumpCount;

	SYNTHESIZE(RECT, m_rc_Collide, RectCollide);

public:
	virtual HRESULT init();
	virtual void update();
	virtual void release() ;
	virtual void render(HDC hdc);

	MyHero();
	~MyHero();
};

