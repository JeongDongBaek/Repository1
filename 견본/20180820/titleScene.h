#pragma once
#include "scene.h"
#include "soundManager.h"

class PlayerCharacter;
class progressBar;
class bulletManger;
class effectManager;
class itemManager;
class monsterManger;
class animation;

#define OPTION_SOUND_X 50
#define OPTION_SOUND_Y 30
#define OPTION_SOUND_SIZE_Y 120




class titleScene : public scene
{


private:
	struct buttonSelect
	{
		RECT	m_rc;
		float	m_fX;
		float	m_fY;
		int		carrFrameX;
		int		carrFrameY;
		float	m_moveSpeed;
		bool	m_isMovement;
	};
	PlayerCharacter* m_player;
	image* m_titleScene;
	image* m_button;
	buttonSelect m_tButtonInfo;
	bulletManger * m_pBulletMag;
	bulletManger * m_pBulletMagMons;
	itemManager * m_pItemMag;
	monsterManger * m_pMonsterMag;
	effectManager * m_pEffMagr;
	progressBar* m_pProgressBar;

	soundManager m_soundMag;

	int m_buttonSetX;
	int m_buttonSetY;

	bool m_isOption;
	int m_soundSelectValue;
	int m_BgmValue;
	int m_SeValue;

public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	void OptionOn();

public:

	titleScene();
	~titleScene();
};

