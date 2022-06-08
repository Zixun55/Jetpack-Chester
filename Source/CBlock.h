namespace game_framework {

	class CBlock
	{
	public:
		CBlock();
		bool HitEraser(Ccharacter *character);						// �O�_�I�쨤��
		bool IsAlive();											// �O�_�٦b
		void LoadBitmap();										// ���J�ϧ�
		void OnMove();											// ����
		void OnShow();											// �N�ϧζK��e��
		void SetXY(int nx, int ny);								// �]�w�y��
		void SetIsAlive(bool alive);							// �]�w�O�_����
		void SetMovingLeft(bool flag);
		void SetMovingRight(bool flag);
		void CantMoving(bool flag);
		void MovingCheck(bool flag, bool flag2);
	protected:
		CAnimation laser;			// �y����	
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