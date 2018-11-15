#include "stdafx.h"
#include "StageScene.h"
#include "Fox.h"
#include "Squirrel.h"
#include "Rabbit.h"
#include "MyHero.h"

char szFileName1[512];





void StageScene::FixedLoad()
{
	TXTDATA->getSingleton()->mapLoad("SaveFile/t2.map", m_pTiles);

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
	ITEMMANAGER->init(20); // 
	m_pMyHero = new MyHero;
	
	m_nNumberOfBlock = 0;
	m_nNumberOfTemp = 0;

	st_mouse = st_MouseIdle;
	g_saveData.gIsRectangleOn = false;
	m_bMiniMapOn = false;
	m_fUIscaleUp = 1.0f;
	m_nSelectedInven = NULL_CLICK; // 0여우 1토끼 2다람쥐
	g_saveData.gSelectedInven = 3;

	m_pImg_Back = IMAGEMANAGER->findImage("back");
	m_pImg_Middle[0] = IMAGEMANAGER->findImage("middle");
	m_pImg_Middle[1] = IMAGEMANAGER->findImage("middle");
	m_pImg_UI_char = IMAGEMANAGER->findImage("ui_character");
	m_pImg_UI_top = IMAGEMANAGER->findImage("ui_bar_top");
	m_pImg_UI_bottom = IMAGEMANAGER->findImage("ui_bar_bottom");
	m_pMiniPlayer = IMAGEMANAGER->findImage("mini_Player");
	m_pMiniEnemy = IMAGEMANAGER->findImage("mini_Enemy");
	m_pImg_TileSet = IMAGEMANAGER->findImage("tileset1_Stage");
	m_pImg_Pixel = IMAGEMANAGER->findImage("delta");

	m_pImg_UIMiniMap = IMAGEMANAGER->findImage("ui_minimap");
	m_pImg_UIFox = IMAGEMANAGER->findImage("ui_fox");
	m_pImg_UISquirrel = IMAGEMANAGER->findImage("ui_squirrel");
	m_pImg_UIRabbit = IMAGEMANAGER->findImage("ui_rabbit");
	m_pImg_UIinventory = IMAGEMANAGER->findImage("parchment");
	m_pImg_MapUI = IMAGEMANAGER->findImage("parchment");
	m_pImg_House = IMAGEMANAGER->findImage("house");


	ENEMYMANAGER->init(60);
	

	for (int i = 0; i < 3; ++i)
	{
		m_rcUIcharacter[i] = RectMake(40 + (103 * i), 12, 88, 88);
	}

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


			if (m_pTiles[y *  g_saveData.gTileMaxCountX + x].unitID == 10)
			{
				m_pFox->setX(m_pTiles[y *  g_saveData.gTileMaxCountX + x].rc.left);
				m_pFox->setY(m_pTiles[y *  g_saveData.gTileMaxCountX + x].rc.top);
			}

			if (m_pTiles[y *  g_saveData.gTileMaxCountX + x].unitID == 11)
			{
				m_pRabbit->setX(m_pTiles[y *  g_saveData.gTileMaxCountX + x].rc.left);
				m_pRabbit->setY(m_pTiles[y *  g_saveData.gTileMaxCountX + x].rc.top);
			}

			if (m_pTiles[y *  g_saveData.gTileMaxCountX + x].unitID == 12)
			{
				m_pSquirrel->setX(m_pTiles[y *  g_saveData.gTileMaxCountX + x].rc.left);
				m_pSquirrel->setY(m_pTiles[y *  g_saveData.gTileMaxCountX + x].rc.top);
			}

			if (m_pTiles[y * g_saveData.gTileMaxCountX + x].terrain == isBlock)
			{
				m_Collide_Tiles[m_nNumberOfBlock] = m_pTiles[y *  g_saveData.gTileMaxCountX + x].rc;
				m_nNumberOfBlock++;
			}

			if (m_pTiles[y *  g_saveData.gTileMaxCountX + x].unitID <= 9)
			{
				ENEMYMANAGER->setEnemy(m_pTiles[y *  g_saveData.gTileMaxCountX + x].unitID,
					m_pTiles[y *  g_saveData.gTileMaxCountX + x].rc.left,
					m_pTiles[y *  g_saveData.gTileMaxCountX + x].rc.top,
					0,Pattern_ofRule);
			}

		}

	}

	g_saveData.gCollideCount = m_nNumberOfBlock;

	SCROLL->init(m_pRabbit->getX(), m_pRabbit->getY());

	ITEMMANAGER->ItemCreate(300, 100, 4, false);
	ITEMMANAGER->ItemCreate(340, 100, 4, false);
	ITEMMANAGER->ItemCreate(380, 100, 4, false);
	ITEMMANAGER->ItemCreate(420, 100, 4, false);
	ITEMMANAGER->ItemCreate(480, 100, 4, false);
	ITEMMANAGER->ItemCreate(560, 100, 4, false);
	ITEMMANAGER->ItemCreate(720, 100, 4, false);
	ITEMMANAGER->ItemCreate(780, 100, 4, false);
	ITEMMANAGER->ItemCreate(880, 100, 4, false);
	ITEMMANAGER->ItemCreate(920, 100, 4, false);

	ITEMMANAGER->ItemCreate(300, 20, 7, false);
	ITEMMANAGER->ItemCreate(340, 20, 7, false);
	ITEMMANAGER->ItemCreate(380, 20, 7, false);
	ITEMMANAGER->ItemCreate(420, 20, 7, false);

	return S_OK;
}

void StageScene::update()
{
	//m_pMyHero->setY(m_pMyHero->getY() + 0.8f);
	//m_pMyHero->setCurrY((int)m_pMyHero->getY() - RABBIT_HEIGHT / 2); 키면좆댐
	//for (int i = m_pMyHero->getY() - 50; i < m_pMyHero->getY() + 50; ++i)
	//{
	//	COLORREF color = GetPixel(GetWindowDC(g_hWnd), (int)m_pMyHero->getX(), i);

	//	int r = GetRValue(color);
	//	int g = GetGValue(color);
	//	int b = GetBValue(color);

	//	if (!(r == 255 && g == 0 && b == 255))
	//	{
	//		m_pMyHero->setY(i - RABBIT_HEIGHT / 2);

	//	}
	//}


	SCROLL->update(m_pMyHero->getX(), m_pMyHero->getY());
	m_pRabbit->update();
	m_pFox->update();
	m_pSquirrel->update();
	ENEMYMANAGER->update();

	m_nNumberOfTemp = 0;
	for (int y = 0; y < g_saveData.gTileMaxCountY; y++)
	{
		for (int x = 0; x < g_saveData.gTileMaxCountX; x++)
		{


			if (m_nNumberOfTemp < m_nNumberOfBlock &&m_pTiles[y *  g_saveData.gTileMaxCountX + x].terrain == isBlock)
			{
				m_pTiles[y *  g_saveData.gTileMaxCountX + x].rc = RectMake(x * TILESIZEX_STAGE - SCROLL->GetX(), y * TILESIZEX_STAGE - SCROLL->GetY(), TILESIZEX_STAGE, TILESIZEY_STAGE);
				m_Collide_Tiles[m_nNumberOfTemp] = RectMake(x * TILESIZEX_STAGE - SCROLL->GetX(), y * TILESIZEX_STAGE - SCROLL->GetY(), TILESIZEX_STAGE, TILESIZEY_STAGE);
				m_nNumberOfTemp++;
			}
			else
				m_pTiles[y *  g_saveData.gTileMaxCountX + x].rc = RectMake(x * TILESIZEX_STAGE - SCROLL->GetX(), y * TILESIZEX_STAGE - SCROLL->GetY(), TILESIZEX_STAGE, TILESIZEY_STAGE);
	
			
		}
	}
	
	for (int i = 0; i < m_nNumberOfBlock; ++i)
	{
		RECT temp_rc;


		if (IntersectRect(&temp_rc, &(m_pMyHero->getRect()), &(m_Collide_Tiles[i])))
		{
			m_pMyHero->setIsGravity(false);

			if (m_pMyHero->getRect().top <= m_Collide_Tiles[i].bottom &&
				m_pMyHero->getRect().bottom >= m_Collide_Tiles[i].bottom
				)  // 벽이 위에 있고 캐릭터가 위로감
			{
				m_pMyHero->setY(m_Collide_Tiles[i].bottom + SCROLL->GetY() );
				m_pMyHero->setIsGravity(true);

			}

			else if (m_pMyHero->getRect().bottom >= m_Collide_Tiles[i].top &&
				m_pMyHero->getRect().top <= m_Collide_Tiles[i].top
				)  // 벽이 아래에 있고 캐릭터가 아래로감
			{


				m_pMyHero->setIsRected(true);
				m_pMyHero->setY(m_Collide_Tiles[i].top + SCROLL->GetY() - RABBIT_HEIGHT);
				m_pMyHero->setIsGravity(false);


			}

			else if (m_pMyHero->getRect().left <= m_Collide_Tiles[i].right &&
				m_pMyHero->getRect().right >= m_Collide_Tiles[i].right
				)  // 벽이 왼쪽에 있고 캐릭터가 왼쪽으로감
			{

				m_pMyHero->setY(m_Collide_Tiles[i].right + SCROLL->GetX() + RABBIT_WIDTH);
			}

			else if (m_pMyHero->getRect().right >= m_Collide_Tiles[i].left &&
				m_pMyHero->getRect().left <= m_Collide_Tiles[i].left
				)  // 벽이 오른쪽에 있고 캐릭터가 오른쪽으로감
			{

				m_pMyHero->setY(m_Collide_Tiles[i].left + SCROLL->GetX() - RABBIT_WIDTH);
			}


		}
		else
		{
			m_pMyHero->setIsGravity(true);
		}


		
	}



	ChangeCharacter();
	KeyEvent();
	UI_Click();
	ITEMMANAGER->update();
	Item_Collide();
	Unit_TileCollide();
	Character_UnitCollide();
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
		m_pMyHero = m_pFox;
	}
	if (mySelectedCh == sel_rabbit)
	{
		m_pRabbit->setIsChoosed(true);
		m_pRabbit->setIsInvin(false);
		m_pFox->setIsChoosed(false);
		m_pFox->setIsInvin(true);
		m_pSquirrel->setIsChoosed(false);
		m_pSquirrel->setIsInvin(true);
		m_pMyHero = m_pRabbit;
	}
	if (mySelectedCh == sel_Squirrel)
	{
		m_pSquirrel->setIsChoosed(true);
		m_pSquirrel->setIsInvin(false);
		m_pRabbit->setIsChoosed(false);
		m_pRabbit->setIsInvin(true);
		m_pFox->setIsChoosed(false);
		m_pFox->setIsInvin(true);
		m_pMyHero = m_pSquirrel;
	}
}

void StageScene::UI_Click()
{

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		st_mouse = tagMOUSE_STATE::st_MouseDown;
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && st_mouse == tagMOUSE_STATE::st_MouseDown)
	{
		for (int i = 0; i < 3; ++i)
		{
			if (PtInRect(&m_rcUIcharacter[i], g_ptMouse))
			{
				st_mouse = tagMOUSE_STATE::st_MouseUp;
				g_saveData.gSelectedInven = i;
			}
			else
			{
				st_mouse = tagMOUSE_STATE::st_MouseIdle;
			}
		}
	}

}

void StageScene::Item_Collide()
{
	std::vector<item*> vItem = ITEMMANAGER->getVec();
	std::vector<item*>::iterator ItemIter;
	for (ItemIter = vItem.begin(); ItemIter != vItem.end(); ItemIter++)
	{
		RECT Item_tempRC;
		if (IntersectRect(&Item_tempRC, &(m_pMyHero->getRect()), &(*ItemIter)->getRect()))
		{
			if ((*ItemIter)->getIsAlive() == false) continue;

			if (m_pMyHero->getIsAlive() == true)
			{
				m_pMyHero->setSpeed(m_pMyHero->getSpeed() + (*ItemIter)->getItemInformation().m_fSpeed);
				m_pMyHero->setDef(m_pMyHero->getDef() + (*ItemIter)->getItemInformation().m_fDef);
				m_pMyHero->sethaveWand((*ItemIter)->getItemInformation().m_bFireball);
				m_pMyHero->setMaxHP(m_pMyHero->getMaxHP() + (*ItemIter)->getItemInformation().m_fMaxHP);
				m_pMyHero->setMaxStamina(m_pMyHero->getMaxStamina() + (*ItemIter)->getItemInformation().m_fMaxStamina);
				m_pMyHero->setMaxMana(m_pMyHero->getMaxMana() + (*ItemIter)->getItemInformation().m_fMaxMana);
				m_pMyHero->setHP(m_pMyHero->getHP() + (*ItemIter)->getItemInformation().m_fHP);
				m_pMyHero->setStamina(m_pMyHero->getStamina() + (*ItemIter)->getItemInformation().m_fStamina);
				m_pMyHero->setMana(m_pMyHero->getMana() + (*ItemIter)->getItemInformation().m_fMana);
				m_pMyHero->setWeight(m_pMyHero->getWeight() + (*ItemIter)->getItemInformation().m_fWeight);
				m_pMyHero->setAccrancy(m_pMyHero->getAccrancy() + (*ItemIter)->getItemInformation().m_fAccuracy);
				m_pMyHero->setCoolDown(m_pMyHero->getCoolDown() + (*ItemIter)->getItemInformation().m_nCharacterChange); // 줄어들수록 쿨다운
				(*ItemIter)->setIsAlive(false);
			}

		}


	}


}

void StageScene::Unit_TileCollide() // 에니미과 벽의 충돌
{

	std::vector<Enemy*> vEnemy = ENEMYMANAGER->getVec();
	std::vector<Enemy*>::iterator EnemyIter;
	for (EnemyIter = vEnemy.begin(); EnemyIter != vEnemy.end(); EnemyIter++)
	{


			if ((*EnemyIter)->getPattern() == Pattern_Stop)
			{
				RECT temp_rc5;
				if (IntersectRect(&temp_rc5, (&m_pMyHero->getRect()), &(*EnemyIter)->getrcMoveArea()))
				{

					if ((*EnemyIter)->getX() <= m_pMyHero->getX())
					{
						(*EnemyIter)->setIsRight(true);
					}
					else
						(*EnemyIter)->setIsRight(false);

					(*EnemyIter)->setState(st_isAttack_Enemy);
					
				}
				else
				{
					(*EnemyIter)->setState(st_isIdle_Enemy);

				}
			}
		


		for (int i = 0; i < m_nNumberOfBlock; ++i)
		{
			RECT temp_rc;
			if (IntersectRect(&temp_rc, (&m_Collide_Tiles[i]), &(*EnemyIter)->getRect()))
			{
				(*EnemyIter)->setrcCollide(m_Collide_Tiles[i]);


				if ((*EnemyIter)->getPattern() == Pattern_moveTileUpDown)
				{

					if ((*EnemyIter)->getRect().bottom >= m_Collide_Tiles[i].top && (*EnemyIter)->getRect().top <= m_Collide_Tiles[i].top) // 위(캐릭터) 아래(벽)
						(*EnemyIter)->setIsDown(false);

					if ((*EnemyIter)->getRect().top <= m_Collide_Tiles[i].bottom && (*EnemyIter)->getRect().bottom >= m_Collide_Tiles[i].bottom) // 위(벽) 아래(캐릭터)
						(*EnemyIter)->setIsDown(true);
				}

				else if ((*EnemyIter)->getPattern() == Pattern_moveStep) // 바닥은 인식못하니 벽을 깔아서 벽을 인식하게하자
				{
					if ((*EnemyIter)->getRect().bottom - 20.0f > m_Collide_Tiles[i].top)
					{
						if ((*EnemyIter)->getRect().left <= m_Collide_Tiles[i].right && (*EnemyIter)->getRect().right >= m_Collide_Tiles[i].right) // 위(캐릭터) 아래(벽)
							(*EnemyIter)->setIsRight(true);

						if ((*EnemyIter)->getRect().right >= m_Collide_Tiles[i].left && (*EnemyIter)->getRect().left <= m_Collide_Tiles[i].left) // 위(캐릭터) 아래(벽)
							(*EnemyIter)->setIsRight(false);
					}
				}

				else if ((*EnemyIter)->getPattern() == Pattern_moveNormal) // 바닥은 인식못하니 벽을 깔아서 벽을 인식하게하자
				{
					if ((*EnemyIter)->getRect().bottom - 20.0f > m_Collide_Tiles[i].top)
					{
						if ((*EnemyIter)->getRect().left <= m_Collide_Tiles[i].right && (*EnemyIter)->getRect().right >= m_Collide_Tiles[i].right) // 위(캐릭터) 아래(벽)
							(*EnemyIter)->setIsRight(true);

						if ((*EnemyIter)->getRect().right >= m_Collide_Tiles[i].left && (*EnemyIter)->getRect().left <= m_Collide_Tiles[i].left) // 위(캐릭터) 아래(벽)
							(*EnemyIter)->setIsRight(false);
					}
				}

				else if ((*EnemyIter)->getPattern() == Pattern_JumpOfFlog || (*EnemyIter)->getPattern() == Pattern_JumpOfGlass) // 바닥은 인식못하니 벽을 깔아서 벽을 인식하게하자
				{
					if ((*EnemyIter)->getRect().bottom - 20.0f > m_Collide_Tiles[i].top)
					{
						if ((*EnemyIter)->getRect().left <= m_Collide_Tiles[i].right && (*EnemyIter)->getRect().right >= m_Collide_Tiles[i].right) // 위(캐릭터) 아래(벽)
							(*EnemyIter)->setIsRight(true);

						if ((*EnemyIter)->getRect().right >= m_Collide_Tiles[i].left && (*EnemyIter)->getRect().left <= m_Collide_Tiles[i].left) // 위(캐릭터) 아래(벽)
							(*EnemyIter)->setIsRight(false);
					}
				}

			}
		
		}

	}

	}

void StageScene::Character_UnitCollide() // 캐릭터와 유닛과의 충돌
{
	std::vector<Enemy*> vEnemy = ENEMYMANAGER->getVec();
	std::vector<Enemy*>::iterator EnemyIter;
	for (EnemyIter = vEnemy.begin(); EnemyIter != vEnemy.end(); EnemyIter++)
	{
		RECT temp_rc;
		if (IntersectRect(&temp_rc, (&m_pMyHero->getRect()), &(*EnemyIter)->getRect()))
		{

			if ((*EnemyIter)->getRect().top <= (m_pMyHero)->getRect().bottom &&
				(*EnemyIter)->getRect().bottom >= (m_pMyHero)->getRect().top && m_pMyHero->getIsRected() == false)
			{
				m_pMyHero->setJumpTemp(m_pMyHero->getJumpPower() / 2 - 1.0f);
				(*EnemyIter)->setDamage(m_pMyHero->getDamage());
			}

			else if ((m_pMyHero)->getRect().right >= (*EnemyIter)->getRect().left &&
				(m_pMyHero)->getRect().left <= (*EnemyIter)->getRect().left) // 몬스터의 왼쪽을 캐릭터가 충돌
			{
				if (m_pMyHero->getIsInvin() == false || m_pMyHero->getState() != st_isHurt)
				{

					if (m_pMyHero->getIsRight() == true)
						m_pMyHero->setX(m_pMyHero->getX() - 45.0f);
					else
						m_pMyHero->setX(m_pMyHero->getX() + 45.0f);

					m_pMyHero->setState(st_isHurt);
					m_pMyHero->setHurtCountTemp(0);
				}
			}
			else if ((m_pMyHero)->getRect().left <= (*EnemyIter)->getRect().right &&
				(m_pMyHero)->getRect().right >= (*EnemyIter)->getRect().right) // 몬스터의 오른쪽을 캐릭터가 충돌
			{
				if (m_pMyHero->getIsRight() == true)
					m_pMyHero->setX(m_pMyHero->getX() - 45.0f);
				else
					m_pMyHero->setX(m_pMyHero->getX() + 45.0f);

				m_pMyHero->setState(st_isHurt);
				m_pMyHero->setHurtCountTemp(0);
			}
			
		}

			
			
				
		}
		


	}

	/*RECT temp1_rc;
	for (int i = 0; i < m_nNumberOfBlock; ++i)
	{
		if (!IntersectRect(&temp1_rc, (&m_pMyHero->getRect()), (&m_Collide_Tiles[i])))
		{
			m_pMyHero->setY(m_pMyHero->getY() + 0.01f);
		}
	}
*/
	




void StageScene::KeyEvent()
{
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
		mySelectedCh = sel_Fox;
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
		mySelectedCh = sel_rabbit;
	if (KEYMANAGER->isOnceKeyDown(VK_F3))
		mySelectedCh = sel_Squirrel;
	if (KEYMANAGER->isOnceKeyDown(VK_F4))
	{
		if (m_bIsPixelOn)
			m_bIsPixelOn = false;
		else
			m_bIsPixelOn = true;
	}
		
	if (KEYMANAGER->isOnceKeyDown(VK_F7))
	{
		if (g_saveData.gIsRectangleOn == true)
			g_saveData.gIsRectangleOn = false;
		else
			g_saveData.gIsRectangleOn = true;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F8))
	{
		if (m_bMiniMapOn == true)
		{
			m_bMiniMapOn = false;
			g_saveData.gGamePause = false;
		}
		else
		{
			m_bMiniMapOn = true;
			g_saveData.gGamePause = true;
		}
	}


	if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE))
	{
		if (g_saveData.gSelectedInven <= 2)
		{
			m_nSelectedInven = 3;
			g_saveData.gSelectedInven = 3;
		}
	}

}




void StageScene::release()
{

}

void StageScene::render(HDC hdc)
{
	m_pImg_Back->render(hdc, 0, 0);
	m_pImg_Middle[0]->render(hdc, 0, 377);
	m_pImg_Middle[1]->render(hdc, m_pImg_Middle[0]->getX() + m_pImg_Middle[1]->getWidth(), 377);
	


	for (int y = 0; y < g_saveData.gTileMaxCountY; y++)
	{
		for (int x = 0; x < g_saveData.gTileMaxCountX; x++)
		{
			
			if (!MY_UTIL::isScreenIn(m_pTiles[y *  g_saveData.gTileMaxCountX + x].rc.left, m_pTiles[y *  g_saveData.gTileMaxCountX + x].rc.top)) continue;

			m_pImg_TileSet->frameRender(hdc,
				m_pTiles[y *  g_saveData.gTileMaxCountX + x].rc.left ,
				m_pTiles[y *  g_saveData.gTileMaxCountX + x].rc.top ,
				m_pTiles[y *  g_saveData.gTileMaxCountX + x].terrainFrameX,
				m_pTiles[y *  g_saveData.gTileMaxCountX + x].terrainFrameY);

			
			if (m_bIsPixelOn == true )
			{
				if (m_pTiles[y *  g_saveData.gTileMaxCountX + x].terrain == isEmpty)
				{
					m_pImg_Pixel->render(hdc,
						m_pTiles[y *  g_saveData.gTileMaxCountX + x].rc.left,
						m_pTiles[y *  g_saveData.gTileMaxCountX + x].rc.top);

				}
			}
		}
	}

	


	if (g_saveData.gIsRectangleOn == true)
	{
		Rectangle(hdc, m_pRabbit->getRect().left, m_pRabbit->getRect().top, m_pRabbit->getRect().right, m_pRabbit->getRect().bottom);
		Rectangle(hdc, m_pFox->getRect().left, m_pFox->getRect().top, m_pFox->getRect().right, m_pFox->getRect().bottom);
		Rectangle(hdc, m_pSquirrel->getRect().left, m_pSquirrel->getRect().top, m_pSquirrel->getRect().right, m_pSquirrel->getRect().bottom);



		for (int i = 0; i < m_nNumberOfBlock; ++i)
			Rectangle(hdc, m_Collide_Tiles[i].left, m_Collide_Tiles[i].top, m_Collide_Tiles[i].right, m_Collide_Tiles[i].bottom);

		char SzText1[128];
		// TRANSPARENT : 투명, OPAQUE : 불투명
		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, RGB(5, 0, 15));
		MY_UTIL::FontOption(hdc, 22, 0);

		sprintf_s(SzText1, "fX : %f /  fY : %f  ", m_pMyHero->getX(), m_pMyHero->getY());
		TextOut(hdc, WINSIZEX / 2 -100, 40, SzText1, strlen(SzText1));

		sprintf_s(SzText1, "left : %ld /  top : %ld  ", m_pMyHero->getRect().left, m_pMyHero->getRect().top);
		TextOut(hdc, WINSIZEX / 2 - 100, 85, SzText1, strlen(SzText1));

		


		std::vector<Enemy*> vEnemy = ENEMYMANAGER->getVec();
		std::vector<Enemy*>::iterator EnemyIter;
		for (EnemyIter = vEnemy.begin(); EnemyIter != vEnemy.end(); EnemyIter++) // 플레이어 총알 백터
		{
			if ((*EnemyIter)->getIsAlive() == false) continue;

			Rectangle(hdc, (*EnemyIter)->getRect().left, (*EnemyIter)->getRect().top, (*EnemyIter)->getRect().right, (*EnemyIter)->getRect().bottom);
		}



	}

	ENEMYMANAGER->render(hdc);
	ITEMMANAGER->render(hdc);

	m_pRabbit->render(hdc);
	m_pFox->render(hdc);
	m_pSquirrel->render(hdc);


	m_pImg_UI_char->render(hdc, 12, 12); 

	if(m_pFox->getIsChoosed() == true)
		m_pImg_UIFox->frameRender(hdc, 72, 20, 0, 0, m_fUIscaleUp);
	else
		m_pImg_UIFox->frameRender(hdc, 72, 20, 1, 0, m_fUIscaleUp);

	if(m_pRabbit->getIsChoosed() == true)
		m_pImg_UIRabbit->frameRender(hdc, 66 + 108, 22, 0, 0, m_fUIscaleUp);
	else
		m_pImg_UIRabbit->frameRender(hdc, 66 + 108, 22, 1, 0, m_fUIscaleUp);

	if(m_pSquirrel->getIsChoosed() == true)
		m_pImg_UISquirrel->frameRender(hdc, 66 + 207, 22, 0, 0, m_fUIscaleUp);
	else
		m_pImg_UISquirrel->frameRender(hdc, 66 + 207, 22, 1, 0, m_fUIscaleUp);

	/*if (g_saveData.gSelectedInven <= 2)
	{
		IMAGEMANAGER->findImage("white2")->render(hdc, WINSIZEX / 2 - IMAGEMANAGER->findImage("white2")->getWidth() / 2, 220);
	}*/

	//////////////////////// 미니맵 ///////////////////////////
	if (m_bMiniMapOn == true)
	{
		m_pImg_MapUI->render(hdc, 200, 200);

		for (int y = 0; y < g_saveData.gTileMaxCountY; y++)
		{
			for (int x = 0; x < g_saveData.gTileMaxCountX; x++)
			{

				m_pImg_TileSet->RatioRender(hdc,
					310 + (m_pTiles[y *  g_saveData.gTileMaxCountX + x].rc.left / MINIMAP_RATIO) + SCROLL->GetX() / MINIMAP_RATIO, // 750은 미니맵 시작X좌표 + 미니맵에 렌더할 객체의 위치left값 / 죽척값 ( 축소될 비율 8~ 10이 적당 ) + 카메라좌표X / 죽척값
					320 + (m_pTiles[y *  g_saveData.gTileMaxCountX + x].rc.top / MINIMAP_RATIO) + SCROLL->GetY() / MINIMAP_RATIO, // 30은 미니맵 시작Y좌표 + 미니맵에 렌더할 객체의 위치top값 / 죽척값 ( 축소될 비율 8~ 10이 적당 ) + 카메라좌표Y / 죽척값
																								// update에서 객체의 위치값이 카메라값에 의해 유동적인경우,  미니맵은 고정될 수 있게 + 스크롤값을 해주어 움직임이 상쇄되게 해주어야한다.
					m_pTiles[y *  g_saveData.gTileMaxCountX + x].terrainFrameX, // 렌더링되는 대상
					m_pTiles[y *  g_saveData.gTileMaxCountX + x].terrainFrameY, // 렌더링되는 대상. 보통의 이미지의 경우 0 으로 해도된다.
					MINIMAP_RATIO * 4, // 죽척값
					TILESIZEX_STAGE, // 객체 이미지 사이즈 X
					TILESIZEY_STAGE); // 객체 이미지 사이즈 Y


				m_pMiniPlayer->RatioRender(hdc,
					310 + m_pRabbit->getRect().left / MINIMAP_RATIO + SCROLL->GetX() / MINIMAP_RATIO,
					320 + m_pRabbit->getRect().top / MINIMAP_RATIO + SCROLL->GetY() / MINIMAP_RATIO,
					m_pMiniPlayer->getFrameX(),
					m_pMiniPlayer->getFrameY(),
					MINIMAP_RATIO,
					33,
					32);

				m_pMiniPlayer->RatioRender(hdc,
					310 + m_pFox->getRect().left / MINIMAP_RATIO + SCROLL->GetX() / MINIMAP_RATIO,
					320 + m_pFox->getRect().top / MINIMAP_RATIO + SCROLL->GetY() / MINIMAP_RATIO,
					m_pMiniPlayer->getFrameX(),
					m_pMiniPlayer->getFrameY(),
					MINIMAP_RATIO,
					33,
					32);

				m_pMiniPlayer->RatioRender(hdc,
					310 + m_pSquirrel->getRect().left / MINIMAP_RATIO + SCROLL->GetX() / MINIMAP_RATIO,
					320 + m_pSquirrel->getRect().top / MINIMAP_RATIO + SCROLL->GetY() / MINIMAP_RATIO,
					m_pMiniPlayer->getFrameX(),
					m_pMiniPlayer->getFrameY(),
					MINIMAP_RATIO,
					33,
					32);
			}
		}
	}/////////////////////////////////////////////////////////////


	// 미니맵 UI
	//m_pImg_UIMiniMap->render(hdc, WINSIZEX - (IMAGEMANAGER->findImage("ui_minimap")->getWidth() + 3), 5);
}





StageScene::StageScene()
{
}
StageScene::~StageScene()
{
}
