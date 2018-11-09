#pragma once
#include "item.h"
#include <vector>
#include "singletonBase.h"

class EffectManager;

class ItemManager : public singletonBase<ItemManager>
{
private:
	std::vector<item*> m_vecItem;
	std::vector<item*>::iterator m_iter;
	std::vector<std::string> m_vecItemList;
	effectManager * m_pEffectMgr;

	int m_nMaxLimitNumber;
	int m_nNumberofKindItem;
	tagItemInfor m_tItem[12];
	
public:
	HRESULT init(int MaxLimitNumber);

	void release();
	void update();

	void ItemCreate(float x, float y, int ItemNumber, bool persisting);

	static bool comp(item* a, item* b);

	void render(HDC hdc);


	int getIter() { return m_vecItem.size(); }
	inline std::vector<item*> getVec()
	{
		return m_vecItem;
	}

	void SetEffectPoint(effectManager * effect) { m_pEffectMgr = effect; }


	ItemManager();
	~ItemManager();
};

