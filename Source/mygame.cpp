/*
 * mygame.cpp: 本檔案儲遊戲本身的class的implementation
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * History:
 *   2002-03-04 V3.1
 *          Add codes to demostrate the use of CMovingBitmap::ShowBitmap(CMovingBitmap &).
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *      2. Demo the use of CInteger in CGameStateRun.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *      1. Add codes to display IDC_GAMECURSOR in GameStateRun.
 *   2006-02-08 V4.2
 *      1. Revise sample screens to display in English only.
 *      2. Add code in CGameStateInit to demo the use of PostQuitMessage().
 *      3. Rename OnInitialUpdate() -> OnInit().
 *      4. Fix the bug that OnBeginState() of GameStateInit is not called.
 *      5. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      6. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2006-12-30
 *      1. Bug fix: fix a memory leak problem by replacing PostQuitMessage(0) as
 *         PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0).
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress.
 *   2010-03-23 V4.6
 *      1. Demo MP3 support: use lake.mp3 to replace lake.wav.
*/
//commit test
#include <ctime> 
#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"
#include <stdlib.h>

////////////////////////////////
// 全域變數
////////////////////////////////
int scores;           // 分數
int maps;			  // 選擇的地圖
bool isFinish = false;// 是否有成功完成地圖


namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲開頭畫面物件
	/////////////////////////////////////////////////////////////////////////////

	CGameStateInit::CGameStateInit(CGame *g)
		: CGameState(g)
	{
	}

	void CGameStateInit::OnInit()
	{
		ShowInitProgress(0);	
		//
		// 開始載入資料
		//
		title.LoadBitmap(".\\Bitmaps\\background_true.bmp");
		start.LoadBitmap(".\\Bitmaps\\background_startbutton.bmp", RGB(255, 255, 255));
		start_dark.LoadBitmap(".\\Bitmaps\\background_startbutton_dark.bmp", RGB(255, 255, 255));
		intro.LoadBitmap(".\\Bitmaps\\background_instructionbutton.bmp", RGB(255, 255, 255));
		intro_dark.LoadBitmap(".\\Bitmaps\\background_instructionbutton_dark.bmp", RGB(255, 255, 255));
		instructions.LoadBitmap(".\\Bitmaps\\instruction.bmp", RGB(255, 255, 255));
		CAudio::Instance()->Load(99, "sounds\\button.mp3");	// 載入按鈕聲音
	}

	void CGameStateInit::OnBeginState()
	{
		in = false;
		intro_in = intro_view = false;
	}
	void CGameStateInit::OnMouseMove(UINT nFlags, CPoint point)
	{
		CPoint start0(243, 250);
		CPoint start_intro_point(243, 350);
		int allx = 296;
		int ally = 87;
		CPoint new_point = point - start0;
		CPoint intro_point = point - start_intro_point;
		if (new_point.x > 0 && new_point.y > 0) {
			if (new_point.x < allx && new_point.y < ally) {
				in = true;
				CAudio::Instance()->Play(99);
			}
			else {
				in = false;
			}
		}
		else
		{
			in = false;
		}
		if (intro_point.x > 0 && intro_point.y > 0) {
			if (intro_point.x < allx && intro_point.y < ally) {
				intro_in = true;
				CAudio::Instance()->Play(99);
			}
			else {
				intro_in = false;
			}
		}
		else
		{
			intro_in = false;
		}
	}
	void CGameStateInit::OnLButtonUp(UINT nFlags, CPoint point)
	{
		CPoint start0(243, 250);
		CPoint start1(539, 337);
		CPoint new_point = point - start0;
		int allx = 539 - 243;
		int ally = 337 - 250;
		if (new_point.x > 0 && new_point.y > 0) {
			if (new_point.x < allx && new_point.y < ally) {
				GotoGameState(GAME_STATE_CHOOSE);		// 切換至GAME_STATE_RUN
			}
		}
		CPoint start_intro_point(243, 350);
		CPoint intro_point = point - start_intro_point;
		if (intro_view) {
			intro_view = false;
		}
		else if (intro_point.x > 0 && intro_point.y > 0) {
			if (intro_point.x < allx && intro_point.y < ally) {
				intro_view = true;
			}
		}
	}
	void CGameStateInit::OnShow()
	{
		title.SetTopLeft(0, 0);
		title.ShowBitmap();

		if (in) {
			start_dark.SetTopLeft(243, 250);
			start_dark.ShowBitmap();
		}
		else {
			start.SetTopLeft(243, 250);
			start.ShowBitmap();
		}
		if (intro_in) {
			intro_dark.SetTopLeft(243, 350);
			intro_dark.ShowBitmap();
		}
		else {
			intro.SetTopLeft(243, 350);
			intro.ShowBitmap();
		}
		if (intro_view) {
			instructions.SetTopLeft(125, 110);
			instructions.ShowBitmap();
		}

	}

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	/////////////////////////////////////////////////////////////////////////////

	CGameStateOver::CGameStateOver(CGame *g)
		: CGameState(g)
	{
	}

	void CGameStateOver::OnMove()
	{
		if (points.GetInteger() != scores) {
			points.Add(1);
		}


	}

	void CGameStateOver::OnBeginState()
	{
		const int P = 0;
		points.SetInteger(P);
		points.SetTopLeft(200, 425);
		if (isFinish) {
			CAudio::Instance()->Play(16);
		}
		else {
			CAudio::Instance()->Play(17);
		}
	}

	void CGameStateOver::OnInit()
	{
		ShowInitProgress(66);	// 接個前一個狀態的進度，此處進度視為66%
		//
		// 開始載入資料
		//
		Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
		//
		// 最終進度為100%
		//
		ShowInitProgress(100);
		lost.LoadBitmap(".\\Bitmaps\\over_background.bmp");
		finish.LoadBitmap(".\\Bitmaps\\finish_image.bmp", RGB(255, 255, 255));
		lost_image.LoadBitmap(".\\Bitmaps\\lost_image.bmp", RGB(255, 255, 255));
		again.LoadBitmap(".\\Bitmaps\\againbutton.bmp");
		menu.LoadBitmap(".\\Bitmaps\\menubutton.bmp");
		again_dark.LoadBitmap(".\\Bitmaps\\againbutton_dark.bmp");
		menu_dark.LoadBitmap(".\\Bitmaps\\menubutton_dark.bmp");
		points.LoadBitmap();
		CAudio::Instance()->Load(16, "sounds\\finish.mp3");	// 載入完成的聲音
		CAudio::Instance()->Load(17, "sounds\\fail.mp3");	// 載入失敗的聲音
		CAudio::Instance()->Load(98, "sounds\\button.mp3");	// 載入按鈕聲音
	}

	void CGameStateOver::OnShow()
	{
		lost.ShowBitmap();
		if (!isFinish) {
			lost_image.SetTopLeft(225, 0);
			lost_image.ShowBitmap();
		}
		else {
			finish.SetTopLeft(190, 0);
			finish.ShowBitmap();
		}
		points.ShowBitmap();

		if (!in) {
			again.SetTopLeft(243, 180);
			again.ShowBitmap();
		}
		else {
			again_dark.SetTopLeft(243, 180);
			again_dark.ShowBitmap();
		}


		if (!in1) {                            
			menu.SetTopLeft(243, 280);
			menu.ShowBitmap();
		}
		else {
			menu_dark.SetTopLeft(243, 280);
			menu_dark.ShowBitmap();
		}
	}
	void CGameStateOver::OnMouseMove(UINT nFlags, CPoint point)
	{
		CPoint start0(243, 180);
		int allx = 296;
		int ally = 87;
		CPoint new_point = point - start0;
		if (new_point.x > 0 && new_point.y > 0) {
			if (new_point.x < allx && new_point.y < ally) {
				in = true;
				CAudio::Instance()->Play(98);
			}
			else {
				in = false;
			}
		}
		else
		{
			in = false;
		}
		CPoint start1(243, 280);
		CPoint ne_point = point - start1;
		if (ne_point.x > 0 && ne_point.y > 0) {
			if (ne_point.x < allx && ne_point.y < ally) {
				in1 = true;
				CAudio::Instance()->Play(98);
			}
			else {
				in1 = false;
			}
		}
		else
		{
			in1 = false;
		}
	}
	void CGameStateOver::OnLButtonUp(UINT nFlags, CPoint point)
	{
		CPoint start0(243, 180);
		CPoint new_point = point - start0;
		int allx = 278;
		int ally = 85;
		if (new_point.x > 0 && new_point.y > 0) {
			if (new_point.x < allx && new_point.y < ally) {
				GotoGameState(GAME_STATE_RUN);		// 切換至GAME_STATE_RUN
			}
		}
		CPoint start1(243, 280);
		CPoint ne_point = point - start1;
		int alx = 278;
		int aly = 85;
		if (ne_point.x > 0 && ne_point.y > 0) {
			if (ne_point.x < allx && ne_point.y < ally) {
				GotoGameState(GAME_STATE_INIT);		// 切換至GAME_STATE_RUN
			}
		}
	}
	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
	/////////////////////////////////////////////////////////////////////////////

	CGameStateRun::CGameStateRun(CGame *g)
		: CGameState(g)
	{
	}

	CGameStateRun::~CGameStateRun()
	{
	}
	void CGameStateRun::OnBeginState()
	{
		ALLoB.Initialize(maps);
		isFinish = false;
		Clearance = 0;

		if (maps == 1) {
			CAudio::Instance()->Play(11, true);			// 撥放 地圖一的聲音
		}
		else if (maps == 2) {
			CAudio::Instance()->Play(12, true);			// 撥放 地圖二的聲音
		}
		else if (maps == 3) {
			CAudio::Instance()->Play(13, true);			// 撥放 地圖三的聲音
		}
		else {
			CAudio::Instance()->Play(14, true);			// 撥放 地圖四的聲音
		}
	}
	void CGameStateRun::OnMove()							// 移動遊戲元素
	{
		scores = ALLoB.Getpoint_n();
		ALLoB.OnMove();
		if (ALLoB.Audio_Coin()) {
			TRACE("test\n");
			CAudio::Instance()->Play(0);
			ALLoB.SetAudioCoin(false);
		}
		if (ALLoB.Audio_Laser()) {
			TRACE("test\n");
			CAudio::Instance()->Play(15);
			ALLoB.SetAudioLaser(false);
		}
		if (ALLoB.GetLife_n() <= 0) {
			isFinish = false;
			CAudio::Instance()->Stop(11);	// 停止 地圖一的聲音
			CAudio::Instance()->Stop(12);	// 停止 地圖二的聲音
			CAudio::Instance()->Stop(13);	// 停止 地圖三的聲音
			CAudio::Instance()->Stop(14);	// 停止 地圖四的聲音
			GotoGameState(GAME_STATE_OVER); // 切換至GAME_STATE_OVER
		}
		if (ALLoB.map_finish_map()) {
			isFinish = true;
			CAudio::Instance()->Stop(11);	// 停止 地圖一的聲音
			CAudio::Instance()->Stop(12);	// 停止 地圖二的聲音
			CAudio::Instance()->Stop(13);	// 停止 地圖三的聲音
			CAudio::Instance()->Stop(14);	// 停止 M地圖四的聲音
			GotoGameState(GAME_STATE_OVER); // 切換至GAME_STATE_OVER
		}
	}

	void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
	{
		ShowInitProgress(33);	// 接個前一個狀態的進度，此處進度視為33%

		ShowInitProgress(50);
		//
		// 載入資料
		//
		CAudio::Instance()->Load(0, "sounds\\coin.mp3");		// 載入金幣的聲音
		CAudio::Instance()->Load(15, "sounds\\laser.mp3");		// 載入雷射的聲音
		CAudio::Instance()->Load(11, "sounds\\noob_00.mp3");	// 載入地圖一的聲音
		CAudio::Instance()->Load(12, "sounds\\dream_01.mp3");	// 載入地圖二的聲音
		CAudio::Instance()->Load(13, "sounds\\rock_10.mp3");	// 載入地圖三的聲音
		CAudio::Instance()->Load(14, "sounds\\paradise_11.mp3");// 載入地圖四的聲音
	}

	void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_LEFT = 0x25;		// keyboard左箭頭
		const char KEY_RIGHT = 0x27;	// keyboard右箭頭
		Clearance = 0;					// 通關密技順序歸零
		if (nChar == KEY_LEFT) {
			ALLoB.SetMovingLeft(true);
		}
		if (nChar == KEY_RIGHT) {
			ALLoB.SetMovingRight(true);
		}

	}

	void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_LEFT = 0x25;  // keyboard左箭頭
		const char KEY_RIGHT = 0x27; // keyboard右箭頭

		Clearance = 0;
		if (nChar == KEY_LEFT) {
			ALLoB.SetMovingLeft(false);
		}
		if (nChar == KEY_RIGHT) {
			ALLoB.SetMovingRight(false);
		}
	}

	void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{
		Clearance = 1;  // 通關密技的第一個按鍵
	}

	void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{
		if (Clearance) {  // 密技通關
			isFinish = true;
			CAudio::Instance()->Stop(11);	// 停止 地圖一的聲音
			CAudio::Instance()->Stop(12);	// 停止 地圖二的聲音
			CAudio::Instance()->Stop(13);	// 停止 地圖三的聲音
			CAudio::Instance()->Stop(14);	// 停止 地圖四的聲音
			GotoGameState(GAME_STATE_OVER); // 切換至GAME_STATE_OVER
		}
	}

	void CGameStateRun::OnShow()
	{
		ALLoB.OnShow();
	}


	///////地圖選擇

	CGameStateChoose::CGameStateChoose(CGame *g)
		: CGameState(g)
	{
	}

	void CGameStateChoose::OnInit()
	{
		ShowInitProgress(0);	
		//
		// 開始載入資料
		//
		select.LoadBitmap(".\\Bitmaps\\mapselect.bmp");
		return_dark.LoadBitmap(".\\Bitmaps\\return.bmp");
		CAudio::Instance()->Load(96, "sounds\\button.mp3");	// 載入按鈕聲音
	}

	void CGameStateChoose::OnBeginState()
	{
		in = false;
	}
	void CGameStateChoose::OnLButtonUp(UINT nFlags, CPoint point)
	{
		CPoint start_return0(22, 348);               //返回鍵
		CPoint start_return1(127, 460);
		CPoint new_point = point - start_return0;
		int allx = 125 - 22;
		int ally = 460 - 348;
		if (new_point.x > 0 && new_point.y > 0) {
			if (new_point.x < allx && new_point.y < ally) {
				GotoGameState(GAME_STATE_INIT);		// 切換至GAME_STATE_INIT
			}
		}


		CPoint start_map0(154, 67);                  //關卡一
		CPoint start_map1(379, 272);
		CPoint new_point1 = point - start_map0;
		int allx1 = 379 - 154;
		int ally1 = 272 - 67;
		if (new_point1.x > 0 && new_point1.y > 0) {
			if (new_point1.x < allx1 && new_point1.y < ally1) {
				maps = 1;
				GotoGameState(GAME_STATE_RUN);		// 切換至GAME_STATE_RUN
			}
		}
		CPoint start_map2(465, 68);                  //關卡二
		CPoint start_map3(690, 273);
		CPoint new_point2 = point - start_map2;
		int allx2 = 690 - 465;
		int ally2 = 273 - 68;
		if (new_point2.x > 0 && new_point2.y > 0) {
			if (new_point2.x < allx2 && new_point2.y < ally2) {
				maps = 2;
				GotoGameState(GAME_STATE_RUN);		// 切換至GAME_STATE_RUN
			}
		}
		CPoint start_map4(154, 291);                  //關卡三
		CPoint start_map5(379, 497);
		CPoint new_point3 = point - start_map4;
		int allx3 = 379 - 154;
		int ally3 = 497 - 291;
		if (new_point3.x > 0 && new_point3.y > 0) {
			if (new_point3.x < allx3 && new_point3.y < ally3) {
				maps = 3;
				GotoGameState(GAME_STATE_RUN);		// 切換至GAME_STATE_RUN
			}
		}
		CPoint start_map6(466, 292);                  //關卡四
		CPoint start_map7(690, 497);
		CPoint new_point4 = point - start_map6;
		int allx4 = 690 - 466;
		int ally4 = 497 - 292;
		if (new_point4.x > 0 && new_point4.y > 0) {
			if (new_point4.x < allx4 && new_point4.y < ally4) {
				maps = 4;
				GotoGameState(GAME_STATE_RUN);		// 切換至GAME_STATE_RUN
			}
		}
	}
	void CGameStateChoose::OnShow()
	{
		select.SetTopLeft(0, 0);
		select.ShowBitmap();
		if (!in) {
			select.SetTopLeft(0, 0);
			select.ShowBitmap();
		}
		else {
			return_dark.SetTopLeft(28, 345);
			return_dark.ShowBitmap();
		}
	}
	void CGameStateChoose::OnMouseMove(UINT nFlags, CPoint point)
	{
		CPoint start0(28, 345);               //返回鍵
		int allx = 125 - 28;
		int ally = 460 - 345;
		CPoint new_point = point - start0;
		if (new_point.x > 0 && new_point.y > 0) {
			if (new_point.x < allx && new_point.y < ally) {
				in = true;
				CAudio::Instance()->Play(96);
			}
			else {
				in = false;
			}
		}
		else
		{
			in = false;
		}
	}
}
