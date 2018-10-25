#include "stdafx.h"
#include "mainGame.h"
#include "titleScene.h"
#include "stageScene.h"
#include "loadingScene.h"
#include "editor.h"
#include "EndingScene.h"
#include "CreatorScene.h"


void mainGame::setBackBuffer()
{
	m_pBackBuffer = new image;
	m_pBackBuffer->init(WINSIZEX, WINSIZEY);
}

HRESULT mainGame::init()
{
	hdc = GetDC(g_hWnd);



	//HANDLE hTimer = (HANDLE)SetTimer(g_hWnd, 1, 10, NULL);
	KEYMANAGER->init();
	IMAGEMANAGER->init();
	TIMEMANAGER->init();
	SCENEMANAGER->init();

	setBackBuffer();

	// 필요한 리소스 미리 로드
	
	//m_pTileMapScene = new tileMap;
	//SCENEMANAGER->addScene("tileMap", m_pTileMapScene);



	m_pEditor = new editor;
	SCENEMANAGER->addScene("editor", m_pEditor);

	m_pTitleScene = new titleScene;
	SCENEMANAGER->addScene("title", m_pTitleScene);

	m_pStageScene = new stageScene;
	SCENEMANAGER->addScene("stage", m_pStageScene);

	m_pLoadingScene = new loadingScene;
	SCENEMANAGER->addLoadingScene("loading", m_pLoadingScene);
	
	SCENEMANAGER->changeScene("title");

	m_pEndingScene = new EndingScene;
	SCENEMANAGER->addScene("ending", m_pEndingScene);

	m_pCreatorScene = new CreatorScene;
	SCENEMANAGER->addScene("creator", m_pCreatorScene);
	

	// 민욱이는 과연 누구인가? 알랄라 내첫사랑 지수 ㅇㅇ
	// 이순현 테스트
	// 정지수 로그인 테스트
	return S_OK;
}

void mainGame::release()
{
	// 씬 매니저 내부(SCENEMANAGER->release())에서 처리하므로
	// 여기서는 삭제
	//m_pBattleScene->release();
	//SAFE_DELETE(m_pBattleScene);

	//m_pTitleScene->release();
	//SAFE_DELETE(m_pTitleScene);

	SAFE_DELETE(m_pBackBuffer);

	//KillTimer(g_hWnd, 1);
	ReleaseDC(g_hWnd, hdc);

	TXTDATA->release();
	KEYMANAGER->release();
	IMAGEMANAGER->release();
	TIMEMANAGER->release();
	SCENEMANAGER->release();

	TXTDATA->releaseSingleton();
	KEYMANAGER->releaseSingleton();
	IMAGEMANAGER->releaseSingleton();
	TIMEMANAGER->releaseSingleton();
	SCENEMANAGER->releaseSingleton();

}

LRESULT mainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	//case WM_MOUSEHWHEEL:
	//	if ((SHORT)HIWORD(wParam) > 0)
	//	{ // 0 보다 크면 위로 올라감
	//		m_pEditorScene_RE->WheelEvent(1, wParam);
	//	}
	//	else
	//	{ // 0 보다 작으면 밑으로 내려감
	//		m_pEditorScene_RE->WheelEvent(-1, wParam);
	//	}
	//	break;
	case WM_MOUSEMOVE:
		g_ptMouse.x = LOWORD(lParam);
		g_ptMouse.y = HIWORD(lParam);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			return 0;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_COMMAND:
		m_pEditor->ButtonEvent(hWnd, iMessage, wParam);
		break;
	}


	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

void mainGame::update()
{
	InvalidateRect(g_hWnd, NULL, false);

	// titleScene
	//m_pTitleScene->update();

	// battleScene
	//m_pBattleScene->update();

	SCENEMANAGER->update();
}

void mainGame::render()
{
	HDC backDC = m_pBackBuffer->getMemDC();





	// titleScene
	//m_pTitleScene->render(backDC);

	// battleScene
	//m_pBattleScene->render(backDC);

	SCENEMANAGER->render(backDC);

	m_pBackBuffer->render(hdc, 0, 0);

}

mainGame::mainGame()
{
}


mainGame::~mainGame()
{
}
