#pragma once
#include "GameObject.h"

class MyHero : public GameObject
{
protected:
	bool m_bIsChoosed;
	tagCharacterState m_eState;

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

