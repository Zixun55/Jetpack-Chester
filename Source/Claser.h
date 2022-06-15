namespace game_framework {

	class Claser
	{
	public:
		Claser();
		bool HitEraser(Ccharacter *character);					// 是否碰到角色
		bool IsAlive();											// 是否活著
		void LoadBitmap();										// 載入圖形
		void OnMove();											// 移動
		void OnShow();											// 將圖形貼到畫面
		void SetXY(int nx, int ny);								// 設定座標
		void SetIsAlive(bool alive);							// 設定是否還在
		void SetMovingLeft(bool flag);							// 設定按下左鍵
		void SetMovingRight(bool flag);							// 設定按下右鍵
		void CantMoving(bool flag);								// 設定是否能移動
		void MovingCheck(bool flag, bool flag2);				// 載入與物體碰撞之運算
		void ch_CantMoving(bool flag);							// 設定角色之慣性
	protected:
		CAnimation laser;			// 用動畫做雷射	
		int x, y;					// 圓心的座標
		int dx, dy;					// 雷射的位移量
		bool is_alive;				// 是否還在
		bool isMovingLeft;			// 按下左鍵
		bool isMovingRight;			// 按下右鍵
		bool cantMoving;			// 是否能移動
		bool movingcheck;			// 碰撞運算之參數
		bool movingcheck2;          // 碰撞運算之參數
		bool ch_cantMoving;			// 角色之慣性
		bool direct;                // 慣性方向
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// 是否碰到參數範圍的矩形
	};
}