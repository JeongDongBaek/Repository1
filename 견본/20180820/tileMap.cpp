#include "stdafx.h"
//#include "tileMap.h"
//
//char szFileName[512];
//
//HRESULT tileMap::init()
//{
//	m_pTileSet = IMAGEMANAGER->addImage("image/tileMap/maptiles.bmp",
//		"image/tileMap/maptiles.bmp", 640, 288, 20, 9,
//		true, RGB(255, 0, 255));
//
//	m_pObjSet = IMAGEMANAGER->addImage("image/tileMap/obj.bmp",
//		"image/tileMap/obj.bmp", 640, 288, 20, 9,
//		true, RGB(255, 0, 255));
//	m_pObj1Set = IMAGEMANAGER->addImage("image/tileMap/obj2.bmp",
//		"image/tileMap/obj2.bmp", 640, 288, 20, 9,
//		true, RGB(255, 0, 255));
//
//	//버튼 셋팅
//	m_hBtnSave = CreateWindow("button", "Save", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, WINSIZEX - m_pTileSet->getWidth(), m_pTileSet->getHeight() + 30, 100, 40, g_hWnd,
//		HMENU(0), g_hInstance, NULL);
//	//버튼2 셋팅
//	m_hBtnLoad = CreateWindow("button", "Load", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, WINSIZEX - m_pTileSet->getWidth()+110, m_pTileSet->getHeight() + 30, 100, 40, g_hWnd,
//		HMENU(1), g_hInstance, NULL);
//	//버튼3 셋팅
//	m_hBtnSelectTerrain = CreateWindow("button", "Terrain", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, WINSIZEX - m_pTileSet->getWidth(), m_pTileSet->getHeight() + 80, 100, 40, g_hWnd,
//		HMENU(2), g_hInstance, NULL);
//	//버튼4 셋팅
//	m_hBtnSelectObject = CreateWindow("button", "Object", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, WINSIZEX - m_pTileSet->getWidth()+110, m_pTileSet->getHeight() + 80, 100, 40, g_hWnd,
//		HMENU(3), g_hInstance, NULL);
//	//버튼5 셋팅
//	m_hBtnEraser = CreateWindow("button", "Eraser", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, WINSIZEX - m_pTileSet->getWidth()+220, m_pTileSet->getHeight() + 80, 100, 40, g_hWnd,
//		HMENU(4), g_hInstance, NULL);
//
//	//기본 타일 정보 셋팅
//	for (int x= 0; x< TILE_X; x++)
//	{
//		for (int y = 0; y < TILE_Y; y++)
//		{
//			m_pTiles[x * TILE_X + y].rc = RectMake(x* TILE_SIZE, y*TILE_SIZE, TILE_SIZE, TILE_SIZE);
//
//			m_pTiles[x * TILE_X + y].terrainFrameX = 12;
//			m_pTiles[x * TILE_X + y].terrainFrameY = 0;
//
//			m_pTiles[x * TILE_X + y].objectFrameX = 100;
//			m_pTiles[x * TILE_X + y].objectFrameY = 100;
//
//
//		}
//	}	
//
//	//샘플 타일 정보 셋팅
//	for (int y = 0; y < SAMPLE_TILE_Y; y++) //x축을 먼저 그려줘야해서
//	{
//		for (int x = 0; x< SAMPLE_TILE_X; x++)
//		{
//			m_pSampleTiles[y * SAMPLE_TILE_X + x].rc = RectMake(WINSIZEX - m_pTileSet->getWidth()+x * TILE_SIZE, y *TILE_SIZE, TILE_SIZE, TILE_SIZE);
//
//			m_pSampleTiles[y * SAMPLE_TILE_X + x].frameX = x; //?
//			m_pSampleTiles[y * SAMPLE_TILE_X + x].frameY = y;
//		}
//	}
//	return S_OK;
//}
//
//void tileMap::release()
//{
//}
//
//void tileMap::update()
//{	
//
//	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
//	{
//		for (int i = 0; i < SAMPLE_TILE_X * SAMPLE_TILE_Y; i++)
//		{
//	
//			if (PtInRect(&m_pSampleTiles[i].rc, g_ptMouse))
//			{
//				m_rcSelectedTile.left = m_pSampleTiles[i].frameX;
//				m_rcSelectedTile.top = m_pSampleTiles[i].frameY;
//				break;
//			}
//		}
//	}
//
//	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
//	{
//		for (int i = 0; i <TILE_X * TILE_Y; i++)
//		{
//			if (m_bObjPrint)
//			{
//				if (PtInRect(&m_pTiles[i].rc, g_ptMouse))
//				{
//
//					m_pTiles[i].objectFrameX = m_rcSelectedTile.left;
//					m_pTiles[i].objectFrameY = m_rcSelectedTile.top;
//
//					break;
//				}
//			}
//			else
//			{
//				if (PtInRect(&m_pTiles[i].rc, g_ptMouse))
//				{
//				
//					m_pTiles[i].terrainFrameX = m_rcSelectedTile.left;
//					m_pTiles[i].terrainFrameY = m_rcSelectedTile.top;
//
//					break;
//				}
//
//			}
//		}
//	}
//}
//
//void tileMap::render(HDC hdc)
//{
//	if (m_bObjPrint)
//	{
//		if (m_pObjSet)
//			m_pObjSet->render(hdc, WINSIZEX - m_pObjSet->getWidth(), 0);
//	}
//	else
//	{
//		if (m_pTileSet)
//			m_pTileSet->render(hdc, WINSIZEX- m_pTileSet->getWidth(), 0);
//
//	}
//
//	for (int x = 0; x < TILE_X; x++)
//	{
//		for (int y = 0; y < TILE_Y; y++)
//		{
//			m_pTileSet->frameRender(hdc,
//				m_pTiles[x*TILE_X + y].rc.left,
//				m_pTiles[x*TILE_X + y].rc.top,
//				m_pTiles[x*TILE_X + y].terrainFrameX,
//				m_pTiles[x*TILE_X + y].terrainFrameY);
//
//
//			if (!(m_pTiles[x*TILE_X + y].objectFrameX == 100 && m_pTiles[x*TILE_X + y].objectFrameY == 100))
//			{
//				m_pObj1Set->frameRender(hdc,
//					m_pTiles[x*TILE_X + y].rc.left,
//					m_pTiles[x*TILE_X + y].rc.top,
//					m_pTiles[x*TILE_X + y].objectFrameX,
//					m_pTiles[x*TILE_X + y].objectFrameY);
//			}
//			
//		}
//		
//	}
//	
//
//	//선택된 타일 표시
//
//	if (m_bObjPrint)
//	{
//		m_pObjSet->frameRender(hdc,
//			TILE_X * TILE_SIZE + 30,
//			WINSIZEY / 2,
//			m_rcSelectedTile.left,
//			m_rcSelectedTile.top);
//	}
//	else
//	{
//		m_pTileSet->frameRender(hdc,
//			TILE_X * TILE_SIZE + 30,
//			WINSIZEY / 2,
//			m_rcSelectedTile.left,
//			m_rcSelectedTile.top);
//	}
//
//}
//
//void tileMap::objectPrint()
//{
//	m_bObjPrint = true;
//}
//
//void tileMap::mapSave()
//{
//	OPENFILENAME ofn;
//
//
//	ZeroMemory(&ofn, sizeof(OPENFILENAME));
//	ofn.lStructSize = sizeof(OPENFILENAME);
//	ofn.hwndOwner = g_hWnd;
//	ofn.lpstrFilter = _T("txt Files(*.txt)\0*.txt\0All Files (*.*)\0*.*\0");
//	ofn.lpstrFile = szFileName;
//	ofn.nMaxFile = 512;
//	//ofn.nFilterIndex = 1;
//	//ofn.lpstrFileTitle = szFileName;
//	//ofn.nMaxFileTitle = 0;
//	//ofn.lpstrInitialDir = NULL;
//	ofn.Flags = OFN_OVERWRITEPROMPT;
//	GetSaveFileName(&ofn);
//
//	TXTDATA->getSingleton()->mapSave(szFileName,m_pTiles, &m_rcSelectedTile);
//}
//
//void tileMap::mapLoad()
//{
//	OPENFILENAME ofn;
//	HWND hEditFileToBeOpened=NULL;
//
//	ZeroMemory(&ofn, sizeof(OPENFILENAME));
//	ofn.lStructSize = sizeof(OPENFILENAME);
//	ofn.hwndOwner = g_hWnd;
//	ofn.lpstrFilter = "txt Files(*.txt)\0*.txt\0All Files (*.*)\0*.*\0"; //"All Files(*.*)\0*.*\0";
//	ofn.lpstrFile = szFileName;
//	ofn.nMaxFile = 512;
//
//	if (0 != GetOpenFileName(&ofn))
//	{
//		SetWindowText(hEditFileToBeOpened, ofn.lpstrFile);
//		TXTDATA->getSingleton()->mapLoad(szFileName, m_pTiles, &m_rcSelectedTile);
//	}
//
//
//
//}
//
//
//
//void tileMap::tilePrint()
//{
//	m_bObjPrint = false;
//}
//
//void tileMap::tileEraser()
//{
//	//기본 타일 정보 셋팅
//	for (int x = 0; x< TILE_X; x++)
//	{
//		for (int y = 0; y < TILE_Y; y++)
//		{
//
//			m_pTiles[x * TILE_X + y].objectFrameX = 100;
//			m_pTiles[x * TILE_X + y].objectFrameY = 100;
//
//
//		}
//	}
//}
//
//tileMap::tileMap()
//	: m_pTileSet(NULL)
//{
//}
//
//
//tileMap::~tileMap()
//{
//}
