#include "stdafx.h"
#include "EndingScene.h"
#include "image.h"
#include "animation.h"

HRESULT EndingScene::init()
{
	m_pImg_BG;
	m_pImg_Alice;
	m_pAni;


	return S_OK;
}

void EndingScene::update()
{
	
}

void EndingScene::release()
{
}

void EndingScene::render(HDC hdc)
{
	

	char SzText1[128];
	// TRANSPARENT : ����, OPAQUE : ������
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255, 240, 200));
	MY_UTIL::FontOption(hdc, 42, 0);
	sprintf_s(SzText1, "%s : ", "�� �� ��");
	TextOut(hdc, WINSIZEX/2 - 86, 570, SzText1, strlen(SzText1));
	MY_UTIL::FontDelete(hdc);

	// TRANSPARENT : ����, OPAQUE : ������
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255, 240, 200));
	MY_UTIL::FontOption(hdc, 42, 0);
	sprintf_s(SzText1, "%s  ", "���ο�");
	TextOut(hdc, WINSIZEX / 2 - 86, 620, SzText1, strlen(SzText1));

	MY_UTIL::FontDelete(hdc);
	sprintf_s(SzText1, "%s  ", "�����մϴ�.");
	TextOut(hdc, WINSIZEX / 2 - 86, 690, SzText1, strlen(SzText1));

}

EndingScene::EndingScene()
{
}


EndingScene::~EndingScene()
{
}
