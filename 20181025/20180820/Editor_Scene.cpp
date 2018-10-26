#include "stdafx.h"
#include "Editor_Scene.h"
#include "button.h"
#include "animation.h"
#include "Enemy.h"

int Editor_Scene::m_editorStateNum = 0;

static void button_func0(void)
{
	Editor_Scene::m_editorStateNum = 0;
}

static void button_func1(void)
{
	Editor_Scene::m_editorStateNum = 1;
}

static void button_func2(void)
{
	Editor_Scene::m_editorStateNum = 2;
}


void Editor_Scene::ButtonEvent(HWND hWnd, UINT iMessage, WPARAM wParam)
{
	switch (LOWORD(wParam))
	{
	case 32788: //Save
		MessageBox(hWnd, "Save Button Clicked", "Button", MB_OK);
		SaveEvent();
		break;
	case 32791: // Load
		MessageBox(hWnd, "Load Button Clicked", "Button", MB_OK);
		LoadEvent();
		break;
	case 32781: // Save and Start
		MessageBox(hWnd, "Save Button Clicked", "Button", MB_OK);
		SaveEvent();
		SCENEMANAGER->changeScene("stage");
		break;
	case 32801: // Exit
		PostQuitMessage(0);
		break;
	case 32804: // return to titleScene
		SCENEMANAGER->changeScene("title");
		break;

	}

	// aboutBox 여는법
	// 윈도우 MessageBox처럼 기본 함수가 있다.
	
}
void Editor_Scene::SaveEvent()
{
}

void Editor_Scene::LoadEvent()
{
}












HRESULT Editor_Scene::init()
{

	m_bIsMiniMapOn = false;
	m_bIsHelpOn = false;
	m_bIsAutoOn = false;
	m_bIsUIOpen = false;
	m_bIsSel = false;
	m_bIsTextOn = false;
	m_editorState = st_Terrains;

	init_image();
	SCROLL_MAP->init();
	m_pButton_Terrains = new button;
	m_pButton_Terrains->init("button_terrains", WINSIZEX / 2 - IMAGEMANAGER->findImage("button_else")->getWidth() / 2 - 220, WINSIZEY / 2 + 270
		, PointMake(0,1), PointMake(0,0), button_func0);

	m_pButton_Units = new button;
	m_pButton_Units->init("button_units", WINSIZEX / 2 - 0, WINSIZEY / 2 + 270
		, PointMake(0, 1), PointMake(0, 0), button_func1);

	m_pButton_Else = new button;
	m_pButton_Else->init("button_else", WINSIZEX / 2 + IMAGEMANAGER->findImage("button_else")->getWidth() / 2 + 220, WINSIZEY / 2 + 270
		, PointMake(0, 1), PointMake(0, 0), button_func2);

	int tempB = 0;
	m_pImg_Enemy[tempB] = IMAGEMANAGER->findImage("ant_idle"); tempB++;
	m_pImg_Enemy[tempB] = IMAGEMANAGER->findImage("bee_idle"); tempB++;
	m_pImg_Enemy[tempB] = IMAGEMANAGER->findImage("crocodile_idle"); tempB++;
	m_pImg_Enemy[tempB] = IMAGEMANAGER->findImage("grasshopper_idle"); tempB++;
	//m_pImg_Enemy[tempB] = IMAGEMANAGER->findImage("grasshopper_jump"); tempB++;//
	//m_pImg_Enemy[tempB] = IMAGEMANAGER->findImage("grasshopper_fly"); tempB++;//
	m_pImg_Enemy[tempB] = IMAGEMANAGER->findImage("monster_plant_idle"); tempB++;
	//m_pImg_Enemy[tempB] = IMAGEMANAGER->findImage("monster_plant_attack"); tempB++;//
	m_pImg_Enemy[tempB] = IMAGEMANAGER->findImage("eagle_idle"); tempB++;
	m_pImg_Enemy[tempB] = IMAGEMANAGER->findImage("frog_idle"); tempB++;
	//m_pImg_Enemy[tempB] = IMAGEMANAGER->findImage("frog_jump"); tempB++;
	m_pImg_Enemy[tempB] = IMAGEMANAGER->findImage("oposum_idle"); tempB++;


	for (int i = 0; i < NUMBER_OF_KIND_UNITS - 4; ++i)
	{
		m_pAni_Enemy[i] = new animation;
		m_pAni_Enemy[i]->init(m_pImg_Enemy[i]->getWidth(), m_pImg_Enemy[i]->getHeight(), m_pImg_Enemy[i]->getFrameWidth(), m_pImg_Enemy[i]->getFrameHeight());
		m_pAni_Enemy[i]->setDefPlayFrame(false, true);
		m_pAni_Enemy[i]->setFPS(13);
		m_pAni_Enemy[i]->start();
	}

	
	init_tileset();


	return S_OK;
}
void Editor_Scene::init_image()
{
	m_pImg_UIopen = IMAGEMANAGER->findImage("white");
	m_pImg_BG = IMAGEMANAGER->findImage("black");
	m_pImg_tileset1 = IMAGEMANAGER->findImage("tileset1");
	m_pImg_tileset1_div = IMAGEMANAGER->findImage("tileset1_div");
	m_pImg_EnemyBox = IMAGEMANAGER->findImage("enemy_box");
}

void Editor_Scene::init_tileset()
{
	// 기본 타일 정보 셋팅
	for (int x = 0; x < g_saveData.gTileMaxCountX; x++)
	{
		for (int y = 0; y < g_saveData.gTileMaxCountY; y++)
		{
			m_pTiles[x * g_saveData.gTileMaxCountX + y].rc = RectMake(0 + x * TILESIZEX, 0 + y * TILESIZEY, TILESIZEX, TILESIZEY);
			m_pTiles[x * g_saveData.gTileMaxCountX + y].terrainFrameX = 130;
			m_pTiles[x * g_saveData.gTileMaxCountX + y].terrainFrameY = 0;  // 29

		}
	}

}

void Editor_Scene::update()
{
	for (int i = 0; i < NUMBER_OF_KIND_UNITS - 4; ++i)
	{
		m_pAni_Enemy[i]->frameUpdate(TIMEMANAGER->getElapsedTime());
	}

	SCROLL_MAP->update();
	KeyEvent();
	buttonUpdate();
	update_once();


}

void Editor_Scene::KeyEvent()
{
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		if (m_bIsUIOpen == true)
			m_bIsUIOpen = false;
		else
			m_bIsUIOpen = true;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F7))
	{
		if (m_bIsGridOn == true)
			m_bIsGridOn = false;
		else
			m_bIsGridOn = true;
	}
}

void Editor_Scene::buttonUpdate()
{
	if (m_bIsUIOpen == true)
	{
		m_pButton_Terrains->update();
		m_pButton_Units->update();
		m_pButton_Else->update();
	}

	switch (Editor_Scene::m_editorStateNum)
	{
	case 0:
		m_editorState = st_Terrains;
		break;
	case 1:
		m_editorState = st_Units;
		break;
	case 2:
		m_editorState = st_else;
		break;
	}
}

void Editor_Scene::update_once()
{
}





void Editor_Scene::release()
{
}

void Editor_Scene::render(HDC hdc)
{
	m_pImg_BG->render(hdc, 0, 0);

	for (int x = 0; x < g_saveData.gTileMaxCountX; x++)
	{
		for (int y = 0; y < g_saveData.gTileMaxCountY; y++)
		{
			m_pImg_tileset1->frameRender(hdc,
				m_pTiles[x *  g_saveData.gTileMaxCountX + y].rc.left -SCROLL_MAP->GetX(),
				m_pTiles[x *  g_saveData.gTileMaxCountX + y].rc.top - SCROLL_MAP->GetY(),
				m_pTiles[x *  g_saveData.gTileMaxCountX + y].terrainFrameX,
				m_pTiles[x *  g_saveData.gTileMaxCountX + y].terrainFrameY);
		}
	}

	if (m_bIsGridOn == true)
	{
		for (int i = 1; i < g_saveData.gTileMaxCountX; ++i)
		{
			MoveToEx(hdc, i * TILESIZEX - SCROLL_MAP->GetX(), 0 - SCROLL_MAP->GetY(), NULL);
			LineTo(hdc, i * TILESIZEX - SCROLL_MAP->GetX(), g_saveData.gTileMaxCountY * TILESIZEY - SCROLL_MAP->GetY());
		}

		for (int i = 1; i < g_saveData.gTileMaxCountY; ++i)
		{
			MoveToEx(hdc, 0 - SCROLL_MAP->GetX(), i * TILESIZEY - SCROLL_MAP->GetY(), NULL);
			LineTo(hdc, g_saveData.gTileMaxCountX * TILESIZEX - SCROLL_MAP->GetX(), i * TILESIZEY - SCROLL_MAP->GetY());
		}
	}



	if (m_bIsUIOpen == true)
	{
		m_pImg_UIopen->render(hdc, WINSIZEX / 2 - m_pImg_UIopen->getWidth() / 2, WINSIZEY / 2 - m_pImg_UIopen->getHeight() / 2);
		if(m_editorState == st_Terrains)
		{
			int temp = 56;
			m_pImg_tileset1_div->frameRender(hdc, 105, WINSIZEY / 2 , 0, 1);
			m_pImg_tileset1_div->frameRender(hdc, 105, WINSIZEY / 2 + temp, 1, 1); temp += 56;
			m_pImg_tileset1_div->frameRender(hdc, 105, WINSIZEY / 2 + temp, 2, 1); temp += 56;
			m_pImg_tileset1_div->frameRender(hdc, 105, WINSIZEY / 2 + temp, 3, 1); 
		}
		else if (m_editorState == st_Units)
		{
			int tempF = -224;
			m_pImg_EnemyBox->render(hdc, WINSIZEX / 2 - (m_pImg_EnemyBox->getWidth() / 2) + tempF, WINSIZEY / 2 - 48); tempF += 150;
			m_pImg_EnemyBox->render(hdc, WINSIZEX / 2 - (m_pImg_EnemyBox->getWidth() / 2) + tempF, WINSIZEY / 2 - 48); tempF += 150;
			m_pImg_EnemyBox->render(hdc, WINSIZEX / 2 - (m_pImg_EnemyBox->getWidth() / 2) + tempF, WINSIZEY / 2 - 48); tempF += 150;
			m_pImg_EnemyBox->render(hdc, WINSIZEX / 2 - (m_pImg_EnemyBox->getWidth() / 2) + tempF, WINSIZEY / 2 - 48); tempF = -224;
																		
			m_pImg_EnemyBox->render(hdc, WINSIZEX / 2 - (m_pImg_EnemyBox->getWidth() / 2) + tempF, WINSIZEY / 2 + 100); tempF += 150;
			m_pImg_EnemyBox->render(hdc, WINSIZEX / 2 - (m_pImg_EnemyBox->getWidth() / 2) + tempF, WINSIZEY / 2 + 100); tempF += 150;
			m_pImg_EnemyBox->render(hdc, WINSIZEX / 2 - (m_pImg_EnemyBox->getWidth() / 2) + tempF, WINSIZEY / 2 + 100); tempF += 150;
			m_pImg_EnemyBox->render(hdc, WINSIZEX / 2 - (m_pImg_EnemyBox->getWidth() / 2) + tempF, WINSIZEY / 2 + 100); 

			int tempC = 0, tempD = 0;
			for (int i = 0; i < NUMBER_OF_KIND_UNITS - 4; ++i)
			{
				m_pImg_Enemy[i]->aniRender(hdc, WINSIZEX / 2 - (m_pImg_EnemyBox->getWidth() / 2) -224 + tempC, WINSIZEY / 2 - 48 + tempD, m_pAni_Enemy[i], 2.5f, false, 100); tempC += 150;
				if (i == 3)
					tempC = 0, tempD += 148;
			}

			m_pImg_EnemyBox->render(hdc, WINSIZEX / 2 - 120, WINSIZEY / 2 - 290, 2);
		}
		else if (m_editorState == st_else)
		{

		}

		m_pButton_Terrains->render(hdc);
		m_pButton_Units->render(hdc);
		m_pButton_Else->render(hdc);
		
	}
	
}












Editor_Scene::Editor_Scene()
{
}

Editor_Scene::~Editor_Scene()
{
}
