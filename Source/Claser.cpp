#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Ccharacter.h"
#include "Claser.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CBall: Ball class
	/////////////////////////////////////////////////////////////////////////////

	Claser::Claser()
	{
		is_alive = true;
		x = y = dx = dy = index = delay_counter = 0;
		isMovingLeft = false;
		isMovingRight = false;
	}

	bool Claser::HitEraser(Ccharacter *character)
	{
		// �˴����l�Һc�����x�άO�_�I��y
		return HitRectangle(character->GetX1(), character->GetY1(),character->GetX2(), character->GetY2());
	}

	bool Claser::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x + dx;				// �y�����W��x�y��
		int y1 = y + dy;				// �y�����W��y�y��
		int x2 = x1 + laser.Width();	// �y���k�U��x�y��
		int y2 = y1 + laser.Height();	// �y���k�U��y�y��
									//
									// �˴��y���x�λP�ѼƯx�άO�_���涰
									//
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}

	bool Claser::IsAlive()
	{
		return is_alive;
	}

	void Claser::LoadBitmap()
	{
		laser.AddBitmap(".//Bitmaps//laser3.bmp", RGB(255, 255, 255));			// ���J�y���ϧ�
		laser.AddBitmap(".//Bitmaps//laser6.bmp", RGB(255, 255, 255));			// ���J�y���ϧ�
		laser.AddBitmap(".//Bitmaps//laser5.bmp", RGB(255, 255, 255));			// ���J�y���ϧ�
		laser.AddBitmap(".//Bitmaps//laser4.bmp", RGB(255, 255, 255));			// ���J�y���ϧ�
	}

	void Claser::OnMove()
	{
		laser.OnMove();
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
		//delay_counter--;
		//if (delay_counter < 0) {
			//delay_counter = delay;
			//
			// �p��y�V����ߪ��첾�qdx, dy
			//
			//const int STEPS = 18;
			//static const int DIFFX[] = { 35, 32, 26, 17, 6, -6, -17, -26, -32, -34, -32, -26, -17, -6, 6, 17, 26, 32, };
			//static const int DIFFY[] = { 0, 11, 22, 30, 34, 34, 30, 22, 11, 0, -11, -22, -30, -34, -34, -30, -22, -11, };
			//index++;
			//if (index >= STEPS)
				//index = 0;
			//dx = DIFFX[index];
		//	dy = DIFFY[index];
		//}
	}

	void Claser::SetDelay(int d)
	{
		delay = d;
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
}
