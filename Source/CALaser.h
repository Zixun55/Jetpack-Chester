#include <vector>
#include "Ccoin.h"
namespace game_framework {

	class CALaser
	{
	public:
		CALaser();
		~CALaser();
		void Initialize();
		void LoadBitmap();
		void OnMove();
		void OnShow();
		void CantMoving(bool flag);
		int  ClosestBox();
		int  GetLife_n();
		int  Getpoint_n();
		int  GetCheck_map();
		void SetMovingLeft(bool flag);
		void SetMovingRight(bool flag);
		bool Get_check_chx();
	protected:
		int check_map;
		int x, y;
		bool check_chx;
		bool check_chx2;
		bool cantMoving;
		bool isLeft  = false;
		bool isRight = false;
		bool isLoadBitmap = false;
		Ccoin    *coins;
		Claser    *laser2;
		CBlock    *laser;
		
		Ccharacter chtest;          // ����
		CLife      Life;
		Cpoint     point;
		CBox       *boxes;
	};
}