#pragma once
class loadingScene;
class stageScene;
class EndingScene;
class titleScene;
class editor;
class CreatorScene;


class mainGame
{
private:


	// DC
	HDC hdc;

	// ¹é¹öÆÛ
	image * m_pBackBuffer;
	void setBackBuffer();

	char m_szText[128];

	editor * m_pEditor;

	loadingScene * m_pLoadingScene;
	stageScene * m_pStageScene;
	titleScene * m_pTitleScene;
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

