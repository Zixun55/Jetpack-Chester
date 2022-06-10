#pragma once
namespace game_framework {

	class Ccoin
	{
	public:
		Ccoin();
		bool HitEraser(Ccharacter *character);					// 是否碰到角色
		bool IsAlive();											// 是否還在
		void LoadBitmap();										// 載入圖形
		void OnMove();											// 移動
		void OnShow();											// 將圖形貼到畫面
		void SetXY(int nx, int ny);								// 設定座標
		void SetIsAlive(bool alive);							// 設定是否還在
		void SetMovingLeft(bool flag);
		void SetMovingRight(bool flag);
		void CantMoving(bool flag);
		void MovingCheck(bool flag, bool flag2);
	protected:
		CAnimation coin;			// 錢幣的圖	
		int x, y;					// 座標
		int dx, dy;					// 錢幣的位移
		bool is_alive;				// 是否還在
		bool isMovingLeft;
		bool isMovingRight;
		bool cantMoving;
		bool movingcheck;
		bool movingcheck2;
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// 是否碰到參數範圍的矩形
	};
}