
#include "resource.h"
#include "stdafx.h"
#include "editor.h"
#include "button.h"
#include "image.h"

char szFileName_1[512];
int editor::m_nPreviewNum = 0;
int editor::m_nMonsterID = 0;


static void SpaceFunc_left(void)
{
	if ((editor::m_nPreviewNum) > 0)
		editor::m_nPreviewNum -= 1;
	
	if ((editor::m_nMonsterID) > 0)
		editor::m_nMonsterID -= 1;
}

static void SpaceFunc_right(void)
{
	if ((editor::m_nPreviewNum) < 3)
		editor::m_nPreviewNum += 1;

	if ((editor::m_nMonsterID) < ENEMYKINDNUMBER - 2)
		editor::m_nMonsterID += 1;
}

void editor::ButtonEvent(HWND hWnd, UINT iMessage, WPARAM wParam)
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

	case 32796: // Terrains 
		st_obj = isTerrain;
		m_nPreviewNum = 0;
		break;
	case 32782: // Units
		st_obj = isUnit; 
		m_nPreviewNum = 0;
		break;

	case 32783: // 사이즈체크
		st_selSize = x800;
		m_pTiles[0].terrain = xx800;
		m_bIsSelectSize = true;
		MAPCAMERA->init();
		break;
	case 32784:
		st_selSize = x1120;
		m_pTiles[0].terrain = xx1120;
		m_bIsSelectSize = true;
		MAPCAMERA->init();
		break;
	case 32785:
		st_selSize = x1440;
		m_pTiles[0].terrain = xx1440;
		m_bIsSelectSize = true;
		MAPCAMERA->init();
		break;
	case 32786:
		st_selSize = x1600;
		m_pTiles[0].terrain = xx1600;
		m_bIsSelectSize = true;
		MAPCAMERA->init();
		break;

	//case 32803: // 32772
	//	DialogBox(g_hInstance, MAKEINTRESOURCE(ID_NOTICE_HELP), hWnd, NULL);
	//	break;
	}

	// aboutBox 여는법
	// 윈도우 MessageBox처럼 기본 함수가 있다.
}







HRESULT editor::init()
{
	ShowCursor(TRUE);

	init_image();
	st_selSize = x1120;
	g_saveData.gTileMaxCountX = st_selSize / TILE_SIZEX;
	g_saveData.gTileMaxCountY = st_selSize / TILE_SIZEY;
	st_selTile = tileset1;
	m_pTiles[0].terrain = xx1120;
	st_view = x1;
	m_bIsSelectSize = true; // 메뉴에서 사이즈체크시 초기화되고 사이즈 다시측정된다.
	m_bIsUnfold = true;
	m_bIsNumberOn = false;
	m_isSel = false;
	m_bIsHelpOn = false;
	m_bIsMiniMapOn = true;
	m_bIsStartingPoint = false;
	m_bIsTextOn = false;
	MiniMap_Ratio = 8;
	MAPCAMERA->init();

	tileReset();
	return S_OK;
}

void editor::init_image()
{
	m_pHelp = IMAGEMANAGER->findImage("help");
	m_pBG =	IMAGEMANAGER->findImage("black");
	m_pBox = IMAGEMANAGER->findImage("parchment");
	m_pTileSet[0] = IMAGEMANAGER->findImage("tileset1");
	m_pTileSet[1] = IMAGEMANAGER->findImage("tileset2");
	m_pTileSet[2] = IMAGEMANAGER->findImage("tileset3");
	m_pTileSet[3] = IMAGEMANAGER->findImage("tileset4");
	m_pCursor = IMAGEMANAGER->findImage("Cursor");
	m_pTag = IMAGEMANAGER->findImage("tag");
	m_pTag2 = IMAGEMANAGER->findImage("tag_done");
	m_pPlayer = IMAGEMANAGER->findImage("player");
	m_pBtnLspace = new button;
	m_pBtnLspace->init("space_left", IMAGEMANAGER->findImage("space_left")->getWidth() / 2 + 0, WINSIZEY - 150, PointMake(0, 1), PointMake(0, 0), SpaceFunc_left);

	m_pBtnRspace = new button;
	m_pBtnRspace->init("space_right", IMAGEMANAGER->findImage("space_right")->getWidth() / 2 + 301, WINSIZEY - 150, PointMake(0, 1), PointMake(0, 0), SpaceFunc_right);


	int i = 0;
	m_pEnemy[i] = IMAGEMANAGER->findImage("BG_Beholder"); ++i;
	m_pEnemy[i] = IMAGEMANAGER->findImage("BG_Blue_Guardian"); ++i;
	m_pEnemy[i] = IMAGEMANAGER->findImage("BG_Blue_Mindflayer"); ++i;
	m_pEnemy[i] = IMAGEMANAGER->findImage("BG_Bugman"); ++i;
	m_pEnemy[i] = IMAGEMANAGER->findImage("BG_Cetus"); ++i;
	m_pEnemy[i] = IMAGEMANAGER->findImage("BG_Coven"); ++i;
	m_pEnemy[i] = IMAGEMANAGER->findImage("BG_Cow"); ++i;
	m_pEnemy[i] = IMAGEMANAGER->findImage("BG_Cyclops"); ++i;
	m_pEnemy[i] = IMAGEMANAGER->findImage("BG_Dark_Lord"); ++i; // 8
	m_pEnemy[i] = IMAGEMANAGER->findImage("BG_Dog"); ++i;
	m_pEnemy[i] = IMAGEMANAGER->findImage("BG_Eye_Slime"); ++i;
	m_pEnemy[i] = IMAGEMANAGER->findImage("BG_Faun_Archer"); ++i;
	m_pEnemy[i] = IMAGEMANAGER->findImage("BG_Firewolf"); ++i;
	m_pEnemy[i] = IMAGEMANAGER->findImage("BG_Gargoyle"); ++i;
	m_pEnemy[i] = IMAGEMANAGER->findImage("BG_Giant_Run"); ++i;
	m_pEnemy[i] = IMAGEMANAGER->findImage("BG_Gnome_Run"); ++i;
	m_pEnemy[i] = IMAGEMANAGER->findImage("BG_Igor"); ++i;
	m_pEnemy[i] = IMAGEMANAGER->findImage("BG_Itchy"); ++i;
	m_pEnemy[i] = IMAGEMANAGER->findImage("BG_Knife_dude"); ++i; // i = 18
	
}

void editor::tileReset()
{
	// 기본 타일 정보 셋팅
	for (int x = 0; x < g_saveData.gTileMaxCountX; x++)
	{
		for (int y = 0; y < g_saveData.gTileMaxCountY; y++)
		{
			m_pTiles[x * g_saveData.gTileMaxCountX + y].rc = RectMake(0 + x * TILE_SIZEX, 0 + y * TILE_SIZEY, TILE_SIZEX, TILE_SIZEY);
			m_pTiles[x * g_saveData.gTileMaxCountX + y].terrainFrameX = 6;
			m_pTiles[x * g_saveData.gTileMaxCountX + y].terrainFrameY = 3;  // 29
			m_pTiles[x * g_saveData.gTileMaxCountX + y].SampleNum = 1;
			m_pTiles[x * g_saveData.gTileMaxCountX + y].MonsterNumber = 20;
		}
	}
}

void editor::release()
{
}

void editor::update()
{
	MAPCAMERA->update();
	SizeUpdate();
	KeyEvent();
	if (m_pBtnLspace && m_bIsUnfold)
		m_pBtnLspace->update();
	if (m_pBtnRspace && m_bIsUnfold)
		m_pBtnRspace->update();

	if (st_obj == isTerrain)
	{
		MouseEvent();

		if (m_pTileSet[0] && editor::m_nPreviewNum == 0)
			st_selTile = tileset1;
		if (m_pTileSet[1] && editor::m_nPreviewNum == 1)
			st_selTile = tileset2;
		if (m_pTileSet[2] && editor::m_nPreviewNum == 2)
			st_selTile = tileset3;
		if (m_pTileSet[3] && editor::m_nPreviewNum == 3)
			st_selTile = tileset4;
		//ShowCursor(FALSE);

		if (m_bIsUnfold)
		{

			for (int j = 0; j < SAMPLE_COUNTY; ++j)
			{
				for (int i = 0; i < SAMPLE_COUNTX; ++i)
				{
					m_pSampleTiles[j * SAMPLE_COUNTX + i].rc = RectMake(40 + i * TILE_SIZEX,
						(WINSIZEY - 240) + j * TILE_SIZEY, TILE_SIZEX, TILE_SIZEY);
					m_pSampleTiles[j * SAMPLE_COUNTX + i].frameX = i; //8까지
					m_pSampleTiles[j * SAMPLE_COUNTX + i].frameY = j; //6까지
					m_pSampleTiles[j * SAMPLE_COUNTX + i].SampleNum = (int)st_selTile;
					// 샘플넘은 계속 바뀔것이다. 최초에는 1
				}
			}
		}
	}
	else
	{
		Unit_MouseEvent();

	}

		for (int x = 0; x < g_saveData.gTileMaxCountX; x++)
		{
			for (int y = 0; y < g_saveData.gTileMaxCountY; y++)
			{
				m_pTiles[x * g_saveData.gTileMaxCountX + y].rc = RectMake(x * TILE_SIZEX - MAPCAMERA->getCameraX(), y * TILE_SIZEY - MAPCAMERA->getCameraY(), TILE_SIZEX, TILE_SIZEY);
			}
		}
	
		//g_saveData.gTileMaxCountX = 35;
		//g_saveData.gTileMaxCountY = 35;
}

void editor::Unit_MouseEvent()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		st_mouse = tagMOUSE_STATE::MOUSE_DOWN1;
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && st_mouse == tagMOUSE_STATE::MOUSE_DOWN1)
	{
		for (int i = 0; i < g_saveData.gTileMaxCountX * g_saveData.gTileMaxCountY; ++i)
		{
			if (PtInRect(&m_pTiles[i].rc, g_ptMouse))
			{
				if (m_pTiles[i].SampleNum == 3)
				{
					if (m_pTiles[i].terrainFrameX == 4 && m_pTiles[i].terrainFrameY == 3)
					{
						m_pTiles[i].MonsterNumber = m_nMonsterID;
					}
				}
			}
			else
			{
				st_mouse = tagMOUSE_STATE::MOUSE_IDLE1;
			}
		}
	}
}


void editor::SizeUpdate()
{
	if (m_bIsSelectSize == true)
	{
		g_saveData.gTileMaxCountX = (int)st_selSize / TILE_SIZEX;
		g_saveData.gTileMaxCountY = (int)st_selSize / TILE_SIZEY;
		//tagTile * m_pTiles = new tagTile[g_saveData.gTileMaxCountX * g_saveData.gTileMaxCountY];
		tileReset();
		m_bIsSelectSize = false;
	}
}

void editor::KeyEvent()
{
	MAPCAMERA->keyUpdate();

	if (KEYMANAGER->isOnceKeyDown(VK_PRIOR))
	{
		switch (st_view)
		{
		case x1:
			st_view = x2;
			break;
		case x2:
			st_view = x3;
			break;
		case x3:
			st_view = x1;
			break;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(0x55)) // 'U'
	{
		if (m_bIsUnfold == true) // 이미 펼쳐져있다면
			m_bIsUnfold = false;
		else
			m_bIsUnfold = true;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
		SCENEMANAGER->changeScene("stage");

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && m_isSel == true)
		m_isSel = false; // 선택해제 단축키
	if (KEYMANAGER->isOnceKeyDown(VK_DELETE))
	{
		m_isSel = false;
		tileReset();  //초기화 단축키
	}
	if (KEYMANAGER->isOnceKeyDown('M') && m_bIsUnfold == true)
	{
		if (m_bIsMiniMapOn)
			m_bIsMiniMapOn = false;
		else
			m_bIsMiniMapOn = true;
	}
	if (KEYMANAGER->isOnceKeyDown('Z') && m_bIsUnfold == true)
	{
		if (st_obj == isTerrain) m_rcSelectedTile.left -= 1;
		else 
			if(m_nMonsterID > 0) m_nMonsterID--;
	}
	if (KEYMANAGER->isOnceKeyDown('X') && m_bIsUnfold == true)
	{
		if (st_obj == isTerrain)m_rcSelectedTile.left += 1;
		else
			if (m_nMonsterID < ENEMYKINDNUMBER - 2) m_nMonsterID++;
	}
	if (KEYMANAGER->isOnceKeyDown('C') && m_bIsUnfold == true)
	{
		if (st_obj == isTerrain) m_rcSelectedTile.top += 1;
	}
	if (KEYMANAGER->isOnceKeyDown('V') && m_bIsUnfold == true)
	{
		if (st_obj == isTerrain) m_rcSelectedTile.top -= 1;
	}
	if (KEYMANAGER->isOnceKeyDown('O'))
	{
		if (m_bIsAutoOn)
			m_bIsAutoOn = false;
		else
			m_bIsAutoOn = true;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F6))
	{
		if (m_bIsTextOn)
			m_bIsTextOn = false;
		else
			m_bIsTextOn = true;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F7))
	{
		if (m_bIsNumberOn)
			m_bIsNumberOn = false;
		else
			m_bIsNumberOn = true;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		if (m_bIsHelpOn)
			m_bIsHelpOn = false;
		else
			m_bIsHelpOn = true;
	}
}

void editor::MouseEvent()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		st_mouse = tagMOUSE_STATE::MOUSE_DOWN1;

		if (m_rcSelectedTileSampleNum == 3)
		{
			if ((m_rcSelectedTile.left == 5) && (m_rcSelectedTile.top == 3))
			{
				if (m_bIsStartingPoint)
					m_isSel = false;
			}
		}

	}
	else if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && st_mouse == tagMOUSE_STATE::MOUSE_DOWN1)
	{
		for (int i = 0; i < SAMPLE_COUNTX * SAMPLE_COUNTY; ++i)
		{
			if (PtInRect(&m_pSampleTiles[i].rc, g_ptMouse))
			{	
				st_mouse = tagMOUSE_STATE::MOUSE_UP1;
				m_rcSelectedTile.left = m_pSampleTiles[i].frameX;
				m_rcSelectedTile.top = m_pSampleTiles[i].frameY;
				m_rcSelectedTileSampleNum = m_pSampleTiles[i].SampleNum;
				m_isSel = true;
			}
			else
			{
				st_mouse = tagMOUSE_STATE::MOUSE_IDLE1;
			}
		}
	}



	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && m_isSel == true)
	{
		for (int i = 0; i < g_saveData.gTileMaxCountX * g_saveData.gTileMaxCountY; ++i)
		{
			if (m_bIsUnfold == true && g_ptMouse.y >= 542) continue;

			if (PtInRect(&m_pTiles[i].rc, g_ptMouse))
			{
				m_pTiles[i].terrainFrameX = m_rcSelectedTile.left;
				m_pTiles[i].terrainFrameY = m_rcSelectedTile.top;
				m_pTiles[i].SampleNum = m_rcSelectedTileSampleNum;
				m_pTiles[i].MonsterNumber = 20;
			}

		}
	}


}

void editor::render(HDC hdc)
{
	m_pBG->render(hdc, 0, 0);

	// 실제 뿌려지는 맵//
	render_mapTile(hdc);
	/////////////////////


	////////////////// 펼쳤을때의 이벤트 렌더링/////////////////
	if (m_bIsUnfold)
	{
		m_pBox->render(hdc, 0, WINSIZEY - 250);

		// 왼쪽에 나타나는 타일 미리보기 렌더링//
		if (st_obj == isTerrain)
		{
			if (m_pTileSet[0] && editor::m_nPreviewNum == 0)
				m_pTileSet[0]->render(hdc, 40, WINSIZEY - 240);
			if (m_pTileSet[1] && editor::m_nPreviewNum == 1)
				m_pTileSet[1]->render(hdc, 40, WINSIZEY - 240);
			if (m_pTileSet[2] && editor::m_nPreviewNum == 2)
				m_pTileSet[2]->render(hdc, 40, WINSIZEY - 240);
			if (m_pTileSet[3] && editor::m_nPreviewNum == 3)
				m_pTileSet[3]->render(hdc, 40, WINSIZEY - 240);
		}
		if (st_obj == isUnit)
		{
			m_pEnemy[m_nMonsterID]->frameRender(hdc, 67, WINSIZEY - 172, 1, 0);
			m_pEnemy[m_nMonsterID]->frameAlphaRender(hdc, - 22, WINSIZEY - 252, 0, 0, 3.0f, 170);
		}
		///////////////////////////////////

		//미니맵//
		if (m_bIsMiniMapOn)
		{
			for (int x = 0; x < g_saveData.gTileMaxCountX; x++)
			{
				for (int y = 0; y < g_saveData.gTileMaxCountY; y++)
				{
					m_pTileSet[m_pTiles[x *  g_saveData.gTileMaxCountX + y].SampleNum]->RatioRender(hdc,
						550 + m_pTiles[x *  g_saveData.gTileMaxCountX + y].rc.left / MiniMap_Ratio + (MAPCAMERA->getCameraX() / MiniMap_Ratio),
						560 + m_pTiles[x *  g_saveData.gTileMaxCountX + y].rc.top / MiniMap_Ratio + (MAPCAMERA->getCameraY() / MiniMap_Ratio),
						m_pTiles[x *  g_saveData.gTileMaxCountX + y].terrainFrameX,
						m_pTiles[x *  g_saveData.gTileMaxCountX + y].terrainFrameY,
						MiniMap_Ratio,
						TILE_SIZEX,
						TILE_SIZEY);
				}
			}
		}
		//////////
		if (m_bIsAutoOn)
		{
			char szTextAuto[50];
			// TRANSPARENT : 투명, OPAQUE : 불투명
			SetBkMode(hdc, TRANSPARENT);
			SetTextColor(hdc, RGB(0, 0, 10));
			MY_UTIL::FontOption(hdc, 25, 0);
			sprintf_s(szTextAuto, "%s", "오토타일ON");
			TextOut(hdc, 340, 600, szTextAuto, strlen(szTextAuto));
			MY_UTIL::FontDelete(hdc);
		}

		char szTextHelp[64];
		// TRANSPARENT : 투명, OPAQUE : 불투명
		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, RGB(0, 0, 10));
		MY_UTIL::FontOption(hdc, 25, 0);
		sprintf_s(szTextHelp, "%s", "도움말 : F1");
		TextOut(hdc, 340, 725, szTextHelp, strlen(szTextHelp));
		MY_UTIL::FontDelete(hdc);
		

		m_pBtnLspace->render(hdc);
		m_pBtnRspace->render(hdc);
	}
	////////////////////////////////////////////////////////////

	if (m_isSel == true)
	{
		if(st_obj == isTerrain)
		m_pTileSet[m_rcSelectedTileSampleNum]->frameRender(hdc,
			g_ptMouse.x,
			g_ptMouse.y,
			m_rcSelectedTile.left,
			m_rcSelectedTile.top);
		else
		{
			/*m_pEnemy[m_nMonsterID]->frameRender(hdc, g_ptMouse.x - m_pEnemy[m_nMonsterID]->getWidth() / 8,
				g_ptMouse.y,0,0);*/
		}

	}




	if (m_bIsStartingPoint == false)
	{
		for (int x = 0; x < g_saveData.gTileMaxCountX; x++)
		{
			for (int y = 0; y < g_saveData.gTileMaxCountY; y++)
			{
				if ((m_pTiles[x *  g_saveData.gTileMaxCountX + y].SampleNum == 3) &&
					m_pTiles[x *  g_saveData.gTileMaxCountX + y].terrainFrameX == 5 &&
					m_pTiles[x *  g_saveData.gTileMaxCountX + y].terrainFrameY == 3)
				{
					m_bIsStartingPoint = true;
				}
			}
		}
	}


	if (m_bIsTextOn)
	{
		char szText[256];

		// TRANSPARENT : 투명, OPAQUE : 불투명
		SetBkMode(hdc, TRANSPARENT);

		SetTextColor(hdc, RGB(255, 0, 255));

		sprintf_s(szText, "m_ptMoveCameraX : %f / m_ptMoveCameraY : %f",
			MAPCAMERA->getfocusCameraX(), MAPCAMERA->getfocusCameraY());
		TextOut(hdc, 400, 0, szText, strlen(szText));

		sprintf_s(szText, "m_ptCameraX : %f / m_ptCameraY : %f",
			MAPCAMERA->getCameraX(), MAPCAMERA->getCameraY());
		TextOut(hdc, 400, 100, szText, strlen(szText));

	}


	if (m_bIsHelpOn)
	{
		m_pHelp->render(hdc, WINSIZEX / 2 - m_pHelp->getWidth() / 2, 100);

		
		// TRANSPARENT : 투명, OPAQUE : 불투명
		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, RGB(0, 0, 10));
		MY_UTIL::FontOption(hdc, 28, 0);
		char szTextHelp1[256];
		int temp_term = 0;
		sprintf_s(szTextHelp1, "%s", "타일 생성창 : 'U' "); 
		TextOut(hdc, WINSIZEX/2 - 140, 120 + temp_term, szTextHelp1, strlen(szTextHelp1)); temp_term += 80;

		sprintf_s(szTextHelp1, "%s", "타일 미니맵 : 'M' ");
		TextOut(hdc, WINSIZEX / 2 - 140, 120 + temp_term, szTextHelp1, strlen(szTextHelp1)); temp_term += 80;

		sprintf_s(szTextHelp1, "%s", "타일 넘버링 : 'F7' ");
		TextOut(hdc, WINSIZEX / 2 - 140, 120 + temp_term, szTextHelp1, strlen(szTextHelp1)); temp_term += 80;

		sprintf_s(szTextHelp1, "%s", "카메라 좌표계 : 'F6' ");
		TextOut(hdc, WINSIZEX / 2 - 140, 120 + temp_term, szTextHelp1, strlen(szTextHelp1)); temp_term += 80;

		sprintf_s(szTextHelp1, "%s", "타일선택단축키 :  'Z, X, C, V' ");
		TextOut(hdc, WINSIZEX / 2 - 140, 120 + temp_term, szTextHelp1, strlen(szTextHelp1)); temp_term += 80;

		MY_UTIL::FontDelete(hdc);

	}

	/*Rectangle(hdc, m_pTiles[x * g_saveData.gTileMaxCountX + y].rc.left,
		m_pTiles[x * g_saveData.gTileMaxCountX + y].rc.top, m_pTiles[x * g_saveData.gTileMaxCountX + y].rc.right,
		m_pTiles[x * g_saveData.gTileMaxCountX + y].rc.bottom);*/

	//m_pCursor->render(hdc, g_ptMouse.x, g_ptMouse.y);
}

void editor::render_mapTile(HDC hdc)
{

	for (int x = 0; x < g_saveData.gTileMaxCountX; x++)
	{
		for (int y = 0; y < g_saveData.gTileMaxCountY; y++)
		{
			m_pTileSet[m_pTiles[x *  g_saveData.gTileMaxCountX + y].SampleNum]->frameRender(hdc,
				m_pTiles[x *  g_saveData.gTileMaxCountX + y].rc.left,
				m_pTiles[x *  g_saveData.gTileMaxCountX + y].rc.top,
				m_pTiles[x *  g_saveData.gTileMaxCountX + y].terrainFrameX,
				m_pTiles[x *  g_saveData.gTileMaxCountX + y].terrainFrameY);

			if (m_bIsNumberOn)
			{
				char szText[50];
				// TRANSPARENT : 투명, OPAQUE : 불투명
				SetBkMode(hdc, TRANSPARENT);
				SetTextColor(hdc, RGB(255, 200, 255));
				MY_UTIL::FontOption(hdc, 12, 0);
				sprintf_s(szText, "%d",
					m_pTiles[x *  g_saveData.gTileMaxCountX + y].rc.left/ TILE_SIZEX);
				TextOut(hdc, m_pTiles[x *  g_saveData.gTileMaxCountX + y].rc.left + 11, m_pTiles[x *  g_saveData.gTileMaxCountX + y].rc.top - 55, szText, strlen(szText));
				MY_UTIL::FontDelete(hdc);

				char szText2[50];
				// TRANSPARENT : 투명, OPAQUE : 불투명
				SetBkMode(hdc, TRANSPARENT);
				SetTextColor(hdc, RGB(255, 191, 255));
				MY_UTIL::FontOption(hdc, 12, 0);
				sprintf_s(szText2, "%d",
					m_pTiles[x *  g_saveData.gTileMaxCountX + y].rc.bottom / TILE_SIZEY);
				TextOut(hdc, m_pTiles[x *  g_saveData.gTileMaxCountX + y].rc.left + 11, m_pTiles[x *  g_saveData.gTileMaxCountX + y].rc.top - 47, szText2, strlen(szText2));
				MY_UTIL::FontDelete(hdc);
			}

			if (m_pTiles[x *  g_saveData.gTileMaxCountX + y].SampleNum == 3 && m_pTiles[x * g_saveData.gTileMaxCountX + y].MonsterNumber == 20)
			{
				if (m_pTiles[x *  g_saveData.gTileMaxCountX + y].terrainFrameX == 4 && m_pTiles[x *  g_saveData.gTileMaxCountX + y].terrainFrameY == 3)
					m_pTag->alphaRender(hdc, m_pTiles[x *  g_saveData.gTileMaxCountX + y].rc.left, m_pTiles[x *  g_saveData.gTileMaxCountX + y].rc.top - 15, 140);
			}
			else if (m_pTiles[x *  g_saveData.gTileMaxCountX + y].SampleNum == 3 && m_pTiles[x * g_saveData.gTileMaxCountX + y].MonsterNumber != 20)
			{
				if (m_pTiles[x *  g_saveData.gTileMaxCountX + y].terrainFrameX == 4 && m_pTiles[x *  g_saveData.gTileMaxCountX + y].terrainFrameY == 3)
				{
					m_pTag2->alphaRender(hdc, m_pTiles[x *  g_saveData.gTileMaxCountX + y].rc.left, m_pTiles[x *  g_saveData.gTileMaxCountX + y].rc.top - 15, 140);
					char szText[256];

					// TRANSPARENT : 투명, OPAQUE : 불투명
					SetBkMode(hdc, TRANSPARENT);

					SetTextColor(hdc, RGB(255, 255, 255));

					sprintf_s(szText, "%d",
						m_pTiles[x *  g_saveData.gTileMaxCountX + y].MonsterNumber);
					TextOut(hdc, m_pTiles[x *  g_saveData.gTileMaxCountX + y].rc.left + 5, m_pTiles[x *  g_saveData.gTileMaxCountX + y].rc.top - 5, szText, strlen(szText));
				}

			}

			if ((m_pTiles[x *  g_saveData.gTileMaxCountX + y].SampleNum == 3))
			{
				if (m_pTiles[x *  g_saveData.gTileMaxCountX + y].terrainFrameX == 5 && m_pTiles[x *  g_saveData.gTileMaxCountX + y].terrainFrameY == 3)
				{
					m_pPlayer->alphaRender(hdc, m_pTiles[x *  g_saveData.gTileMaxCountX + y].rc.left - 2, m_pTiles[x *  g_saveData.gTileMaxCountX + y].rc.top - 2, 140);
				}
			}
		}

	}
}








void editor::SaveEvent()
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

void editor::LoadEvent()
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
	g_saveData.gTileMaxCountX = m_pTiles[0].terrain;
	g_saveData.gTileMaxCountY = m_pTiles[0].terrain;
}


editor::editor()
{
}


editor::~editor()
{
}
