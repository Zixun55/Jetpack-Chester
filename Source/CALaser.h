#include <vector>
#include "Ccoin.h"
namespace game_framework {

	class CALaser
	{
	public:
		CALaser();
		~CALaser();
		void Initialize(int maps);		// 初始化
		void LoadBitmap();				// 載入圖形
		void OnMove();					// 所有物件的移動判定
		void OnShow();					// 呼叫所有物件的OnShow，讓物件貼到畫面上
		void CantMoving(bool flag);		// 判斷物件是否能移動
		void SetMovingLeft(bool flag);  // 按下方向鍵左鍵
		void SetMovingRight(bool flag); // 按下方向鍵右鍵
		void SetAudioLaser(bool flag);  // 設定是否撥放雷射音效
		void SetAudioCoin(bool flag);   // 設定是否撥放金幣音效
		int  ClosestBox();              // 離角色最近的箱子
		int  GetLife_n();               // 回傳當前生命值
		int  Getpoint_n();				// 回傳當前金幣分數
		bool Audio_Laser();				// 回傳是否撥放雷射音效
		bool Audio_Coin();				// 回傳是否撥放金幣音效
		bool map_finish_map();			// 回傳地圖是否有跑到終點
	protected:
		bool check_chx;
		bool check_chx2;
		bool cantMoving;				 // 物件是否能移動
		bool isLeft = false;			 // 是否按下方向鍵左鍵
		bool isRight = false;			 // 是否按下方向鍵右鍵
		bool isLoadBitmap = false;       // 是否已載入過圖片
		bool audio_laser = false;		 // 是否撥放雷射音效
		bool audio_coin = false;         // 是否撥放金幣音效
		Ccoin    *coins;			     // 金幣
		Claser    *laser2;				 // 雷射_直
		CBlock    *laser;				 // 雷射_橫
		Ccharacter chtest;				 // 角色
		CLife      Life;				 // 生命
		Cpoint     point;				 // 金幣分數
		CBox       *boxes;				 // 箱子
		CMap       map;					 // 地圖
	};
}