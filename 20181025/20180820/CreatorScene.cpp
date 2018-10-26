#include "stdafx.h"
#include "CreatorScene.h"
#include "image.h"
#include "button.h"


bool CreatorScene::buttonInput = false;

static void Func_button1(void)
{
	CreatorScene::buttonInput = true; // 시나리오 게임
}



HRESULT CreatorScene::init()
{
	m_pImg_BG = IMAGEMANAGER->findImage("black");
	m_pButton1 = new button;
	//m_pButton1->init()


	return S_OK;
}

void CreatorScene::update()
{
}

void CreatorScene::release()
{
}

void CreatorScene::render(HDC hdc)
{
	m_pImg_BG->render(hdc, 0, 0);
}




CreatorScene::CreatorScene()
{
}


CreatorScene::~CreatorScene()
{
}