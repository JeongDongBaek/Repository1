#pragma once

class Inventory;

class InventoryManager
{
private:
	vector<Inventory*> m_vec;
	vector<Inventory*>::iterator m_iter;
	
	int m_nLimitNum;

public:

	HRESULT init(int MaxLimitNumber);

	void setInven(int m_nEnemyNum, float StartingX, float StartingY, int UpGrade); // gSelectedInven (전역변수) 에 따라 렌더링한다.

	void release();
	void update();
	void render(HDC hdc);

	int getIter() { return m_vec.size(); }
	inline std::vector<Inventory*> getVec()
	{
		return m_vec;
	}



	InventoryManager();
	~InventoryManager();
};

