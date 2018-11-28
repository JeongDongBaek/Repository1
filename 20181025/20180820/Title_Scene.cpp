#include "stdafx.h"
#include "Title_Scene.h"
#include "image.h"
#include "animation.h"

HRESULT Title_Scene::init()
{
	m_nindex_Scene = 0;
	m_bIsOptionOn = false;
	m_bIsCreatorOn = false;

	
	IMAGEMANAGER->addImage("back", "image/back.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("middle", "image/middle.bmp", WINSIZEX , 1700, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("tileset1", "image/tileset1.bmp", 4224, 32, 132, 1, true, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("pixel", "image/pixel.bmp", 8448 , 74, 132, 1, true, RGB(255, 255, 255));
	IMAGEMANAGER->addImage("tileset1_Stage", "image/tileset1.bmp", 8448, 64, 132, 1, true, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("tileset1_div", "image/tileset1.bmp", 4224, 32, 4, 1, true, RGB(0, 0, 0)); // 위를 4개씩으로 쪼갠것
	IMAGEMANAGER->addImage("black", "image/black.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("real_black", "image/real_black.bmp", WINSIZEX, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("delta", "image/delta.bmp", 64,64, true, RGB(255, 255, 255));
	
	IMAGEMANAGER->addImage("white", "image/white.bmp", (WINSIZEX / 10) * 9, (WINSIZEY / 10) * 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("white2", "image/white.bmp", (WINSIZEX / 10) * 5, (WINSIZEY / 10) * 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("button_terrains", "image/button/button_placing_terrains.bmp", 250,100,1,2, (WINSIZEY / 10) * 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("button_units", "image/button/button_placing_units.bmp", 250, 100,1,2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("button_else", "image/button/button_placing_else.bmp", 250, 100,1,2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ant_idle", "image/enemy/ant_idle_ani.bmp", 296, 31, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("left_ant_idle", "image/enemy/left_ant_idle_ani.bmp", 296, 31, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bee_idle", "image/enemy/bee_idle_ani.bmp", 296, 39, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("left_bee_idle", "image/enemy/left_bee_idle_ani.bmp", 296, 39, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("crocodile_idle", "image/enemy/crocodile_idle_ani.bmp", 184, 49, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("left_crocodile_idle", "image/enemy/left_crocodile_idle_ani.bmp", 184, 49, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("grasshopper_idle", "image/enemy/grasshopper_idle_ani.bmp", 208, 45, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("left_grasshopper_idle", "image/enemy/left_grasshopper_idle_ani.bmp", 208, 45, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("grasshopper_jump", "image/enemy/grasshopper_jump_ani.bmp", 104, 45, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("left_grasshopper_jump", "image/enemy/left_grasshopper_jump_ani.bmp", 104, 45, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("grasshopper_fly", "image/enemy/grasshopper_fly_ani.bmp", 104, 45, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("left_grasshopper_fly", "image/enemy/left_grasshopper_fly_ani.bmp", 104, 45, 2, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("monster_plant_idle", "image/enemy/monster_plant_idle_ani.bmp", 305, 45, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("left_monster_plant_idle", "image/enemy/left_monster_plant_idle_ani.bmp", 305, 45, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("monster_plant_attack", "image/enemy/monster_plant_attack_ani.bmp", 244, 45, 4, 1, true, RGB(255, 255, 255));
	IMAGEMANAGER->addImage("left_monster_plant_attack", "image/enemy/left_monster_plant_attack_ani.bmp", 244, 45, 4, 1, true, RGB(255, 255, 255));

	IMAGEMANAGER->addImage("eagle_idle", "image/enemy/eagle_idle_ani.bmp", 160, 41, 4, 1, true, RGB(255, 255, 255));
	IMAGEMANAGER->addImage("left_eagle_idle", "image/enemy/left_eagle_idle_ani.bmp", 160, 41, 4, 1, true, RGB(255, 255, 255));
	IMAGEMANAGER->addImage("frog_idle", "image/enemy/frog_idle_ani.bmp", 140, 30, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("left_frog_idle", "image/enemy/left_frog_idle_ani.bmp", 140, 30, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("frog_jump", "image/enemy/frog_jump_ani.bmp", 70, 35, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("left_frog_jump", "image/enemy/left_frog_jump_ani.bmp", 70, 35, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("oposum_idle", "image/enemy/oposum_idle_ani.bmp", 216, 28, 6, 1, true, RGB(255, 255, 255));
	IMAGEMANAGER->addImage("left_oposum_idle", "image/enemy/left_oposum_idle_ani.bmp", 216, 28, 6, 1, true, RGB(255, 255, 255));
	IMAGEMANAGER->addImage("slug_idle", "image/enemy/slug_idle_ani.bmp", 128 * 6, 21 * 6, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("left_slug_idle", "image/enemy/left_slug_idle_ani.bmp", 128 * 6, 21 * 6, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("dark_slug_idle", "image/enemy/dark_slug_idle_ani.bmp", 128 * 6, 21 * 6, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("left_dark_slug_idle", "image/enemy/left_dark_slug_idle_ani.bmp", 128 * 6, 21 * 6, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("enemy_box", "image/enemy_box.bmp", 120, 110,1,1, true, RGB(255,255,255));
	IMAGEMANAGER->addImage("boss_box", "image/boss_box.bmp", 216, 198,1,1, true, RGB(255,255,255));
	IMAGEMANAGER->addImage("text", "image/text.bmp", 260, 210, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BG1", "image/BG1.bmp", WINSIZEX * 16, WINSIZEY,16,1, true, RGB(255, 0, 255));

	// Player///////////
	IMAGEMANAGER->addImage("fox_idle", "image/fox/player-idle-1-horz.bmp", 132, 32, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("fox_jump", "image/fox/player-jump.bmp", 33, 32, 1, 1, true, RGB(255, 0, 255)); // 1은 점프 // 2는 하강
	IMAGEMANAGER->addImage("fox_fall", "image/fox/player-fall.bmp", 33, 32, 1, 1, true, RGB(255, 0, 255)); // 1은 점프 // 2는 하강
	IMAGEMANAGER->addImage("fox_run", "image/fox/player-run-1-horz.bmp", 198, 32, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("fox_hurt", "image/fox/player-hurt-1-horz.bmp", 66, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("fox_climb", "image/fox/player-climb-1-horz.bmp", 99, 32, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("fox_crouch", "image/fox/player-crouch-1-horz.bmp", 66, 32, 2, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("left_fox_idle", "image/fox/left_player-idle-1-horz.bmp", 132, 32, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("left_fox_jump", "image/fox/left_player-jump.bmp", 33, 32, 1, 1, true, RGB(255, 0, 255)); // 1은 점프 // 2는 하강
	IMAGEMANAGER->addImage("left_fox_fall", "image/fox/left_player-fall.bmp", 33, 32, 1, 1, true, RGB(255, 0, 255)); // 1은 점프 // 2는 하강
	IMAGEMANAGER->addImage("left_fox_run", "image/fox/left_player-run-1-horz.bmp", 198, 32, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("left_fox_hurt", "image/fox/left_player-hurt-1-horz.bmp", 66, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("left_fox_climb", "image/fox/left_player-climb-1-horz.bmp", 99, 32, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("left_fox_crouch", "image/fox/left_player-crouch-1-horz.bmp", 66, 32, 2, 1, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->addImage("left_bug_walk", "image/fox/left_bug_walk.bmp", 42 * 6, 21, 6, 1, true, RGB(0, 248, 0));
	IMAGEMANAGER->addImage("bug_walk", "image/fox/left_bug_walk.bmp", 42 * 6, 21, 6, 1, true, RGB(0, 248, 0));
	IMAGEMANAGER->addImage("left_bug_idle", "image/fox/left_bug_idle.bmp", 36 * 4, 21, 4, 1, true, RGB(0, 248, 0));
	IMAGEMANAGER->addImage("bug_idle", "image/fox/left_bug_idle.bmp", 36 * 4, 21, 4, 1, true, RGB(0, 248, 0));



	/////////////////////

	////////////////////////
	IMAGEMANAGER->addImage("rabbit_idle", "image/rabbit/player-idle-1-horz.bmp", 333, 32, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("rabbit_jump", "image/rabbit/player-jump-1-horz.bmp", 148, 32, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("rabbit_run", "image/rabbit/player-run-1-horz.bmp", 296, 32, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("rabbit_hurt", "image/rabbit/player-hurt-1-horz.bmp", 74, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("rabbit_climb", "image/rabbit/player-climb-1-horz.bmp", 148, 32, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("rabbit_fall", "image/rabbit/player-fall-1-horz.bmp", 148, 32, 4, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("left_rabbit_idle", "image/rabbit/left_player-idle-1-horz.bmp", 333, 32, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("left_rabbit_jump", "image/rabbit/left_player-jump-1-horz.bmp", 148, 32, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("left_rabbit_run", "image/rabbit/left_player-run-1-horz.bmp", 296, 32, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("left_rabbit_hurt", "image/rabbit/left_player-hurt-1-horz.bmp", 74, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("left_rabbit_climb", "image/rabbit/left_player-climb-1-horz.bmp", 148, 32, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("left_rabbit_fall", "image/rabbit/left_player-fall-1-horz.bmp", 148, 32, 4, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("boomerang", "image/rabbit/boomerang.bmp", 40, 66, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("house", "image/house.bmp", 33, 38, 1, 1, true, RGB(255, 255, 255));
	/////////////////		



	///////////////////
	IMAGEMANAGER->addImage("squirrel_idle", "image/squirrel/player-idle-1-horz.bmp", 720, 58, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("squirrel_round", "image/squirrel/player-round-1-horz.bmp", 360, 58, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("squirrel_run", "image/squirrel/player-run-1-horz.bmp", 540, 58, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("squirrel_hurt", "image/squirrel/player-hurt-1-horz.bmp", 180, 58, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("squirrel_crouch", "image/squirrel/player-crouch-1-horz.bmp", 180, 58, 2, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("left_squirrel_idle", "image/squirrel/left_player-idle-1-horz.bmp", 720, 58, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("left_squirrel_round", "image/squirrel/left_player-round-1-horz.bmp", 360, 58, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("left_squirrel_run", "image/squirrel/left_player-run-1-horz.bmp", 540, 58, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("left_squirrel_hurt", "image/squirrel/left_player-hurt-1-horz.bmp", 180, 58, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("left_squirrel_crouch", "image/squirrel/left_player-crouch-1-horz.bmp", 180, 58, 2, 1, true, RGB(255, 0, 255));
	///////////////////////



	IMAGEMANAGER->addImage("ui_bar_top", "image/ui/ui_bar_top.bmp", 200, 70, true, RGB(255, 255, 255));
	IMAGEMANAGER->addImage("ui_bar_bottom", "image/ui/ui_bar_bottom.bmp", 200, 70, true, RGB(255, 255, 255));
	IMAGEMANAGER->addImage("ui_character", "image/ui/ui_character.bmp", 360, 96, true, RGB(255, 255, 255));
	IMAGEMANAGER->addImage("mini_Player", "image/ui/mini_Player.bmp", 32, 32,1,1, true, RGB(255, 255, 255));
	IMAGEMANAGER->addImage("mini_Enemy", "image/ui/mini_Enemy.bmp", 32, 32,1,1, true, RGB(255, 255, 255));
	IMAGEMANAGER->addImage("ui_fox", "image/ui/UI_fox.bmp", 76, 76,2,1,true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ui_squirrel", "image/ui/UI_squirrel.bmp", 76, 76,2,1,true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ui_rabbit", "image/ui/UI_rabbit.bmp", 76, 76, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ui_minimap", "image/ui/ui_minimap.bmp", 374, 270,true, RGB(255, 255, 255));
	IMAGEMANAGER->addImage("ui_minimap", "image/ui/ui_minimap.bmp", 374, 270,true, RGB(255, 255, 255));
	IMAGEMANAGER->addImage("item_box", "image/ui/item_box.bmp", 74, 74,true, RGB(255, 255, 255));
	IMAGEMANAGER->addImage("item", "image/item.bmp", 400 + 80, 300+ 60, 8, 6, true, RGB(255, 129, 255));
	IMAGEMANAGER->addImage("fireball", "image/fireball.bmp", 768 / 2, 128 / 2, 6, 1, true, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("fireball_left", "image/left_fireball.bmp", 768 / 2, 128 / 2, 6, 1, true, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("text2", "image/text2.bmp", 280 , 220, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("label", "image/ui/label.bmp", (WINSIZEX / 10) * 5, (WINSIZEY / 12) * 5, true, RGB(255, 0, 255));

	/*IMAGEMANAGER->addImage("health_bar", "image/ui/health_bar.bmp", 220, 24, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("empty_bar", "image/ui/empty_bar.bmp", 220, 24, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("mana_bar", "image/ui/mana_bar.bmp", 220, 24, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("stamina_bar", "image/ui/stamina_bar.bmp", 220, 24, true, RGB(255, 0, 255));*/

	
	///////////////////
	
	m_pImg_Menu[0] = IMAGEMANAGER->addImage("sc_gamestart", "image/button/sc_gamestart.bmp", 500, 120, true, RGB(255,255,255));
	m_pImg_Menu[1] = IMAGEMANAGER->addImage("sc_editor", "image/button/sc_editor.bmp", 500, 120, true, RGB(255,255,255));
	m_pImg_Menu[2] = IMAGEMANAGER->addImage("sc_option", "image/button/sc_option.bmp", 500, 120, true, RGB(255,255,255));
	m_pImg_Menu[3] = IMAGEMANAGER->addImage("sc_creator", "image/button/sc_creator.bmp", 500, 120, true, RGB(255,255,255));
	m_pImg_Menu[4] = IMAGEMANAGER->addImage("sc_quit", "image/button/sc_quit.bmp", 500, 120, true, RGB(255,255,255));

	m_pImg_BG = IMAGEMANAGER->addImage("black", "image/black.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	m_pImg_Parchment = IMAGEMANAGER->addImage("parchment", "image/parchment.bmp", (WINSIZEX / 4) * 3, (WINSIZEY / 4) * 3, true, RGB(255, 255, 255));
	
	m_pImg_BG = IMAGEMANAGER->findImage("BG1");

	m_pAni = new animation;
	m_pAni->init(m_pImg_BG->getWidth(), m_pImg_BG->getHeight(), m_pImg_BG->getFrameWidth(), m_pImg_BG->getFrameHeight());
	m_pAni->setDefPlayFrame(false, true);
	m_pAni->setFPS(10);
	m_pAni->start();

	AddFontResourceA("BMHANNAAir_ttf.ttf");

	return S_OK;
}

void Title_Scene::update()
{
	m_pAni->frameUpdate(TIMEMANAGER->getElapsedTime());
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
			g_saveData.bIsCustomGame = false;
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
	m_pImg_BG->aniRender(hdc, 0, 0, m_pAni, 1.0f,false);

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

		//MY_UTIL::FontDelete(hdc);

	}



}






Title_Scene::Title_Scene()
{
}

Title_Scene::~Title_Scene()
{
}
