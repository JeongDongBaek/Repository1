#include "stdafx.h"
#include "stageScene.h"
#include "button.h"
#include "image.h"
#include "PlayerCharacter.h"
#include "bulletManger.h"
#include "effectManager.h"
#include "PlayerCharacter.h"
#include "itemManager.h"
#include "monsterManger.h"
#include "animation.h"
#include "uiManager.h"

char szFileName1[512];

int stageScene::buttonNum = 0;

static void Func_button1(void)
{
	stageScene::buttonNum = 1; // 시나리오 게임
}

static void Func_button2(void)
{
	stageScene::buttonNum = 2; // 사용자 지정 게임
}

HRESULT stageScene::init()
{
	DWORD dwRemove = WS_CAPTION | WS_BORDER | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
	// This should be kept for reverse operation
	DWORD dwStyle = ::GetWindowLong(g_hWnd, 2);
	HMENU hMenu = ::GetMenu(g_hWnd);
	WINDOWPLACEMENT wp = { sizeof WINDOWPLACEMENT };
	::GetWindowPlacement(g_hWnd, &wp);

	::LockWindowUpdate(g_hWnd); // prevent intermediate redrawing
	::SetMenu(g_hWnd, NULL);
	::SetWindowLong(g_hWnd, 2, dwStyle & ~dwRemove);
	HDC hDC = ::GetWindowDC(NULL);
	::LockWindowUpdate(NULL); // allow redrawing
	::SetWindowPos(g_hWnd, NULL, 100, 100, 816, 832, SWP_FRAMECHANGED);



	m_soundMag.init();
	//m_soundMag.addSound("sound/sound_StageBGM.wav", true, true);
	m_soundMag.addSound("sound/EnemyDead0.wav", false, false);
	m_soundMag.addSound("sound/EnemyDead1.wav", false, false);
	m_soundMag.addSound("sound/EnemyDead2.wav", false, false);
	m_soundMag.addSound("sound/EnemyDead3.wav", false, false);
	m_soundMag.addSound("sound/EnemyDead4.wav", false, false);
	m_soundMag.addSound("sound/EnemyDead5.wav", false, false);
	m_soundMag.addSound("sound/EnemyDead6.wav", false, false);

	m_soundMag.addSound("sound/sound_MonsterHit.wav", false, false);

	m_soundMag.addSound("sound/sound_itemGet.wav", false, false);
	m_soundMag.addSound("sound/sound_playerHit.wav", false, false);
	m_soundMag.addSound("sound/sound_playerAtt.wav", false, false);


	//tagTile * m_pTiles = new tagTile[g_saveData.gTileMaxCountX * g_saveData.gTileMaxCountY];
	m_pTileSet[0] = IMAGEMANAGER->findImage("tileset1");
	m_pTileSet[1] = IMAGEMANAGER->findImage("tileset2");
	m_pTileSet[2] = IMAGEMANAGER->findImage("tileset3");
	m_pTileSet[3] = IMAGEMANAGER->findImage("tileset4");
	m_pMiniPlayer = IMAGEMANAGER->findImage("mini_player");
	m_pMiniEnemy = IMAGEMANAGER->findImage("mini_enemy");




	m_bIsMiniMapOn = false;
	m_bIsScoreOn = false;
	m_bIsCameraTextOn = false;
	MiniMap_Ratio = 8;

	m_pImage_checkBox = IMAGEMANAGER->findImage("black");

	m_pButton1 = new button;
	m_pButton1->init("prepared", WINSIZEX / 2, 380, PointMake(0, 1), PointMake(0, 0), Func_button1); // 시나리오

	m_pButton2 = new button;
	m_pButton2->init("custom", WINSIZEX / 2, 480, PointMake(0, 1), PointMake(0, 0), Func_button2); // 사용자 지정게임

																								   // 타이틀 CPP 이동

	m_pEffMagr = new effectManager;
	m_pEffMagr->addEffect("Bullet_End_0", "image/resources/bullet_image/Bullet_End_0.bmp", 238, 30, 34, 30, 15, 50);
	m_pEffMagr->addEffect("Bullet_End_1", "image/resources/bullet_image/Bullet_End_1.bmp", 238, 34, 34, 34, 15, 50);
	m_pEffMagr->addEffect("Bullet_End_2", "image/resources/bullet_image/Bullet_End_2.bmp", 224, 32, 32, 32, 15, 50);
	m_pEffMagr->addEffect("Bullet_End_3", "image/resources/bullet_image/Bullet_End_3.bmp", 210, 24, 30, 24, 15, 50);

	m_pEffMagr->addEffect("Monster_die", "image/resources/monster_image/Monster_Die_Eff.bmp", 512, 384, 512 / 4, 384 / 3, 15, 10);

	m_pEffMagr->addEffect("Item_Get1", "image/resources/item_image/Item_Get.bmp", 320, 31, (320 / 4), 31, 15, 5);
	m_pEffMagr->addEffect("Item_Get2", "image/resources/item_image/Item_Get2.bmp", 230, 70, (230 / 5), 70, 15, 5);

	m_pUiMag = new uiManager;
	m_pUiMag->init(100);

	m_player = new PlayerCharacter;
	m_player->init(&m_soundMag);
	m_player->setBulletMagPointer(&m_pBulletMag);

	m_pBulletMag = new bulletManger;
	m_pBulletMag->init(100, m_pEffMagr);

	m_pBulletMagMons = new bulletManger;
	m_pBulletMagMons->init(100, m_pEffMagr);

	m_pMonsterMag = new monsterManger;
	m_pMonsterMag->setEffMagPoint(m_pEffMagr);
	m_pMonsterMag->init(50);

	m_tBulletInfo.tIsAlive = true;
	m_tBulletInfo.tBulletSetNum = 1;
	m_tBulletInfo.tScale = 1.0f;
	m_tBulletInfo.tScaleMax = m_tBulletInfo.tScale * 2.0f;
	m_tBulletInfo.tRadius = IMAGEMANAGER->findImage("Bullet_R")->getFrameWidth() / 2;
	m_tBulletInfo.tExpRadius = m_tBulletInfo.tRadius * 2.0f;
	m_tBulletInfo.tRange = 500.0f;
	m_tBulletInfo.tBulletBoom = false;

	m_tBulletInfo.tDmage = 1.0f;
	m_tBulletInfo.tKnokBack = 0.5f;
	m_tBulletInfo.tMoveSpeed = 3.0f;
	m_tBulletInfo.tScatter = 10.0f;


	m_tBulletInfo.tBoomType = BULLET_BOOM_TYPE::ANGLE_LINE;
	m_tBulletInfo.tShootType = BULLET_SHOOT_TYPE::BULLET_SHOOT_NUM;
	m_tBulletInfo.tMasterType = BULLET_MASTER_TYPE::MONSTER;
	m_tBulletInfo.tMoveActType = BULLET_MOVE_ACT_TYPE::BULLET_MOVE_ACT_NUM;
	m_tBulletInfo.tImageType = BULLET_MOVE_TYPE::ONE_LINE;
	m_tBulletInfo.tMoveType = BULLET_IMAGE_TYPE::COLOR_R;

	//m_pMonsterMag->Regeneration("BG_Blue_Guardian", 1, Moninfo, m_pBulletMagMons, m_player, m_tBulletInfo);

	m_pItemMag = new itemManager;
	m_pItemMag->init(10);
	m_isSpawnCycle = false;
	m_GateNum = 0;
	m_GateMonsterIndex = 0;
	m_GateMonsterNum = 0;
	m_stageNum = 0;
	m_MaxSpawnNum = 0;
	m_ClearScore = 0;
	m_nNumber = 0;
	m_nTempNumber = 0;


	m_isTest = false; // 정지수 : 테스트용으로 만듦

					  //CAMERA->init();
	return S_OK;
}

void stageScene::release()
{
	m_pUiMag->release();
	m_pBulletMag->release();
	m_pBulletMagMons->release();
	m_pEffMagr->release();
	m_pItemMag->release();
	m_soundMag.release();
}

void stageScene::update()
{



	KeyEvent();

	if (buttonNum == 0)
	{
		m_pButton1->update();
		m_pButton2->update();
	}
	if (buttonNum == 1)
	{
		g_saveData.gTileMaxCountX = 35;
		g_saveData.gTileMaxCountY = 35;
		FixedLoadEvent(); // 시나리오의 맵 최대크기는 1600 1600
		buttonNum = 3;
	}
	if (buttonNum == 2)
	{
		g_saveData.gTileMaxCountX = 50;
		g_saveData.gTileMaxCountY = 50;
		LoadEvent();
		buttonNum = 3;
	}
	if (buttonNum == 3)
	{
		// 최초 한번만 실행되는 부분
		ShowCursor(FALSE);
		m_bIsMiniMapOn = true;

		for (int x = 0; x < g_saveData.gTileMaxCountX; x++)
		{
			for (int y = 0; y < g_saveData.gTileMaxCountX; y++)
			{
				m_pTiles[x * g_saveData.gTileMaxCountX + y].rc = RectMake(x * TILE_SIZEX, y * TILE_SIZEY, TILE_SIZEX, TILE_SIZEY);
				m_pTiles[x * g_saveData.gTileMaxCountX + y].isMove = true; // 특정 타일의 이동불가// */

				if (m_pTiles[x * g_saveData.gTileMaxCountX + y].SampleNum == 1)
				{
					if ((m_pTiles[x * g_saveData.gTileMaxCountX + y].terrainFrameX == 6 && m_pTiles[x * g_saveData.gTileMaxCountX + y].terrainFrameY == 3) ||
						(m_pTiles[x * g_saveData.gTileMaxCountX + y].terrainFrameX == 6 && m_pTiles[x * g_saveData.gTileMaxCountX + y].terrainFrameY == 4) ||
						(m_pTiles[x * g_saveData.gTileMaxCountX + y].terrainFrameX == 6 && m_pTiles[x * g_saveData.gTileMaxCountX + y].terrainFrameY == 5) ||
						(m_pTiles[x * g_saveData.gTileMaxCountX + y].terrainFrameX == 7 && m_pTiles[x * g_saveData.gTileMaxCountX + y].terrainFrameY == 4) ||
						(m_pTiles[x * g_saveData.gTileMaxCountX + y].terrainFrameX == 7 && m_pTiles[x * g_saveData.gTileMaxCountX + y].terrainFrameY == 5))
					{
						m_nNumber++;
						m_pTiles[x * g_saveData.gTileMaxCountX + y].isMove = false;
					}
				}

				if (m_pTiles[x * g_saveData.gTileMaxCountX + y].SampleNum == 3)
				{
					if ((m_pTiles[x * g_saveData.gTileMaxCountX + y].terrainFrameX == 5 && m_pTiles[x * g_saveData.gTileMaxCountX + y].terrainFrameY == 3))
					{
						m_player->setX(m_pTiles[x * g_saveData.gTileMaxCountX + y].rc.left + 16.0f);
						m_player->setY(m_pTiles[x * g_saveData.gTileMaxCountX + y].rc.top + 16.0f);
						m_pEffMagr->play("Item_Get1", m_player->getX() - (320 / 4) / 2, m_player->getY());
						m_pEffMagr->play("Item_Get2", m_player->getX() - (230 / 5) / 2, m_player->getY() - (70) / 2);
					}
				}
			}
		}
		// 충돌타일만 따로 빼기/////////////////////
		//RECT*  m_pTiles_Collide = new RECT[m_nNumber];

		for (int x = 0; x < g_saveData.gTileMaxCountX; x++)
		{
			for (int y = 0; y < g_saveData.gTileMaxCountX; y++)
			{
				if (m_pTiles[x * g_saveData.gTileMaxCountX + y].isMove == false)
				{
					m_pTiles_Collide[m_nTempNumber] = m_pTiles[x * g_saveData.gTileMaxCountX + y].rc;
					m_nTempNumber++;
				}
			}

		}
		//////////////////////////////
		buttonNum++;
	}



	if (buttonNum == 4)
	{
		KeyEvent();

		if (!m_BGMreSet)
		{
			m_BGMreSet = true;
			m_soundMag.play("sound/sound_StageBGM.wav", g_saveData.gMainBGMValue);
		}

		if (KEYMANAGER->isOnceKeyDown('R'))
		{
			int tempItemValue = m_pItemMag->getItemMax();


			tagItemInfo ItemInfo;
			ItemInfo.tScale = 1.0f;
			ItemInfo.tTimer = 1000;
			ItemInfo.tRadius = 1.5f;
			ItemInfo.posX = m_player->getX() - 100.0f;
			ItemInfo.posY = m_player->getY() - 100.0f;
			int tempItem = RANDOM->getFromIntTo(1, tempItemValue);


			m_pItemMag->itemDrop("ItemObject", tempItem, ItemInfo, m_pEffMagr);
		}



		m_nTilesNumber = 0;
		for (int x = 0; x < g_saveData.gTileMaxCountX; x++)
		{
			for (int y = 0; y < g_saveData.gTileMaxCountY; y++)
			{
				if (m_nTilesNumber < m_nNumber && !m_pTiles[x * g_saveData.gTileMaxCountX + y].isMove)
				{
					m_pTiles_Collide[m_nTilesNumber] = RectMake(x * TILE_SIZEX - SCROLL->GetX(), y * TILE_SIZEY - SCROLL->GetY(), TILE_SIZEX, TILE_SIZEY);
					m_pTiles[x * g_saveData.gTileMaxCountX + y].rc = RectMake(x * TILE_SIZEX - SCROLL->GetX(), y * TILE_SIZEY - SCROLL->GetY(), TILE_SIZEX, TILE_SIZEY);

					m_nTilesNumber++;
				}
				else
				{
					m_pTiles[x * g_saveData.gTileMaxCountX + y].rc = RectMake(x * TILE_SIZEX - SCROLL->GetX(), y * TILE_SIZEY - SCROLL->GetY(), TILE_SIZEX, TILE_SIZEY);
				}
			}
		}


		SpawnGateTime();
		m_player->update();
		m_pMonsterMag->update();
		m_pItemMag->update();
		m_pBulletMag->update();

		m_pBulletMagMons->update();
		m_pEffMagr->update();
		m_pUiMag->update();

		ColRc();

		for (int i = 0; i < m_nNumber; i++)
		{
			RECT m_rc;

			if (IntersectRect(&m_rc, &m_pTiles_Collide[i], &m_player->getRect()))
			{
				m_player->setTileRc(m_pTiles_Collide[i]);
				m_player->ColP2T();
				//break;
			}
		}
		SCROLL->update(m_player->getX(), m_player->getY());
	}

}




void stageScene::KeyEvent()
{
	// 단축키
	if (KEYMANAGER->isOnceKeyDown(VK_F6))
	{
		if (m_bIsCameraTextOn)
			m_bIsCameraTextOn = false;
		else
			m_bIsCameraTextOn = true;
	}
}

void stageScene::render(HDC hdc)
{
	if (buttonNum == 0)
	{
		m_pImage_checkBox->render(hdc, 0, 0);
		m_pButton1->render(hdc);
		m_pButton2->render(hdc);
	}
	if (buttonNum == 3)
	{

	}
	if (buttonNum == 4)
	{
		for (int x = 0; x < g_saveData.gTileMaxCountX; x++)
		{
			for (int y = 0; y < g_saveData.gTileMaxCountY; y++)
			{
				m_pTileSet[m_pTiles[x * g_saveData.gTileMaxCountX + y].SampleNum]->frameRender(hdc,
					m_pTiles[x * g_saveData.gTileMaxCountX + y].rc.left,
					m_pTiles[x * g_saveData.gTileMaxCountX + y].rc.top,
					m_pTiles[x * g_saveData.gTileMaxCountX + y].terrainFrameX,
					m_pTiles[x * g_saveData.gTileMaxCountX + y].terrainFrameY);


				//Rectangle(hdc,
				// m_pTiles[x * g_saveData.gTileMaxCountX + y].rc.left,
				// m_pTiles[x * g_saveData.gTileMaxCountX + y].rc.top,
				// m_pTiles[x * g_saveData.gTileMaxCountX + y].rc.right,
				// m_pTiles[x * g_saveData.gTileMaxCountX + y].rc.bottom);
			}
		}

		//for (int i = 0; i < m_nNumber; ++i)
		//{
		//	Rectangle(hdc, m_pTiles_Collide[i].left,
		//		m_pTiles_Collide[i].top, m_pTiles_Collide[i].right,
		//		m_pTiles_Collide[i].bottom);
		//}


		char szText[256];

		// TRANSPARENT : 투명, OPAQUE : 불투명
		SetBkMode(hdc, TRANSPARENT);

		SetTextColor(hdc, RGB(255, 0, 255));

		sprintf_s(szText, "BulletSetNum : %d",
			m_pBulletMag->getIter());
		TextOut(hdc, 10, WINSIZEY - 20, szText, strlen(szText));

		m_pMonsterMag->render(hdc);
		m_pItemMag->render(hdc);
		m_pBulletMag->render(hdc);
		m_pBulletMagMons->render(hdc);
		//m_pMonsterMag->render(hdc);
		m_pItemMag->render(hdc);
		m_pEffMagr->render(hdc);
		m_player->render(hdc);
		m_pUiMag->render(hdc);

		ClearEvent();
		//TIMEMANAGER->render(hdc);
	}


	//미니맵//
	if (m_bIsMiniMapOn)
	{
		for (int x = 0; x < g_saveData.gTileMaxCountX; x++)
		{
			for (int y = 0; y < g_saveData.gTileMaxCountY; y++)
			{
				m_pTileSet[m_pTiles[x *  g_saveData.gTileMaxCountX + y].SampleNum]->RatioRender(hdc,
					649 + m_pTiles[x *  g_saveData.gTileMaxCountX + y].rc.left / MiniMap_Ratio + (SCROLL->GetX() / MiniMap_Ratio),
					11 + m_pTiles[x *  g_saveData.gTileMaxCountX + y].rc.top / MiniMap_Ratio + (SCROLL->GetY() / MiniMap_Ratio),
					m_pTiles[x *  g_saveData.gTileMaxCountX + y].terrainFrameX,
					m_pTiles[x *  g_saveData.gTileMaxCountX + y].terrainFrameY,
					MiniMap_Ratio,
					TILE_SIZEX,
					TILE_SIZEY);



				


			}
		}


		std::vector<monster*> vMonster = m_pMonsterMag->getVecMons();
		std::vector<monster*>::iterator MonsIter;
		for (MonsIter = vMonster.begin(); MonsIter != vMonster.end(); MonsIter++) // 플레이어 총알 백터
		{
			if (!(*MonsIter)->getMonInfo().tIsAlive) continue;

			m_pMiniEnemy->RatioRender(hdc,
				649 + (*MonsIter)->getMonInfo().m_rc.left / MiniMap_Ratio + (SCROLL->GetX() / MiniMap_Ratio),
				11 + (*MonsIter)->getMonInfo().m_rc.top / MiniMap_Ratio + (SCROLL->GetY() / MiniMap_Ratio),
				m_pMiniEnemy->getFrameX(),
				m_pMiniEnemy->getFrameY(),
				MiniMap_Ratio * 4,
				54,
				54);
		}

		m_pMiniPlayer->RatioRender(hdc,
			649 + m_player->getRect().left / MiniMap_Ratio + (SCROLL->GetX() / MiniMap_Ratio),
			11 + m_player->getRect().top / MiniMap_Ratio + (SCROLL->GetY() / MiniMap_Ratio),
			m_pMiniPlayer->getFrameX(),
			m_pMiniPlayer->getFrameY(),
			MiniMap_Ratio * 4,
			54,
			54);

	}
	//////////

	if (m_bIsCameraTextOn)
	{
		char szText[256];

		// TRANSPARENT : 투명, OPAQUE : 불투명
		SetBkMode(hdc, TRANSPARENT);

		SetTextColor(hdc, RGB(255, 0, 255));

		sprintf_s(szText, "화면시작좌표X : %f / 화면시작좌표Y : %f",
			SCROLL->GetX(), SCROLL->GetY());
		TextOut(hdc, 400, 0, szText, strlen(szText));

		sprintf_s(szText, "캐릭터좌표 : %f / 캐릭터좌표Y : %f",
			m_player->getX(), m_player->getY());
		TextOut(hdc, 400, 100, szText, strlen(szText));
	}

	if (m_bIsScoreOn)
	{
		char szTextStage[128];
		// TRANSPARENT : 투명, OPAQUE : 불투명
		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, RGB(255, 255, 255));
		MY_UTIL::FontOption(hdc, 25, 1000);
		sprintf_s(szTextStage, "%s : %d", "스테이지", m_stageNum);
		TextOut(hdc, 320, 42, szTextStage, strlen(szTextStage));
		MY_UTIL::FontDelete(hdc);


		char szTextScore[128];
		// TRANSPARENT : 투명, OPAQUE : 불투명
		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, RGB(255, 255, 255));
		MY_UTIL::FontOption(hdc, 25, 1000);
		sprintf_s(szTextScore, "%s : %d", "점수", m_ClearScore);
		TextOut(hdc, 320, 15, szTextScore, strlen(szTextScore));
		MY_UTIL::FontDelete(hdc);

	}


}

void stageScene::LoadEvent()
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

	g_saveData.gTileMaxCountX = m_pTiles[0].terrain;
	g_saveData.gTileMaxCountY = m_pTiles[0].terrain;

}

void stageScene::FixedLoadEvent()
{

	TXTDATA->getSingleton()->mapLoad("SaveFile/mainGame7.map", m_pTiles);

}

void stageScene::MonSpawnCycle(int SpawnOfNumber, int MonNumber)
{
	tSpawnTile.nSpawnOfNumber = SpawnOfNumber;
	tSpawnTile.nSPawnNumber = MonNumber;

	// 설정
	m_tBulletInfo.tIsAlive = true;
	m_tBulletInfo.tBulletSetNum = 1;
	m_tBulletInfo.tScale = 1.0f;
	m_tBulletInfo.tScaleMax = m_tBulletInfo.tScale * 2.0f;
	m_tBulletInfo.tRadius = IMAGEMANAGER->findImage("Bullet_R")->getFrameWidth() / 2;
	m_tBulletInfo.tExpRadius = m_tBulletInfo.tRadius * 2.0f;
	m_tBulletInfo.tRange = 500.0f;
	m_tBulletInfo.tBulletBoom = false;

	m_tBulletInfo.tDmage = 1.0f;
	m_tBulletInfo.tKnokBack = 0.5f;
	m_tBulletInfo.tMoveSpeed = 5.0f;
	m_tBulletInfo.tScatter = 10.0f;


	m_tBulletInfo.tBoomType = BULLET_BOOM_TYPE::ANGLE_LINE;
	m_tBulletInfo.tShootType = BULLET_SHOOT_TYPE::ONE_SHOOT;
	m_tBulletInfo.tMasterType = BULLET_MASTER_TYPE::PLAYER;
	m_tBulletInfo.tMoveActType = BULLET_MOVE_ACT_TYPE::BULLET_MOVE_ACT_NUM;
	m_tBulletInfo.tImageType = BULLET_IMAGE_TYPE::COLOR_R;
	m_tBulletInfo.tMoveType = BULLET_MOVE_TYPE::ONE_LINE;


	for (int i = 0; i < tSpawnTile.nSpawnOfNumber; i++)
	{
		switch (tSpawnTile.nSPawnNumber)
		{
		case 0:
			tMoninfo.tHpMax = tMoninfo.tHp;
			m_tBulletInfo.tBulletSetNum = 1;

			m_pMonsterMag->Regeneration("BG_Beholder", 1, tMoninfo, m_pBulletMagMons, m_player, m_tBulletInfo);
			break;
		case 1:
			tMoninfo.tHpMax = tMoninfo.tHp;
			m_tBulletInfo.tBulletSetNum = 2;

			m_pMonsterMag->Regeneration("BG_Blue_Guardian", 2, tMoninfo, m_pBulletMagMons, m_player, m_tBulletInfo);
			break;
		case 2:
			tMoninfo.tHpMax = tMoninfo.tHp;
			m_tBulletInfo.tBulletSetNum = 3;

			m_pMonsterMag->Regeneration("BG_Blue_Mindflayer", 3, tMoninfo, m_pBulletMagMons, m_player, m_tBulletInfo);
			break;
		case 3:
			tMoninfo.tHpMax = tMoninfo.tHp;
			m_tBulletInfo.tBulletSetNum = 3;

			m_pMonsterMag->Regeneration("BG_Bugman", 4, tMoninfo, m_pBulletMagMons, m_player, m_tBulletInfo);
			break;
		case 4:
			tMoninfo.tHpMax = tMoninfo.tHp;
			m_pMonsterMag->Regeneration("BG_Cetus", 5, tMoninfo, m_pBulletMagMons, m_player, m_tBulletInfo);
			break;
		case 5:
			tMoninfo.tHpMax = tMoninfo.tHp;
			m_tBulletInfo.tBulletSetNum = 3;

			m_pMonsterMag->Regeneration("BG_Coven", 6, tMoninfo, m_pBulletMagMons, m_player, m_tBulletInfo);
			break;
		case 6:
			tMoninfo.tHpMax = tMoninfo.tHp;
			m_pMonsterMag->Regeneration("BG_Cow", 7, tMoninfo, m_pBulletMagMons, m_player, m_tBulletInfo);
			break;
		case 7:
			tMoninfo.tHpMax = tMoninfo.tHp;
			m_tBulletInfo.tBulletSetNum = 3;

			m_pMonsterMag->Regeneration("BG_Cyclops", 8, tMoninfo, m_pBulletMagMons, m_player, m_tBulletInfo);
			break;
		case 8:
			// 설정
			m_tBulletInfo.tIsAlive = true;
			m_tBulletInfo.tBulletSetNum = 3;
			m_tBulletInfo.tScale = 1.0f;
			m_tBulletInfo.tScaleMax = m_tBulletInfo.tScale * 2.0f;
			m_tBulletInfo.tRadius = IMAGEMANAGER->findImage("Bullet_R")->getFrameWidth() / 2;
			m_tBulletInfo.tExpRadius = m_tBulletInfo.tRadius * 2.0f;
			m_tBulletInfo.tRange = 500.0f;
			m_tBulletInfo.tBulletBoom = false;

			m_tBulletInfo.tDmage = 1.0f;
			m_tBulletInfo.tKnokBack = 0.5f;
			m_tBulletInfo.tMoveSpeed = 5.0f;
			m_tBulletInfo.tScatter = 10.0f;


			m_tBulletInfo.tBoomType = BULLET_BOOM_TYPE::ANGLE_LINE;
			m_tBulletInfo.tShootType = BULLET_SHOOT_TYPE::CUFF_SHOOT;
			m_tBulletInfo.tMasterType = BULLET_MASTER_TYPE::MONSTER;
			m_tBulletInfo.tMoveActType = BULLET_MOVE_ACT_TYPE::BULLET_MOVE_ACT_NUM;
			m_tBulletInfo.tImageType = BULLET_IMAGE_TYPE::COLOR_R;
			m_tBulletInfo.tMoveType = BULLET_MOVE_TYPE::ONE_LINE;

			tMoninfo.tHpMax = tMoninfo.tHp;
			m_pMonsterMag->Regeneration("BG_Dark_Lord", 9, tMoninfo, m_pBulletMagMons, m_player, m_tBulletInfo);
			break;
		case 9:
			tMoninfo.tHpMax = tMoninfo.tHp;
			m_pMonsterMag->Regeneration("BG_Dog", 10, tMoninfo, m_pBulletMagMons, m_player, m_tBulletInfo);
			break;
		case 10:
			tMoninfo.tHpMax = tMoninfo.tHp;
			m_tBulletInfo.tBulletSetNum = 3;

			m_pMonsterMag->Regeneration("BG_Eye_Slime", 11, tMoninfo, m_pBulletMagMons, m_player, m_tBulletInfo);
			break;
		case 11:
			tMoninfo.tHpMax = tMoninfo.tHp;
			m_tBulletInfo.tIsAlive = true;
			m_tBulletInfo.tBulletSetNum = 4;
			m_tBulletInfo.tScale = 1.0f;
			m_tBulletInfo.tScaleMax = m_tBulletInfo.tScale * 2.0f;
			m_tBulletInfo.tRadius = IMAGEMANAGER->findImage("Bullet_R")->getFrameWidth() / 2;
			m_tBulletInfo.tExpRadius = m_tBulletInfo.tRadius * 2.0f;
			m_tBulletInfo.tRange = 500.0f;
			m_tBulletInfo.tBulletBoom = false;

			m_tBulletInfo.tDmage = 1.0f;
			m_tBulletInfo.tKnokBack = 0.5f;
			m_tBulletInfo.tMoveSpeed = 5.0f;
			m_tBulletInfo.tScatter = 10.0f;


			m_tBulletInfo.tBoomType = BULLET_BOOM_TYPE::ANGLE_LINE;
			m_tBulletInfo.tShootType = BULLET_SHOOT_TYPE::ONE_SHOOT;
			m_tBulletInfo.tMasterType = BULLET_MASTER_TYPE::MONSTER;
			m_tBulletInfo.tMoveActType = BULLET_MOVE_ACT_TYPE::BULLET_MOVE_ACT_NUM;
			m_tBulletInfo.tImageType = BULLET_IMAGE_TYPE::COLOR_R;
			m_tBulletInfo.tMoveType = BULLET_MOVE_TYPE::MOVE_CENTRIFUGAL;

			m_pMonsterMag->Regeneration("BG_Faun_Archer", 12, tMoninfo, m_pBulletMagMons, m_player, m_tBulletInfo);
			break;
		case 12:
			tMoninfo.tHpMax = tMoninfo.tHp;
			m_pMonsterMag->Regeneration("BG_Firewolf", 13, tMoninfo, m_pBulletMagMons, m_player, m_tBulletInfo);
			break;
		case 13:
			tMoninfo.tHpMax = tMoninfo.tHp;
			m_pMonsterMag->Regeneration("BG_Gargoyle", 14, tMoninfo, m_pBulletMagMons, m_player, m_tBulletInfo);
			break;
		case 14:
			tMoninfo.tHpMax = tMoninfo.tHp;
			m_pMonsterMag->Regeneration("BG_Giant_Run", 15, tMoninfo, m_pBulletMagMons, m_player, m_tBulletInfo);
			break;
		case 15:
			tMoninfo.tHpMax = tMoninfo.tHp;
			m_pMonsterMag->Regeneration("BG_Gnome_Run", 16, tMoninfo, m_pBulletMagMons, m_player, m_tBulletInfo);
			break;
		case 16:
			tMoninfo.tHpMax = tMoninfo.tHp;
			m_pMonsterMag->Regeneration("BG_Igor", 17, tMoninfo, m_pBulletMagMons, m_player, m_tBulletInfo);
			break;
		case 17:
			tMoninfo.tHpMax = tMoninfo.tHp;
			m_pMonsterMag->Regeneration("BG_Itchy", 18, tMoninfo, m_pBulletMagMons, m_player, m_tBulletInfo);
			break;
		case 18:
			tMoninfo.tHpMax = tMoninfo.tHp;
			m_pMonsterMag->Regeneration("BG_Knife_dude", 19, tMoninfo, m_pBulletMagMons, m_player, m_tBulletInfo);
			break;
		}
	}
	m_SpawnCount++;
	m_isSpawnCycle = false;
}



void stageScene::ColRc()
{
	RECT temp_rc;

	// 몬스터 매니저 정보
	std::vector<monster*> vMonster = m_pMonsterMag->getVecMons();
	std::vector<monster*>::iterator MonsIter;
	for (MonsIter = vMonster.begin(); MonsIter != vMonster.end(); MonsIter++) // 플레이어 총알 백터
	{
		if (!(*MonsIter)->getMonInfo().tIsAlive) continue;

		// 플레이어와 몬스터 충돌
		RECT tempRC = (*MonsIter)->getMonInfo().m_rc;
		if ((*MonsIter)->getMonInfo().tIsAlive && IntersectRect(&temp_rc, &m_player->getRect(), &tempRC))
		{
			if (!m_player->getHitState())
				m_player->PlayerDamage(1.0f);
		}

		for (int i = 0; i < m_nNumber; i++)
		{
			if (IntersectRect(&temp_rc, &m_pTiles_Collide[i], &tempRC))
			{
				(*MonsIter)->rectNotMove(m_pTiles_Collide[i]);
			}
		}
	}

	// 몬스터 총알 충돌
	std::vector<bullet*> vMonsterBullet = m_pBulletMagMons->getVecBullet();
	std::vector<bullet*>::iterator MonsterBulletIter;
	for (MonsterBulletIter = vMonsterBullet.begin(); MonsterBulletIter != vMonsterBullet.end(); MonsterBulletIter++) // 플레이어 총알 백터
	{
		if (!(*MonsterBulletIter)->getIsAlive()) continue;

		for (int i = 0; i < m_nNumber; i++)
		{
			if (IntersectRect(&temp_rc, &m_pTiles_Collide[i], &(*MonsterBulletIter)->getRect()))
			{
				(*MonsterBulletIter)->HitEff();
			}
		}

		if ((*MonsterBulletIter)->getIsAlive() &&
			(*MonsterBulletIter)->getTagBulletInfo().tRadius + m_player->getRadius() >
			(MY_UTIL::getDistance(
			(*MonsterBulletIter)->getTagBulletInfo().tPosX,
				(*MonsterBulletIter)->getTagBulletInfo().tPosY,
				m_player->getX(),
				m_player->getY()))
			)
		{
			// 플레이어 피격 처리
			if (!m_player->getHitState())
			{
				m_player->PlayerDamage((*MonsterBulletIter)->getTagBulletInfo().tDmage);
				(*MonsterBulletIter)->HitEff();
			}
		}
	}

	// 플레이어 총알 충돌
	std::vector<bullet*> vPlayerBullet = m_pBulletMag->getVecBullet();
	std::vector<bullet*>::iterator PlayerBulletIter;
	for (PlayerBulletIter = vPlayerBullet.begin(); PlayerBulletIter != vPlayerBullet.end(); PlayerBulletIter++) // 플레이어 총알 백터
	{
		if (!(*PlayerBulletIter)->getIsAlive()) continue;

		for (int i = 0; i < m_nNumber; i++)
		{
			if (IntersectRect(&temp_rc, &m_pTiles_Collide[i], &(*PlayerBulletIter)->getRect()))
			{
				(*PlayerBulletIter)->HitEff();
			}
		}

		for (MonsIter = vMonster.begin(); MonsIter != vMonster.end(); MonsIter++) // 몬스터 백터
		{
			if (!(*MonsIter)->getMonInfo().tIsAlive) continue;
			{
				if ((*PlayerBulletIter)->getIsAlive() &&
					(*PlayerBulletIter)->getTagBulletInfo().tRadius + (*MonsIter)->getMonInfo().tRadius >
					(MY_UTIL::getDistance(
					(*PlayerBulletIter)->getTagBulletInfo().tPosX,
						(*PlayerBulletIter)->getTagBulletInfo().tPosY,
						(*MonsIter)->getMonInfo().tPosX,
						(*MonsIter)->getMonInfo().tPosY))
					)
				{
					// 몬스터 피격 처리
					(*MonsIter)->Damge((*PlayerBulletIter)->getTagBulletInfo().tDmage, &m_soundMag, m_pItemMag);
					(*MonsIter)->knokback((*PlayerBulletIter)->getTagBulletInfo().tKnokBack, (*MonsIter)->getMonInfo().tUnKnokBack, (*PlayerBulletIter)->getTagBulletInfo().tAngle);
					(*PlayerBulletIter)->HitEff();
					m_pUiMag->addHitTxt((*PlayerBulletIter)->getTagBulletInfo().tDmage, (*MonsIter)->getMonInfo().tPosX, (*MonsIter)->getMonInfo().tPosY);
					m_soundMag.play("sound/sound_MonsterHit.wav", g_saveData.gSeValue);
				}
			}
		}
	}
	for (MonsIter = vMonster.begin(); MonsIter != vMonster.end(); MonsIter++)
	{
		(*MonsIter)->TypeSub(tMoninfo.tminGaugeSub, tMoninfo.tmaxGaugeSub, tMoninfo.tminGaugeInfo, tMoninfo.tmaxGaugeInfo, true, 1);
	}

	// 아이템 획득
	std::vector<item*> vItem = m_pItemMag->getVecItem();
	std::vector<item*>::iterator ItemIter;
	for (ItemIter = vItem.begin(); ItemIter != vItem.end(); ItemIter++)
	{

		if ((*ItemIter)->getIsAlive() && m_player->getRadius() + (*ItemIter)->getItemRadius() > (MY_UTIL::getDistance(m_player->getX(), m_player->getY(), (*ItemIter)->getItemInfo().posX, (*ItemIter)->getItemInfo().posY)))
		{
			m_pEffMagr->play("Item_Get1", m_player->getX() - (320 / 4) / 2, m_player->getY());
			m_pEffMagr->play("Item_Get2", m_player->getX() - (230 / 5) / 2, m_player->getY() - (70) / 2);

			(*ItemIter)->setIsAlive(false);
			m_player->getItem((*ItemIter)->getItemInfo());
			m_soundMag.play("sound/sound_itemGet.wav", g_saveData.gSeValue);

		}
	}

}

void stageScene::SpawnGateTime()
{
	if (g_saveData.gGamePause) return;

	m_isCount++; // 스폰되는 주기 카운트
	if (m_isCount > 100.0f /*&& (MAX_SPAWN_NUMBER >= m_MaxSpawnNum)*/)
	{
		m_isSpawnCycle = true;
		m_GateNum++;
		m_MaxSpawnNum++;
		m_isCount = 0;
		if (m_GateNum > 19)
		{
			m_GateNum = 0;
		}
	}
	if (m_isSpawnCycle/* && MAX_SPAWN_NUMBER >= m_MaxSpawnNum*/)
	{
		for (int x = 0; x < g_saveData.gTileMaxCountX; x++)
		{
			for (int y = 0; y < g_saveData.gTileMaxCountX; y++)
			{
				if (m_pTiles[x * g_saveData.gTileMaxCountX + y].MonsterNumber == 20) continue;
				
				tMoninfo.tPosX = m_pTiles[x * g_saveData.gTileMaxCountX + y].rc.left + 16.0f + SCROLL->GetX();
				tMoninfo.tPosY = m_pTiles[x * g_saveData.gTileMaxCountX + y].rc.top + 16.0f + SCROLL->GetY();
				if (m_pTiles[x * g_saveData.gTileMaxCountX + y].MonsterNumber == m_GateNum)
				{
					m_pEffMagr->play("Item_Get1", tMoninfo.tPosX - (320 / 4) / 2, tMoninfo.tPosY);
					m_pEffMagr->play("Item_Get2", tMoninfo.tPosX - (230 / 5) / 2, tMoninfo.tPosY - (70) / 2);
					MonSpawnCycle(m_GateMonsterNum, m_GateMonsterIndex); // (몬스터 한번에 생성 마리, 몬스터 ID)
				}
			}
		}
	}
	//else if (MAX_SPAWN_NUMBER < m_MaxSpawnNum)
	//{
	//	m_stageNum++;
	//}

	switch (m_stageNum)
	{
	case GATE_1:
		m_GateMonsterNum = 1;
		m_GateMonsterIndex = RANDOM->getFromIntTo(1, 18);
		break;
	case GATE_2:
		m_GateMonsterNum = 1;
		m_GateMonsterIndex = RANDOM->getFromIntTo(4, 6);
		break;
	case GATE_3:
		m_GateMonsterNum = 1;
		m_GateMonsterIndex = RANDOM->getFromIntTo(7, 9);
		break;
	case GATE_4:
		m_GateMonsterNum = 1;
		m_GateMonsterIndex = RANDOM->getFromIntTo(10, 13);
		break;
	case GATE_5:
		m_GateMonsterNum = 1;
		m_GateMonsterIndex = RANDOM->getFromIntTo(14, 16);
		break;
	case GATE_6:
		m_GateMonsterNum = 1;
		m_GateMonsterIndex = RANDOM->getFromIntTo(17, 18);
		break;
	case GATE_7:
		m_GateMonsterNum = 2;
		m_GateMonsterIndex = RANDOM->getFromIntTo(1, 6);
		break;
	case GATE_8:
		m_GateMonsterNum = 2;
		m_GateMonsterIndex = RANDOM->getFromIntTo(7, 13);
		break;
	case GATE_9:
		m_GateMonsterNum = 3;
		m_GateMonsterIndex = RANDOM->getFromIntTo(14, 18);
		break;
	case GATE_10:
		m_GateMonsterNum = 3;
		m_GateMonsterIndex = RANDOM->getFromIntTo(1, 10);
		break;
	case GATE_11:
		m_GateMonsterNum = 3;
		m_GateMonsterIndex = RANDOM->getFromIntTo(11, 18);
		break;
	case GATE_12:
		m_GateMonsterNum = 3;
		m_GateMonsterIndex = RANDOM->getFromIntTo(1, 18);
		break;
	case GATE_13:
		m_GateMonsterNum = 3;
		m_GateMonsterIndex = RANDOM->getFromIntTo(1, 18);
		break;
	case GATE_14:
		m_GateMonsterNum = 3;
		m_GateMonsterIndex = RANDOM->getFromIntTo(1, 18);
		break;
	case GATE_15:
		m_GateMonsterNum = 3;
		m_GateMonsterIndex = RANDOM->getFromIntTo(1, 18);
		break;
	case GATE_16:
		m_GateMonsterNum = 3;
		m_GateMonsterIndex = RANDOM->getFromIntTo(1, 18);
		break;
	case GATE_17:
		m_GateMonsterNum = 4;
		m_GateMonsterIndex = RANDOM->getFromIntTo(1, 18);
		break;
	case GATE_18:
		m_GateMonsterNum = 4;
		m_GateMonsterIndex = RANDOM->getFromIntTo(1, 18);
		break;
	}

}

void stageScene::ClearEvent()
{
	if (m_stageNum >= 18 && m_ClearScore >= 500)
		SCENEMANAGER->changeScene("ending");



}

stageScene::stageScene()
{
}


stageScene::~stageScene()
{
}