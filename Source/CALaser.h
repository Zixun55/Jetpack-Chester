#include <vector>
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
		int  GetCheck_map();
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void SetMovingLeft(bool flag);
		void SetMovingRight(bool flag);
	protected:
		int check_map;
		int x, y;
		bool cantMoving;
		bool isLeft  = false;
		bool isRight = false;
		bool isLoadBitmap = false;
		Claser    *laser2;
		CBlock    *laser;
		Ccharacter chtest;          // ¨¤¦â
		CLife      Life;
		CBox       *boxes;
	};
}