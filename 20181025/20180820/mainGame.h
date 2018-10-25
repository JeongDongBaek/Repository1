#pragma once
class loadingScene;
class EndingScene;
class CreatorScene;
class Editor_Scene;
class Title_Scene;
class Editor_SetSize;

class mainGame
{
private:


	// DC
	HDC hdc;

	// ¹é¹öÆÛ
	image * m_pBackBuffer;
	void setBackBuffer();

	char m_szText[128];

	Editor_Scene * m_pEditorScene;
	Editor_SetSize * m_pEditorSetSize;

	loadingScene * m_pLoadingScene;
	Title_Scene * m_pTitleScene;
	EndingScene * m_pEndingScene;
	CreatorScene * m_pCreatorScene;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	mainGame();
	~mainGame();
};

