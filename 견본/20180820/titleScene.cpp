#include "stdafx.h"
#include "titleScene.h"
#include "PlayerCharacter.h"
#include "bulletManger.h"
#include "effectManager.h"
#include "PlayerCharacter.h"
#include "itemManager.h"
#include "monsterManger.h"
#include "animation.h"

HRESULT titleScene::init()
{
	// 사운드
	m_soundMag.init();
	m_soundMag.addSound("sound/sound_titleBGM.wav", true, true);
	m_soundMag.addSound("sound/sound_playerAtt.wav", false, false);
	m_soundMag.play("sound/sound_titleBGM.wav", g_saveData.gMainBGMValue);

	m_isOption = false;
	m_soundSelectValue = 0;
	m_BgmValue = 10;
	m_SeValue = 10;

	// 폰트
	AddFontResourceA("BMHANNAAir_ttf.ttf");

	// 몬스터
	IMAGEMANAGER->addImage("BG_Beholder", "image/resources/monster_image/BG_Beholder_Run.bmp", 930, 78, 12, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BG_Blue_Guardian", "image/resources/monster_image/BG_Blue_Guardian_Run.bmp", 930, 57, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BG_Blue_Mindflayer", "image/resources/monster_image/BG_Blue_Mindflayer_Run.bmp", 930, 54, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BG_Bugman", "image/resources/monster_image/BG_Bugman_Run.bmp", 620, 61, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BG_Cetus", "image/resources/monster_image/BG_Cetus_Run.bmp", 620, 37, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BG_Coven", "image/resources/monster_image/BG_Coven_Run.bmp", 620, 33, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BG_Cow", "image/resources/monster_image/BG_Cow.bmp", 620, 28, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BG_Cyclops", "image/resources/monster_image/BG_Cyclops.bmp", 930, 46, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BG_Dark_Lord", "image/resources/monster_image/BG_Dark_Lord.bmp", 620, 78, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BG_Dog", "image/resources/monster_image/BG_Dog.bmp", 465, 37, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BG_Eye_Slime", "image/resources/monster_image/BG_Eye_Slime_Run.bmp", 465, 39, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BG_Faun_Archer", "image/resources/monster_image/BG_Faun_Archer_Run.bmp", 930, 46, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BG_Firewolf", "image/resources/monster_image/BG_Firewolf.bmp", 620, 46, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BG_Gargoyle", "image/resources/monster_image/BG_Gargoyle.bmp", 620, 65, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BG_Giant_Run", "image/resources/monster_image/BG_Giant_Run.bmp", 930, 63, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BG_Gnome_Run", "image/resources/monster_image/BG_Gnome_Run.bmp", 930, 26, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BG_Igor", "image/resources/monster_image/BG_Igor.bmp", 930, 44, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BG_Itchy", "image/resources/monster_image/BG_Itchy.bmp", 930, 37, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BG_Knife_dude", "image/resources/monster_image/BG_Knife_dude.bmp", 930, 60, 6, 1, true, RGB(255, 0, 255));

	// 블렛
	IMAGEMANAGER->addImage("Bullet_Y", "image/resources/bullet_image/Bullet_Y.bmp", 108, 27, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Bullet_B", "image/resources/bullet_image/Bullet_B.bmp", 108, 27, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Bullet_P", "image/resources/bullet_image/Bullet_P.bmp", 108, 27, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Bullet_G", "image/resources/bullet_image/Bullet_G.bmp", 108, 27, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Bullet_R", "image/resources/bullet_image/Bullet_R.bmp", 108, 27, 4, 1, true, RGB(255, 0, 255));

	// 플레이어
	IMAGEMANAGER->addImage("Player_ItemUI", "image/resources/UI_image/player_Ui/Player_Item_Ui.bmp", 449, 550, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Player_InfoIcon", "image/resources/UI_image/player_Ui/BG_Player_Icon.bmp", 37 * 2, 43 * 2, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Player_ItemPopupUI", "image/resources/UI_image/player_Ui/Player_Item_PopupUI.bmp", 307, 126, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Player_HP_Point", "image/resources/UI_image/player_Ui/Player_Hp_Point.bmp", 27 * 5, 7 * 5, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Player_CrossHair", "image/resources/bullet_image/crossHair.bmp", 207, 69, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Player_UI_BG", "image/resources/UI_image/player_Ui/Player_UI_BG.bmp", WINSIZEX, WINSIZEY);
	IMAGEMANAGER->addImage("Player_L_Idle", "image/resources/player_image/BG_Player_L_idle.bmp", 128, 54, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Player_R_Idle", "image/resources/player_image/BG_Player_R_idle.bmp", 128, 54, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Player_L_Run", "image/resources/player_image/BG_Player_L_Run.bmp", 342, 54, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Player_R_Run", "image/resources/player_image/BG_Player_R_Run.bmp", 342, 54, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Player_Shadow", "image/resources/item_image/Item_shadow.bmp", 32*1.5f, 9*1.5f, 1, 1, true, RGB(255, 0, 255));


	////// 맵에디터 소스//////////////////////////////
	IMAGEMANAGER->addImage("black", "image/wook/black.bmp", 1000, 1000, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("space_left", "image/wook/space_left.bmp", 36, 72, 1, 2, true, RGB(255, 255, 255));
	IMAGEMANAGER->addImage("space_right", "image/wook/space_right.bmp", 36, 72, 1, 2, true, RGB(255, 255, 255));

	IMAGEMANAGER->addImage("box", "image/wook/white.bmp", WINSIZEX, 250, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("tileset1", "image/wook/tileset1.bmp", 256, 192, 8, 6, true, RGB(255, 255, 255));
	IMAGEMANAGER->addImage("tileset2", "image/wook/tileset2.bmp", 256, 192, 8, 6, true, RGB(255, 255, 255));
	IMAGEMANAGER->addImage("tileset3", "image/wook/tileset3.bmp", 256, 192, 8, 6, true, RGB(255, 255, 255));
	IMAGEMANAGER->addImage("tileset4", "image/wook/tileset4.bmp", 256, 192, 8, 6, true, RGB(255, 255, 255));
	IMAGEMANAGER->addImage("Cursor", "image/wook/Cursor.bmp", 30, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("800x", "image/wook/800x.bmp", 320, 168, 1, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("ItemObject", "image/resources/item_image/Item_set.bmp", 682, 614, 20, 18, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ItemShadow", "image/resources/item_image/Item_shadow.bmp", 32, 9, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("tag", "image/wook/tag.bmp", 38, 38, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("parchment", "image/wook/parchment.bmp", WINSIZEX, 350, true, RGB(255, 255, 255));
	IMAGEMANAGER->addImage("tag_done", "image/wook/tag_done.bmp", 38, 38, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("black_big", "image/wook/black_big.bmp", 800, 800, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("alice_move", "image/wook/alice_move.bmp", 10800, 300, 18,1,true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("custom", "image/wook/button_custom.bmp", 480, 120,1,2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("prepared", "image/wook/button_prepared.bmp", 480, 120,1,2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("help", "image/wook/help.bmp", 480, 600, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("player", "image/wook/player.bmp", 34, 34, true, RGB(255, 255, 255));
	IMAGEMANAGER->addImage("mini_player", "image/wook/mini_player.bmp", 54, 54,1,1, true, RGB(255, 255, 255));
	IMAGEMANAGER->addImage("mini_enemy", "image/wook/mini_enemy.bmp", 54, 54,1,1, true, RGB(255, 255, 255));



	// 타이틀 이미지
	m_titleScene = IMAGEMANAGER->addImage("titleImage", "image/resources/UI_image/title_image/titleScene.bmp", WINSIZEX, WINSIZEY);
	m_button = IMAGEMANAGER->addImage("buttonBase", "image/resources/UI_image/title_image/button_base.bmp", 162 * 2, 360 * 2, 1, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("option_UI", "image/resources/UI_image/title_image/option_Ui.bmp", 498, 365, 1, 1);
	IMAGEMANAGER->addImage("option_UI_Sound", "image/resources/UI_image/title_image/option_Sound_Icon_Ui.bmp", 43, 69, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("option_UI_Sound_Value", "image/resources/UI_image/title_image/option_Sound_Value_Ui.bmp", 12, 59, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("option_UI_Sound_Select", "image/resources/UI_image/title_image/option_Sound_select_Ui.bmp", 75, 69, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("option_UI_Sound_BG", "image/resources/UI_image/title_image/option_Sound_BG_Ui.bmp", WINSIZEX, WINSIZEY, 1, 1, true, RGB(255, 0, 255));

	// 버튼 tag 초기화
	memset(&m_tButtonInfo, NULL, sizeof(m_tButtonInfo));

	// 최초 게임 시작 선택 상태
	m_tButtonInfo.carrFrameX = TITEL::GAME_START_SC;
	m_tButtonInfo.m_moveSpeed = 1.5f;
	m_tButtonInfo.m_isMovement = false;

	

	return S_OK;
}

void titleScene::release()
{
	m_soundMag.release();
}

void titleScene::update()
{
	//if (KEYMANAGER->isOnceKeyDown(VK_F2))
	//	SCENEMANAGER->changeScene("editor");

	OptionOn();

	if (m_isOption) return;

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{

		switch (m_tButtonInfo.carrFrameX)
		{
		case TITEL::GAME_START_SC: // 스테이지씬
			m_soundMag.stop("sound/sound_titleBGM.wav");

			SCENEMANAGER->changeScene("stage");
			break;
		case TITEL::EDITOR_MODE_SC: // 에디터씬
			SCENEMANAGER->changeScene("editor");
			break;
		case TITEL::OPTION_SC: // 옵션
			m_isOption = true;
			break;
		case TITEL::CREATERS_SC: // 만든이들
			SCENEMANAGER->changeScene("creator");
			break;
		case TITEL::EXIT_SC: // 나가기
			PostQuitMessage(0);
			break;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F10))
	{
		SCENEMANAGER->changeScene("ending");
	}


	if (!m_tButtonInfo.m_isMovement)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			if (m_tButtonInfo.carrFrameX == TITEL::GAME_START_SC) return;

			m_tButtonInfo.carrFrameX--;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			if (m_tButtonInfo.carrFrameX == TITEL::EXIT_SC) return;

			m_tButtonInfo.carrFrameX++;
		}
	}
	

}

void titleScene::render(HDC hdc)
{
	if (m_titleScene)
	{
		m_titleScene->render(hdc,0,0);

		// 우측 대기
		if (!(m_tButtonInfo.carrFrameX == TITEL::GAME_START_SC))
			m_button->frameAlphaRender(hdc, (WINSIZEX / 2) - ((WINSIZEX / 2) / 2) - (m_button->getFrameWidth() / 2) * 0.8f, (WINSIZEY / 2) + ((WINSIZEY / 2) / 2) - (m_button->getFrameHeight() / 2) * 0.8f, 0, m_tButtonInfo.carrFrameX - 1, 0.8f, 150);
		// 좌측 대기
		if (!(m_tButtonInfo.carrFrameX == TITEL::EXIT_SC))
			m_button->frameAlphaRender(hdc, (WINSIZEX / 2) + ((WINSIZEX / 2) / 2) - (m_button->getFrameWidth() / 2) * 0.8f, (WINSIZEY / 2) + ((WINSIZEY / 2) / 2) - (m_button->getFrameHeight() / 2) * 0.8f, 0, m_tButtonInfo.carrFrameX + 1, 0.8f ,150);
		// 센터
		m_button->frameAlphaRender(hdc, (WINSIZEX / 2) - (m_button->getFrameWidth() / 2) * 1.2f, (WINSIZEY / 2) + ((WINSIZEY / 2) / 2) - (m_button->getFrameHeight() / 2) * 1.2f, 0, m_tButtonInfo.carrFrameX, 1.2f, 0);
	}

	if (m_isOption)
	{
		IMAGEMANAGER->findImage("option_UI_Sound_BG")->alphaRender(hdc, 155);


		IMAGEMANAGER->findImage("option_UI")->render(hdc,
			(WINSIZEX / 2) - 498 / 2,
			(WINSIZEY / 2) - 365 / 2);

		for (int i = 0; i < 2; i++)
		{
			IMAGEMANAGER->findImage("option_UI_Sound")->render(hdc,
				(WINSIZEX / 2 - OPTION_SOUND_X - 10) - 43 / 2,
				(WINSIZEY / 2 - OPTION_SOUND_Y) + ((i) * OPTION_SOUND_SIZE_Y) - 69 / 2);
		}


		for (int i = 0; i < m_BgmValue; i++)
		{
			IMAGEMANAGER->findImage("option_UI_Sound_Value")->render(hdc,
				(WINSIZEX / 2 - OPTION_SOUND_X + ((i + 1) * 25)) - 12 / 2,
				(WINSIZEY / 2 - OPTION_SOUND_Y) - 59 / 2);
		}

		for (int i = 0; i < m_SeValue; i++)
		{
			IMAGEMANAGER->findImage("option_UI_Sound_Value")->render(hdc,
				(WINSIZEX / 2 - OPTION_SOUND_X + ((i + 1) * 25)) - 12 / 2,
				(WINSIZEY / 2 - OPTION_SOUND_Y) + (OPTION_SOUND_SIZE_Y) - 59 / 2);
		}

		if (m_soundSelectValue == 0)
		{
			IMAGEMANAGER->findImage("option_UI_Sound_Select")->render(hdc,
				(WINSIZEX / 2 - OPTION_SOUND_X - 150) - 75 / 2,
				(WINSIZEY / 2 - OPTION_SOUND_Y) - 69 / 2);
		}
		else if (m_soundSelectValue == 1)
		{
			IMAGEMANAGER->findImage("option_UI_Sound_Select")->render(hdc,
				(WINSIZEX / 2 - OPTION_SOUND_X - 150) - 75 / 2,
				(WINSIZEY / 2 - OPTION_SOUND_Y) + (OPTION_SOUND_SIZE_Y) - 69 / 2);
		}

		char szText[256];
		SetBkMode(hdc, TRANSPARENT);

		MY_UTIL::FontOption(hdc, 42, 0);
		sprintf_s(szText, "사운드 설정");
		TextOut(hdc,
			(WINSIZEX / 2) - 100,
			(WINSIZEY / 2) - 160,
			szText, strlen(szText));
		MY_UTIL::FontDelete(hdc);

		MY_UTIL::FontOption(hdc, 32, 0);
		sprintf_s(szText, "BGM");
		TextOut(hdc,
			(WINSIZEX / 2 - OPTION_SOUND_X - 70) - 43 / 2,
			(WINSIZEY / 2 - OPTION_SOUND_Y) - 69 / 2,
			szText, strlen(szText));

		sprintf_s(szText, "SE");
		TextOut(hdc,
			(WINSIZEX / 2 - OPTION_SOUND_X - 70) - 43 / 2,
			(WINSIZEY / 2 - OPTION_SOUND_Y) + (OPTION_SOUND_SIZE_Y) - 69 / 2,
			szText, strlen(szText));

		MY_UTIL::FontDelete(hdc);

	}

}

void titleScene::OptionOn()
{
	if (!m_isOption) return;

	if (KEYMANAGER->isOnceKeyDown(VK_BACK))
		m_isOption = false;

	if (m_soundSelectValue != 1 && KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		m_soundSelectValue += 1;
	}
	else if (m_soundSelectValue != 0 && KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		m_soundSelectValue -= 1;
	}

	if (m_soundSelectValue == 0)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			if (m_BgmValue == 0) return;

			g_saveData.gMainBGMValue -= 0.1f;
			m_BgmValue -= 1;
			m_soundMag.setVolume("sound/sound_titleBGM.wav", g_saveData.gMainBGMValue);
		}
		else if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			if (m_BgmValue == 10) return;

			g_saveData.gMainBGMValue += 0.1f;
			m_BgmValue += 1;
			m_soundMag.setVolume("sound/sound_titleBGM.wav", g_saveData.gMainBGMValue);
		}
	}
	else if (m_soundSelectValue == 1)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			if (m_SeValue == 0) return;

			g_saveData.gSeValue -= 0.1f;
			m_SeValue -= 1;
			m_soundMag.setVolume("sound/sound_playerAtt.wav", g_saveData.gSeValue);
			m_soundMag.play("sound/sound_playerAtt.wav", g_saveData.gSeValue);
		}
		else if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			if (m_SeValue == 10) return;

			g_saveData.gSeValue += 0.1f;
			m_SeValue += 1;
			m_soundMag.setVolume("sound/sound_playerAtt.wav", g_saveData.gSeValue);
			m_soundMag.play("sound/sound_playerAtt.wav", g_saveData.gSeValue);
		}
	}
}



titleScene::titleScene()
{
}


titleScene::~titleScene()
{
}
