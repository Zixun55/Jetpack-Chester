#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "Ccharacter.h"
#include "CBox.h"
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
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = cantMoving = false;
		movingcheck = false;
	}

	void CMap::LoadBitmap()
	{
		animation.SetDelayCount(1);
		animation.AddBitmap(".\\Bitmaps\\bg12.bmp");
		animation.AddBitmap(".\\Bitmaps\\bg22.bmp");
		animation.AddBitmap(".\\Bitmaps\\bg32.bmp");
		animation.AddBitmap(".\\Bitmaps\\bg42.bmp");
	}

	void CMap::OnMove()
	{
		const int STEP_SIZE = 5;
		if (x < 100) {
			if (isMovingLeft && x >= 0) {
				x = 0;
			}
			else if (isMovingRight && x <= -2324) {
				x = -2324;
			}
			else {
				if (!cantMoving) {
					if (isMovingLeft) {
						x += STEP_SIZE;
					}
					if (isMovingRight) {

						x -= STEP_SIZE;
					}
				}
				else if (movingcheck2 && isMovingRight) {
					x -= STEP_SIZE;
				}
				else if (movingcheck && isMovingLeft) {
					x += STEP_SIZE;
				}
			}
		}
		if (map == 1) {
			animation.Reset();
			map = 0;
		}
		else if (map == 2) {
			animation.Reset();
			animation.OnMove();
			map = 0;
		}
		else if (map == 3) {
			animation.Reset();
			animation.OnMove();
			animation.OnMove();
			map = 0;
		}
		else if (map == 4) {
			animation.Reset();
			animation.OnMove();
			animation.OnMove();
			animation.OnMove();
			map = 0;
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
	void CMap::CantMoving(bool flag) {
		cantMoving = flag;
	}
	void CMap::chooseMap(int maps) {
		map = maps;
	}
	void CMap::MovingCheck(bool flag, bool flag2) {
		movingcheck = flag;
		movingcheck2 = flag2;
	}
	bool CMap::FinishMap() {
		return x <= -2324;
	}
}