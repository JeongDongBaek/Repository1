#include "stdafx.h"
#include "Title_Scene.h"
#include "image.h"

HRESULT Title_Scene::init()
{
	m_nindex_Scene = 0;
	m_bIsOptionOn = false;

	IMAGEMANAGER->addImage("tileset1", "image/tileset1.bmp", 4224, 32, 132, 1, true, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("tileset1_div", "image/tileset1.bmp", 4224, 32, 4, 1, true, RGB(0, 0, 0)); // 위를 4개씩으로 쪼갠것
	IMAGEMANAGER->addImage("black", "image/black.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("real_black", "image/real_black.bmp", WINSIZEX, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("white", "image/white.bmp", (WINSIZEX / 10) * 9, (WINSIZEY / 10) * 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("button_terrains", "image/button/button_placing_terrains.bmp", 250,100,1,2, (WINSIZEY / 10) * 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("button_units", "image/button/button_placing_units.bmp", 250, 100,1,2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("button_else", "image/button/button_placing_else.bmp", 250, 100,1,2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ant_idle", "image/enemy/ant_idle_ani.bmp", 296, 31, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bee_idle", "image/enemy/bee_idle_ani.bmp", 296, 39, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("crocodile_idle", "image/enemy/crocodile_idle_ani.bmp", 184, 49, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("grasshopper_idle", "image/enemy/grasshopper_idle_ani.bmp", 208, 45, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("grasshopper_jump", "image/enemy/grasshopper_jump_ani.bmp", 104, 45, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("grasshopper_fly", "image/enemy/grasshopper_fly_ani.bmp", 104, 45, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("monster_plant_idle", "image/enemy/monster_plant_idle_ani.bmp", 305, 45, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("monster_plant_attack", "image/enemy/monster_plant_attack_ani.bmp", 244, 45, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("eagle_idle", "image/enemy/eagle_idle_ani.bmp", 160, 41, 4, 1, true, RGB(255, 255, 255));
	IMAGEMANAGER->addImage("frog_idle", "image/enemy/frog_idle_ani.bmp", 140, 32, 4, 1, true, RGB(255, 255, 255));
	IMAGEMANAGER->addImage("frog_jump", "image/enemy/frog_jump_ani.bmp", 105, 35, 3, 1, true, RGB(255, 255, 255));
	IMAGEMANAGER->addImage("oposum_idle", "image/enemy/oposum_idle_ani.bmp", 216, 28, 6, 1, true, RGB(255, 255, 255));
	IMAGEMANAGER->addImage("enemy_box", "image/enemy_box.bmp", 120, 110, true, RGB(255,255,255));


	m_pImg_Menu[0] = IMAGEMANAGER->addImage("sc_gamestart", "image/button/sc_gamestart.bmp", 500, 120, true, RGB(255,255,255));
	m_pImg_Menu[1] = IMAGEMANAGER->addImage("sc_editor", "image/button/sc_editor.bmp", 500, 120, true, RGB(255,255,255));
	m_pImg_Menu[2] = IMAGEMANAGER->addImage("sc_option", "image/button/sc_option.bmp", 500, 120, true, RGB(255,255,255));
	m_pImg_Menu[3] = IMAGEMANAGER->addImage("sc_creator", "image/button/sc_creator.bmp", 500, 120, true, RGB(255,255,255));
	m_pImg_Menu[4] = IMAGEMANAGER->addImage("sc_quit", "image/button/sc_quit.bmp", 500, 120, true, RGB(255,255,255));
	m_pImg_BG = IMAGEMANAGER->addImage("black", "image/black.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	m_pImg_Parchment = IMAGEMANAGER->addImage("parchment", "image/parchment.bmp", (WINSIZEX / 4) * 3, (WINSIZEY / 4) * 3, true, RGB(255, 255, 255));
	



	AddFontResourceA("BMHANNAAir_ttf.ttf");

	return S_OK;
}

void Title_Scene::update()
{
	KeyEvent();

}

void Title_Scene::KeyEvent()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT) && ( m_nindex_Scene > 0) )
		m_nindex_Scene--;
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT) && ( m_nindex_Scene < 4 ))
		m_nindex_Scene++;
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		switch (m_nindex_Scene)
		{
		case 0:
			SCENEMANAGER->changeScene("stage");
			break;
		case 1:
			SCENEMANAGER->changeScene("editor_setsize");
			break;
		case 2:
			if (m_bIsOptionOn == false)
				m_bIsOptionOn = true;
			else
				m_bIsOptionOn = false;
			break;
		case 3:
			if (m_bIsCreatorOn == false)
				m_bIsCreatorOn = true;
			else
				m_bIsCreatorOn = false;
			break;
		case 4:
			PostQuitMessage(0);
			break;

		}
	}
	
	
}


void Title_Scene::release()
{
}

void Title_Scene::render(HDC hdc)
{
	m_pImg_BG->render(hdc, 0, 0);

	m_pImg_Menu[m_nindex_Scene]->render(hdc, WINSIZEX / 2 - m_pImg_Menu[0]->getWidth() / 2 , WINSIZEY / 2 + 200);

	if (m_bIsOptionOn == true)
	{
		m_pImg_Parchment->render(hdc, WINSIZEX / 2 - m_pImg_Parchment->getWidth() / 2, WINSIZEY / 2 - m_pImg_Parchment->getHeight() / 2);

	}

	if (m_bIsCreatorOn == true)
	{
		m_pImg_Parchment->render(hdc, WINSIZEX / 2 - m_pImg_Parchment->getWidth() / 2, WINSIZEY / 2 - m_pImg_Parchment->getHeight()/ 2);

		char SzText1[128];
		// TRANSPARENT : 투명, OPAQUE : 불투명
		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, RGB(255, 240, 200));
		MY_UTIL::FontOption(hdc, 42, 0);


		char SzText2[256];
		int temp = 58;
		int tempS = 220;
		// TRANSPARENT : 투명, OPAQUE : 불투명
		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, RGB(25, 140, 140));
		MY_UTIL::FontOption(hdc, 42, 0);

		sprintf_s(SzText1, "%s : ", "만 든 이 들");
		TextOut(hdc, WINSIZEX / 2 - 110, tempS + temp, SzText1, strlen(SzText1)); temp += 58;

		sprintf_s(SzText2, "%s  ", "정민욱");
		TextOut(hdc, WINSIZEX / 2 - 70, tempS + temp, SzText2, strlen(SzText2)); temp += 58;

		sprintf_s(SzText2, "%s :  ", "사용프로그램");
		TextOut(hdc, WINSIZEX / 2 - 124, tempS + temp, SzText2, strlen(SzText2)); temp += 58;

		SetTextColor(hdc, RGB(255, 140, 200));
		sprintf_s(SzText2, "%s  ", "비쥬얼스튜디오 (winAPI)");
		TextOut(hdc, WINSIZEX / 2 - 202, tempS + temp, SzText2, strlen(SzText2)); temp += 58;

		SetTextColor(hdc, RGB(255, 88, 200));
		sprintf_s(SzText2, "%s  ", "제작기간 : ");
		TextOut(hdc, WINSIZEX / 2 - 95, tempS + temp, SzText2, strlen(SzText2)); temp += 58;

		SetTextColor(hdc, RGB(255, 2, 200));
		sprintf_s(SzText2, "%s  ", "3주 (3 week)");
		TextOut(hdc, WINSIZEX / 2 - 123, tempS + temp, SzText2, strlen(SzText2)); temp += 33;

		MY_UTIL::FontOption(hdc, 29, 0);
		SetTextColor(hdc, RGB(255, 2, 188));
		sprintf_s(SzText2, "%s  ", "2018.10.01 ~ 2018.10.22");
		TextOut(hdc, WINSIZEX / 2 - 163, tempS + temp, SzText2, strlen(SzText2)); temp += 58;

		MY_UTIL::FontDelete(hdc);

	}



}






Title_Scene::Title_Scene()
{
}

Title_Scene::~Title_Scene()
{
}
