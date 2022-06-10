#include <vector>
#include "Ccoin.h"
namespace game_framework {

	class CALaser
	{
	public:
		CALaser();
		~CALaser();
		void Initialize(int maps);		// ��l��
		void LoadBitmap();				// ���J�ϧ�
		void OnMove();					// �Ҧ����󪺲��ʧP�w
		void OnShow();					// �I�s�Ҧ�����OnShow�A������K��e���W
		void CantMoving(bool flag);		// �P�_����O�_�ಾ��
		void SetMovingLeft(bool flag);  // ���U��V�䥪��
		void SetMovingRight(bool flag); // ���U��V��k��
		void SetAudioLaser(bool flag);  // �]�w�O�_����p�g����
		void SetAudioCoin(bool flag);   // �]�w�O�_�����������
		int  ClosestBox();              // ������̪񪺽c�l
		int  GetLife_n();               // �^�Ƿ�e�ͩR��
		int  Getpoint_n();				// �^�Ƿ�e��������
		bool Audio_Laser();				// �^�ǬO�_����p�g����
		bool Audio_Coin();				// �^�ǬO�_�����������
		bool map_finish_map();			// �^�Ǧa�ϬO�_���]����I
	protected:
		bool check_chx;
		bool check_chx2;
		bool cantMoving;				 // ����O�_�ಾ��
		bool isLeft = false;			 // �O�_���U��V�䥪��
		bool isRight = false;			 // �O�_���U��V��k��
		bool isLoadBitmap = false;       // �O�_�w���J�L�Ϥ�
		bool audio_laser = false;		 // �O�_����p�g����
		bool audio_coin = false;         // �O�_�����������
		Ccoin    *coins;			     // ����
		Claser    *laser2;				 // �p�g_��
		CBlock    *laser;				 // �p�g_��
		Ccharacter chtest;				 // ����
		CLife      Life;				 // �ͩR
		Cpoint     point;				 // ��������
		CBox       *boxes;				 // �c�l
		CMap       map;					 // �a��
	};
}