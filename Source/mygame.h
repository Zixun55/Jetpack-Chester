/*
 * mygame.h: ���ɮ��x�C��������class��interface
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
	// �o��class���C�����@�}�l���A(Game Init)
	/////////////////////////////////////////////////////////////////////////////
	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnMouseMove(UINT nFlags, CPoint point);	// �B�z�ƹ�������
		void OnLButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
	protected:
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		CMovingBitmap title;                            // init���ʭ�
		CMovingBitmap start;                            // start�����s
		CMovingBitmap start_dark;                       // start�����s_�t��
		bool in;
		CMovingBitmap intro;                            // intro�����s
		CMovingBitmap intro_dark;                       // intro�����s_�t��
		CMovingBitmap instructions;                     // ��������
		bool intro_view;                                // ��ܻ���
		bool intro_in;

		CMovingBitmap about_btn;                            // about�����s
		CMovingBitmap about_dark;                       // about�����s_�t��
		CMovingBitmap about_img;                     // about����
		bool about_view;                                // ���about
		bool about_in;
	};

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����i�檬�A(Game Run)
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
		void OnRButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		int             Clearance;  // �q���K�ޭp��  ��������A���S�ا��q���� �@�w�n�s��~�i�H ��������L������ �N�n�A�@��
		CALaser			ALLoB;      // �Ҧ�����
	};

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����������A(Game Over)
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();
		void OnMouseMove(UINT nFlags, CPoint point);
		void OnLButtonUp(UINT nFlags, CPoint point);
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		CMovingBitmap lost;				 //�����e��
		CMovingBitmap finish;			 //finish image
		CMovingBitmap lost_image;		 //lost   image
		CMovingBitmap again;			 //again button
		CMovingBitmap menu;				 //menu button
		CInteger points;				 //����

		CMovingBitmap again_dark;        //again_dark button
		CMovingBitmap menu_dark;         //menu_dark button
		bool in = false;
		bool in1 = false;
		bool showscore = false;
	};


	/////////////////////////////////////////////////////////////////////////////
	// �o��class��������d������
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateChoose : public CGameState {
	public:
		CGameStateChoose(CGame *g);
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnLButtonUp(UINT nFlags, CPoint point);
		void OnMouseMove(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@ 

	protected:
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		CMovingBitmap select;                            // �a�Ͽ�ܵe��
		CMovingBitmap return_dark;						 // ����_�t
		bool in;
	};
}