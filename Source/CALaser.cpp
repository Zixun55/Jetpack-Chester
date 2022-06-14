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
	// CALaser: all object class
	/////////////////////////////////////////////////////////////////////////////
	CALaser::CALaser()
	{
		laser = nullptr;       //雷射_橫的
		laser2 = nullptr;      //雷射直的
		boxes = nullptr;       //箱子
		coins = nullptr;       //金幣
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
		///////////////////////////////////////
		//直接把物品定位，設置給所有地圖
		int laserx_1[10] = { 450, 500, 730, 900, 1400, 1600, 1900, 2100, 2400, 2650 };  
		int lasery_1[10] = { 50, 300, 430, 100, 250, 175, 350, 220 , 7 ,213};            
		int laserx_2[10] = { 700, 850, 1100, 1300, 1700, 2200, 2300, 2400, 2500 ,2700};  
		int lasery_2[10] = { 350, 10, 20, 150, 140, 145, 250, 370 ,30 ,230};    

		int lasery_12[10] = { 40, 300, 370, 350, 10, 150, 20, 240, 330, 310};
		int lasery_22[10] = { 200, 10, 100, 250, 380, 150, 290, 10, 240, 5};

		int lasery_13[10] = { 300, 40, 230, 30, 210, 30, 160, 30, 17, 150};
		int lasery_23[10] = { 360, 310, 25, 230, 5, 10, 230, 340 , 240, 230};

		int lasery_14[10] = { 60, 270, 306, 306, 310, 290, 25, 215 , 6, 400};
		int lasery_24[10] = { 220, 5, 110, 30, 3, 140, 180, 312, 23, 120};

		int coinx[10] = { 510, 657, 789, 952, 1243, 1589, 1904, 2175, 2356, 2501 };

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
			boxes[i].SetXY((i + 1) * 1000, 320);
		}
		///////////////////////////////////////
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
	}

	void CALaser::OnMove()
	{
		///////////////////////////////////////
		//判斷箱子碰撞以及其他物件是否能移動
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
		for (int i = 0; i < 10; i++) {
			if (check_box) {
				map.CantMoving(true);
				boxes[i].CantMoving(true);
				laser[i].CantMoving(true);
				laser2[i].CantMoving(true);
				coins[i].CantMoving(true);
				map.MovingCheck(check_chx, check_chx2);
				boxes[i].MovingCheck(check_chx, check_chx2);
				laser[i].MovingCheck(check_chx, check_chx2);
				laser2[i].MovingCheck(check_chx, check_chx2);
				coins[i].MovingCheck(check_chx, check_chx2);
				if (check_ch) {
					chtest.CantMoving(true);
				}
				else {
					chtest.CantMoving(false);
				}
			}
			else if (map.Left_Moving_Start() && isLeft) {
				map.CantMoving(true);
				boxes[i].CantMoving(true);
				laser[i].CantMoving(true);
				laser2[i].CantMoving(true);
				coins[i].CantMoving(true);

				map.MovingCheck(0,0);
				boxes[i].MovingCheck(0,0);
				laser[i].MovingCheck(0,0);
				laser2[i].MovingCheck(0,0);
				coins[i].MovingCheck(0,0);
			}
			else {
				map.CantMoving(false);
				boxes[i].CantMoving(false);
				laser[i].CantMoving(false);
				laser2[i].CantMoving(false);
				coins[i].CantMoving(false);
				map.MovingCheck(check_chx, check_chx2);
				boxes[i].MovingCheck(check_chx, check_chx2);
				laser[i].MovingCheck(check_chx, check_chx2);
				laser2[i].MovingCheck(check_chx, check_chx2);
				coins[i].MovingCheck(check_chx, check_chx2);
				chtest.CantMoving(false);
			}
			boxes[i].OnMove();
		}
		///////////////////////////////////////
		for (int i = 0; i < 10; i++) {
			laser[i].OnMove();
			if (laser[i].IsAlive() && laser[i].HitEraser(&chtest)) {
				laser[i].SetIsAlive(false);                                //如果角色碰到雷射，雷射會消失       
				Life.Add(-1);											   //扣命
				Life.OnMove();                                             //扣命動畫
				audio_laser = true;
			}
		}
		for (int i = 0; i < 10; i++) {
			laser2[i].OnMove();
			if (laser2[i].IsAlive() && laser2[i].HitEraser(&chtest)) {
				laser2[i].SetIsAlive(false);                                //如果角色碰到雷射，雷射會消失
				Life.Add(-1);												//扣命
				Life.OnMove();												//扣命動畫
				audio_laser = true;
			}
		}
		for (int i = 0; i < 10; i++) {
			coins[i].OnMove();
			if (coins[i].IsAlive() && coins[i].HitEraser(&chtest)) {
				coins[i].SetIsAlive(false);                                //如果角色碰到錢幣，錢幣會消失        
				point.Add(1);											   //分數加一
				point.OnMove();											   //加分動畫
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
	int CALaser::GetLife_n() {   //當前生命值
		return Life.get_n();
	}
	int CALaser::Getpoint_n() {  //當前分數
		return point.get_n();
	}

	void CALaser::SetMovingLeft(bool flag) {  //按下方向鍵左鍵
		isLeft = true;
		map.SetMovingLeft(flag);
		chtest.SetMovingLeft(flag);
		for (int i = 0; i < 10; i++) {
			laser[i].SetMovingLeft(flag);
			laser2[i].SetMovingLeft(flag);
			coins[i].SetMovingLeft(flag);
			boxes[i].SetMovingLeft(flag);
		}
	}
	void CALaser::SetMovingRight(bool flag) {  //按下方向鍵右鍵
		isLeft = false;
		map.SetMovingRight(flag);
		chtest.SetMovingRight(flag);
		for (int i = 0; i < 10; i++) {
			laser[i].SetMovingRight(flag);
			laser2[i].SetMovingRight(flag);
			coins[i].SetMovingRight(flag);
			boxes[i].SetMovingRight(flag);
		}
	}
	bool CALaser::Audio_Laser() {  //播放雷射音效
		return audio_laser;
	}
	bool CALaser::Audio_Coin() {   //播放金幣音效
		return audio_coin;
	}
	void CALaser::SetAudioLaser(bool flag) {
		audio_laser = flag;
	}
	void CALaser::SetAudioCoin(bool flag) {
		audio_coin = flag;
	}
	bool CALaser::map_finish_map() {//地圖是否完成
		return map.FinishMap();
	}
}