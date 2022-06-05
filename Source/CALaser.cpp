#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "Ccharacter.h"
#include "CBox.h"
#include "CBlock.h"
#include "Claser.h"
#include "CMap.h"
#include "CALaser.h"
#include "math.h"


namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CEraser: Eraser class
	/////////////////////////////////////////////////////////////////////////////

	CALaser::CALaser()
	{
		laser = nullptr;
		laser2 = nullptr;
		boxes = nullptr;
		coins = nullptr;
	}
	CALaser::~CALaser() {
		if (laser != nullptr) delete[] laser;
		if (laser2 != nullptr) delete[] laser2;
		if (boxes != nullptr) delete[] boxes;
		if (coins != nullptr) delete[] coins;
	}


	void CALaser::Initialize(int maps)
	{
		if (laser != nullptr) delete[] laser;
		if (laser2 != nullptr) delete[] laser2;
		if (boxes != nullptr) delete[] boxes;
		if (coins != nullptr) delete[] coins;
		laser = new CBlock[10];
		laser2 = new Claser[10];
		boxes = new CBox[10];
		coins = new Ccoin[10];
		this->LoadBitmap();
		int laserx_1[10] = { 450, 500, 730, 900, 1400, 1600, 1900, 2100, 2400, 2650 };
		int lasery_1[10] = { 50, 300, 430, 50, 450, 175, 350, 220 , 7 ,213 };
		int laserx_2[10] = { 700, 850, 1100, 1300, 1700, 2200, 2300, 2400, 2500 ,2700 };
		int lasery_2[10] = { 350, 10, 2, 150, 140, 175, 350, 370 ,30 ,230 };

		int lasery_12[10] = { 40, 400, 370, 350, 10, 150, 20, 240, 110, 310 };
		int lasery_22[10] = { 240, 10, 100, 250, 380, 150, 250, 300, 220, 124 };

		int lasery_13[10] = { 300, 40, 270, 30, 380, 30, 360, 230, 17, 150 };
		int lasery_23[10] = { 360, 310, 0, 230, 5, 150, 230, 340 , 40, 123 };

		int lasery_14[10] = { 260, 15, 336, 320, 480, 290, 5, 224 , 6, 400 };
		int lasery_24[10] = { 320, 5, 110, 0, 3, 140, 160, 312, 23, 300 };
		int coinx[10] = { 510, 700, 825, 1350, 1575, 2333, 2668, 3212, 3924, 4354 };
		int coiny[10] = { 150, 30, 110, 150, 230, 90, 50, 135, 200, 140 };
		if (maps == 2) {
			for (int i = 0; i < 10; i++) {
				lasery_1[i] = lasery_12[i];
				lasery_2[i] = lasery_22[i];
			}
		}
		else if (maps == 3) {
			for (int i = 0; i < 10; i++) {
				lasery_1[i] = lasery_13[i];
				lasery_2[i] = lasery_23[i];
			}
		}
		else if (maps == 4) {
			for (int i = 0; i < 10; i++) {
				lasery_1[i] = lasery_14[i];
				lasery_2[i] = lasery_24[i];
			}
		}
		for (int i = 0; i < 10; i++) {
			laser[i].SetXY(laserx_1[i], lasery_1[i]);
			laser[i].SetIsAlive(true);
			laser2[i].SetXY(laserx_2[i], lasery_2[i]);
			laser2[i].SetIsAlive(true);
			coins[i].SetXY(coinx[i], coiny[i]);
			coins[i].SetIsAlive(true);
		}
		for (int i = 0; i < 10; i++) {
			boxes[i].SetXY((i + 1) * 1000, 280);
		}
		chtest.Initialize();
		map.Initialize();
		map.chooseMap(maps);
		isLeft = isRight = cantMoving = false;
		Life.Reset();
		Life.set_n(3);
		point.Reset();
		point.set_n(0);
	}

	void CALaser::LoadBitmap()
	{
		if (!isLoadBitmap) {
			map.LoadBitmap();
			chtest.LoadBitmap();
			Life.LoadBitmap();
			point.LoadBitmap();
		}
		for (int i = 0; i < 10; i++) {
			laser[i].LoadBitmap();
		}
		for (int i = 0; i < 10; i++) {
			laser2[i].LoadBitmap();
		}
		for (int i = 0; i < 10; i++) {
			coins[i].LoadBitmap();
		}
		for (int i = 0; i < 10; i++) {
			boxes[i].LoadBitmap();
		}
		isLoadBitmap = true;
		//}
	}

	void CALaser::OnMove()
	{
		int check_box = 0;
		int check_ch = 0;
		for (int i = 0; i < 10; i++) {
			if (boxes[i].HitEraser(&chtest)) {
				check_box = 1;
			}
		}
		int close_box = ClosestBox();
		if (boxes[close_box].ChxBigThanBox(&chtest)) {
			check_ch = 1;
		}
		check_chx = false;
		if (boxes[close_box].ChxXBigThanBox(&chtest)) {
			check_chx = true;
		}
		check_chx2 = false;
		if (boxes[close_box].ChxXSmallThanBox(&chtest)) {
			check_chx2 = true;
		}
		check_map = check_box;
		for (int i = 0; i < 10; i++) {
			if (check_box) {
				map.CantMoving(true);
				boxes[i].CantMoving(true);
				laser[i].CantMoving(true);
				laser2[i].CantMoving(true);
				coins[i].CantMoving(true);
				boxes[i].MovingCheck(check_chx, check_chx2);
				//laser[i].MovingCheck(check_chx);
				//laser2[i].MovingCheck(check_chx);
				if (check_ch) {
					chtest.CantMoving(true);
				}
				else {
					chtest.CantMoving(false);
				}
			}
			else {
				map.CantMoving(false);
				boxes[i].CantMoving(false);
				laser[i].CantMoving(false);
				laser2[i].CantMoving(false);
				coins[i].CantMoving(false);
				boxes[i].MovingCheck(check_chx, check_chx2);
				//laser[i].MovingCheck(check_chx);
				//laser2[i].MovingCheck(check_chx);
				chtest.CantMoving(false);
			}
			boxes[i].OnMove();
		}
		for (int i = 0; i < 10; i++) {
			laser[i].OnMove();
			if (laser[i].IsAlive() && laser[i].HitEraser(&chtest)) {
				laser[i].SetIsAlive(false);                                //�p�G����I��p�g�A�p�g�|����       
				Life.Add(-1);
				Life.OnMove();                                             //���R
				audio_laser = true;
			}
		}
		for (int i = 0; i < 10; i++) {
			laser2[i].OnMove();
			if (laser2[i].IsAlive() && laser2[i].HitEraser(&chtest)) {
				laser2[i].SetIsAlive(false);                                //�p�G����I��p�g�A�p�g�|����
				Life.Add(-1);                                        //���R
				Life.OnMove();
				audio_laser = true;
			}
		}
		for (int i = 0; i < 10; i++) {
			coins[i].OnMove();
			if (coins[i].IsAlive() && coins[i].HitEraser(&chtest)) {
				coins[i].SetIsAlive(false);                                //�p�G����I������A�����|����        
				point.Add(1);
				point.OnMove();
				audio_coin = true;
			}
		}
		map.OnMove();
		chtest.OnMove();
		check_box = 0;
		check_ch = 0;
	}
	void CALaser::OnShow()
	{
		map.OnShow();
		chtest.OnShow();
		for (int i = 0; i < 10; i++) {
			laser[i].OnShow();
			laser2[i].OnShow();
			coins[i].OnShow();
			boxes[i].OnShow();
		}
		Life.OnShow();
		point.OnShow();
	}
	void CALaser::CantMoving(bool flag) {
		cantMoving = flag;
	}
	int  CALaser::ClosestBox() {
		int x[100][100];
		for (int i = 0; i < 10; i++) {
			x[i][0] = abs(boxes[i].BoxX1() - chtest.GetX2());
			x[i][1] = i;
		}
		int min = x[0][0];
		int closet = 0;
		for (int i = 1; i < 10; i++)
		{
			if (x[i][0] < min) {
				min = x[i][0];
				closet = x[i][1];
			}
		}
		return closet;
	}
	int CALaser::GetLife_n() {
		return Life.get_n();
	}
	int CALaser::Getpoint_n() {
		return point.get_n();
	}
	int CALaser::GetCheck_map() {
		return check_map;
	}


	void CALaser::SetMovingLeft(bool flag) {
		map.SetMovingLeft(flag);
		chtest.SetMovingLeft(flag);
		for (int i = 0; i < 10; i++) {
			laser[i].SetMovingLeft(flag);
			laser2[i].SetMovingLeft(flag);
			coins[i].SetMovingLeft(flag);
			boxes[i].SetMovingLeft(flag);
		}
	}
	void CALaser::SetMovingRight(bool flag) {
		map.SetMovingRight(flag);
		chtest.SetMovingRight(flag);
		for (int i = 0; i < 10; i++) {
			laser[i].SetMovingRight(flag);
			laser2[i].SetMovingRight(flag);
			coins[i].SetMovingRight(flag);
			boxes[i].SetMovingRight(flag);
		}
	}
	bool CALaser::Get_check_chx() {
		return check_chx;
	}
	bool CALaser::Audio_Laser() {
		return audio_laser;
	}
	bool CALaser::Audio_Coin() {
		return audio_coin;
	}
	void CALaser::SetAudioLaser(bool flag) {
		audio_laser = flag;
	}
	void CALaser::SetAudioCoin(bool flag) {
		audio_coin = flag;
	}
	bool CALaser::map_finish_map() {
		return map.FinishMap();
	}
}