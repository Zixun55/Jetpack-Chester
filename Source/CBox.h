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
		void SetMovingLeft(bool flag);
		void SetMovingRight(bool flag);
		void CantMoving(bool flag);
		void MovingCheck(bool flag,bool flag2);
		bool ChxBigThanBox(Ccharacter *character);
		bool ChxXBigThanBox(Ccharacter *character);
		bool ChxXSmallThanBox(Ccharacter *character);
		
		int  BoxX1();
	protected:
		CAnimation bmp;				// 箱子用動畫做移動	
		int x, y;					// 座標
		int dx, dy;					// 用這個做位移
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
#endif