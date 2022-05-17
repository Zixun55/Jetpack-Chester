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
		// �˴����l�Һc�����x�άO�_�I��y
		return HitRectangle(character->GetX1(), character->GetY1(), character->GetX2(), character->GetY2());
	}

	bool Ccoin::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x + dx;				// �y�����W��x�y��
		int y1 = y + dy;				// �y�����W��y�y��
		int x2 = x1 + coin.Width();	// �y���k�U��x�y��
		int y2 = y1 + coin.Height();	// �y���k�U��y�y��
									//
									// �˴��y���x�λP�ѼƯx�άO�_���涰
									//
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}

	bool Ccoin::IsAlive()
	{
		return is_alive;
	}

	void Ccoin::LoadBitmap()
	{
		coin.AddBitmap(".//Bitmaps//coin.bmp", RGB(255, 255, 255));			// ���J�y���ϧ�
		coin.AddBitmap(".//Bitmaps//coin1.bmp", RGB(255, 255, 255));			// ���J�y���ϧ�
		coin.AddBitmap(".//Bitmaps//coin2.bmp", RGB(255, 255, 255));			// ���J�y���ϧ�
		coin.AddBitmap(".//Bitmaps//coin3.bmp", RGB(255, 255, 255));			// ���J�y���ϧ�
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
