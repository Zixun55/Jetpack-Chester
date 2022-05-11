/*
 * mygame.cpp: ���ɮ��x�C��������class��implementation
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

#include <ctime> 
#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"
#include <stdlib.h>

int maps;
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����C���}�Y�e������
	/////////////////////////////////////////////////////////////////////////////

	CGameStateInit::CGameStateInit(CGame *g)
		: CGameState(g)
	{
	}

	void CGameStateInit::OnInit()
	{
		//
		// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
		//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
		//
		ShowInitProgress(0);	// �@�}�l��loading�i�׬�0%
		//
		// �}�l���J���
		//
		title.LoadBitmap(".\\Bitmaps\\background_true.bmp");
		start.LoadBitmap(".\\Bitmaps\\background_startbutton.bmp", RGB(255, 255, 255));
		start_dark.LoadBitmap(".\\Bitmaps\\background_startbutton_dark.bmp", RGB(255, 255, 255));
		//title.LoadBitmap("./game_image/background.bmp");
		//Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
		//
		// ��OnInit�ʧ@�|����CGameStaterRun::OnInit()�A�ҥH�i���٨S��100%
		//
	}

	void CGameStateInit::OnBeginState()
	{
		in = false;
	}
	void CGameStateInit::OnMouseMove(UINT nFlags, CPoint point)
	{
		CPoint start0(243, 250);
		int allx = 296;
		int ally = 87;
		CPoint new_point = point - start0;
		if (new_point.x > 0 && new_point.y > 0) {
			if (new_point.x < allx && new_point.y < ally) {
				in = true;
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
	void CGameStateInit::OnLButtonUp(UINT nFlags, CPoint point)
	{
		CPoint start0(243, 250);
		CPoint start1(539, 337);
		CPoint new_point = point - start0;
		int allx = 539 - 243;
		int ally = 337 - 250;
		if (new_point.x > 0 && new_point.y > 0) {
			if (new_point.x < allx && new_point.y < ally) {
				GotoGameState(GAME_STATE_CHOOSE);		// ������GAME_STATE_RUN
			}
		}
	}
	void CGameStateInit::OnShow()
	{
		//
		// �K�Wlogo
		//
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
		//
		// Demo�ù��r�����ϥΡA���L�}�o�ɽкɶq�קK�����ϥΦr���A���CMovingBitmap����n
		//
		//CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
		//CFont f,*fp;
		//f.CreatePointFont(160,"Times New Roman");	// ���� font f; 160���16 point���r
		//fp=pDC->SelectObject(&f);					// ��� font f
		//pDC->SetBkColor(RGB(0,0,0));
		//pDC->SetTextColor(RGB(255,255,0));
		//pDC->TextOut(120,220,"Please click mouse or press SPACE to begin.");
		//pDC->TextOut(5,395,"Press Ctrl-F to switch in between window mode and full screen mode.");
		//if (ENABLE_GAME_PAUSE)
		//	pDC->TextOut(5,425,"Press Ctrl-Q to pause the Game.");
		//pDC->TextOut(5,455,"Press Alt-F4 or ESC to Quit.");
		//pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
		//CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
	}

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����������A(Game Over)
	/////////////////////////////////////////////////////////////////////////////

	CGameStateOver::CGameStateOver(CGame *g)
		: CGameState(g)
	{
	}

	void CGameStateOver::OnMove()
	{
		//counter--;
		//if (counter < 0)
			//GotoGameState(GAME_STATE_INIT);
	}

	void CGameStateOver::OnBeginState()
	{
		counter = 30 * 5; // 5 seconds
	}

	void CGameStateOver::OnInit()
	{
		//
		// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
		//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
		//
		ShowInitProgress(66);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���66%
		//
		// �}�l���J���
		//
		Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
		//
		// �̲׶i�׬�100%
		//
		ShowInitProgress(100);
		lost.LoadBitmap(".\\Bitmaps\\lost.bmp");
		again.LoadBitmap(".\\Bitmaps\\againbutton.bmp");
		menu.LoadBitmap(".\\Bitmaps\\menubutton.bmp");
		again_dark.LoadBitmap(".\\Bitmaps\\againbutton_dark.bmp");
		menu_dark.LoadBitmap(".\\Bitmaps\\menubutton_dark.bmp");
	}

	void CGameStateOver::OnShow()
	{
		lost.ShowBitmap();


		if (!in) {
			again.SetTopLeft(243, 180);
			again.ShowBitmap();
		}
		else {
			again_dark.SetTopLeft(243, 180);
			again_dark.ShowBitmap();
		}


		if (!in1) {                              //�ثe��ӫ��s�|�P�ɷt�A�ݭק�
			menu.SetTopLeft(243, 280);
			menu.ShowBitmap();
		}
		else {
			menu_dark.SetTopLeft(243, 280);
			menu_dark.ShowBitmap();
		}


		CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC      
		CFont f, *fp;
		f.CreatePointFont(160, "Times New Roman");	// ���� font f; 160���16 point���r
		fp = pDC->SelectObject(&f);					// ��� font f
		pDC->SetBkColor(RGB(0, 0, 0));
		pDC->SetTextColor(RGB(255, 255, 0));
		//char str[80];								// Demo �Ʀr��r�ꪺ�ഫ
		//sprintf(str, "Game Over ! (%d)", counter / 30);
		//pDC->TextOut(240, 210, str);
		pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
		CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
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
				GotoGameState(GAME_STATE_RUN);		// ������GAME_STATE_RUN
			}
		}
		CPoint start1(243, 280);
		CPoint ne_point = point - start1;
		int alx = 278;
		int aly = 85;
		if (ne_point.x > 0 && ne_point.y > 0) {
			if (ne_point.x < allx && ne_point.y < ally) {
				GotoGameState(GAME_STATE_INIT);		// ������GAME_STATE_RUN
			}
		}
	}
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
	/////////////////////////////////////////////////////////////////////////////

	CGameStateRun::CGameStateRun(CGame *g)
		: CGameState(g), NUMBALLS(28), NUMLASER(10), NUMLASER2(10),NUMBOXES(10)
	{
		ball = new CBall[NUMBALLS];
		laser = new CBlock[NUMLASER];
		laser2 = new Claser[NUMLASER2];
		boxes = new CBox[NUMBOXES];
		map = CMap();
	}

	CGameStateRun::~CGameStateRun()
	{
		delete[] boxes;
		delete[] laser;
		delete[] laser2;
		delete[] ball;
		TRACE("del\n");
	}

	void CGameStateRun::OnBeginState()
	{
		const int BALL_GAP = 90;
		const int BALL_XY_OFFSET = 45;
		const int BALL_PER_ROW = 7;
		const int HITS_LEFT = 3;
		const int HITS_LEFT_X = 590;
		const int HITS_LEFT_Y = 0;
		const int BACKGROUND_X = 60;
		const int ANIMATION_SPEED = 15;
		for (int i = 0; i < NUMBALLS; i++) {				// �]�w�y���_�l�y��
			int x_pos = i % BALL_PER_ROW;
			int y_pos = i / BALL_PER_ROW;
			ball[i].SetXY(x_pos * BALL_GAP + BALL_XY_OFFSET, y_pos * BALL_GAP + BALL_XY_OFFSET);
			ball[i].SetDelay(x_pos);
			ball[i].SetIsAlive(true);
		}

		//�p�g��m
		laser[0].SetXY(500, 50);
		laser[0].SetIsAlive(true);
		laser[1].SetXY(1000, 200);
		laser[1].SetIsAlive(true);
		laser[2].SetXY(1500, 400);
		laser[2].SetIsAlive(true);
		laser[3].SetXY(2000, 150);
		laser[3].SetIsAlive(true);
		laser[4].SetXY(2500, 500);
		laser[4].SetIsAlive(true);
		laser[5].SetXY(3000, 175);
		laser[5].SetIsAlive(true);
		laser[6].SetXY(3500, 350);
		laser[6].SetIsAlive(true);
		laser[7].SetXY(4000, 135);
		laser[7].SetIsAlive(true);
		laser[8].SetXY(4500, 375);
		laser[8].SetIsAlive(true);
		laser[9].SetXY(5000, 185);
		laser[9].SetIsAlive(true);

		laser2[0].SetXY(700, 300);
		laser2[0].SetIsAlive(true);
		laser2[1].SetXY(1400, 120);
		laser2[1].SetIsAlive(true);
		laser2[2].SetXY(1700, 75);
		laser2[2].SetIsAlive(true);
		laser2[3].SetXY(2200, 150);
		laser2[3].SetIsAlive(true);
		laser2[4].SetXY(2700, 500);
		laser2[4].SetIsAlive(true);
		laser2[5].SetXY(3200, 175);
		laser2[5].SetIsAlive(true);
		laser2[6].SetXY(3700, 350);
		laser2[6].SetIsAlive(true);
		laser2[7].SetXY(4200, 135);
		laser2[7].SetIsAlive(true);
		laser2[8].SetXY(4700, 375);
		laser2[8].SetIsAlive(true);
		laser2[9].SetXY(5200, 185);
		laser2[9].SetIsAlive(true);


		//for (int i = 0; i < NUMLASER; i++) {
		//	laser[i].SetXY((i + 1) * 500, 50);
		//	laser[i].SetIsAlive(true);
		//}


		for (int i = 0; i < NUMBOXES; i++) {
			boxes[i].SetXY((i + 1) * 1000, 280);
		}
		eraser.Initialize();
		chtest.Initialize();
		map.Initialize();
		map.chooseMap(maps);
		map.LoadBitmap();
		TRACE("%d\n", maps);
		help.SetTopLeft(0, SIZE_Y - help.Height());			// �]�w�����Ϫ��_�l�y��
		hits_left.SetInteger(HITS_LEFT);					// ���w�ѤU��������
		hits_left.SetTopLeft(HITS_LEFT_X, HITS_LEFT_Y);		// ���w�ѤU�����ƪ��y��

		//CAudio::Instance()->Play(AUDIO_LAKE, true);			// ���� WAVE
		//CAudio::Instance()->Play(AUDIO_DING, false);		// ���� WAVE
		//CAudio::Instance()->Play(AUDIO_NTUT, true);			// ���� MIDI
	}
	int  CGameStateRun::ClosestBox() {
		int x[100][100];
		for (int i = 0; i < NUMBOXES; i++) {
			x[i][0] = abs(boxes[i].BoxX1() - chtest.GetX2());
			x[i][1] = i;
		}
		int min = x[0][0];
		int closet = 0;
		for (int i = 1; i < NUMBOXES;i++)
		{
			if (x[i][0] < min) {
				min = x[i][0];
				closet = x[i][1];
			}
		}
		return closet;
	}
	void CGameStateRun::OnMove()							// ���ʹC������
	{
		//
		// �p�G�Ʊ�ק�cursor���˦��A�h�N�U���{����commment�����Y�i
		//
		// SetCursor(AfxGetApp()->LoadCursor(IDC_GAMECURSOR));
		//
		// ���ʭI���Ϫ��y��
		//
		//if (background.Top() > SIZE_Y)
			//background.SetTopLeft(60, -background.Height());

		//if (background.Left() > -640) {                                       //�e������
		//	background.SetTopLeft(background.Left() - 1, background.Top());
		//}


		//
		// ���ʲy
		//

		for (int i = 0; i < NUMBALLS; i++)
			ball[i].OnMove();
		//
		// �������l
		//
		eraser.OnMove();
		map.OnMove();
		//
		// �P�_���l�O�_�I��y
		//
		for (int i = 0; i < NUMBALLS; i++)
			if (ball[i].IsAlive() && ball[i].HitEraser(&eraser)) {
				ball[i].SetIsAlive(false);
				CAudio::Instance()->Play(AUDIO_DING);
				hits_left.Add(-1);
				//
				// �Y�Ѿl�I�����Ƭ�0�A�h����Game Over���A
				//
				if (hits_left.GetInteger() <= 0) {
					CAudio::Instance()->Stop(AUDIO_LAKE);	// ���� WAVE
					CAudio::Instance()->Stop(AUDIO_NTUT);	// ���� MIDI
					GotoGameState(GAME_STATE_OVER);
				}
			}
		for (int i = 0; i < NUMLASER; i++) {
			laser[i].OnMove();
			if (laser[i].IsAlive() && laser[i].HitEraser(&chtest)) {
				laser[i].SetIsAlive(false);                                //�p�G����I��p�g�A�p�g�|����
				hits_left.Add(-1);                                        //���R
				

				
			}
		}

		for (int i = 0; i < NUMLASER2; i++) {
			laser2[i].OnMove();
			if (laser2[i].IsAlive() && laser2[i].HitEraser(&chtest)) {
				laser2[i].SetIsAlive(false);                                //�p�G����I��p�g�A�p�g�|����
				hits_left.Add(-1);                                        //���R
				
			}
		}

		int check_box = 0;
		int check_ch = 0;
		for (int i = 0; i < NUMBOXES; i++) {
			if (boxes[i].HitEraser(&chtest)) {
				check_box = 1;
			}
		}
		int close_box = CGameStateRun::ClosestBox();
		if (boxes[close_box].ChxBigThanBox(&chtest)) {
			check_ch = 1;
		}
		for (int i = 0; i < NUMBOXES; i++) {
			if (check_box) {
				boxes[i].CantMoving(true);
				laser[i].CantMoving(true);
				laser2[i].CantMoving(true);
				map.CantMoving(true);
				if (check_ch) {
					chtest.CantMoving(true);
				}
				else {
					chtest.CantMoving(false);
				}
			}
			else {
				boxes[i].CantMoving(false);
				laser[i].CantMoving(false);
				laser2[i].CantMoving(false);
				map.CantMoving(false);
				chtest.CantMoving(false);
			}
			boxes[i].OnMove();
		}
		chtest.OnMove();
		check_box = 0;
		check_ch = 0;

		//
		// ���ʼu�����y
		//
		bball.OnMove();
	}

	void CGameStateRun::OnInit()  								// �C������Ȥιϧγ]�w
	{
		//
		// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
		//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
		//
		ShowInitProgress(33);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���33%
		//
		// �}�l���J���
		//
		for (int i = 0; i < NUMBALLS; i++)
			ball[i].LoadBitmap();								// ���J��i�Ӳy���ϧ�
		eraser.LoadBitmap();
		chtest.LoadBitmap();


		for (int i = 0; i < NUMLASER; i++) {
			laser[i].LoadBitmap();
		}
		for (int i = 0; i < NUMLASER2; i++) {
			laser2[i].LoadBitmap();
		}
		for (int i = 0; i < NUMBOXES; i++) {
			boxes[i].LoadBitmap();
		}

		//
		// ��������Loading�ʧ@�A�����i��
		//
		ShowInitProgress(50);
		//Sleep(300); // ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
		//
		// �~����J��L���
		//
		help.LoadBitmap(IDB_HELP, RGB(255, 255, 255));				// ���J�������ϧ�
		corner.LoadBitmap(IDB_CORNER);							// ���J�����ϧ�stea
		//corner.ShowBitmap(background);							// �Ncorner�K��background
		bball.LoadBitmap();										// ���J�ϧ�
		hits_left.LoadBitmap();
		steam.LoadBitmap(".\\Bitmaps\\steam.bmp", RGB(255, 255, 255));
		steam1.LoadBitmap(".\\Bitmaps\\steam1.bmp", RGB(255, 255, 255));
		steam2.LoadBitmap(".\\Bitmaps\\steam2.bmp", RGB(255, 255, 255));
		
		live.AddBitmap(".\\Bitmaps\\live.bmp", RGB(255, 255, 255));
		live.AddBitmap(".\\Bitmaps\\aaa.bmp", RGB(255, 255, 255));
		live.AddBitmap(".\\Bitmaps\\nolive.bmp", RGB(255, 255, 255));
		live2.AddBitmap(".\\Bitmaps\\live.bmp", RGB(255, 255, 255));
		live2.AddBitmap(".\\Bitmaps\\aaa.bmp", RGB(255, 255, 255));
		live2.AddBitmap(".\\Bitmaps\\nolive.bmp", RGB(255, 255, 255));
		live3.AddBitmap(".\\Bitmaps\\live.bmp", RGB(255, 255, 255));
		live3.AddBitmap(".\\Bitmaps\\aaa.bmp", RGB(255, 255, 255));
		live3.AddBitmap(".\\Bitmaps\\nolive.bmp", RGB(255, 255, 255));
		


		CAudio::Instance()->Load(AUDIO_DING, "sounds\\ding.wav");	// ���J�s��0���n��ding.wav
		CAudio::Instance()->Load(AUDIO_LAKE, "sounds\\lake.mp3");	// ���J�s��1���n��lake.mp3
		CAudio::Instance()->Load(AUDIO_NTUT, "sounds\\ntut.mid");	// ���J�s��2���n��ntut.mid
		//
		// ��OnInit�ʧ@�|����CGameStaterOver::OnInit()�A�ҥH�i���٨S��100%
		//
	}

	void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_LEFT = 0x25; // keyboard���b�Y
		const char KEY_UP = 0x26; // keyboard�W�b�Y
		const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
		const char KEY_DOWN = 0x28; // keyboard�U�b�Y
		if (nChar == KEY_LEFT)
			eraser.SetMovingLeft(true);
		if (nChar == KEY_RIGHT)
			eraser.SetMovingRight(true);
		if (nChar == KEY_UP)
			eraser.SetMovingUp(true);
		if (nChar == KEY_DOWN)
			eraser.SetMovingDown(true);


		if (nChar == KEY_LEFT) {
			chtest.SetMovingLeft(true);
			map.SetMovingLeft(true);
			for (int i = 0; i < NUMLASER; i++) {
				laser[i].SetMovingLeft(true);
				laser2[i].SetMovingLeft(true);
				boxes[i].SetMovingLeft(true);
			}
		}
		if (nChar == KEY_RIGHT) {
			chtest.SetMovingRight(true);
			map.SetMovingRight(true);
			for (int i = 0; i < NUMLASER; i++) {
				laser[i].SetMovingRight(true);
				laser2[i].SetMovingRight(true);
				boxes[i].SetMovingRight(true);
			}
		}
	}

	void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_LEFT = 0x25; // keyboard���b�Y
		const char KEY_UP = 0x26; // keyboard�W�b�Y
		const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
		const char KEY_DOWN = 0x28; // keyboard�U�b�Y
		if (nChar == KEY_LEFT)
			eraser.SetMovingLeft(false);
		if (nChar == KEY_RIGHT)
			eraser.SetMovingRight(false);
		if (nChar == KEY_UP)
			eraser.SetMovingUp(false);
		if (nChar == KEY_DOWN)
			eraser.SetMovingDown(false);

		if (nChar == KEY_LEFT) {
			chtest.SetMovingLeft(false);
			map.SetMovingLeft(false);
			for (int i = 0; i < NUMLASER; i++) {
				laser[i].SetMovingLeft(false);
				laser2[i].SetMovingLeft(false);
				boxes[i].SetMovingLeft(false);
			}
		}
		if (nChar == KEY_RIGHT) {
			chtest.SetMovingRight(false);
			map.SetMovingRight(false);
			for (int i = 0; i < NUMLASER; i++) {
				laser[i].SetMovingRight(false);
				laser2[i].SetMovingRight(false);
				boxes[i].SetMovingRight(false);
			}
		}
		//if (nChar == KEY_LEFT)
		//	character.SetTopLeft(character.Left() - 1, character.Top());
		//if (nChar == KEY_RIGHT)
		//	character.SetTopLeft(character.Left() - 1, character.Top());
	}

	void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
	{
		eraser.SetMovingLeft(true);
	}

	void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
	{
		eraser.SetMovingLeft(false);
	}

	void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
	{
		// �S�ơC�p�G�ݭn�B�z�ƹ����ʪ��ܡA�gcode�b�o��
	}

	void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
	{
		eraser.SetMovingRight(true);
	}

	void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
	{
		GotoGameState(GAME_STATE_OVER);
		eraser.SetMovingRight(false);
	}

	void CGameStateRun::OnShow()
	{

		//
		//  �`�N�GShow�̭��d�U���n���ʥ��󪫥󪺮y�СA���ʮy�Ъ��u�@����Move���~��A
		//        �_�h��������sø�Ϯ�(OnDraw)�A����N�|���ʡA�ݰ_�ӷ|�ܩǡC���ӳN�y
		//        ���AMove�t�dMVC����Model�AShow�t�dView�A��View�������Model�C
		//
		//
		//  �K�W�I���ϡB�����ơB�y�B���l�B�u�����y
		//
		//background.ShowBitmap();			// �K�W�I����
		help.ShowBitmap();					// �K�W������
		for (int i = 0; i < NUMBALLS; i++)
			ball[i].OnShow();				// �K�W��i���y
		eraser.OnShow();					// �K�W���l
		bball.OnShow();						// �K�W�u�����y
		map.OnShow();
		chtest.OnShow();
		hits_left.ShowBitmap();
		for (int i = 0; i < NUMLASER; i++) {
			laser[i].OnShow();
			laser2[i].OnShow();
			boxes[i].OnShow();
		}


		//
		//  �K�W���W�Υk�U��������
		//
		corner.SetTopLeft(0, 0);
		corner.ShowBitmap();
		corner.SetTopLeft(SIZE_X - corner.Width(), SIZE_Y - corner.Height());
		corner.ShowBitmap();

		live.SetTopLeft(700, 10);
		live.OnShow();
		live2.SetTopLeft(640, 10);
		live2.OnShow();
		live3.SetTopLeft(580, 10);
		live3.OnShow();

		if (hits_left.GetInteger() == 2) {
			if (live.GetCurrentBitmapNumber() != 2) {
				live.OnMove();
			}
			if (live2.GetCurrentBitmapNumber() != 0) {
				live2.OnMove();
			}
		}
		if (hits_left.GetInteger() == 1) {
			if (live2.GetCurrentBitmapNumber() != 2) {
				live2.OnMove();
			}
			if (live3.GetCurrentBitmapNumber() != 0) {
				live3.OnMove();
			}
		}
		if (hits_left.GetInteger() == 0) {
			if (live3.GetCurrentBitmapNumber() != 2) {
				live3.OnMove();
			}
			GotoGameState(GAME_STATE_OVER);
		}

	}


	///////�a�Ͽ��

	CGameStateChoose::CGameStateChoose(CGame *g)
		: CGameState(g)
	{
	}

	void CGameStateChoose::OnInit()
	{
		//
		// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
		//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
		//
		ShowInitProgress(0);	// �@�}�l��loading�i�׬�0%
		//
		// �}�l���J���
		//
		select.LoadBitmap(".\\Bitmaps\\mapselect.bmp");
		return_dark.LoadBitmap(".\\Bitmaps\\return.bmp");

		//title.LoadBitmap("./game_image/background.bmp");
		//Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
		//
		// ��OnInit�ʧ@�|����CGameStaterRun::OnInit()�A�ҥH�i���٨S��100%
		//
	}

	void CGameStateChoose::OnBeginState()
	{
		in = false;
	}
	void CGameStateChoose::OnLButtonUp(UINT nFlags, CPoint point)
	{
		CPoint start_return0(22, 348);               //��^��
		CPoint start_return1(127, 460);
		CPoint new_point = point - start_return0;
		int allx = 125 - 22;
		int ally = 460 - 348;
		if (new_point.x > 0 && new_point.y > 0) {
			if (new_point.x < allx && new_point.y < ally) {
				GotoGameState(GAME_STATE_INIT);		// ������GAME_STATE_INIT
			}
		}


		CPoint start_map0(154, 67);                  //���d�@
		CPoint start_map1(379, 272);
		CPoint new_point1 = point - start_map0;
		int allx1 = 379 - 154;
		int ally1 = 272 - 67;
		if (new_point1.x > 0 && new_point1.y > 0) {
			if (new_point1.x < allx1 && new_point1.y < ally1) {
				maps = 1;
				GotoGameState(GAME_STATE_RUN);		// ������GAME_STATE_RUN
			}
		}
		CPoint start_map2(465, 68);                  //���d�G
		CPoint start_map3(690, 273);
		CPoint new_point2 = point - start_map2;
		int allx2 = 690 - 465;
		int ally2 = 273 - 68;
		if (new_point2.x > 0 && new_point2.y > 0) {
			if (new_point2.x < allx2 && new_point2.y < ally2) {
				maps = 2;
				GotoGameState(GAME_STATE_RUN);		// ������GAME_STATE_RUN
			}
		}
		CPoint start_map4(154, 291);                  //���d�T
		CPoint start_map5(379, 497);
		CPoint new_point3 = point - start_map4;
		int allx3 = 379 - 154;
		int ally3 = 497 - 291;
		if (new_point3.x > 0 && new_point3.y > 0) {
			if (new_point3.x < allx3 && new_point3.y < ally3) {
				maps = 3;
				GotoGameState(GAME_STATE_RUN);		// ������GAME_STATE_RUN
			}
		}
		CPoint start_map6(466, 292);                  //���d�|
		CPoint start_map7(690, 497);
		CPoint new_point4 = point - start_map6;
		int allx4 = 690 - 466;
		int ally4 = 497 - 292;
		if (new_point4.x > 0 && new_point4.y > 0) {
			if (new_point4.x < allx4 && new_point4.y < ally4) {
				maps = 4;
				GotoGameState(GAME_STATE_RUN);		// ������GAME_STATE_RUN
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
		CPoint start0(28, 345);               //��^��
		int allx = 125 - 28;
		int ally = 460 - 345;
		CPoint new_point = point - start0;
		if (new_point.x > 0 && new_point.y > 0) {
			if (new_point.x < allx && new_point.y < ally) {
				in = true;
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

//154 67   351 272   �a�Ϥ@
//465 68   663 273   �a�ϤG
//154 291  351 497   �a�ϤT
//466 292  663 497   �a�ϥ|