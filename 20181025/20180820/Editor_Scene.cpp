#include "stdafx.h"
#include "Editor_Scene.h"

void Editor_Scene::ButtonEvent(HWND hWnd, UINT iMessage, WPARAM wParam)
{
	
}






HRESULT Editor_Scene::init()
{
	m_pImg_tileset1 = IMAGEMANAGER->findImage("tileset1");
	m_pImg_tileset1 = IMAGEMANAGER->findImage("tileset1_div");




	return S_OK;
}

void Editor_Scene::update()
{
	
	update_once();


}

void Editor_Scene::update_once()
{
}




void Editor_Scene::release()
{
}

void Editor_Scene::render(HDC hdc)
{
}












Editor_Scene::Editor_Scene()
{
}

Editor_Scene::~Editor_Scene()
{
}
