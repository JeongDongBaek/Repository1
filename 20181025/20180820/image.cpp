#include "stdafx.h"
#include "image.h"
#include "animation.h"

#pragma comment (lib, "msimg32.lib")

image::image()
{
}


image::~image()
{
}

HRESULT image::init(int width, int height)
{
	HDC hdc = GetDC(g_hWnd);

	m_pImageInfo = new IMAGE_INFO;
	// 기본 DC와 분리되는 메모리 DC, 비트맵 출력을 위한 공간
	m_pImageInfo->hMemDC = CreateCompatibleDC(hdc);
	// 원본 DC와 호환되는 비트맵 생성
	m_pImageInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);
	// 새로 생성한 메모리DC 와 새로 생성한 비트맵을 연동시킨다
	m_pImageInfo->hOldBitmap = (HBITMAP)SelectObject(m_pImageInfo->hMemDC, m_pImageInfo->hBitmap);

	m_pImageInfo->nWidth = width;
	m_pImageInfo->nHeight = height;

	// 알파 블렌드
	// 옵션
	m_blendFunc.AlphaFormat = 0;
	m_blendFunc.BlendFlags = 0;
	m_blendFunc.BlendOp = AC_SRC_OVER;

	// 알파 블렌드 사용을 위한 중간 이미지
	m_pBlendImage = new IMAGE_INFO;
	m_pBlendImage->hMemDC = CreateCompatibleDC(hdc);
	m_pBlendImage->hBitmap = CreateCompatibleBitmap(hdc, 
		WINSIZEX, WINSIZEY);
	m_pBlendImage->hOldBitmap = (HBITMAP)SelectObject(
		m_pBlendImage->hMemDC, m_pBlendImage->hBitmap);
	m_pBlendImage->nWidth = WINSIZEX;
	m_pBlendImage->nHeight = WINSIZEY;

	ReleaseDC(g_hWnd, hdc);

	if (m_pImageInfo->hBitmap == NULL)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

//HRESULT image::init(const char * szFileName, int width, int height)
//{
//	if (szFileName == NULL) return E_FAIL;
//
//	HDC hdc = GetDC(g_hWnd);
//
//	m_pImageInfo = new IMAGE_INFO;
//	// 기본 DC와 분리되는 메모리 DC, 비트맵 출력을 위한 공간
//	m_pImageInfo->hMemDC = CreateCompatibleDC(hdc);
//	// 원본 DC와 호환되는 비트맵 생성
//	m_pImageInfo->hBitmap = (HBITMAP)LoadImage(
//		g_hInstance, 
//		szFileName,
//		IMAGE_BITMAP,
//		width, height,
//		LR_LOADFROMFILE);
//	// 새로 생성한 메모리DC 와 새로 생성한 비트맵을 연동시킨다
//	m_pImageInfo->hOldBitmap = (HBITMAP)SelectObject(m_pImageInfo->hMemDC, m_pImageInfo->hBitmap);
//
//	m_pImageInfo->nWidth = width;
//	m_pImageInfo->nHeight = height;
//
//	ReleaseDC(g_hWnd, hdc);
//
//	if (m_pImageInfo->hBitmap == NULL)
//	{
//		release();
//		return E_FAIL;
//	}
//
//	return S_OK;
//}

HRESULT image::init(const char * szFileName, int width, int height, bool trans /*= false*/, COLORREF transColor)
{
	if (szFileName == NULL) return E_FAIL;

	HDC hdc = GetDC(g_hWnd);

	m_pImageInfo = new IMAGE_INFO;
	// 기본 DC와 분리되는 메모리 DC, 비트맵 출력을 위한 공간
	m_pImageInfo->hMemDC = CreateCompatibleDC(hdc);
	// 원본 DC와 호환되는 비트맵 생성
	m_pImageInfo->hBitmap = (HBITMAP)LoadImage(
		g_hInstance,
		szFileName,
		IMAGE_BITMAP,
		width, height,
		LR_LOADFROMFILE);
	// 새로 생성한 메모리DC 와 새로 생성한 비트맵을 연동시킨다
	m_pImageInfo->hOldBitmap = (HBITMAP)SelectObject(m_pImageInfo->hMemDC, m_pImageInfo->hBitmap);

	m_pImageInfo->nWidth = width;
	m_pImageInfo->nHeight = height;

	// 알파 블렌드
	// 옵션
	m_blendFunc.AlphaFormat = 0;
	m_blendFunc.BlendFlags = 0;
	m_blendFunc.BlendOp = AC_SRC_OVER;

	// 알파 블렌드 사용을 위한 중간 이미지
	m_pBlendImage = new IMAGE_INFO;
	m_pBlendImage->hMemDC = CreateCompatibleDC(hdc);
	m_pBlendImage->hBitmap = CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	m_pBlendImage->hOldBitmap = (HBITMAP)SelectObject(
		m_pBlendImage->hMemDC, m_pBlendImage->hBitmap);
	m_pBlendImage->nWidth = WINSIZEX;
	m_pBlendImage->nHeight = WINSIZEY;

	// 피격 블렌드
	m_blendFuncHit.AlphaFormat = 0;
	m_blendFuncHit.BlendFlags = 0;
	m_blendFuncHit.BlendOp = AC_SRC_OVER;

	m_pBlendImageHit = new IMAGE_INFO;
	m_pBlendImageHit->hMemDC = CreateCompatibleDC(hdc);
	m_pBlendImageHit->hBitmap = CreateCompatibleBitmap(hdc, m_pImageInfo->nWidth, m_pImageInfo->nHeight);
	m_pBlendImageHit->hOldBitmap = (HBITMAP)SelectObject(m_pBlendImageHit->hMemDC, m_pBlendImageHit->hBitmap);
	m_pBlendImageHit->nWidth = m_pImageInfo->nWidth;
	m_pBlendImageHit->nHeight = m_pImageInfo->nHeight;

	// 브러시 색상 이미지 준비
	HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(m_pBlendImageHit->hMemDC, brush);
	FillRect(m_pBlendImageHit->hMemDC, &RectMake(0, 0, m_pBlendImageHit->nWidth, m_pBlendImageHit->nHeight), brush);
	SelectObject(m_pBlendImageHit->hMemDC, oldBrush);
	DeleteObject(brush);

	//for (int y = 0; y < m_pBlendImageHit->nHeight; y++)
	//{
	//	for (int x = 0; x < m_pBlendImageHit->nWidth; x++)
	//	{
	//		COLORREF color = GetPixel(m_pImageInfo->hMemDC, x, y);
	//		int r = GetRValue(color);
	//		int g = GetGValue(color);
	//		int b = GetBValue(color);
	//		if (!(r == 255 && g == 0 && b == 255))
	//		{
	//			SetPixel(m_pBlendImageHit->hMemDC, x, y, RGB(255, 0, 0));
	//		}
	//		else
	//		{
	//			SetPixel(m_pBlendImageHit->hMemDC, x, y, RGB(255, 0, 255));
	//		}
	//	}
	//}

	m_pBlendImageHit = new IMAGE_INFO;
	// 기본 DC와 분리되는 메모리 DC, 비트맵 출력을 위한 공간
	m_pBlendImageHit->hMemDC = CreateCompatibleDC(hdc);
	// 원본 DC와 호환되는 비트맵 생성
	m_pBlendImageHit->hBitmap = (HBITMAP)LoadImage(
		g_hInstance,
		szFileName,
		IMAGE_BITMAP,
		width, height,
		LR_LOADFROMFILE);
	// 새로 생성한 메모리DC 와 새로 생성한 비트맵을 연동시킨다
	m_pBlendImageHit->hOldBitmap = (HBITMAP)SelectObject(m_pBlendImageHit->hMemDC, m_pBlendImageHit->hBitmap);

	m_pBlendImageHit->nWidth = width;
	m_pBlendImageHit->nHeight = height;

	// 투명 컬러 셋팅
	m_isTransparent = trans;
	m_transColor = transColor;

	ReleaseDC(g_hWnd, hdc);

	if (m_pImageInfo->hBitmap == NULL)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

HRESULT image::init(const char * szFileName, float x, float y,
	int width, int height, int frameX, int frameY,
	bool trans, COLORREF transColor)
{
	if (szFileName == NULL) return E_FAIL;

	HDC hdc = GetDC(g_hWnd);

	m_pImageInfo = new IMAGE_INFO;
	// 기본 DC와 분리되는 메모리 DC, 비트맵 출력을 위한 공간
	m_pImageInfo->hMemDC = CreateCompatibleDC(hdc);
	// 원본 DC와 호환되는 비트맵 생성
	m_pImageInfo->hBitmap = (HBITMAP)LoadImage(
		g_hInstance,
		szFileName,
		IMAGE_BITMAP,
		width, height,
		LR_LOADFROMFILE);
	// 새로 생성한 메모리DC 와 새로 생성한 비트맵을 연동시킨다
	m_pImageInfo->hOldBitmap = (HBITMAP)SelectObject(m_pImageInfo->hMemDC, m_pImageInfo->hBitmap);

	m_pImageInfo->fX = x;
	m_pImageInfo->fY = y;
	m_pImageInfo->nCurrFrameX = 0;
	m_pImageInfo->nCurrFrameY = 0;
	m_pImageInfo->nWidth = width;
	m_pImageInfo->nHeight = height;
	m_pImageInfo->nFrameWidth = width / frameX;
	m_pImageInfo->nFrameHeight = height / frameY;
	m_pImageInfo->nMaxFrameX = frameX - 1;
	m_pImageInfo->nMaxFrameY = frameY - 1;

	// 알파 블렌드
	// 옵션
	m_blendFunc.AlphaFormat = 0;
	m_blendFunc.BlendFlags = 0;
	m_blendFunc.BlendOp = AC_SRC_OVER;

	// 알파 블렌드 사용을 위한 중간 이미지
	m_pBlendImage = new IMAGE_INFO;
	m_pBlendImage->hMemDC = CreateCompatibleDC(hdc);
	m_pBlendImage->hBitmap = CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	m_pBlendImage->hOldBitmap = (HBITMAP)SelectObject(
		m_pBlendImage->hMemDC, m_pBlendImage->hBitmap);
	m_pBlendImage->nWidth = WINSIZEX;
	m_pBlendImage->nHeight = WINSIZEY;

	// 투명 컬러 셋팅
	m_isTransparent = trans;
	m_transColor = transColor;

	ReleaseDC(g_hWnd, hdc);

	if (m_pImageInfo->hBitmap == NULL)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

void image::release()
{
	

	if (m_pBlendImage)
	{
		SelectObject(m_pBlendImage->hMemDC, m_pBlendImage->hOldBitmap);
		DeleteObject(m_pBlendImage->hBitmap);
		DeleteDC(m_pBlendImage->hMemDC);

		delete m_pBlendImage;
	}

	if (m_pImageInfo)
	{
		SelectObject(m_pImageInfo->hMemDC, m_pImageInfo->hOldBitmap);
		DeleteObject(m_pImageInfo->hBitmap);
		DeleteDC(m_pImageInfo->hMemDC);

		delete m_pImageInfo;
	}
}

void image::render(HDC hdc, int destX, int destY)
{
	if (m_isTransparent)
	{
		GdiTransparentBlt(
			// 목적지
			hdc,	// 복사될 목적지 DC
			destX, destY,		// 복사될 좌표 시작점
			m_pImageInfo->nWidth,
			m_pImageInfo->nHeight,	// 복사될 크기
			
			// 대상
			m_pImageInfo->hMemDC,	// 복사할 대상 DC
			0, 0,					// 복사될 영역 시작좌표
			m_pImageInfo->nWidth,
			m_pImageInfo->nHeight,	// 복사될 영역지정 좌표

			m_transColor);			// 복사에서 제외할 색상
	}
	else
	{
		// hdc : 복사될 목적지 DC
		// destX : 출력을 시작할 x 좌표
		// destY : 출력을 시작할 y 좌표
		// cx : 출력할 이미지를 어느정도까지 출력할 것인가의 가로값
		// cy : 출력할 이미지를 어느정도까지 출력할 것인가의 세로값
		// hdcSrc : 복사할 정보를 제공하는 DC
		// x1 : 이미지의 시작점을 잘라낼 것인가의 가로값
		// y1 : 이미지의 시작점을 잘라낼 것인가의 세로값
		// rop : 복사하는 옵션 (SRCCOPY)
		BitBlt(
			hdc, 
			destX, destY,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_pImageInfo->hMemDC,
			0, 0, SRCCOPY);
	}
}

void image::render(HDC hdc, int destX, int destY, int scalar)
{
	if (m_isTransparent)
	{
		GdiTransparentBlt(
			// 목적지
			hdc,	// 복사될 목적지 DC
			destX, destY,		// 복사될 좌표 시작점
			m_pImageInfo->nWidth * scalar,
			m_pImageInfo->nHeight * scalar,	// 복사될 크기

									// 대상
			m_pImageInfo->hMemDC,	// 복사할 대상 DC
			0, 0,					// 복사될 영역 시작좌표
			m_pImageInfo->nWidth,
			m_pImageInfo->nHeight,	// 복사될 영역지정 좌표

			m_transColor);			// 복사에서 제외할 색상
	}
	else
	{
		// hdc : 복사될 목적지 DC
		// destX : 출력을 시작할 x 좌표
		// destY : 출력을 시작할 y 좌표
		// cx : 출력할 이미지를 어느정도까지 출력할 것인가의 가로값
		// cy : 출력할 이미지를 어느정도까지 출력할 것인가의 세로값
		// hdcSrc : 복사할 정보를 제공하는 DC
		// x1 : 이미지의 시작점을 잘라낼 것인가의 가로값
		// y1 : 이미지의 시작점을 잘라낼 것인가의 세로값
		// rop : 복사하는 옵션 (SRCCOPY)
		BitBlt(
			hdc,
			destX, destY,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_pImageInfo->hMemDC,
			0, 0, SRCCOPY);
	}
}


void image::render(HDC hdc, int destX, int destY, 
	int sourX, int sourY, int sourWidth, int sourHeight, float scalar)
{
	if (m_isTransparent)
	{
		GdiTransparentBlt(
			// 목적지
			hdc,					// 복사될 목적지 DC
			destX, destY,			// 복사될 좌표 시작점
			sourWidth * scalar, sourHeight * scalar,	// 복사될 크기

			// 대상
			m_pImageInfo->hMemDC,	// 복사할 대상 DC
			sourX, sourY,			// 복사될 영역 시작좌표
			sourWidth, sourHeight,	// 복사될 영역지정 좌표

			m_transColor);			// 복사에서 제외할 색상
	}
	else
	{
		BitBlt(
			hdc,
			destX, destY,
			sourX, sourY,
			m_pImageInfo->hMemDC,
			0, 0, SRCCOPY);
	}
}

void image::render(HDC hdc, int destX, int destY,
	int sourX, int sourY, int sourWidth, int sourHeight, float scalar, BYTE alpha)
{
	m_blendFunc.SourceConstantAlpha = alpha;

	if (m_isTransparent)
	{
		// 1. 출력해야되는 DC에 그려져있는 내용을 blendImage에 복사
		BitBlt(
			// 목적지
			m_pBlendImage->hMemDC,
			0, 0,
			sourWidth * scalar, sourHeight * scalar,

			// 대상
			hdc,
			destX, destY,
			SRCCOPY);

		// 2. 출력할 이미지를 blendImage에 복사
		GdiTransparentBlt(
			// 목적지
			m_pBlendImage->hMemDC,
			0, 0,
			sourWidth * scalar, sourHeight * scalar,

			// 대상
			m_pImageInfo->hMemDC,	// 복사할 대상 DC
			sourX, sourY,			// 복사될 영역 시작좌표
			sourWidth, sourHeight,

			m_transColor);			// 복사에서 제외할 색상
									// 3. blendDC를 출력해야되는 DC에 복사
		AlphaBlend(
			// 목적지
			hdc,
			destX, destY,
			sourWidth * scalar, sourHeight * scalar,

			// 대상
			m_pBlendImage->hMemDC,
			0, 0,
			sourWidth * scalar, sourHeight * scalar,
			m_blendFunc);
	}
	else
	{
		AlphaBlend(
			// 복사할 목표
			hdc,
			destX, destY,
			sourWidth * scalar, sourHeight * scalar,

			// 대상
			m_pBlendImage->hMemDC,
			0, 0,
			sourWidth * scalar, sourHeight * scalar,
			m_blendFunc);
	}
}

void image::frameRender(HDC hdc, int destX, int destY, int currFrameX, int currFrameY)
{
	m_pImageInfo->nCurrFrameX = currFrameX;
	m_pImageInfo->nCurrFrameY = currFrameY;

	if (currFrameX > m_pImageInfo->nMaxFrameX)
		m_pImageInfo->nCurrFrameX = m_pImageInfo->nMaxFrameX;
	if (currFrameY > m_pImageInfo->nMaxFrameY)
		m_pImageInfo->nCurrFrameY = m_pImageInfo->nMaxFrameY;

	if (m_isTransparent)
	{
		GdiTransparentBlt(
			hdc,	// 복사될 목적지 DC
			destX, destY,		// 복사될 좌표 시작점
			m_pImageInfo->nFrameWidth,
			m_pImageInfo->nFrameHeight,	// 복사될 크기

									// 대상
			m_pImageInfo->hMemDC,	// 복사할 대상 DC
			m_pImageInfo->nFrameWidth * m_pImageInfo->nCurrFrameX,
			m_pImageInfo->nFrameHeight * m_pImageInfo->nCurrFrameY,					// 복사될 영역 시작좌표
			m_pImageInfo->nFrameWidth,
			m_pImageInfo->nFrameHeight,	// 복사될 영역지정 좌표

			m_transColor);			// 복사에서 제외할 색상
	}

	else
	{
		BitBlt(
			hdc,
			destX, destY,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_pImageInfo->hMemDC,
			0, 0, SRCCOPY);
	}
}

void image::frameAlphaRender(HDC hdc, int destX, int destY, int currFrameX, int currFrameY, float scale, BYTE alpha)
{

	// 알파 값을 받아주는 펑션
	m_blendFunc.SourceConstantAlpha = alpha;

	m_pImageInfo->nCurrFrameX = currFrameX;
	m_pImageInfo->nCurrFrameY = currFrameY;

	if (currFrameX > m_pImageInfo->nMaxFrameX)
		m_pImageInfo->nCurrFrameX = m_pImageInfo->nMaxFrameX;
	if (currFrameY > m_pImageInfo->nMaxFrameY)
		m_pImageInfo->nCurrFrameY = m_pImageInfo->nMaxFrameY;

	if (m_isTransparent)
	{
		// 1. 출력해야되는 DC에 그려져있는 내용을 blendImage에 복사
		BitBlt(m_pBlendImage->hMemDC,
			0, 0,
			m_pImageInfo->nFrameWidth * scale, m_pImageInfo->nFrameHeight * scale,

			hdc,
			destX, destY,
			SRCCOPY);

		GdiTransparentBlt(
			hdc,	// 복사될 목적지 DC
			destX, destY,		// 복사될 좌표 시작점
			m_pImageInfo->nFrameWidth * scale,
			m_pImageInfo->nFrameHeight * scale,	// 복사될 크기

										// 대상
			m_pImageInfo->hMemDC,	// 복사할 대상 DC
			(m_pImageInfo->nFrameWidth)* m_pImageInfo->nCurrFrameX,
			(m_pImageInfo->nFrameHeight) * m_pImageInfo->nCurrFrameY,					// 복사될 영역 시작좌표
			m_pImageInfo->nFrameWidth,
			m_pImageInfo->nFrameHeight,	// 복사될 영역지정 좌표

			m_transColor);			// 복사에서 제외할 색상

		AlphaBlend(
			hdc,
			destX, destY,
			m_pImageInfo->nFrameWidth * scale, m_pImageInfo->nFrameHeight * scale,

			// 복사할 대상
			m_pBlendImage->hMemDC,
			0, 0,
			m_pImageInfo->nFrameWidth * scale, m_pImageInfo->nFrameHeight * scale,
			m_blendFunc);
	}
	else
	{
		AlphaBlend(
			// 복사할 목표
			hdc,
			destX, destY,
			(m_pImageInfo->nFrameWidth * scale) * m_pImageInfo->nCurrFrameX,
			(m_pImageInfo->nFrameHeight * scale) * m_pImageInfo->nCurrFrameY,

			// 복사할 대상
			m_pBlendImage->hMemDC,
			0, 0,
			(m_pImageInfo->nFrameWidth * scale) * m_pImageInfo->nCurrFrameX,
			(m_pImageInfo->nFrameHeight * scale) * m_pImageInfo->nCurrFrameY,
			m_blendFunc);
	}
}

void image::RatioRender(HDC hdc, int destX, int destY, int currFrameX, int currFrameY, int scalar, int tilesizeX, int tilesizeY)
{
	m_pImageInfo->nCurrFrameX = currFrameX;
	m_pImageInfo->nCurrFrameY = currFrameY;

	if (currFrameX > m_pImageInfo->nMaxFrameX)
		m_pImageInfo->nCurrFrameX = m_pImageInfo->nMaxFrameX;
	if (currFrameY > m_pImageInfo->nMaxFrameY)
		m_pImageInfo->nCurrFrameY = m_pImageInfo->nMaxFrameY;

	if (tilesizeX >= 16)
		tilesizeX = tilesizeX / 16;

	if (tilesizeY >= 16)
		tilesizeY = tilesizeY / 16;

	if (m_isTransparent)
	{
		GdiTransparentBlt(
			hdc,	// 복사될 목적지 DC
			destX, destY,		// 복사될 좌표 시작점
			m_pImageInfo->nFrameWidth / scalar * tilesizeX,
			m_pImageInfo->nFrameHeight / scalar * tilesizeY,	// 복사될 크기

										// 대상
			m_pImageInfo->hMemDC,	// 복사할 대상 DC
			m_pImageInfo->nFrameWidth * m_pImageInfo->nCurrFrameX,
			m_pImageInfo->nFrameHeight * m_pImageInfo->nCurrFrameY,// 복사될 영역 시작좌표
			m_pImageInfo->nFrameWidth,
			m_pImageInfo->nFrameHeight,	// 복사될 영역지정 좌표
			m_transColor);			// 복사에서 제외할 색상
	}
	else
	{
		BitBlt(
			hdc,
			destX, destY,
			m_pImageInfo->nWidth / scalar, m_pImageInfo->nHeight / scalar,
			m_pImageInfo->hMemDC,
			0, 0, SRCCOPY);
	}

}

void image::alphaRender(HDC hdc, BYTE alpha)
{
	m_blendFunc.SourceConstantAlpha = alpha;

	if (m_isTransparent)
	{
		// 1. 출력해야되는 DC에 그려져있는 내용을 blendImage에 복사
		BitBlt(m_pBlendImage->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			hdc,
			m_pImageInfo->fX, m_pImageInfo->fY,
			SRCCOPY);

		// 2. 출력할 이미지를 blendImage에 복사
		GdiTransparentBlt(m_pBlendImage->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_pImageInfo->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_transColor);
		// 3. blendDC를 출력해야되는 DC에 복사
		AlphaBlend(hdc,
			m_pImageInfo->fX, m_pImageInfo->fY,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_pBlendImage->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_blendFunc);
	}
	else
	{
		AlphaBlend(
			// 복사할 목표
			hdc,
			m_pImageInfo->fX, m_pImageInfo->fY,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			// 복사할 대상
			m_pImageInfo->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_blendFunc);
	}
}

void image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	m_blendFunc.SourceConstantAlpha = alpha;

	if (m_isTransparent)
	{
		// 1. 출력해야되는 DC에 그려져있는 내용을 blendImage에 복사
		BitBlt(
			// 목적지
			m_pBlendImage->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,

			// 대상
			hdc,
			destX, destY,
			SRCCOPY);

		// 2. 출력할 이미지를 blendImage에 복사
		GdiTransparentBlt(
			// 목적지
			m_pBlendImage->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,

			// 대상
			m_pImageInfo->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_transColor);
		// 3. blendDC를 출력해야되는 DC에 복사
		AlphaBlend(
			// 목적지
			hdc,
			destX, destY,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,

			// 대상
			m_pBlendImage->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_blendFunc);
	}
	else
	{
		AlphaBlend(
			// 복사할 목표
			hdc,
			destX, destY,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			// 복사할 대상
			m_pImageInfo->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_blendFunc);
	}
}

void image::alphaRender(HDC hdc, int destX, int destY, int rad, BYTE alpha)
{
	m_blendFunc.SourceConstantAlpha = alpha;

	if (m_isTransparent)
	{
		// 1. 출력해야되는 DC에 그려져있는 내용을 blendImage에 복사
		BitBlt(
			// 목적지
			m_pBlendImage->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,

			// 대상
			hdc,
			destX, destY,
			SRCCOPY);

		// 2. 출력할 이미지를 blendImage에 복사
		GdiTransparentBlt(
			// 목적지
			m_pBlendImage->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,

			// 대상
			m_pImageInfo->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_transColor);
		// 3. blendDC를 출력해야되는 DC에 복사
		AlphaBlend(
			// 목적지
			hdc,
			destX, destY,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,

			// 대상
			m_pBlendImage->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_blendFunc);
	}
	else
	{
		AlphaBlend(
			// 복사할 목표
			hdc,
			destX, destY,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			// 복사할 대상
			m_pImageInfo->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_blendFunc);
	}
}

void image::aniRender(HDC hdc, int destX, int destY, animation * ani, float scalar, bool isAlpha, BYTE alpha)
{
	if (isAlpha)
	{
		render(hdc, destX, destY,
			ani->getFramePos().x, ani->getFramePos().y,
			ani->getFrameWidth(), ani->getFrameHeight(), scalar, alpha);
	}
	else
	{
		render(hdc, destX, destY,
			ani->getFramePos().x, ani->getFramePos().y,
			ani->getFrameWidth(), ani->getFrameHeight(), scalar);
	}
}

void image::rotateRender(HDC hdc, float rotateAngle, float fX, float fY, int scalar/*=1*/)
{

	// 현재 각도를 라디안값으로 변환
	float theta = rotateAngle * PI / 180.0f;

	// sin, cos값 구하기
	float s = sinf(theta);
	float c = cosf(theta);

	float fAncherX = 0.5; // 앵커들은 회전의 기준이 됨 그러나 이번 프로젝트에선 가운데를 기준으로 회전만 하기 떄문에 0.5로 고정값을 해놓음
	float fAncherY = 0.5;

	float posXSrcL = m_pImageInfo->nWidth * fAncherX;
	float posYSrcL = m_pImageInfo->nHeight * fAncherY;
	float posXSrcR = m_pImageInfo->nWidth * (1.0f - fAncherX);
	float posYSrcR = m_pImageInfo->nHeight * (1.0f - fAncherY);

	POINT m_vertices[3];








	//m_vertices[0].x = (LONG)(m_pImageInfo->fX - (0.5f * m_pImageInfo->nWidth));
	//m_vertices[0].y = (LONG)(m_pImageInfo->fY - (0.5f * m_pImageInfo->nHeight));

	//// Upper-Right
	//m_vertices[1].x = (LONG)(m_pImageInfo->fX + (m_pImageInfo->nWidth - (0.5f * m_pImageInfo->nWidth)));
	//m_vertices[1].y = (LONG)(m_pImageInfo->fY - (0.5f * m_pImageInfo->nHeight));

	//// Lower-Right
	//m_vertices[2].x = (LONG)(m_pImageInfo->fX + (m_pImageInfo->nWidth - (0.5f * m_pImageInfo->nWidth)));
	//m_vertices[2].y = (LONG)(m_pImageInfo->fY + (m_pImageInfo->nHeight - (0.5f * m_pImageInfo->nHeight)));



	if (m_isTransparent)
	{

		// Upper-Left
		m_vertices[0].x = (LONG)((-posXSrcL * c + posYSrcL * s) + m_pImageInfo->nWidth / 2);
		m_vertices[0].y = (LONG)((-posXSrcL * s - posYSrcL * c) + m_pImageInfo->nHeight / 2);
		// Upper-Right
		m_vertices[1].x = (LONG)((posXSrcR * c + posYSrcL * s) + m_pImageInfo->nWidth / 2);
		m_vertices[1].y = (LONG)((posXSrcR * s - posYSrcL * c) + m_pImageInfo->nHeight / 2);
		// Lower-Right
		m_vertices[2].x = (LONG)((-posXSrcL * c - posYSrcR * s) + m_pImageInfo->nWidth / 2);
		m_vertices[2].y = (LONG)((-posXSrcL * s + posYSrcR * c) + m_pImageInfo->nHeight / 2);

		HBRUSH brush = CreateSolidBrush(RGB(255, 0, 255));

		RECT rc;
		rc = RectMake(0, 0, m_pImageInfo->nWidth + (m_pImageInfo->nWidth / 2), m_pImageInfo->nHeight + (m_pImageInfo->nHeight / 2));

		FillRect(m_pBlendImage->hMemDC, &rc, brush);
		DeleteObject(brush);




		PlgBlt(m_pBlendImage->hMemDC, m_vertices, m_pImageInfo->hMemDC, 0, 0, m_pImageInfo->nWidth, m_pImageInfo->nHeight, NULL, 0, 0);



		// 2. 출력할 이미지를 blendImage에 복사
		GdiTransparentBlt(hdc,
			fX - m_pImageInfo->nWidth / 2, fY - m_pImageInfo->nHeight / 2,
			(m_pImageInfo->nWidth)*scalar, (m_pImageInfo->nHeight)*scalar,
			m_pBlendImage->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			RGB(255, 0, 255));
	}
	else
	{
		// Upper-Left
		m_vertices[0].x = (LONG)((-posXSrcL * c + posYSrcL * s) + fX);
		m_vertices[0].y = (LONG)((-posXSrcL * s - posYSrcL * c) + fY);
		// Upper-Right
		m_vertices[1].x = (LONG)((posXSrcR * c + posYSrcL * s) + fX);
		m_vertices[1].y = (LONG)((posXSrcR * s - posYSrcL * c) + fY);
		// Lower-Right
		m_vertices[2].x = (LONG)((-posXSrcL * c - posYSrcR * s) + fX);
		m_vertices[2].y = (LONG)((-posXSrcL * s + posYSrcR * c) + fY);

		PlgBlt(hdc, m_vertices, m_pImageInfo->hMemDC, 0, 0, m_pImageInfo->nWidth + 20, m_pImageInfo->nHeight + 20, NULL, 0, 0);

	}

}


void image::hitRender(HDC hdc, int destX, int destY, COLORREF color)
{
	//// 브러시 색상 이미지 준비
	//HBRUSH brush = CreateSolidBrush(color);
	//HBRUSH oldBrush = (HBRUSH)SelectObject(m_pBlendImageHit->hMemDC, brush);

	//BitBlt(
	//	// 목적지
	//	m_pBlendImageHit->hMemDC,
	//	0, 0,
	//	m_pBlendImageHit->nWidth, m_pBlendImageHit->nHeight,

	//	// 대상
	//	m_pBlendImageHit->hMemDC,
	//	0, 0,
	//	PATCOPY);

	//SelectObject(m_pBlendImageHit->hMemDC, oldBrush);
	//DeleteObject(brush);

	// 임시 이미지 준비
	BitBlt(
		// 목적지
		m_pBlendImageHit->hMemDC,
		0, 0,
		m_pBlendImageHit->nWidth, m_pBlendImageHit->nHeight,

		// 대상
		m_pImageInfo->hMemDC,
		0, 0,
		SRCCOPY);

	// 브러시 + 임시
	BitBlt(
		// 목적지
		m_pBlendImageHit->hMemDC,
		0, 0,
		m_pBlendImageHit->nWidth, m_pBlendImageHit->nHeight,

		// 대상
		m_pBlendImageHit->hMemDC,
		0, 0,
		SRCPAINT);

	if (m_isTransparent)
	{
		// 임시 이미지 출력
		GdiTransparentBlt(
			// 목적지
			hdc,
			destX, destY,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			// 대상
			m_pBlendImageHit->hMemDC,
			0, 0,
			m_pBlendImageHit->nWidth, m_pBlendImageHit->nHeight,
			m_transColor);
	}
	else
	{
		// 임시 이미지 출력
		BitBlt(
			// 목적지
			hdc,
			destX, destY,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			// 대상
			m_pBlendImageHit->hMemDC,
			0, 0,
			SRCCOPY);
	}
}

void image::hitFrameRender(HDC hdc, int destX, int destY, int currFrameX, int currFrameY, COLORREF color)
{

	m_pImageInfo->nCurrFrameX = currFrameX;
	m_pImageInfo->nCurrFrameY = currFrameY;

	if (currFrameX > m_pImageInfo->nMaxFrameX)
		m_pImageInfo->nCurrFrameX = m_pImageInfo->nMaxFrameX;
	if (currFrameY > m_pImageInfo->nMaxFrameY)
		m_pImageInfo->nCurrFrameY = m_pImageInfo->nMaxFrameY;


	// 임시 이미지 준비
	BitBlt(
		// 목적지
		m_pBlendImageHit->hMemDC,
		0, 0,
		m_pBlendImageHit->nFrameWidth, m_pBlendImageHit->nFrameHeight,

		// 대상
		m_pImageInfo->hMemDC,
		0, 0,
		SRCCOPY);

	// 브러시 + 임시
	BitBlt(
		// 목적지
		m_pBlendImageHit->hMemDC,
		0, 0,
		m_pBlendImageHit->nFrameWidth, m_pBlendImageHit->nFrameHeight,

		// 대상
		m_pBlendImageHit->hMemDC,
		0, 0,
		SRCPAINT);

	if (m_isTransparent)
	{
		// 임시 이미지 출력
		GdiTransparentBlt(
			// 목적지
			hdc,
			destX, destY,
			m_pImageInfo->nFrameWidth,
			m_pImageInfo->nFrameHeight,	// 복사될 크기

										// 대상
			m_pImageInfo->hMemDC,	// 복사할 대상 DC
			m_pImageInfo->nFrameWidth * m_pImageInfo->nCurrFrameX,
			m_pImageInfo->nFrameHeight * m_pImageInfo->nCurrFrameY,					// 복사될 영역 시작좌표
			m_pImageInfo->nFrameWidth,
			m_pImageInfo->nFrameHeight,	// 복사될 영역지정 좌표
			m_transColor);
	}
	else
	{
		// 임시 이미지 출력
		BitBlt(
			// 목적지
			hdc,
			destX, destY,
			m_pImageInfo->nFrameWidth, m_pImageInfo->nFrameHeight,
			// 대상
			m_pBlendImageHit->hMemDC,
			0, 0,
			SRCCOPY);
	}

}

void image::setTransColor(bool trans, COLORREF transColor)
{
	m_isTransparent = trans;
	m_transColor = transColor;
}

