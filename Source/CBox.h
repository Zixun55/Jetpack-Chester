namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供繞圈圈的球
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////

	class CBox
	{
	public:
		CBox();
		bool HitEraser(Ccharacter *character);						// 是否碰到擦子
		bool IsAlive();											// 是否活著
		void LoadBitmap();										// 載入圖形
		void OnMove();											// 移動
		void OnShow();											// 將圖形貼到畫面
		void SetXY(int nx, int ny);								// 設定圓心的座標
		void SetMovingLeft(bool flag);
		void SetMovingRight(bool flag);
		void CantMoving(bool flag);
		bool ChxBigThanBox(Ccharacter *character);
		int  BoxX1();
	protected:
		CAnimation bmp;			// 球的圖	
		int x, y;					// 圓心的座標
		int dx, dy;					// 球距離圓心的位移量
		bool is_alive;				// 是否活著
		bool isMovingLeft;
		bool isMovingRight;
		bool cantMoving;
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// 是否碰到參數範圍的矩形
	};
}