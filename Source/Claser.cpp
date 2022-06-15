#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Ccharacter.h"
#include "Claser.h"

namespace game_framework {

	Claser::Claser()
	{
		is_alive = true;
		x = y = dx = dy = 0;
		isMovingLeft = false;
		isMovingRight = false;
		movingcheck = false;
	}

	bool Claser::HitEraser(Ccharacter *character)
	{
		// 檢測角色所構成的矩形是否碰到球
		return HitRectangle(character->GetX1() + 5, character->GetY1() + 5, character->GetX2() - 5, character->GetY2() - 5);
	}

	bool Claser::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x + dx;				// 左上角x座標
		int y1 = y + dy;				// 左上角y座標
		int x2 = x1 + laser.Width();	// 右下角x座標
		int y2 = y1 + laser.Height();	// 右下角y座標
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}

	bool Claser::IsAlive()
	{
		return is_alive;
	}

	void Claser::LoadBitmap()
	{
		laser.AddBitmap(".//Bitmaps//laser3.bmp", RGB(255, 255, 255));			// 載入圖形
		laser.AddBitmap(".//Bitmaps//laser6.bmp", RGB(255, 255, 255));			// 載入圖形
		laser.AddBitmap(".//Bitmaps//laser5.bmp", RGB(255, 255, 255));			// 載入圖形
		laser.AddBitmap(".//Bitmaps//laser4.bmp", RGB(255, 255, 255));			// 載入圖形
	}

	void Claser::OnMove()
	{
		laser.OnMove();
		if (!is_alive)
			return;
		if (!cantMoving) {
			if (isMovingRight) {
				direct = 0;
				dx -= 1;
			}
			if (isMovingLeft) {
				direct = 1;
				dx += 1;
			}
			if (!ch_cantMoving) {
				if (direct) {
					dx += 3;
				}
				else {
					dx -= 3;
				}
			}
		}
		else if (movingcheck2 && isMovingRight) {
			dx -= 5;
		}
		else if (movingcheck && isMovingLeft) {
			dx += 5;
		}
	}

	void Claser::SetIsAlive(bool alive)
	{
		is_alive = alive;
	}

	void Claser::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void Claser::OnShow()
	{
		if (is_alive) {
			laser.SetTopLeft(x + dx, y + dy);
			laser.OnShow();
		}
	}
	void Claser::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}

	void Claser::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}
	void Claser::CantMoving(bool flag) {
		cantMoving = flag;
	}
	void Claser::MovingCheck(bool flag, bool flag2) {
		movingcheck = flag;
		movingcheck2 = flag2;
	}
	void Claser::ch_CantMoving(bool flag) {
		ch_cantMoving = flag;
	}
}
