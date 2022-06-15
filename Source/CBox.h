#ifndef CBOX_H 
#define CBOX_H
namespace game_framework {

	class CBox
	{
	public:
		CBox();
		bool HitEraser(Ccharacter *character);					// 是否碰到角色
		bool IsAlive();											// 是否還在
		void LoadBitmap();										// 載入圖形
		void OnMove();											// 移動
		void OnShow();											// 將圖形貼到畫面
		void SetXY(int nx, int ny);								// 設定座標
		void SetMovingLeft(bool flag);							// 按下左鍵
		void SetMovingRight(bool flag);							// 按下右鍵
		void CantMoving(bool flag);								// 設定是否能移動
		void MovingCheck(bool flag,bool flag2);				    // 載入與物體碰撞之運算
		bool ChxBigThanBox(Ccharacter *character);				// 與物體碰撞之運算
		bool ChxXBigThanBox(Ccharacter *character);				// 與物體碰撞之運算
		bool ChxXSmallThanBox(Ccharacter *character);			// 與物體碰撞之運算
		void ch_CantMoving(bool flag);							// 設定角色之慣性
		int  BoxX1();											// 回傳箱子左上X座標
	protected:
		CAnimation bmp;				// 箱子用動畫做移動	
		int x, y;					// 座標
		int dx, dy;					// 用這個做位移
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
#endif