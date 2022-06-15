#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Ccharacter.h"
#include "CBlock.h"

namespace game_framework {

	CBlock::CBlock()
	{
		is_alive = true;
		x = y = dx = dy = 0;
		isMovingLeft = false;
		isMovingRight = false;
		movingcheck = false;
	}

	bool CBlock::HitEraser(Ccharacter *character)
	{
		// 檢測角色所構成的矩形是否碰到碰撞物
		return HitRectangle(character->GetX1() + 5, character->GetY1() + 5, character->GetX2() - 5, character->GetY2() - 5);
	}

	bool CBlock::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x + dx;				// 左上角x座標
		int y1 = y + dy;				// 左上角y座標
		int x2 = x1 + laser.Width();	// 右下角x座標
		int y2 = y1 + laser.Height();	// 右下角y座標
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}

	bool CBlock::IsAlive()
	{
		return is_alive;
	}

	void CBlock::LoadBitmap()
	{
		laser.AddBitmap(".//Bitmaps//laser.bmp", RGB(255, 255, 255));			// 載入圖形
		laser.AddBitmap(".//Bitmaps//laser8.bmp", RGB(255, 255, 255));			// 載入圖形
		laser.AddBitmap(".//Bitmaps//laser7.bmp", RGB(255, 255, 255));			// 載入圖形
		laser.AddBitmap(".//Bitmaps//laser2.bmp", RGB(255, 255, 255));			// 載入圖形
	}

	void CBlock::OnMove()
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

	void CBlock::SetIsAlive(bool alive)
	{
		is_alive = alive;
	}

	void CBlock::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void CBlock::OnShow()
	{
		if (is_alive) {
			laser.SetTopLeft(x + dx, y + dy);
			laser.OnShow();
		}
	}
	void CBlock::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}

	void CBlock::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}
	void CBlock::CantMoving(bool flag) {
		cantMoving = flag;
	}
	void CBlock::MovingCheck(bool flag, bool flag2) {
		movingcheck = flag;
		movingcheck2 = flag2;
	}
	void CBlock::ch_CantMoving(bool flag) {
		ch_cantMoving = flag;
	}
}
