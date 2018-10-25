#include "stdafx.h"
#include "Title_Scene.h"
#include "image.h"

HRESULT Title_Scene::init()
{
	m_nindex_Scene = 0;
	m_bIsOptionOn = false;

	IMAGEMANAGER->addImage("tileset1", "image/tileset1.bmp", 4096, 32, 128, 1, true, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("tileset1_div", "image/tileset1.bmp", 4096, 32, 32, 1, true, RGB(0, 0, 0)); // À§¸¦ 4°³¾¿À¸·Î ÂÉ°µ°Í
	IMAGEMANAGER->addImage("black", "image/black.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	m_pImg_Menu[0] = IMAGEMANAGER->addImage("sc_gamestart", "image/sc_gamestart.bmp", 500, 120, true, RGB(255,255,255));
	m_pImg_Menu[1] = IMAGEMANAGER->addImage("sc_editor", "image/sc_editor.bmp", 500, 120, true, RGB(255,255,255));
	m_pImg_Menu[2] = IMAGEMANAGER->addImage("sc_option", "image/sc_option.bmp", 500, 120, true, RGB(255,255,255));
	m_pImg_Menu[3] = IMAGEMANAGER->addImage("sc_creator", "image/sc_creator.bmp", 500, 120, true, RGB(255,255,255));
	m_pImg_Menu[4] = IMAGEMANAGER->addImage("sc_quit", "image/sc_quit.bmp", 500, 120, true, RGB(255,255,255));
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
			if(m_bIsOptionOn == false)
				m_bIsOptionOn = true;
			break;
		case 3:
			if(m_bIsCreatorOn == false)
				m_bIsCreatorOn = true;
			break;
		case 4:
			PostQuitMessage(0);
			break;

		}
	}
	if (m_bIsOptionOn)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			m_bIsOptionOn = false;
		}
	}
	
	if (m_bIsCreatorOn)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			m_bIsCreatorOn = false;
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

	}

	if (m_bIsCreatorOn == true)
	{
		m_pImg_Parchment->render(hdc, WINSIZEX / 2 - m_pImg_Parchment->getWidth() / 2, WINSIZEY / 2 - m_pImg_Parchment->getHeight()/ 2);
	}



}






Title_Scene::Title_Scene()
{
}

Title_Scene::~Title_Scene()
{
}
