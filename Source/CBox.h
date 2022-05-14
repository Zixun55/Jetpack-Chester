#ifndef CBOX_H 
#define CBOX_H
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class����¶��骺�y
	// �����N�i�H��g���ۤv���{���F
	/////////////////////////////////////////////////////////////////////////////

	class CBox
	{
	public:
		CBox();
		bool HitEraser(Ccharacter *character);						// �O�_�I�����l
		bool IsAlive();											// �O�_����
		void LoadBitmap();										// ���J�ϧ�
		void OnMove();											// ����
		void OnShow();											// �N�ϧζK��e��
		void SetXY(int nx, int ny);								// �]�w��ߪ��y��
		void SetMovingLeft(bool flag);
		void SetMovingRight(bool flag);
		void CantMoving(bool flag);
		void MovingCheck(bool flag,bool flag2);
		bool ChxBigThanBox(Ccharacter *character);
		bool ChxXBigThanBox(Ccharacter *character);
		bool ChxXSmallThanBox(Ccharacter *character);
		
		int  BoxX1();
	protected:
		CAnimation bmp;			// �y����	
		int x, y;					// ��ߪ��y��
		int dx, dy;					// �y�Z����ߪ��첾�q
		bool is_alive;				// �O�_����
		bool isMovingLeft;
		bool isMovingRight;
		bool cantMoving;
		bool movingcheck;
		bool movingcheck2;
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// �O�_�I��Ѽƽd�򪺯x��
	};
}
#endif