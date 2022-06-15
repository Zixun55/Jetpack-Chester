
namespace game_framework {


	class CMap
	{
	public:
		CMap();
		int  GetX1();								// �a�ϥ��WX�y��
		int  GetY1();								// �a�ϥ��WY�y��
		int  GetX2();								// �a�ϥk�UX�y��
		int  GetY2();								// �a�ϥk�UY�y��
		void Initialize();							// ��l��
		void LoadBitmap();							// ���J�a��
		void OnMove();								// ����
		void OnShow();								// �K�W�ϧ�
		void SetMovingLeft(bool flag);				// �]�w���U����
		void SetMovingRight(bool flag);				// �]�w���U�k��
		void SetXY(int nx, int ny);					// �]�w�a�Ϫ��y��
		void CantMoving(bool flag);					// �]�w�O�_�ಾ��
		void MovingCheck(bool flag, bool flag2);    // ���J�P����I�����B��
		void chooseMap(int maps);					// ��ܬ����i�a��
		bool FinishMap();							// �O�_�����a��
		bool Left_Moving_Start();					// �a�ϵL�k�b��l�I�V������
		void ch_CantMoving(bool flag);				// �]�w���⤧�D��
	protected:
		CAnimation animation;						// ��
		int x, y;									// �y��
		bool isMovingLeft;							// ���U����
		bool isMovingRight;							// ���U�k��
		bool cantMoving;							// �O�_�ಾ��
		bool movingcheck;							// �I���B�⤧�Ѽ�
		bool movingcheck2;							// �I���B�⤧�Ѽ�
		bool left_moving_start;						// �L�k�b��l�I�V������
		bool ch_cantMoving;							// ���⤧�D��
		bool direct;								// �D�ʤ�V
		int  map;									// �a�Ͽ��
		Ccharacter chtest;							// ����
	};
}