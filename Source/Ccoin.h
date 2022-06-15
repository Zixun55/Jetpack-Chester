#pragma once
namespace game_framework {

	class Ccoin
	{
	public:
		Ccoin();
		bool HitEraser(Ccharacter *character);					// �O�_�I�쨤��
		bool IsAlive();											// �O�_�٦b
		void LoadBitmap();										// ���J�ϧ�
		void OnMove();											// ����
		void OnShow();											// �N�ϧζK��e��
		void SetXY(int nx, int ny);								// �]�w�y��
		void SetIsAlive(bool alive);							// �]�w�O�_�٦b
		void SetMovingLeft(bool flag);							// �]�w���U����
		void SetMovingRight(bool flag);							// �]�w���U�k��
		void CantMoving(bool flag);								// �]�w�O�_�ಾ��
		void MovingCheck(bool flag, bool flag2);				// ���J�P����I�����B��
		void ch_CantMoving(bool flag);							// �]�w���⤧�D��
	protected:
		CAnimation coin;			// ��������	
		int x, y;					// �y��
		int dx, dy;					// �������첾
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