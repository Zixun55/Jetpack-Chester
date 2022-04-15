namespace game_framework {


	class Ccharacter
	{
	public:
		Ccharacter(); 
		int  GetX1();
		int  GetY1();
		int  GetX2();
		int  GetY2();
		void Initialize();
		void LoadBitmap();
		void OnMove();
		void OnShow();
		void SetMovingLeft(bool flag);
		void SetMovingRight(bool flag);
		void SetXY(int nx, int ny);
		void CantMoving(bool flag);
	protected:
		CAnimation animation;
		CMovingBitmap steam,steamR;
		int x, y;
		bool isMovingDown;
		bool isMovingLeft;
		bool isMovingRight;
		bool isMovingUp;
		bool cantMoving;
	private:
		bool con = true;
	};
	
}