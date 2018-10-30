#include "stdafx.h"
#include "Fox.h"


HRESULT Fox::init()
{
	m_pImage = IMAGEMANAGER->findImage("fox_idle");
	m_pImage_Jump = IMAGEMANAGER->findImage("fox_jump");
	m_pImage_Run = IMAGEMANAGER->findImage("fox_run");
	m_pImage_Hurt = IMAGEMANAGER->findImage("fox_hurt");
	m_pImage_Climb = IMAGEMANAGER->findImage("fox_climb");
	m_pImage_Fall = IMAGEMANAGER->findImage("fox_jump");
	return S_OK;
}

void Fox::update()
{


}

void Fox::release()
{
}

void Fox::render(HDC hdc)
{

}



Fox::Fox()
{
}

Fox::~Fox()
{
}