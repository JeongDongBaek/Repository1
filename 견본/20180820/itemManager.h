#pragma once
#include <vector>
#include "item.h"

class itemManager
{
private:
	std::vector<item*>			m_vecItem;
	std::vector<item*>::iterator	m_iter;

	std::vector<std::string> m_vecItemList;

	int m_itemMax;
	tagItemInfo m_tItemInfo[24];

public:
	HRESULT init(int vecMaxSize);
	void release();
	void update();
	void render(HDC hdc);

	void itemDrop(const char * imageName, int itemNum, tagItemInfo bulletInfo, effectManager * pEffMag);
	void itemGet(const char * imageName, tagItemInfo itemInfo);

	int getItemMax() { return m_itemMax; }

	inline std::vector<item*> getVecItem()
	{
		return m_vecItem;
	}

	itemManager();
	~itemManager();
};

