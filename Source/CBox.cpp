#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Ccharacter.h"
#include "CBox.h"

namespace game_framework {


	CBox::CBox()
	{
		is_alive = true;
		x = y = dx = dy = 0;
		isMovingLeft = cantMoving = isMovingRight = false;
	}

	bool CBox::HitEraser(Ccharacter *character)
	{
		return HitRectangle(character->GetX1(), character->GetY1(), character->GetX2(), character->GetY2());
	}

	bool CBox::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x + dx;				// �y�����W��x�y��
		int y1 = y + dy;				// �y�����W��y�y��
		int x2 = x1 + bmp.Width();	// �y���k�U��x�y��
		int y2 = y1 + bmp.Height();	// �y���k�U��y�y��
									//
									// �˴��y���x�λP�ѼƯx�άO�_���涰
									//
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}
	bool CBox::ChxBigThanBox(Ccharacter *character) {
		return character->GetX2() > (x + dx) && character->GetY2() <= (y + dy + 8);
	}
	int  CBox::BoxX1() {
		return x + dx;
	}
	bool CBox::IsAlive()
	{
		return is_alive;
	}

	void CBox::LoadBitmap()
	{
		bmp.AddBitmap(".//Bitmaps//boxes.bmp", RGB(255, 255, 255));			// ���J�y���ϧ�
	}

	void CBox::OnMove()
	{
		if (!cantMoving) {
			if (isMovingRight) {
				dx -= 5;
			}
			if (isMovingLeft) {
				dx += 5;
			}
		}
	}
	void CBox::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}
	void CBox::OnShow()
	{
		bmp.SetTopLeft(x + dx, y + dy);
		bmp.OnShow();
	}
	void CBox::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}

	void CBox::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}
	void CBox::CantMoving(bool flag) {
		cantMoving = flag;
	}
}
