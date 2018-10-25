#pragma once
class animation;
class PlayerCharacter;
class bulletManger;
class PlayerCharacter;
class progressBar;
class effectManager;
class soundManager;
class itemManager;

#define RECT_SIZE 2.0f

class monster
{
private:
	int m_moveTypeNum;
	int m_lifeCount;
	int m_HealingCount;
	int m_count;
	bool m_isHealing;
	bool m_Follow;
	float m_SubDamgeAdd;
	bool m_isMove;
	image * m_monsterType;
	animation * m_monsterMove;
	PlayerCharacter * m_player;
	progressBar * m_progressBar;

	tagBulletInfo m_tBulletInfo;
	tagBulletInfo * m_tBulletInfoPoint;
	tagBulletInfo m_tBulletInfoSub;
	tagBulletInfo * m_tBulletInfoSubPoint;

	bulletManger* m_pBulletMag;
	PlayerCharacter* m_PlayerCharPoint;

	tagSpawnTile m_tSpawnTile;

	tagMonInfo m_tMonInfo;

	effectManager * m_pEffMag;

public:
	HRESULT init(const char * strKey, int monNumber, tagMonInfo monInfo, bulletManger* bulletP, PlayerCharacter* playerPoint, effectManager* effMagPoint, tagBulletInfo tBulletInfo);

	void release();

	image getImage() { return *m_monsterType; }

	void update();
	void Enemy_LevelUp(int type);
	void Move(int m_moveTypeNum);
	void fireAtk();
	void knokback(float playerkuokback, float monsterHitRecovery, float bulletAngle);
	void Damge(float dam, soundManager * soundMagPoint, itemManager * itemMagPoint);
	void TypeSub(float minGague, float maxGauge, int minSubInfo, int maxSubInfo, bool isTrance, int life);

	void render(HDC hdc);

	void rectNotMove(RECT rRc);

	tagMonInfo getMonInfo() { return m_tMonInfo; }
	void setAlive(bool Alive) { m_tMonInfo.tIsAlive = Alive; };
	monster();
	~monster();
};

