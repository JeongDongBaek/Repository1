#pragma once
class image;
class animation;
class bulletManger;
class effectManager;

class bullet
{
private:
	image * m_pImg;
	animation * m_pAni;
	effectManager* m_eff;
	const char * m_effName;

	RECT	m_rc;
	int		m_ScaleCount;
	
	float	m_fAngle;
	float	m_fMoveAngle;
	float	m_fAngleRadius;
	int		tMoveTypeCount;
	
	float	m_fSetPosX;
	float	m_fSetPosY;

	bool	m_isAlive;
	
	bulletManger * m_pBulletMag;
	tagBulletInfo m_bulletInfo;
	tagBulletInfo * m_bulletInfoSub;

public:
	HRESULT init(const char * imageName, float posX, float posY, float angle, tagBulletInfo * bulletInfo, tagBulletInfo* bulletInfoSub, animation * pAni, effectManager * pEff, bulletManger* bulletMagPoint = NULL);
	void release();
	void update();
	void render(HDC hdc);

	void movement();
	void moveTypeAct(int moveType);

	bool getIsAlive() { return m_isAlive; }
	void setIsAlive(bool alive) { m_isAlive = alive; }

	int getBulletMaster() { return m_bulletInfo.tMasterType; }
	bool getIsBulletBoom() { return m_bulletInfo.tBulletBoom; }

	void HitEff();
	void SecondBulletFire();

	RECT getRect() { return m_rc; }


	tagBulletInfo getTagBulletInfo() { return m_bulletInfo; }

	bullet();
	~bullet();
};

