#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Ccharacter.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CEraser: Eraser class
	/////////////////////////////////////////////////////////////////////////////

	Ccharacter::Ccharacter()
	{
		Initialize();
	}

	int Ccharacter::GetX1()
	{
		return x;
	}

	int Ccharacter::GetY1()
	{
		return y;
	}

	int Ccharacter::GetX2()
	{
		return x + animation.Width();
	}

	int Ccharacter::GetY2()
	{
		return y + animation.Height();
	}

	void Ccharacter::Initialize()
	{
		const int X_POS = 340;
		const int Y_POS = 414;
		x = X_POS;
		y = Y_POS;
		isMovingLeft = isMovingRight = false;
	}

	void Ccharacter::LoadBitmap()
	{
		animation.AddBitmap(".\\Bitmaps\\ch2.bmp", RGB(255, 255, 255));
		steam.LoadBitmap(".\\Bitmaps\\steam.bmp", RGB(255, 255, 255));
	}

	void Ccharacter::OnMove()
	{
		const int STEP_SIZE = 20;
		animation.OnMove();
		if (y <= 0 && isMovingLeft) {
			y = 0;
		}
		if (y <= 0 && isMovingRight) {
			y = 0;
		}
		else {
			if (isMovingLeft) {
				y -= STEP_SIZE;
			}
			if (isMovingRight) {
				y -= STEP_SIZE;
			}
			if (GetY2() < 512) {
				y += 7;
			}
		}
	}


	void Ccharacter::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}

	void Ccharacter::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}



	void Ccharacter::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void Ccharacter::OnShow() // ¦w¦w 
	{
		if (isMovingLeft) {
			steam.SetTopLeft(x - animation.Width() + 30, y + animation.Height() - 10);
			steam.ShowBitmap();
		}
		if (isMovingRight) {
			steam.SetTopLeft(x + animation.Width() - 30, y + animation.Height() - 10);
			steam.ShowBitmap();
		}
		animation.SetTopLeft(x, y);
		animation.OnShow();
	}
}