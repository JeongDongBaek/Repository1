#pragma once
#include "GameObject.h"

class MyHero : public GameObject
{
protected:
	bool m_bIsChoosed;
	bool m_bIsJumped;
	bool m_bIsFloating;
	bool m_bIsFalling;
	bool m_bIsRected;

	float m_fMana;
	float m_fStamina;
	float m_fJumpPower;
	float m_fJumpTemp;

	//RECT m_rc_Collide;
	tagCharacterState m_eState;
	int m_nJumpCount;

	SYNTHESIZE(RECT, m_rc_Collide, RectCollide);

public:
	virtual HRESULT init();
	virtual void update();
	virtual void release() ;
	virtual void render(HDC hdc);


	inline bool getIsChoosed() { return m_bIsChoosed; }
	inline void setIsChoosed(bool isChoosed) { m_bIsChoosed = isChoosed; }

	inline bool getIsRected() { return m_bIsRected; }
	inline void setIsRected(bool bIsRected) { m_bIsRected = bIsRected; }

	MyHero();
	~MyHero();
};

