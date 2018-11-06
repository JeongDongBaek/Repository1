#pragma once
class image;
class animation;

class item
{
	image * m_pImg_item;
	image * m_pImg_itemShadow;
	animation * m_pAni;

	SYNTHESIZE(int, m_nItemNumber, itemNumber);

public:



	item();
	~item();
};

