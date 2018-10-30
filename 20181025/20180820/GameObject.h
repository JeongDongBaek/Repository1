#pragma once
class image;
class animation;

class GameObject
{
protected:
	//// 오브젝트 공통값 ///
	float m_fX;
	float m_fY;
	float m_fHP;
	float m_fSpeed;
	float m_fWeight;

	bool m_bIsInvin; // 무적인지 아닌지
	bool m_bIsAlive;
	/////////////

	image * m_pImage;
	animation * m_pAni;



private:


public:
	inline float getX() { return m_fX; }
	inline float getY() { return m_fY; }
	inline float getHP() { return m_fHP; }
	inline float getWeight() { return m_fWeight; }
	inline float getSpeed() { return m_fSpeed; }
	inline bool getIsAlive() { return m_bIsAlive; }
	inline bool getIsInvin() { return m_bIsInvin; }

	virtual HRESULT init() = 0;
	virtual void update() = 0;
	virtual void release() = 0;
	virtual void render(HDC hdc) = 0;

	GameObject();
	~GameObject();
};

