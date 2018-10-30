#include "stdafx.h"
#include "Squirrel.h"


HRESULT Squirrel::init()
{

	m_pImage = IMAGEMANAGER->findImage("squirrel_idle");
	m_pImage_Jump  = IMAGEMANAGER->findImage("squirrel_round") ;
	m_pImage_Run = IMAGEMANAGER->findImage("squirrel_run") ;
	m_pImage_Hurt = IMAGEMANAGER->findImage("squirrel_hurt");
	m_pImage_Fall = IMAGEMANAGER->findImage("squirrel_round");
	m_pImage_Round = IMAGEMANAGER->findImage("squirrel_round");

	return S_OK;
}

void Squirrel::update()
{
}

void Squirrel::release()
{
}

void Squirrel::render(HDC hdc)
{
}

Squirrel::Squirrel()
{
}


Squirrel::~Squirrel()
{
}
