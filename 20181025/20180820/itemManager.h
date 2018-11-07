#pragma once
#include "item.h"
#include <vector>

class ItemManager
{
private:
	std::vector<item*> m_vecItem;
	std::vector<item*>::iterator m_iter;
	std::vector<std::string> m_vecItemList;

	int m_nMaxLimitNumber;
	int m_nNumberofKindItem;
	tagItemInfor m_tItem[12];
	
public:
	HRESULT init(int MaxLimitNumber);

	void release();
	void update();

	void ItemCreate();

	void render(HDC hdc);

	ItemManager();
	~ItemManager();
};

