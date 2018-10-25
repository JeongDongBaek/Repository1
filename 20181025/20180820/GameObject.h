#pragma once
class GameObject
{
private:

	//// 오브젝트 공통값 ///
	int m_nLevel;
	float m_fX;
	float m_fY;
	float m_fHP;
	float m_fSpeed;
	/////////////


public:
	GameObject();
	~GameObject();
};

