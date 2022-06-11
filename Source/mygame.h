/*
 * mygame.h: 本檔案儲遊戲本身的class的interface
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
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *   2006-02-08 V4.2
 *      1. Rename OnInitialUpdate() -> OnInit().
 *      2. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      3. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress.
*/
#include "Ccharacter.h"
#include "CMap.h"
#include "CBlock.h"
#include "Claser.h"
#include "CBox.h"
#include "CALaser.h" 
#include "Ccoin.h" 
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的一開始狀態(Game Init)
	/////////////////////////////////////////////////////////////////////////////
	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnMouseMove(UINT nFlags, CPoint point);	// 處理滑鼠的移動
		void OnLButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
	protected:
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		CMovingBitmap title;                            // init的封面
		CMovingBitmap start;                            // start的按鈕
		CMovingBitmap start_dark;                       // start的按鈕_暗掉
		bool in;
		CMovingBitmap intro;                            // intro的按鈕
		CMovingBitmap intro_dark;                       // intro的按鈕_暗掉
		CMovingBitmap instructions;                     // 說明的圖
		bool intro_view;                                // 顯示說明
		bool intro_in;

		CMovingBitmap about_btn;                            // about的按鈕
		CMovingBitmap about_dark;                       // about的按鈕_暗掉
		CMovingBitmap about_img;                     // about的圖
		bool about_view;                                // 顯示about
		bool about_in;
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的進行狀態(Game Run)
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		void OnRButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		int             Clearance;  // 通關密技計數  先按左鍵再按又建材通關窩 一定要連續才可以 中間按其他的按鍵 就要再一次
		CALaser			ALLoB;      // 所有物件
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();
		void OnMouseMove(UINT nFlags, CPoint point);
		void OnLButtonUp(UINT nFlags, CPoint point);
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		CMovingBitmap lost;				 //結束畫面
		CMovingBitmap finish;			 //finish image
		CMovingBitmap lost_image;		 //lost   image
		CMovingBitmap again;			 //again button
		CMovingBitmap menu;				 //menu button
		CInteger points;				 //分數

		CMovingBitmap again_dark;        //again_dark button
		CMovingBitmap menu_dark;         //menu_dark button
		bool in = false;
		bool in1 = false;
		bool showscore = false;
	};


	/////////////////////////////////////////////////////////////////////////////
	// 這個class為選擇關卡的部分
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateChoose : public CGameState {
	public:
		CGameStateChoose(CGame *g);
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnLButtonUp(UINT nFlags, CPoint point);
		void OnMouseMove(UINT nFlags, CPoint point);	// 處理滑鼠的動作 

	protected:
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		CMovingBitmap select;                            // 地圖選擇畫面
		CMovingBitmap return_dark;						 // 按紐_暗
		bool in;
	};
}