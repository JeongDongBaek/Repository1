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


	AddFontResourceA("BMHANNAAir_ttf.ttf");

	char SzText1[128];
	// TRANSPARENT : 투명, OPAQUE : 불투명
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255, 240, 200));
	MY_UTIL::FontOption(hdc, 42, 0);


	char SzText2[256];
	int temp = 58;
	// TRANSPARENT : 투명, OPAQUE : 불투명
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255, 240, 200));
	MY_UTIL::FontOption(hdc, 42, 0);

	sprintf_s(SzText1, "%s : ", "만 든 이 들");
	TextOut(hdc, WINSIZEX / 2 - 110, 100 + temp, SzText1, strlen(SzText1)); temp += 58;

	sprintf_s(SzText2, "%s  ", "정지수");
	TextOut(hdc, WINSIZEX / 2 - 70, 100 + temp, SzText2, strlen(SzText2)); temp += 58;

	sprintf_s(SzText2, "%s  ", "정민욱");
	TextOut(hdc, WINSIZEX / 2 - 70, 100 + temp, SzText2, strlen(SzText2)); temp += 58;

	sprintf_s(SzText2, "%s  ", "이순현");
	TextOut(hdc, WINSIZEX / 2 - 70, 100 + temp, SzText2, strlen(SzText2)); temp += 58;

	sprintf_s(SzText2, "%s :  ", "사용프로그램");
	TextOut(hdc, WINSIZEX / 2 - 124, 100 + temp, SzText2, strlen(SzText2)); temp += 58;

	SetTextColor(hdc, RGB(255, 140, 200));
	sprintf_s(SzText2, "%s  ", "비쥬얼스튜디오 (winAPI)");
	TextOut(hdc, WINSIZEX / 2 - 202, 100 + temp, SzText2, strlen(SzText2)); temp += 58;

	SetTextColor(hdc, RGB(255, 240, 200));
	sprintf_s(SzText2, "%s  ", "제작기간 : ");
	TextOut(hdc, WINSIZEX / 2 - 95, 100 + temp, SzText2, strlen(SzText2)); temp += 58;

	SetTextColor(hdc, RGB(255, 240, 200));
	sprintf_s(SzText2, "%s  ", "3주 (3 week)");
	TextOut(hdc, WINSIZEX / 2 - 123, 100 + temp, SzText2, strlen(SzText2)); temp += 33;

	MY_UTIL::FontOption(hdc, 29, 0);
	SetTextColor(hdc, RGB(255, 200, 188));
	sprintf_s(SzText2, "%s  ", "2018.10.01 ~ 2018.10.22");
	TextOut(hdc, WINSIZEX / 2 - 163, 100 + temp, SzText2, strlen(SzText2)); temp += 58;

	MY_UTIL::FontDelete(hdc);
}




CreatorScene::CreatorScene()
{
}


CreatorScene::~CreatorScene()
{
}