#include "stdafx.h"
#include "Editor_Scene.h"
#include "button.h"
#include "animation.h"
#include "Enemy.h"

char szFileName_1[512];
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
		m_pTiles[0].unitID = g_saveData.gTileMaxCountX; // �ӽ÷� ���� // �ϳ��� ����ü �ܿ� ������ �����ʴ´�....
		m_pTiles[1].unitID = g_saveData.gTileMaxCountY; // Ÿ���� 0��°�� 1������ ������ �����
		SaveEvent();
		break;
	case 32791: // Load
		MessageBox(hWnd, "Load Button Clicked", "Button", MB_OK);
		tileReset();
		LoadEvent();
		g_saveData.gTileMaxCountX = m_pTiles[0].unitID;
		g_saveData.gTileMaxCountY = m_pTiles[1].unitID;
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

	// aboutBox ���¹�
	// ������ MessageBoxó�� �⺻ �Լ��� �ִ�.
	
}
void Editor_Scene::SaveEvent()
{
	/*int mapSizeX = (int)st_selSize / TILE_SIZEX;
	int mapSizeY = (int)st_selSize / TILE_SIZEY;*/

	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = g_hWnd;
	ofn.lpstrFilter = _T("All Files (*.*)\0*.*\0");
	ofn.lpstrFile = szFileName_1;
	ofn.nMaxFile = 512;
	//ofn.nFilterIndex = 1;
	//ofn.lpstrFileTitle = szFileName;
	//ofn.nMaxFileTitle = 0;
	//ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_OVERWRITEPROMPT;
	GetSaveFileName(&ofn);

	TXTDATA->mapSave(szFileName_1, m_pTiles);


}

void Editor_Scene::LoadEvent()
{
	OPENFILENAME ofn;
	HWND hEditFileToBeOpened = NULL;

	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = g_hWnd;
	ofn.lpstrFilter = "All Files (*.*)\0*.*\0"; //"All Files(*.*)\0*.*\0";
	ofn.lpstrFile = szFileName_1;
	ofn.nMaxFile = 512;

	if (0 != GetOpenFileName(&ofn))
	{
		SetWindowText(hEditFileToBeOpened, ofn.lpstrFile);
		TXTDATA->getSingleton()->mapLoad(szFileName_1, m_pTiles);
	}

}












HRESULT Editor_Scene::init()
{

	m_rcSelectedUnit = 99; // ���ٴ¶�
	m_bIsMiniMapOn = false;
	m_bPlayerSetting = false;
	m_bIsHelpOn = false;
	m_bIsAutoOn = false;
	m_bIsUIOpen = false;
	m_bIsSel = false;
	m_bIsTextOn = false;
	m_editorState = st_Terrains;
	m_rcSelectedTile.rc.left = 130;
	m_rcSelectedTile.rc.top = 0;
	m_rcSelectedTile.terrain = isEmpty;
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
	m_pImg_Enemy[tempB] = IMAGEMANAGER->findImage("rabbit_idle"); tempB++;


	for (int i = 0; i < NUMBER_OF_KIND_UNITS - 3; ++i)
	{
		m_pAni_Enemy[i] = new animation;
		m_pAni_Enemy[i]->init(m_pImg_Enemy[i]->getWidth(), m_pImg_Enemy[i]->getHeight(), m_pImg_Enemy[i]->getFrameWidth(), m_pImg_Enemy[i]->getFrameHeight());
		m_pAni_Enemy[i]->setDefPlayFrame(false, true);
		m_pAni_Enemy[i]->setFPS(12);
		m_pAni_Enemy[i]->start();
	}


	int tempF = -224;
	m_EnemyBoxRect[0] = RectMake(WINSIZEX / 2 - (m_pImg_EnemyBox->getWidth() / 2) + tempF, WINSIZEY / 2 - 48, m_pImg_EnemyBox->getWidth(), m_pImg_EnemyBox->getHeight()); tempF += 150;
	m_EnemyBoxRect[1] = RectMake(WINSIZEX / 2 - (m_pImg_EnemyBox->getWidth() / 2) + tempF, WINSIZEY / 2 - 48, m_pImg_EnemyBox->getWidth(), m_pImg_EnemyBox->getHeight()); tempF += 150;
	m_EnemyBoxRect[2] = RectMake(WINSIZEX / 2 - (m_pImg_EnemyBox->getWidth() / 2) + tempF, WINSIZEY / 2 - 48, m_pImg_EnemyBox->getWidth(), m_pImg_EnemyBox->getHeight()); tempF += 150;
	m_EnemyBoxRect[3] = RectMake(WINSIZEX / 2 - (m_pImg_EnemyBox->getWidth() / 2) + tempF, WINSIZEY / 2 - 48, m_pImg_EnemyBox->getWidth(), m_pImg_EnemyBox->getHeight()); tempF = -224;

	m_EnemyBoxRect[4] = RectMake(WINSIZEX / 2 - (m_pImg_EnemyBox->getWidth() / 2) + tempF, WINSIZEY / 2 + 100, m_pImg_EnemyBox->getWidth(), m_pImg_EnemyBox->getHeight()); tempF += 150;
	m_EnemyBoxRect[5] = RectMake(WINSIZEX / 2 - (m_pImg_EnemyBox->getWidth() / 2) + tempF, WINSIZEY / 2 + 100, m_pImg_EnemyBox->getWidth(), m_pImg_EnemyBox->getHeight()); tempF += 150;
	m_EnemyBoxRect[6] = RectMake(WINSIZEX / 2 - (m_pImg_EnemyBox->getWidth() / 2) + tempF, WINSIZEY / 2 + 100, m_pImg_EnemyBox->getWidth(), m_pImg_EnemyBox->getHeight()); tempF += 150;
	m_EnemyBoxRect[7] = RectMake(WINSIZEX / 2 - (m_pImg_EnemyBox->getWidth() / 2) + tempF, WINSIZEY / 2 + 100, m_pImg_EnemyBox->getWidth(), m_pImg_EnemyBox->getHeight());

	tempF = -224;
	m_EnemyBoxRect[8] = RectMake(WINSIZEX / 2 - (m_pImg_EnemyBox->getWidth() / 2) + tempF, WINSIZEY / 2 - 300, m_pImg_EnemyBox->getWidth(), m_pImg_EnemyBox->getHeight());
	
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
	m_pImg_TextBox = IMAGEMANAGER->findImage("text");
	m_pHelp_UI = IMAGEMANAGER->findImage("parchment");
}

void Editor_Scene::init_tileset()
{
	Sample_tileSetting();
	tileReset();
}

void Editor_Scene::Sample_tileSetting()
{
	for (int j = 0; j < MAX_SAMPLEX; ++j)
	{
		
		m_pSampleTiles[j].terrain = isBlock;
		m_pSampleTiles[j].unitID = UNIT_NULL;
		m_pSampleTiles[j].frameX = j; //8����
		m_pSampleTiles[j].frameY = 0;
		switch ((j + 0) / 33)
		{
		case 0:
			m_pSampleTiles[j].rc = RectMake(105 + j * TILESIZEX,
				(WINSIZEY / 2 + 0), TILESIZEX, TILESIZEY);
			break;
		case 1:
			m_pSampleTiles[j].rc = RectMake(105 + (j - 33) * TILESIZEX,
				(WINSIZEY / 2 + 56), TILESIZEX, TILESIZEY);
			break;
		case 2:
			m_pSampleTiles[j].rc = RectMake(105 + (j - 66) * TILESIZEX,
				(WINSIZEY / 2 + 112), TILESIZEX, TILESIZEY);
			break;
		case 3:
			m_pSampleTiles[j].rc = RectMake(105 + (j - 99) * TILESIZEX,
				(WINSIZEY / 2 + 168), TILESIZEX, TILESIZEY);
			break;
		}


		if (j == 7 || j == 11)
			m_pSampleTiles[j].terrain = isUpHill1;
		else if (j == 8 || j == 12)
			m_pSampleTiles[j].terrain = isUpHill2;
		else if (j == 9 || j == 13)
			m_pSampleTiles[j].terrain = isDownHill1;
		else if (j == 10 || j == 14)
			m_pSampleTiles[j].terrain = isDownHill2;
		else if (j == 30 || j == 32)
			m_pSampleTiles[j].terrain = isUpHill3;
		else if (j == 31 || j == 34)
			m_pSampleTiles[j].terrain = isDownHill3;
		else if (j == 44 || j == 45 || j == 47 || j == 48)
			m_pSampleTiles[j].terrain = isEmpty;
		else if (j == 60)
			m_pSampleTiles[j].terrain = isladder;
		else if (j == 72 || j == 73 || j == 74 ||
			j == 82 || (j >= 84 && j <=90) || (j >= 95 && j <= 97) )
			m_pSampleTiles[j].terrain = isEmpty;
		else
			m_pSampleTiles[j].terrain = isBlock;


	}
}

void Editor_Scene::tileReset()
{
	
	// �⺻ Ÿ�� ���� ����
	for (int y = 0; y < g_saveData.gTileMaxCountY; y++)
	{
		for (int x = 0; x < g_saveData.gTileMaxCountX ; x++)
		{
			m_pTiles[y * g_saveData.gTileMaxCountX + x].rc = RectMake(0 + y * TILESIZEX, 0 + x * TILESIZEY, TILESIZEX, TILESIZEY);
			m_pTiles[y * g_saveData.gTileMaxCountX + x].terrainFrameX = 130;
			m_pTiles[y * g_saveData.gTileMaxCountX + x].terrainFrameY = 0;  // 29
			m_pTiles[y * g_saveData.gTileMaxCountX + x].unitID = UNIT_NULL;  // 29

		}
	}
}

void Editor_Scene::update()
{



	SCROLL_MAP->update();

	for (int i = 0; i < NUMBER_OF_KIND_UNITS - 3; ++i)
	{
		m_pAni_Enemy[i]->frameUpdate(TIMEMANAGER->getElapsedTime());
	}
	KeyEvent();
	buttonUpdate();
	//update_once();

	if (m_editorState == st_Terrains)
		mouseEvent_Terrains();
	if (m_editorState == st_Units)
		mouseEvent_Units();

	for (int y = 0; y < g_saveData.gTileMaxCountY; y++)
	{
		for (int x = 0; x < g_saveData.gTileMaxCountX; x++)
		{
			m_pTiles[y * g_saveData.gTileMaxCountX + x].rc = RectMake(x * TILESIZEX - SCROLL_MAP->GetX(), y * TILESIZEY - SCROLL_MAP->GetY(), TILESIZEX, TILESIZEY);


		}
	}


}

void Editor_Scene::KeyEvent()
{
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		if (m_bIsHelpOn == true)
			m_bIsHelpOn = false;
		else
			m_bIsHelpOn = true;
	}

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

	if (KEYMANAGER->isOnceKeyDown(VK_F8))
	{
		if (m_bIsMiniMapOn == true)
			m_bIsMiniMapOn = false;
		else
			m_bIsMiniMapOn = true;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F9))
	{
		if (m_bTileNumberOn == true)
			m_bTileNumberOn = false;
		else
			m_bTileNumberOn = true;
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

void Editor_Scene::mouseEvent_Terrains()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		st_mouse = tagMOUSE_STATE::st_MouseDown;
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && st_mouse == tagMOUSE_STATE::st_MouseDown && m_bIsUIOpen == true)
	{
		for (int i = 0; i < MAX_SAMPLEX; ++i)
		{
			if (PtInRect(&m_pSampleTiles[i].rc, g_ptMouse))
			{
				st_mouse = tagMOUSE_STATE::st_MouseUp;
				m_rcSelectedTile.rc.left = m_pSampleTiles[i].frameX;
				m_rcSelectedTile.rc.top = m_pSampleTiles[i].frameY;
				m_rcSelectedTile.terrain = m_pSampleTiles[i].terrain;
				m_bIsSel = true;
			}
			else
			{
				st_mouse = tagMOUSE_STATE::st_MouseIdle;
			}
		}
	}


	
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && m_bIsSel == true && m_bIsUIOpen == false)
	{
		for (int i = 0; i < g_saveData.gTileMaxCountX * g_saveData.gTileMaxCountY; ++i)
		{

			if (PtInRect(&m_pTiles[i].rc, g_ptMouse))
			{
				m_pTiles[i].terrainFrameX = m_rcSelectedTile.rc.left;
				m_pTiles[i].terrainFrameY = m_rcSelectedTile.rc.top;
				m_pTiles[i].terrain = m_rcSelectedTile.terrain;
			}

		}
	}

}

void Editor_Scene::mouseEvent_Units()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		st_mouse = tagMOUSE_STATE::st_MouseDown;
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && st_mouse == tagMOUSE_STATE::st_MouseDown && m_bIsUIOpen == true)
	{
		for (int i = 0; i < NUMBER_OF_KIND_UNITS - 3; ++i)
		{
			if (PtInRect(&m_EnemyBoxRect[i], g_ptMouse))
			{
				st_mouse = tagMOUSE_STATE::st_MouseUp;
				m_rcSelectedUnit = i;
				m_bIsSel = true;
			}
			else
			{
				st_mouse = tagMOUSE_STATE::st_MouseIdle;
			}
		}
	}



	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && m_bIsSel == true && m_bIsUIOpen == false)
	{
		for (int i = 0; i < g_saveData.gTileMaxCountX * g_saveData.gTileMaxCountY; ++i)
		{

			if (PtInRect(&m_pTiles[i].rc, g_ptMouse))
			{
				if (m_pTiles[i].terrain == isEmpty)
					m_pTiles[i].unitID = m_rcSelectedUnit;
			}

		}
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


	for (int y = 0; y < g_saveData.gTileMaxCountY; y++)
	{
		for (int x = 0; x < g_saveData.gTileMaxCountX; x++)
		{
			// ������ Ÿ�ϼ��� �����ӷ������Ѵ�.
			if (m_pTiles[y *  g_saveData.gTileMaxCountX + x].terrain == isEmpty)
			{
				m_pImg_tileset1->frameAlphaRender(hdc,
					m_pTiles[y *  g_saveData.gTileMaxCountX + x].rc.left,
					m_pTiles[y *  g_saveData.gTileMaxCountX + x].rc.top,
					m_pTiles[y *  g_saveData.gTileMaxCountX + x].terrainFrameX,
					m_pTiles[y *  g_saveData.gTileMaxCountX + x].terrainFrameY, 1.0f, 166);
			}
			else
			{
				m_pImg_tileset1->frameRender(hdc,
					m_pTiles[y *  g_saveData.gTileMaxCountX + x].rc.left,
					m_pTiles[y *  g_saveData.gTileMaxCountX + x].rc.top,
					m_pTiles[y *  g_saveData.gTileMaxCountX + x].terrainFrameX,
					m_pTiles[y *  g_saveData.gTileMaxCountX + x].terrainFrameY);
			}
			
			if (m_pTiles[y *  g_saveData.gTileMaxCountX + x].unitID <= 8)
			{
				m_pImg_Enemy[m_pTiles[y *  g_saveData.gTileMaxCountX + x].unitID]->aniRender
				(hdc, m_pTiles[y *  g_saveData.gTileMaxCountX + x].rc.left - (m_pImg_EnemyBox->getWidth() / 4) , m_pTiles[y *  g_saveData.gTileMaxCountX + x].rc.top - 48, m_pAni_Enemy[m_pTiles[y *  g_saveData.gTileMaxCountX + x].unitID], 2.5f, false, 100);
		
			}
		

			

			if (m_bTileNumberOn == true)
			{
				char SzText3[24];
				SetBkMode(hdc, TRANSPARENT);
				SetTextColor(hdc, RGB(255, 244, 210));
				MY_UTIL::FontOption(hdc, 11, 0);
				sprintf_s(SzText3, "%d %d", m_pTiles[y *  g_saveData.gTileMaxCountX + x].rc.left  , m_pTiles[y *  g_saveData.gTileMaxCountX + x].rc.top  );
				TextOut(hdc, m_pTiles[y *  g_saveData.gTileMaxCountX + x].rc.left , m_pTiles[y *  g_saveData.gTileMaxCountX + x].rc.top , SzText3, strlen(SzText3));
				MY_UTIL::FontDelete(hdc);

			}

			if (m_bIsMiniMapOn == true)
			{
				m_pImg_tileset1->RatioRender(hdc,
					(WINSIZEX - 500) + (m_pTiles[y *  g_saveData.gTileMaxCountX + x].rc.left / MINIMAP_RATIO + SCROLL_MAP->GetX() / MINIMAP_RATIO), // 750�� �̴ϸ� ����X��ǥ + �̴ϸʿ� ������ ��ü�� ��ġleft�� / ��ô�� ( ��ҵ� ���� 8~ 10�� ���� ) + ī�޶���ǥX / ��ô��
					30 + (m_pTiles[y *  g_saveData.gTileMaxCountX + x].rc.top / MINIMAP_RATIO + SCROLL_MAP->GetY() / MINIMAP_RATIO), // 30�� �̴ϸ� ����Y��ǥ + �̴ϸʿ� ������ ��ü�� ��ġtop�� / ��ô�� ( ��ҵ� ���� 8~ 10�� ���� ) + ī�޶���ǥY / ��ô��
																																	 // update���� ��ü�� ��ġ���� ī�޶󰪿� ���� �������ΰ��,  �̴ϸ��� ������ �� �ְ� + ��ũ�Ѱ��� ���־� �������� ���ǰ� ���־���Ѵ�.
					m_pTiles[y *  g_saveData.gTileMaxCountX + x].terrainFrameX, // �������Ǵ� ���
					m_pTiles[y *  g_saveData.gTileMaxCountX + x].terrainFrameY, // �������Ǵ� ���. ������ �̹����� ��� 0 ���� �ص��ȴ�.
					MINIMAP_RATIO, // ��ô��
					TILESIZEX, // ��ü �̹��� ������ X
					TILESIZEY); // ��ü �̹��� ������ Y
			}

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
			m_pImg_tileset1_div->frameRender(hdc, 105, WINSIZEY / 2 , 0, 0);
			m_pImg_tileset1_div->frameRender(hdc, 105, WINSIZEY / 2 + temp, 1, 0); temp += 56;
			m_pImg_tileset1_div->frameRender(hdc, 105, WINSIZEY / 2 + temp, 2, 0); temp += 56;
			m_pImg_tileset1_div->frameRender(hdc, 105, WINSIZEY / 2 + temp, 3, 0); 

			char SzText5[24];
			
		}
		else if (m_editorState == st_Units)
		{
			for (int i = 0; i <NUMBER_OF_KIND_UNITS - 3; ++i)
			{
				if (m_rcSelectedUnit == i)
					m_pImg_EnemyBox->hitRender(hdc, m_EnemyBoxRect[i].left, m_EnemyBoxRect[i].top, RGB(255, 0, 255));
				else
					m_pImg_EnemyBox->render(hdc, m_EnemyBoxRect[i].left, m_EnemyBoxRect[i].top);
			}

			int tempC = 0, tempD = 0;
			for (int i = 0; i < NUMBER_OF_KIND_UNITS - 3; ++i)
			{
				if (i == 8)
				{
					m_pImg_Enemy[i]->aniRender(hdc, WINSIZEX / 2 - (m_pImg_EnemyBox->getWidth() / 2)  - 200,
						WINSIZEY / 2 - 450 + tempD, m_pAni_Enemy[i], 2.5f, false, 100); tempC += 150;
				}
				else
				{
					m_pImg_Enemy[i]->aniRender(hdc, WINSIZEX / 2 - (m_pImg_EnemyBox->getWidth() / 2) - 224 + tempC, WINSIZEY / 2 - 48 + tempD, m_pAni_Enemy[i], 2.5f, false, 100); tempC += 150;
					if (i == 3)
						tempC = 0, tempD += 148;

				}
			
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


	for (int i = 0; i < NUMBER_OF_KIND_UNITS - 3; ++i )
	{
		if (PtInRect(&m_EnemyBoxRect[i], g_ptMouse) && m_editorState == st_Units && m_bIsUIOpen == true)
		{


			m_pImg_TextBox->alphaRender(hdc, m_EnemyBoxRect[i].left + 75, m_EnemyBoxRect[i].top - 135,200);
			
			char SzText1[256];
			SetBkMode(hdc, TRANSPARENT);
			SetTextColor(hdc, RGB(111, 46, 66));
			MY_UTIL::FontOption(hdc, 28, 0);
			RECT temp_rc = RectMake(
				m_EnemyBoxRect[i].left + 118,
				m_EnemyBoxRect[i].top - 85,
				178,
				120
			);

			switch (i)
			{
			case 0:
				sprintf_s(SzText1, "%s : ", "0. ���Ұ��� ");
				TextOut(hdc, m_EnemyBoxRect[i].left + 118, m_EnemyBoxRect[i].top - 110, SzText1, strlen(SzText1)); 
				MY_UTIL::FontOption(hdc, 21, 0);
				SetTextColor(hdc, RGB(55, 32, 83));
				sprintf_s(SzText1, "���� �ߵ��� ���̴� ���� ���̴� �͵��� �ű���� �մϴ�.  ���ݷ��� 1, ü���� 2, �̵��ӵ��� 1.2�Դϴ�. ");
				//Rectangle(hdc, temp_rc.left, temp_rc.top, temp_rc.right, temp_rc.bottom);
				break;
			case 1:
				sprintf_s(SzText1, "%s : ", "1. ���Թ��� ");
				TextOut(hdc, m_EnemyBoxRect[i].left + 118, m_EnemyBoxRect[i].top - 110, SzText1, strlen(SzText1));
				MY_UTIL::FontOption(hdc, 21, 0);
				SetTextColor(hdc, RGB(55, 32, 83));
				sprintf_s(SzText1, "���Թ����� ��ī�ο� ���Է� �츮�� �����Ϸ� �մϴ�.  ���ݷ��� 3, ü���� 3, �̵��ӵ��� 2.0�Դϴ�. ");
				break;
			case 2:
				sprintf_s(SzText1, "%s : ", "2. ũ�ι��� ");
				TextOut(hdc, m_EnemyBoxRect[i].left + 118, m_EnemyBoxRect[i].top - 110, SzText1, strlen(SzText1));
				MY_UTIL::FontOption(hdc, 21, 0);
				SetTextColor(hdc, RGB(55, 32, 83));
				sprintf_s(SzText1, "ũ�ι���� ���ƴٴϸ鼭 �����ϰ� �츮�� �����մϴ�.  ���ݷ��� 3, ü���� 6, �̵��ӵ��� 2.2�Դϴ�. ");
				break;
			case 3:
				sprintf_s(SzText1, "%s : ", "3. ��¯�� ");
				TextOut(hdc, m_EnemyBoxRect[i].left + 118, m_EnemyBoxRect[i].top - 110, SzText1, strlen(SzText1));
				MY_UTIL::FontOption(hdc, 21, 0);
				SetTextColor(hdc, RGB(55, 32, 83));
				sprintf_s(SzText1, "��¯�̴� �β��� �ٸ��� ���� ������ �Ͽ� �츮�� ��ġ���մϴ�.  ���ݷ��� 3, ü���� 4, �̵��ӵ��� 2.5�Դϴ�. ");
				break;
			case 4:
				sprintf_s(SzText1, "%s : ", "4. �ȳ��ö�� ");
				TextOut(hdc, m_EnemyBoxRect[i].left + 118, m_EnemyBoxRect[i].top - 110, SzText1, strlen(SzText1));
				MY_UTIL::FontOption(hdc, 21, 0);
				SetTextColor(hdc, RGB(55, 32, 83));
				sprintf_s(SzText1, "�ȳ��ö���� ū ������ �÷��̾ ��Ű���մϴ�.�̵��Ұ�.  ���ݷ��� 3, ü���� 7, �̵��ӵ��� 0�Դϴ� ");
				break;
			case 5:
				sprintf_s(SzText1, "%s : ", "5. �Ĵ��̱� ");
				TextOut(hdc, m_EnemyBoxRect[i].left + 118, m_EnemyBoxRect[i].top - 110, SzText1, strlen(SzText1));
				MY_UTIL::FontOption(hdc, 21, 0);
				SetTextColor(hdc, RGB(55, 32, 83));
				sprintf_s(SzText1, "�Ĵ��̱��� ����� �̵��ӵ��� ���İ��� �÷��̾ �����մϴ�.  ���ݷ��� 4, ü���� 10, �̵��ӵ��� 3.2�Դϴ�. ");
				break;
			case 6:
				sprintf_s(SzText1, "%s : ", "6. ���Ұ��� ");
				TextOut(hdc, m_EnemyBoxRect[i].left + 118, m_EnemyBoxRect[i].top - 110, SzText1, strlen(SzText1));
				MY_UTIL::FontOption(hdc, 21, 0);
				SetTextColor(hdc, RGB(55, 32, 83));
				sprintf_s(SzText1, "���Ұ����� ū ����Ȥ���� �÷��̾ �����մϴ�.  ���ݷ��� 3, ü���� 8, �̵��ӵ��� 1.5�Դϴ�. ");
				break;
			case 7:
				sprintf_s(SzText1, "%s : ", "7. ���ϸ��콺 ");
				TextOut(hdc, m_EnemyBoxRect[i].left + 118, m_EnemyBoxRect[i].top - 110, SzText1, strlen(SzText1));
				MY_UTIL::FontOption(hdc, 21, 0);
				SetTextColor(hdc, RGB(55, 32, 83));
				sprintf_s(SzText1, "���ϸ��콺�� ����� �̵��ӵ��� ���İ��� �÷��̾ �����մϴ�.  ���ݷ��� 3, ü���� 9, �̵��ӵ��� 2.1�Դϴ�. ");
				break;
			case 8:
				sprintf_s(SzText1, "%s : ", "�÷��̾� ");
				TextOut(hdc, m_EnemyBoxRect[i].left + 118, m_EnemyBoxRect[i].top - 110, SzText1, strlen(SzText1));
				MY_UTIL::FontOption(hdc, 21, 0);
				SetTextColor(hdc, RGB(55, 32, 83));
				sprintf_s(SzText1, "�����ϴ� ��ġ���� �÷��̾ �����˴ϴ�! ");
				break;
			}
			DrawText(hdc, SzText1, strlen(SzText1), &temp_rc, DT_WORDBREAK);
			MY_UTIL::FontDelete(hdc);

		}

	}


	if (m_editorState == st_Terrains )
	{
		m_pImg_tileset1->frameRender(hdc,
			g_ptMouse.x, g_ptMouse.y, m_rcSelectedTile.rc.left, m_rcSelectedTile.rc.top);
	}

	char SzText2[30];
	RECT temp_rc2 = RectMake(
		WINSIZEX / 2 - 100,
		15,
		200,
		90
	);;
	MY_UTIL::FontOption(hdc, 42, 0);
	SetTextColor(hdc, RGB(240, 200, 98));
	sprintf_s(SzText2, "���� : F1");
	DrawText(hdc, SzText2, strlen(SzText2), &temp_rc2, DT_WORDBREAK);
	
	if (m_bIsHelpOn == true)
	{
		m_pHelp_UI->render(hdc, WINSIZEX / 2 - m_pHelp_UI->getWidth() / 2, 130);

		char SzText9[64];
		int tempG = 0;
		MY_UTIL::FontOption(hdc, 36, 0);
		SetTextColor(hdc, RGB(40, 10, 20));
		sprintf_s(SzText9, "UIâ ON / OFF : F2");
		TextOut(hdc, WINSIZEX / 2 - 180, 160, SzText9, strlen(SzText9)); tempG += 77;

		sprintf_s(SzText9, "���ڼ� ON / OFF : F7");
		TextOut(hdc, WINSIZEX / 2 - 180, 160 + tempG, SzText9, strlen(SzText9)); tempG += 77;

		sprintf_s(SzText9, "�̴ϸ� ON / OFF : F8");
		TextOut(hdc, WINSIZEX / 2 - 180, 160 + tempG, SzText9, strlen(SzText9)); tempG += 77;

		sprintf_s(SzText9, "Ÿ�ϳѹ��� ON / OFF : F9");
		TextOut(hdc, WINSIZEX / 2 - 180, 160 + tempG, SzText9, strlen(SzText9)); tempG += 77;

		sprintf_s(SzText9, "ī�޶�ӵ� UP / DOWN : ");
		TextOut(hdc, WINSIZEX / 2 - 180, 160 + tempG, SzText9, strlen(SzText9)); tempG += 33;

		sprintf_s(SzText9, "PAGEUP / PAGEDOWN");
		TextOut(hdc, WINSIZEX / 2 - 180, 160 + tempG, SzText9, strlen(SzText9)); tempG += 77;
		MY_UTIL::FontDelete(hdc);
	}

}












Editor_Scene::Editor_Scene()
{
}

Editor_Scene::~Editor_Scene()
{
}
