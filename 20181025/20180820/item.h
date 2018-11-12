#pragma once
class image;
class animation;
class effectManager;

class item
{
	image * m_pImg_item;
	animation * m_pAni;
	effectManager * m_pEffectMgr;

	image * m_pImg_Text;

	float m_fX;
	float m_fY;
	float m_fItemfloppingNum; // 높을수록 밑으로
	bool m_bItemfloppingUpDown;
	bool m_bItemPersisting;
	int m_nAlphaBlendNum;
	int m_nTwinkleNum; // 높아질수록 투명에 가까워짐
	int m_nCountTemp;
	bool m_bAlpahBlendUpDown;
	
	SYNTHESIZE(RECT, m_rc, Rect);

	SYNTHESIZE(tagItemInfor, m_tItemInfor, ItemInformation);


	SYNTHESIZE(bool, m_bIsAlive, IsAlive);
	SYNTHESIZE(int, m_nIndex, Index);

	

public:
	HRESULT init(float x, float y, tagItemInfor itemNumber, bool persisting);

	void release();
	void update();
	void flopping();
	void twinkle();

	void render(HDC hdc);


	item();
	~item();
};

