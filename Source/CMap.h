
namespace game_framework {


	class CMap
	{
	public:
		CMap();
		int  GetX1();								// 地圖左上X座標
		int  GetY1();								// 地圖左上Y座標
		int  GetX2();								// 地圖右下X座標
		int  GetY2();								// 地圖右下Y座標
		void Initialize();							// 初始化
		void LoadBitmap();							// 載入地圖
		void OnMove();								// 移動
		void OnShow();								// 貼上圖形
		void SetMovingLeft(bool flag);				// 設定按下左鍵
		void SetMovingRight(bool flag);				// 設定按下右鍵
		void SetXY(int nx, int ny);					// 設定地圖的座標
		void CantMoving(bool flag);					// 設定是否能移動
		void MovingCheck(bool flag, bool flag2);    // 載入與物體碰撞之運算
		void chooseMap(int maps);					// 選擇為哪張地圖
		bool FinishMap();							// 是否完成地圖
		bool Left_Moving_Start();					// 地圖無法在初始點向左移動
		void ch_CantMoving(bool flag);				// 設定角色之慣性
	protected:
		CAnimation animation;						// 圖
		int x, y;									// 座標
		bool isMovingLeft;							// 按下左鍵
		bool isMovingRight;							// 按下右鍵
		bool cantMoving;							// 是否能移動
		bool movingcheck;							// 碰撞運算之參數
		bool movingcheck2;							// 碰撞運算之參數
		bool left_moving_start;						// 無法在初始點向左移動
		bool ch_cantMoving;							// 角色之慣性
		bool direct;								// 慣性方向
		int  map;									// 地圖選擇
		Ccharacter chtest;							// 角色
	};
}