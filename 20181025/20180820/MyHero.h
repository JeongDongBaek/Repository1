#pragma once
#include "GameObject.h"

class MyHero : public GameObject
{
protected:
	bool m_bIsChoosed;
	bool m_bIsJumped;

	float m_fMana;
	float m_fStamina;
	float m_fJumpPower;
	float m_fJumpTemp;

	tagCharacterState m_eState;
	int m_nJumpCount;

public:
	virtual HRESULT init();
	virtual void update();
	virtual void release() ;
	virtual void render(HDC hdc);


	inline bool getIsChoosed() { return m_bIsChoosed; }
	inline void setIsChoosed(bool isChoosed) { m_bIsChoosed = isChoosed; }
	MyHero();
	~MyHero();
};

