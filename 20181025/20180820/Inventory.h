#pragma once

class image;
class item;


class Inventory // 아이템정보를 전달받음
{
private:
	int m_nLimitItem;
	vector<item*> m_vec;
	vector<item*>::iterator m_iter;
	std::vector<std::string> m_vecItemList;
	tagItemInfor m_tItem[12];

	SYNTHESIZE(int, m_nQuantity, Quantity);
	int m_nNumberofKindItem;


public:
	HRESULT init(int LimitItem);
	void AddItem(tagItemInfor ItemNumber);



	void release();
	void update();

	void render(HDC hdc);


	int getIter() { return m_vec.size(); }
	inline std::vector<item*> getVec()
	{
		return m_vec;
	}

	Inventory();
	~Inventory();
};

