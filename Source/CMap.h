namespace game_framework {


	class CMap
	{
	public:
		CMap();
		int  GetX1();
		int  GetY1();
		int  GetX2();
		int  GetY2();
		void Initialize();
		void LoadBitmap();
		void OnMove();
		void OnShow();
		void SetMovingDown(bool flag);
		void SetMovingLeft(bool flag);
		void SetMovingRight(bool flag);
		void SetMovingUp(bool flag);
		void SetXY(int nx, int ny);
		void CantMoving(bool flag);
		void chooseMap(int maps);
	protected:
		CAnimation animation;
		int x, y;
		bool isMovingDown;
		bool isMovingLeft;
		bool isMovingRight;
		bool isMovingUp;
		bool cantMoving;
		int  map;
	};
}