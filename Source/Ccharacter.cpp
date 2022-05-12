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
		animation.SetDelayCount(1);
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
		const int X_POS = 340; //340
		const int Y_POS = 414;
		x = X_POS;
		y = Y_POS;
		isMovingLeft = isMovingRight = cantMoving = false;
	}

	void Ccharacter::LoadBitmap()
	{
		animation.AddBitmap(".\\Bitmaps\\character.bmp", RGB(255, 255, 255));
		animation.AddBitmap(".\\Bitmaps\\characterreverse.bmp", RGB(255, 255, 255));
		steam.LoadBitmap(".\\Bitmaps\\steam.bmp", RGB(255, 255, 255));
		steam1.LoadBitmap(".\\Bitmaps\\steam1.bmp", RGB(255, 255, 255));
		steam2.LoadBitmap(".\\Bitmaps\\steam2.bmp", RGB(255, 255, 255));
		steamR.LoadBitmap(".\\Bitmaps\\steamreverse.bmp", RGB(255, 255, 255));
		steamR1.LoadBitmap(".\\Bitmaps\\steamreverse1.bmp", RGB(255, 255, 255));
		steamR2.LoadBitmap(".\\Bitmaps\\steamreverse2.bmp", RGB(255, 255, 255));
		counter = 1;
	}

	void Ccharacter::OnMove()
	{
		counter++;
		if (counter > 9) {
			counter = 1;
		}
		const int STEP_SIZE = 20;
		if (y <= 0 && isMovingLeft) {
			y = 0;
			if (con) {
				animation.OnMove();
				con = false;
			}
		}
		if (y <= 0 && isMovingRight) {
			y = 0;
			if (!con) {
				animation.Reset();
				con = true;
			}
		}
		else {
			if (isMovingLeft) {
				y -= STEP_SIZE;
				if (con) {
					animation.OnMove();
					con = false;
				}
			}
			if (isMovingRight) {
				y -= STEP_SIZE;
				if (!con) {
					animation.Reset();
					con = true;
				}
			}
			if (!cantMoving) {
				if (GetY2() < 512) {
					y += 7;
				}
			}
		}
		//if (x != 340) {
			//if (isMovingLeft) {
				//x -= 5;
			//}
			//if (isMovingRight) {
				//x += 5;
			//}
		//}
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
		if (isMovingRight && isMovingLeft) {
			if(con){
				if (counter > 0 && counter < 4) {
					steam.SetTopLeft(x - animation.Width() + 40, y + animation.Height() - 10);
					steam.ShowBitmap();
				}
				else if (counter > 3 && counter < 7) {
					steam1.SetTopLeft(x - animation.Width() + 40, y + animation.Height() - 10);
					steam1.ShowBitmap();
				}
				else {
					steam2.SetTopLeft(x - animation.Width() + 40, y + animation.Height() - 10);
					steam2.ShowBitmap();
				}
			}
			if (!con) {
				if (counter > 0 && counter < 4) {
					steamR.SetTopLeft(x + animation.Width() - 5, y + animation.Height() - 10);
					steamR.ShowBitmap();
				}
				else if (counter > 3 && counter < 7) {
					steamR1.SetTopLeft(x + animation.Width() - 5, y + animation.Height() - 10);
					steamR1.ShowBitmap();
				}
				else {
					steamR2.SetTopLeft(x + animation.Width() - 5, y + animation.Height() - 10);
					steamR2.ShowBitmap();
				}
			}
		}
		else {
			if (isMovingRight) {
				if (counter > 0 && counter < 4) {
					steam.SetTopLeft(x - animation.Width() + 40, y + animation.Height() - 10);
					steam.ShowBitmap();
				}
				else if (counter > 3 && counter < 7) {
					steam1.SetTopLeft(x - animation.Width() + 40, y + animation.Height() - 10);
					steam1.ShowBitmap();
				}
				else {
					steam2.SetTopLeft(x - animation.Width() + 40, y + animation.Height() - 10);
					steam2.ShowBitmap();
				}
			}
			if (isMovingLeft) {
				if (counter > 0 && counter < 4) {
					steamR.SetTopLeft(x + animation.Width() - 5, y + animation.Height() - 10);
					steamR.ShowBitmap();
				}
				else if (counter > 3 && counter < 7) {
					steamR1.SetTopLeft(x + animation.Width() - 5, y + animation.Height() - 10);
					steamR1.ShowBitmap();
				}
				else {
					steamR2.SetTopLeft(x + animation.Width() - 5, y + animation.Height() - 10);
					steamR2.ShowBitmap();
				}
			}
		}
		animation.SetTopLeft(x, y);
		animation.OnShow();
	}
	void Ccharacter::CantMoving(bool flag) {
		cantMoving = flag;
	}
}