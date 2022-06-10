#ifndef CBOX_H 
#define CBOX_H
namespace game_framework {

	class CBox
	{
	public:
		CBox();
		bool HitEraser(Ccharacter *character);					// �O�_�I�쨤��
		bool IsAlive();											// �O�_�٦b
		void LoadBitmap();										// ���J�ϧ�
		void OnMove();											// ����
		void OnShow();											// �N�ϧζK��e��
		void SetXY(int nx, int ny);								// �]�w�y��
		void SetMovingLeft(bool flag);
		void SetMovingRight(bool flag);
		void CantMoving(bool flag);
		void MovingCheck(bool flag,bool flag2);
		bool ChxBigThanBox(Ccharacter *character);
		bool ChxXBigThanBox(Ccharacter *character);
		bool ChxXSmallThanBox(Ccharacter *character);
		
		int  BoxX1();
	protected:
		CAnimation bmp;				// �c�l�ΰʵe������	
		int x, y;					// �y��
		int dx, dy;					// �γo�Ӱ��첾
		bool is_alive;				// �O�_�٦b
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