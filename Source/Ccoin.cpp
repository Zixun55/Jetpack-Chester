#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Ccharacter.h"
#include "Ccoin.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CBall: Ball class
	/////////////////////////////////////////////////////////////////////////////

	Ccoin::Ccoin()
	{
		is_alive = true;
		x = y = dx = dy = index = delay_counter = 0;
		isMovingLeft = false;
		isMovingRight = false;
		movingcheck = false;
	}

	bool Ccoin::HitEraser(Ccharacter *character)
	{
		// 檢測擦子所構成的矩形是否碰到球
		return HitRectangle(character->GetX1(), character->GetY1(), character->GetX2(), character->GetY2());
	}

	bool Ccoin::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x + dx;				// 球的左上角x座標
		int y1 = y + dy;				// 球的左上角y座標
		int x2 = x1 + coin.Width();	// 球的右下角x座標
		int y2 = y1 + coin.Height();	// 球的右下角y座標
									//
									// 檢測球的矩形與參數矩形是否有交集
									//
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}

	bool Ccoin::IsAlive()
	{
		return is_alive;
	}

	void Ccoin::LoadBitmap()
	{
		coin.AddBitmap(".//Bitmaps//coin.bmp", RGB(255, 255, 255));			// 載入球的圖形
		coin.AddBitmap(".//Bitmaps//coin1.bmp", RGB(255, 255, 255));			// 載入球的圖形
		coin.AddBitmap(".//Bitmaps//coin2.bmp", RGB(255, 255, 255));			// 載入球的圖形
		coin.AddBitmap(".//Bitmaps//coin3.bmp", RGB(255, 255, 255));			// 載入球的圖形
	}

	void Ccoin::OnMove()
	{
		coin.OnMove();
		if (!is_alive)
			return;
		if (!cantMoving) {
			if (isMovingRight) {
				dx -= 5;
			}
			if (isMovingLeft) {
				dx += 5;
			}
		}
		else if (movingcheck && isMovingRight) {
			dx -= 5;
		}
		else if (movingcheck && isMovingRight) {
			dx += 5;
		}
	}

	void Ccoin::SetDelay(int d)
	{
		delay = d;
	}

	void Ccoin::SetIsAlive(bool alive)
	{
		is_alive = alive;
	}

	void Ccoin::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void Ccoin::OnShow()
	{
		if (is_alive) {
			coin.SetTopLeft(x + dx, y + dy);
			coin.OnShow();
		}
	}
	void Ccoin::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}

	void Ccoin::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}
	void Ccoin::CantMoving(bool flag) {
		cantMoving = flag;
	}
	void Ccoin::MovingCheck(bool flag) {
		movingcheck = flag;
	}
}
