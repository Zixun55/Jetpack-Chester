#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Ccharacter.h"
#include "Ccoin.h"

namespace game_framework {

	Ccoin::Ccoin()
	{
		is_alive = true;
		x = y = dx = dy = 0;
		isMovingLeft = false;
		isMovingRight = false;
		movingcheck = false;
	}

	bool Ccoin::HitEraser(Ccharacter *character)
	{
		return HitRectangle(character->GetX1()+5, character->GetY1()+5, character->GetX2()-10, character->GetY2()-10);
	}

	bool Ccoin::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x + dx;				// ���W��x�y��
		int y1 = y + dy;				// ���W��y�y��
		int x2 = x1 + coin.Width();		// �k�U��x�y��
		int y2 = y1 + coin.Height();	// �k�U��y�y��

		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}

	bool Ccoin::IsAlive()
	{
		return is_alive;
	}

	void Ccoin::LoadBitmap()
	{
		coin.AddBitmap(".//Bitmaps//coin.bmp", RGB(255, 255, 255));				// ���J�ϧ�
		coin.AddBitmap(".//Bitmaps//coin1.bmp", RGB(255, 255, 255));			// ���J�ϧ�
		coin.AddBitmap(".//Bitmaps//coin2.bmp", RGB(255, 255, 255));			// ���J�ϧ�
		coin.AddBitmap(".//Bitmaps//coin3.bmp", RGB(255, 255, 255));			// ���J�ϧ�
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
		else if (movingcheck2 && isMovingRight) {
			dx -= 5;
		}
		else if (movingcheck && isMovingLeft) {
			dx += 5;
		}
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
	void Ccoin::MovingCheck(bool flag, bool flag2) {
		movingcheck = flag;
		movingcheck2 = flag2;
	}
}
