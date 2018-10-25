#include "stdafx.h"
#include "EndingScene.h"
#include "image.h"
#include "animation.h"

HRESULT EndingScene::init()
{

	m_pImg_BG = IMAGEMANAGER->findImage("black");
	m_pImg_Alice = IMAGEMANAGER->findImage("alice_move"); // 600, 300
	m_pImg_Alice->setX(100);
	m_pImg_Alice->setY(250);

	m_pAni = new animation;
	m_pAni->init(m_pImg_Alice->getWidth(), m_pImg_Alice->getHeight(), 600, 300);
	m_pAni->setDefPlayFrame(false, true);
	m_pAni->setFPS(12);
	m_pAni->start();
	

	return S_OK;
}

void EndingScene::update()
{
	m_pAni->frameUpdate(TIMEMANAGER->getElapsedTime());
}

void EndingScene::release()
{
}

void EndingScene::render(HDC hdc)
{
	m_pImg_BG->render(hdc, 0, 0);
	m_pImg_Alice->aniRender(hdc, m_pImg_Alice->getX(), m_pImg_Alice->getY(), m_pAni, 1);


	AddFontResourceA("BMHANNAAir_ttf.ttf");

	char SzText1[128];
	// TRANSPARENT : 투명, OPAQUE : 불투명
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255, 240, 200));
	MY_UTIL::FontOption(hdc, 42, 0);
	sprintf_s(SzText1, "%s : ", "만 든 이 들");
	TextOut(hdc, WINSIZEX/2 - 86, 570, SzText1, strlen(SzText1));
	MY_UTIL::FontDelete(hdc);

	char SzText2[256];
	// TRANSPARENT : 투명, OPAQUE : 불투명
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255, 240, 200));
	MY_UTIL::FontOption(hdc, 42, 0);
	sprintf_s(SzText2, "%s  ", "사워게코[정지수, 정민욱, 이순현]");
	TextOut(hdc, WINSIZEX / 2 - 252, 620, SzText2, strlen(SzText2));
	MY_UTIL::FontDelete(hdc);

}

EndingScene::EndingScene()
{
}


EndingScene::~EndingScene()
{
}
