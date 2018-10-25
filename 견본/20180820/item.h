#pragma once
class image;
class animation;
class effectManager;

#define ITEM_IDLE_Y_SIZE 5.0f

class item
{
private:
	image * m_pImg;
	image * m_pImgShadow;
	image * m_pItemPopupUi;

	animation * m_pAni;
	effectManager * m_pEffMag;

	RECT	m_rc;
	//float	m_fAngle;

	//float	m_fMoveAngle;
	//float	m_fAngleRadius;

	float m_fItemIdleY;
	float m_fItemIdleCurrY;
	bool m_isItemIdle;
	int m_ItemAlphaNum;

	float m_fItemX;
	float m_fItemY;

	bool m_isGet;

	bool	m_isAlive;
	tagItemInfo m_tItemInfo;

public:
	HRESULT init(const char * imageName, tagItemInfo itemInfo, effectManager * pEffItem);
	void release();
	void update();
	void render(HDC hdc);
	
	int getItemSkill() { return m_tItemInfo.tSkillType; }
	float getItemRadius() { return m_tItemInfo.tRadius; }

	tagItemInfo getItemInfo() { return m_tItemInfo; }

	bool getIsAlive() { return m_isAlive; }
	void setIsAlive(bool alive) { m_isAlive = alive; }

	void setX(float posX) { m_tItemInfo.posX = m_fItemX = posX; }
	void setY(float posY) { m_tItemInfo.posY = m_fItemY = posY; }
	void setItemIdleY(float posY) { m_fItemIdleY = posY; }
	void setItemIdleCurrY(float posY) { m_fItemIdleCurrY = posY; }

	void ItemGetSetting();

	void ItemPopup(HDC hdc);

	item();
	~item();
};

