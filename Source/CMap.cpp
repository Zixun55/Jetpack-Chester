#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CMap.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CEraser: Eraser class
	/////////////////////////////////////////////////////////////////////////////

	CMap::CMap()
	{
		Initialize();
	}

	int CMap::GetX1()
	{
		return x;
	}

	int CMap::GetY1()
	{
		return y;
	}

	int CMap::GetX2()
	{
		return x + animation.Width();
	}

	int CMap::GetY2()
	{
		return y + animation.Height();
	}

	void CMap::Initialize()
	{
		const int X_POS = 0;
		const int Y_POS = 0;
		x = X_POS;
		y = Y_POS;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
	}

	void CMap::LoadBitmap()
	{
		animation.AddBitmap(".\\Bitmaps\\bg12.bmp", RGB(255, 255, 255));

	}

	void CMap::OnMove()
	{
		const int STEP_SIZE = 5;
		animation.OnMove();
		if (x < 100) {
			if (isMovingLeft && x >= 0) {
				x = 0;
			}
			else if (isMovingRight && x <= -2324) {
				x = -2324;
			}
			else {
				if (isMovingLeft) {
					x += STEP_SIZE;
				}
				if (isMovingRight) {

					x -= STEP_SIZE;
				}
			}
		}
	}


	void CMap::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}

	void CMap::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}

	void CMap::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void CMap::OnShow()
	{
		animation.SetTopLeft(x, y);
		animation.OnShow();
	}
}