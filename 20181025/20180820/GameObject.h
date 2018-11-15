#pragma once
class image;
class animation;

class GameObject
{
protected:
	SYNTHESIZE(float, m_fX, X);
	SYNTHESIZE(float, m_fY, Y);
	SYNTHESIZE(float, m_fHP, HP);
	SYNTHESIZE(float, m_fAngle, Angle);
	SYNTHESIZE(float, m_fMaxHP, MaxHP);
	SYNTHESIZE(float, m_fSpeed, Speed);
	SYNTHESIZE(float, m_fDamage, Damage);
	SYNTHESIZE(float, m_fWeight, Weight);
	SYNTHESIZE(float, m_fDef, Def);
	SYNTHESIZE(bool, m_bIsInvin, IsInvin); // 무적인지 아닌지
	SYNTHESIZE(bool, m_bIsAlive, IsAlive);
	SYNTHESIZE(bool, m_bIsGravity, IsGravity); // 중력을 받고있는지 아닌지
	SYNTHESIZE(bool, m_bIsRight, IsRight);
	SYNTHESIZE(RECT, m_rc, Rect);

private:


public:

	

	GameObject();
	~GameObject();
};

