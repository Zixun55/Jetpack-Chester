namespace game_framework {


	class Ccharacter
	{
	public:
		Ccharacter(); 
		int  GetX1();						// 角色左上X座標
		int  GetY1();						// 角色左上Y座標
		int  GetX2();						// 角色右下X座標
		int  GetY2();						// 角色右下Y座標
		void Initialize();					// 初始化
		void LoadBitmap();					// 載入圖片
		void OnMove();						// 移動判定
		void OnShow();						// 貼上圖片
		void SetMovingLeft(bool flag);		// 按下方向鍵左鍵
		void SetMovingRight(bool flag);		// 按下方向鍵右鍵
		void SetXY(int nx, int ny);			// 設定角色的座標
		void CantMoving(bool flag);			// 判斷物件是否能移動
		bool isCantMoving();                // 回傳cantMoing
	protected:
		CAnimation animation;				// 用動畫做角色動畫
		CMovingBitmap steam, steam1, steam2,steamR, steamR1, steamR2; // 用動畫做蒸氣的動畫
		int x, y;							// 角色的座標
		bool isMovingDown;					// 
		bool isMovingLeft;
		bool isMovingRight;
		bool isMovingUp;
		bool cantMoving;
		int Bigthanbox;

	private:
		bool con = true;
		int counter;
	};
	
}