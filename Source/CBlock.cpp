#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Ccharacter.h"
#include "CBlock.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CBall: Ball class
	/////////////////////////////////////////////////////////////////////////////

	CBlock::CBlock()
	{
		is_alive = true;
		x = y = dx = dy = index = delay_counter = 0;
		isMovingLeft = false;
		isMovingRight = false;
		movingcheck = false;
	}

	bool CBlock::HitEraser(Ccharacter *character)
	{
		// �˴����l�Һc�����x�άO�_�I��y
		return HitRectangle(character->GetX1(), character->GetY1(),character->GetX2(), character->GetY2());
	}

	bool CBlock::HitRectangle(int tx1, int ty1, int tx2, int ty2)
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

	bool CBlock::IsAlive()
	{
		return is_alive;
	}

	void CBlock::LoadBitmap()
	{
		laser.AddBitmap(".//Bitmaps//laser.bmp", RGB(255, 255, 255));			// ���J�y���ϧ�
		laser.AddBitmap(".//Bitmaps//laser8.bmp", RGB(255, 255, 255));			// ���J�y���ϧ�
		laser.AddBitmap(".//Bitmaps//laser7.bmp", RGB(255, 255, 255));			// ���J�y���ϧ�
		laser.AddBitmap(".//Bitmaps//laser2.bmp", RGB(255, 255, 255));			// ���J�y���ϧ�
	}

	void CBlock::OnMove()
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
		else if (movingcheck2 && isMovingRight) {
			dx -= 5;
		}
		else if (movingcheck && isMovingLeft) {
			dx += 5;
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

	void CBlock::SetDelay(int d)
	{
		delay = d;
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
}
