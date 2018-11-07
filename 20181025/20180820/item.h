#pragma once
class image;
class animation;
class effectManager;

class item
{
	image * m_pImg_item;
	image * m_pImg_itemShadow;
	animation * m_pAni;
	effectManager * m_pEffectMgr;

	RECT m_rc;
	SYNTHESIZE(bool,m_bIsAlive, IsAlive);
	SYNTHESIZE(int,m_nItemAlphaNum, itemAlphaNum);
	tagItemInfor m_tItemInfor;

public:
	HRESULT init();

	void release();
	void update();
	void render(HDC hdc);


	item();
	~item();
};

