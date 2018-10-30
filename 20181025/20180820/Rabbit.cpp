#include "stdafx.h"
#include "Rabbit.h"
#include "GameObject.h"

HRESULT Rabbit::init()
{
	m_pImage = IMAGEMANAGER->findImage("rabbit_idle");
	m_pImage_Jump = IMAGEMANAGER->findImage("rabbit_jump");
	m_pImage_Run = IMAGEMANAGER->findImage("rabbit_run");
	m_pImage_Hurt = IMAGEMANAGER->findImage("rabbit_hurt");
	m_pImage_Climb = IMAGEMANAGER->findImage("rabbit_climb");
	m_pImage_Fall = IMAGEMANAGER->findImage("rabbit_fall");

	return S_OK;
}

void Rabbit::update()
{
}

void Rabbit::release()
{
}

void Rabbit::render(HDC hdc)
{
}

Rabbit::Rabbit()
{

}


Rabbit::~Rabbit()
{
}
