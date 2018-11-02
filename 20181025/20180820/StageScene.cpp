#include "stdafx.h"
#include "StageScene.h"
#include "Fox.h"
#include "Squirrel.h"
#include "Rabbit.h"
#include "MyHero.h"

char szFileName1[512];



void StageScene::FixedLoad()
{
	TXTDATA->getSingleton()->mapLoad("SaveFile/test10.map", m_pTiles);

}

void StageScene::CustomLoad()
{
	OPENFILENAME ofn;
	HWND hEditFileToBeOpened = NULL;

	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = g_hWnd;
	ofn.lpstrFilter = "All Files (*.*)\0*.*\0"; //"All Files(*.*)\0*.*\0";
	ofn.lpstrFile = szFileName1;
	ofn.nMaxFile = 512;

	if (0 != GetOpenFileName(&ofn))
	{
		SetWindowText(hEditFileToBeOpened, ofn.lpstrFile);
		TXTDATA->getSingleton()->mapLoad(szFileName1, m_pTiles);
	}
	
}














HRESULT StageScene::init()
{	
	m_pFox = new Fox;
	m_pFox->init();
	m_pRabbit = new Rabbit;
	m_pRabbit->init();
	m_pSquirrel = new Squirrel;
	m_pSquirrel->init();

	m_nNumberOfBlock = 0;
	m_nNumberOfTemp = 0;
	m_bRectangleOn = false;
	m_bMiniMapOn = false;

	m_pImg_Back = IMAGEMANAGER->findImage("back");
	m_pImg_Middle[0] = IMAGEMANAGER->findImage("middle");
	m_pImg_Middle[1] = IMAGEMANAGER->findImage("middle");
	m_pImg_UI_char = IMAGEMANAGER->findImage("ui_character");
	m_pImg_UI_top = IMAGEMANAGER->findImage("ui_bar_top");
	m_pImg_UI_bottom = IMAGEMANAGER->findImage("ui_bar_bottom");
	m_pMiniPlayer = IMAGEMANAGER->findImage("mini_Player");
	m_pMiniEnemy = IMAGEMANAGER->findImage("mini_Enemy");
	m_pImg_TileSet = IMAGEMANAGER->findImage("tileset1_Stage");

	m_pImg_UIMiniMap = IMAGEMANAGER->findImage("ui_minimap");
	m_pImg_UIFox = IMAGEMANAGER->findImage("ui_fox");
	m_pImg_UISquirrel = IMAGEMANAGER->findImage("ui_squirrel");
	m_pImg_UIRabbit = IMAGEMANAGER->findImage("ui_rabbit");

	g_saveData.bIsCustomGame == false;// 임시 
	// m_Tiles 초기화
	if (g_saveData.bIsCustomGame == true)
	{
		CustomLoad();
	}
	else
	{
		FixedLoad();
	}
	g_saveData.gTileMaxCountX = m_pTiles[0].unitID;
	g_saveData.gTileMaxCountY = m_pTiles[1].unitID;
	


	mySelectedCh = sel_rabbit; // 캐릭터 전환은 스테이지씬에서 가능.


	// 다시처음부터 돌면서 유닛위치 및 캐릭터위치 초기화
	for (int y = 0; y < g_saveData.gTileMaxCountY; y++)
	{
		for (int x = 0; x < g_saveData.gTileMaxCountX; x++)
		{
			m_pTiles[y *  g_saveData.gTileMaxCountX + x].rc = RectMake(x * TILESIZEX_STAGE, y * TILESIZEY_STAGE, TILESIZEX_STAGE, TILESIZEY_STAGE);


			if (m_pTiles[y *  g_saveData.gTileMaxCountX + x].unitID == 8)
			{
				m_pRabbit->setX(m_pTiles[y *  g_saveData.gTileMaxCountX + x].rc.left);
				m_pRabbit->setY(m_pTiles[y *  g_saveData.gTileMaxCountX + x].rc.top);
			}

			if (m_pTiles[y * g_saveData.gTileMaxCountX + x].terrain == isBlock)
			{
				m_Collide_Tiles[m_nNumberOfBlock].left = m_pTiles[y * g_saveData.gTileMaxCountX + x].rc.left;
				m_Collide_Tiles[m_nNumberOfBlock].top = m_pTiles[y * g_saveData.gTileMaxCountX + x].rc.top;
				m_nNumberOfBlock++;
			}
		}

	}

	SCROLL->init(m_pRabbit->getX(), m_pRabbit->getY());
	ENEMYMANAGER->init(60);


	m_nNumberOfBlock;



	return S_OK;
}

void StageScene::update()
{
	SCROLL->update(m_pRabbit->getX(), m_pRabbit->getY());
	m_pRabbit->update();

	/*for (int y = 0; y < g_saveData.gTileMaxCountY; y++)
	{
		for (int x = 0; x < g_saveData.gTileMaxCountX; x++)
		{
			m_pTiles[y *  g_saveData.gTileMaxCountX + x].rc.left - SCROLL->GetX();
			m_pTiles[y *  g_saveData.gTileMaxCountX + x].rc.top - SCROLL->GetY();
		}
	}*/

	ChangeCharacter();
	KeyEvent();
	

	// 중력 처리
	/*if (m_pRabbit->getIsGravity() == true)
		m_pRabbit->setY(m_pRabbit->getY() + GRAVITY + m_pRabbit->getWeight());*/

	// 

}


void StageScene::ChangeCharacter()
{
	if (mySelectedCh == sel_Fox)
	{
		m_pFox->setIsChoosed(true);
		m_pFox->setIsInvin(false);
		m_pRabbit->setIsChoosed(false);
		m_pRabbit->setIsInvin(true);
		m_pSquirrel->setIsChoosed(false);
		m_pSquirrel->setIsInvin(true);

	}
	if (mySelectedCh == sel_rabbit)
	{
		m_pRabbit->setIsChoosed(true);
		m_pRabbit->setIsInvin(false);
		m_pFox->setIsChoosed(false);
		m_pFox->setIsInvin(true);
		m_pSquirrel->setIsChoosed(false);
		m_pSquirrel->setIsInvin(true);
	}
	if (mySelectedCh == sel_Squirrel)
	{
		m_pSquirrel->setIsChoosed(true);
		m_pSquirrel->setIsInvin(false);
		m_pRabbit->setIsChoosed(false);
		m_pRabbit->setIsInvin(true);
		m_pFox->setIsChoosed(false);
		m_pFox->setIsInvin(true);

	}
}

void StageScene::KeyEvent()
{
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
		mySelectedCh = sel_Fox;
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
		mySelectedCh = sel_rabbit;
	if (KEYMANAGER->isOnceKeyDown(VK_F3))
		mySelectedCh = sel_Squirrel;
	
	if (KEYMANAGER->isOnceKeyDown(VK_F7))
		if(m_bRectangleOn == true)
			m_bRectangleOn = false;
		else
			m_bRectangleOn = true;
	if (KEYMANAGER->isOnceKeyDown(VK_F8))
		if (m_bMiniMapOn == true)
			m_bMiniMapOn = false;
		else
			m_bMiniMapOn = true;

}




void StageScene::release()
{

}

void StageScene::render(HDC hdc)
{
	m_pImg_Back->render(hdc, 0, 0);
	m_pImg_Middle[0]->render(hdc, 0, 377);
	m_pImg_Middle[1]->render(hdc, m_pImg_Middle[0]->getWidth(), 377);
	


	for (int y = 0; y < g_saveData.gTileMaxCountY; y++)
	{
		for (int x = 0; x < g_saveData.gTileMaxCountX; x++)
		{

			m_pImg_TileSet->frameRender(hdc,
				m_pTiles[y *  g_saveData.gTileMaxCountX + x].rc.left - SCROLL->GetX(),
				m_pTiles[y *  g_saveData.gTileMaxCountX + x].rc.top - SCROLL->GetY(),
				m_pTiles[y *  g_saveData.gTileMaxCountX + x].terrainFrameX,
				m_pTiles[y *  g_saveData.gTileMaxCountX + x].terrainFrameY);


			if (m_bMiniMapOn == true)
			{
				m_pImg_TileSet->RatioRender(hdc,
					(WINSIZEX - 400) + (m_pTiles[y *  g_saveData.gTileMaxCountX + x].rc.left / MINIMAP_RATIO), // 750은 미니맵 시작X좌표 + 미니맵에 렌더할 객체의 위치left값 / 죽척값 ( 축소될 비율 8~ 10이 적당 ) + 카메라좌표X / 죽척값
					30 + (m_pTiles[y *  g_saveData.gTileMaxCountX + x].rc.top / MINIMAP_RATIO), // 30은 미니맵 시작Y좌표 + 미니맵에 렌더할 객체의 위치top값 / 죽척값 ( 축소될 비율 8~ 10이 적당 ) + 카메라좌표Y / 죽척값
																								// update에서 객체의 위치값이 카메라값에 의해 유동적인경우,  미니맵은 고정될 수 있게 + 스크롤값을 해주어 움직임이 상쇄되게 해주어야한다.
					m_pTiles[y *  g_saveData.gTileMaxCountX + x].terrainFrameX, // 렌더링되는 대상
					m_pTiles[y *  g_saveData.gTileMaxCountX + x].terrainFrameY, // 렌더링되는 대상. 보통의 이미지의 경우 0 으로 해도된다.
					MINIMAP_RATIO * 4, // 죽척값
					TILESIZEX_STAGE, // 객체 이미지 사이즈 X
					TILESIZEY_STAGE); // 객체 이미지 사이즈 Y


				m_pMiniPlayer->RatioRender(hdc,
					(WINSIZEX - 400) + m_pRabbit->getRC().left / MINIMAP_RATIO + (SCROLL->GetX() / MINIMAP_RATIO),
					30 + m_pRabbit->getRC().top / MINIMAP_RATIO + (SCROLL->GetY() / MINIMAP_RATIO),
					m_pMiniPlayer->getFrameX(),
					m_pMiniPlayer->getFrameY(),
					MINIMAP_RATIO,
					33,
					32);
			}
	
		}
	}

	if (m_bRectangleOn == true)
	{
		Rectangle(hdc, m_pRabbit->getRC().left, m_pRabbit->getRC().top, m_pRabbit->getRC().right, m_pRabbit->getRC().bottom);
		char SzText1[128];
		// TRANSPARENT : 투명, OPAQUE : 불투명
		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, RGB(5, 0, 15));
		MY_UTIL::FontOption(hdc, 22, 0);

		sprintf_s(SzText1, "fX : %f /  fY : %f  ", m_pRabbit->getX(), m_pRabbit->getY());
		TextOut(hdc, WINSIZEX / 2 -100, 40, SzText1, strlen(SzText1));

	}

	m_pRabbit->render(hdc);



	m_pImg_UI_char->render(hdc, 12, 12); 

	if(m_pFox->getIsChoosed() == true)
		m_pImg_UIFox->frameRender(hdc, 72, 20, 0, 0);
	else
		m_pImg_UIFox->frameRender(hdc, 72, 20, 1, 0);

	if(m_pRabbit->getIsChoosed() == true)
		m_pImg_UIRabbit->frameRender(hdc, 66 + 108, 22, 0, 0);
	else
		m_pImg_UIRabbit->frameRender(hdc, 66 + 108, 22, 1, 0);

	if(m_pSquirrel->getIsChoosed() == true)
		m_pImg_UISquirrel->frameRender(hdc, 66 + 207, 22, 0, 0);
	else
		m_pImg_UISquirrel->frameRender(hdc, 66 + 207, 22, 1, 0);
	


	// 미니맵 UI
	//m_pImg_UIMiniMap->render(hdc, WINSIZEX - (IMAGEMANAGER->findImage("ui_minimap")->getWidth() + 3), 5);
}





StageScene::StageScene()
{
}
StageScene::~StageScene()
{
}
