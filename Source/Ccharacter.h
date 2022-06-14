namespace game_framework {


	class Ccharacter
	{
	public:
		Ccharacter(); 
		int  GetX1();						// ���⥪�WX�y��
		int  GetY1();						// ���⥪�WY�y��
		int  GetX2();						// ����k�UX�y��
		int  GetY2();						// ����k�UY�y��
		void Initialize();					// ��l��
		void LoadBitmap();					// ���J�Ϥ�
		void OnMove();						// ���ʧP�w
		void OnShow();						// �K�W�Ϥ�
		void SetMovingLeft(bool flag);		// ���U��V�䥪��
		void SetMovingRight(bool flag);		// ���U��V��k��
		void SetXY(int nx, int ny);			// �]�w���⪺�y��
		void CantMoving(bool flag);			// �P�_����O�_�ಾ��
		bool isCantMoving();                // �^��cantMoing
	protected:
		CAnimation animation;				// �ΰʵe������ʵe
		CMovingBitmap steam, steam1, steam2,steamR, steamR1, steamR2; // �ΰʵe���]�𪺰ʵe
		int x, y;							// ���⪺�y��
		bool isMovingDown;					// 
		bool isMovingLeft;
		bool isMovingRight;
		bool isMovingUp;
		bool cantMoving;
		int Bigthanbox;

	private:
		bool con = true;
		int counter;
	};
	
}