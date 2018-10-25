#pragma once
class animation;
class bulletManger;
class item;
class soundManager;

#define RECT_BOX 1.6f

#define BULLET_FIRST_DELAY 45
#define CROSSHAIR_MAX_SCALE 5.0f
#define CROSSHAIR_MIN_SCALE 1.0f
#define BAES_HP 10

#define ITEM_BAG_X 50.0f
#define ITEM_BAG_Size_X 70.0f
#define ITEM_BAG_Y 250.0f
#define ITEM_BAG_Size_Y 70.0f

#define PLAYER_STATE_X 150.0f
#define PLAYER_STATE_Y 15.0f

#define BULLET_STATE_X 320.0f
#define BULLET_STATE_Y 13.0f

#define PLAYER_ICON_X 50.0f
#define PLAYER_ICON_Y 110.0f

#define PLAYER_HIT_DELAY 120

class PlayerCharacter
{
private:
	std::vector<item*>			m_vecItem;
	std::vector<item*>::iterator	m_iter;

	image * img_PlayerIdle;
	image * img_PlayerRun;
	image * img_PlayerShadow;

	image * img_CrossHair;
	image * img_HpPoint[10];

	image * img_ItemUiBg;
	image * img_InfoIcon;

	animation * ani_PlayerIdle;
	animation * ani_PlayerRun;
	animation * ani_CrossHair;

	soundManager * m_pSoundMag;

	item * m_pItemInfo;

	float m_fPlayerScale;

	bool m_isIdle;
	bool m_isRun;

	bool m_isItemUi;
	bool m_isRect;

	int m_itemNum;
	int m_itemNumY;

	bool m_isHitState;
	int m_HitAlphaValue;
	int m_HitDelayMax;
	int m_HitDelayCount;

	// 정지수 시작

	float m_fRadius;
	float m_fSpeed;
	float m_fCrossHairScale;
	float m_fCrossHairScaleMin;
	float m_fCrossHairScaleMax;

	int m_bulletDelayCount;
	int	m_bulletDelayCountMax;

	// 정지수 끝

	RECT m_rc;
	float m_fX = WINSIZEX / 2;
	float m_fY = WINSIZEY / 2;
	float m_fCurrX;
	float m_fCurrY;
	float m_fReturnX;
	float m_fReturnY;

	RECT m_TileRc;

	int m_currHp;
	int m_currHpMax;
	bool m_isAlive;

	bool m_isRectCol;

	tagBulletInfo m_tBulletInfo;
	tagBulletInfo * m_tBulletInfoPoint;
	tagBulletInfo m_tBulletInfoSub;
	tagBulletInfo * m_tBulletInfoSubPoint;

	bulletManger** m_pBulletMag;
	int			m_enumKey = -1;
public:
	HRESULT init(soundManager * soundPoint);
	void release();
	void update();
	void render(HDC hdc);

	void ColP2T();

	void setBulletMagPointer(bulletManger** bulletP) { m_pBulletMag = bulletP; }

	void getItem(tagItemInfo itemInfo);
	float getRadius() { return m_fRadius; }

	RECT getRect() { return m_rc; }

	float getX() { return m_fX; }
	void setX(float posX) { m_fX = posX; }
	float getY() { return m_fY; }
	void setY(float posY) { m_fY = posY; }

	void setTileRc(RECT rc) { m_TileRc = rc; }
	void setIsRc(bool isRc) { m_isRect = isRc; }

	float getSpeed() { return m_fSpeed; }
	bool getHitState() { return m_isHitState; }

	void PlayerDamage(int dam);
	void itemUi(HDC hdc);
	void PlayerInfoUi(HDC hdc);

	void isColRect(bool isRcet) { m_isRectCol = isRcet; }

	void keyInput();

	void HitState();

	PlayerCharacter();
	~PlayerCharacter();
};

