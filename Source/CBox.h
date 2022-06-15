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
		void SetMovingLeft(bool flag);							// ���U����
		void SetMovingRight(bool flag);							// ���U�k��
		void CantMoving(bool flag);								// �]�w�O�_�ಾ��
		void MovingCheck(bool flag,bool flag2);				    // ���J�P����I�����B��
		bool ChxBigThanBox(Ccharacter *character);				// �P����I�����B��
		bool ChxXBigThanBox(Ccharacter *character);				// �P����I�����B��
		bool ChxXSmallThanBox(Ccharacter *character);			// �P����I�����B��
		void ch_CantMoving(bool flag);							// �]�w���⤧�D��
		int  BoxX1();											// �^�ǽc�l���WX�y��
	protected:
		CAnimation bmp;				// �c�l�ΰʵe������	
		int x, y;					// �y��
		int dx, dy;					// �γo�Ӱ��첾
		bool is_alive;				// �O�_�٦b
		bool isMovingLeft;			// ���U����			
		bool isMovingRight;			// ���U�k��
		bool cantMoving;			// �O�_�ಾ��
		bool movingcheck;			// �I���B�⤧�Ѽ�
		bool movingcheck2;          // �I���B�⤧�Ѽ�
		bool ch_cantMoving;			// ���⤧�D��
		bool direct;                // �D�ʤ�V
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// �O�_�I��Ѽƽd�򪺯x��
	};
}
#endif