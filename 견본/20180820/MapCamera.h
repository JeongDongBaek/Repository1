#pragma once
#include "singletonBase.h"
#include "editor.h"




#define LOC_MINIMAPX_MAP 267
#define LOC_MINIMAPY_MAP 190

#define CAMERA_SPEED 5


class MapCamera : public singletonBase<MapCamera>
{
private:
	int m_nMiniMap_LocationX; // ¹Ì´Ï¸Ê »ý¼ºµÇ´Â À§Ä¡
	int m_nMiniMap_LocationY;

	//editorScene_re m_pEdtior;
	editor m_pEdtior;

	//POINT m_ptCamera;
	//POINT m_ptMiniCamera;

	/*RECT m_rcCamera;
	RECT m_rcMiniCamera;*/

public:
	SYNTHESIZE(float, m_ptMoveCameraX, focusCameraX) // °Ñ¸é
		SYNTHESIZE(float, m_ptCameraX, CameraX)
		SYNTHESIZE(float, m_ptMoveCameraY, focusCameraY)
		SYNTHESIZE(float, m_ptCameraY, CameraY)

		SYNTHESIZE(float, m_ptMiniCameraX, focusMiniCameraX)
		SYNTHESIZE(float, m_ptCameraMiniX, CameraMiniX)
		SYNTHESIZE(float, m_ptMiniCameraY, focusMiniCameraY)
		SYNTHESIZE(float, m_ptCameraMiniY, CameraMiniY)

		//SYNTHESIZE(POINT, m_ptCamera, CameraPoint); // °Ñ¸é
		//SYNTHESIZE(POINT, m_ptMiniCamera, MiniCameraPoint); // °Ñ¸é
		//SYNTHESIZE(RECT, m_rcCamera, CameraRect);
		//SYNTHESIZE(RECT, m_rcMiniCamera, MiniCameraRect);



		HRESULT init();
	void MiniMapRatioInit();

	void release();
	void update();
	void keyUpdate();

	void render(HDC hdc);
	MapCamera();
	~MapCamera();
};

