#include "stdafx.h"
#include "Editor_SetSize.h"
#include "image.h"
#include "button.h"

static char SzText2[256];

HRESULT Editor_SetSize::init()
{
	Enter_Number = 0;
	m_pImg_BG = IMAGEMANAGER->findImage("black");
	m_nTileCountX = 64;
	m_nTileCountY = 32;

	return S_OK;
}

void Editor_SetSize::update()
{
	KeyEvent();




}

void Editor_SetSize::KeyEvent()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		Enter_Number++;


	switch (Enter_Number)
	{
	case 0:
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT) && m_nTileCountX > 48)
			m_nTileCountX -= 16;
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT) && m_nTileCountX < 128)
			m_nTileCountX += 16;
		break;
	case 1:
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT) && m_nTileCountY > 32)
			m_nTileCountY -= 16;
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT) && m_nTileCountY < 64)
			m_nTileCountY += 16;
		break;
	case 2:
		g_saveData.gTileMaxCountX = m_nTileCountX;
		g_saveData.gTileMaxCountY = m_nTileCountY;
		SCENEMANAGER->changeScene("editor");
		break;
	}

	
}

void Editor_SetSize::release()
{
}

void Editor_SetSize::render(HDC hdc)
{
	m_pImg_BG->render(hdc, 0, 0);



	// �ӽ÷� ���ڶ������ //

	int temp = 58;
	// TRANSPARENT : ����, OPAQUE : ������
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255, 240, 200));
	g_hFont = CreateFont(48, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, "����ǹ��� �ѳ�ü Air");
	g_OldFont = (HFONT)SelectObject(hdc, g_hFont);

	sprintf_s(SzText2, "%s :  %d", "X�� ũ��" , m_nTileCountX);
	TextOut(hdc, WINSIZEX / 2 - 110, 100 + temp, SzText2, strlen(SzText2)); temp += 58;

	sprintf_s(SzText2, "%s :  %d", "Y�� ũ��", m_nTileCountY);
	TextOut(hdc, WINSIZEX / 2 - 110, 100 + temp, SzText2, strlen(SzText2)); temp += 58;

}







Editor_SetSize::Editor_SetSize()
{
}


Editor_SetSize::~Editor_SetSize()
{
}