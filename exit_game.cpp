#define _CRT_SECURE_NO_WARNINGS 1


/*
�˳���Ϸ�ӿ�

������ : ����
���� : �˳���Ϸ
*/



#include"something.h"

void exit_game() {
	cleardevice();//����

	Picture_LL_exit_game();
	while (1) {


		ExMessage LL_exit;
		if (peekmessage(&LL_exit)) {
			if (LL_exit.message == WM_LBUTTONDOWN && LL_exit.x > 300 && LL_exit.y > 300 && LL_exit.x < 418 && LL_exit.y < 367) {
				mciSendString("close LL_menu ", 0, 0, 0);//��ҳ������ͣ
				closegraph();//�رմ���
				std::cout << "�˳��ɹ�";
			}
			//���ز˵�
			if (LL_exit.message == WM_LBUTTONDOWN && LL_exit.x > 500 && LL_exit.y > 300 && LL_exit.x < 618 && LL_exit.y < 367) {
				break;
			}
		}


	}
}
//�˳���Ϸ����
void Picture_LL_exit_game() {
	BeginBatchDraw();//˫����
	IMAGE HP_1;
	loadimage(&HP_1, "picture/LL_exit_game.png", 1200, 720);
	putimage(0, 0, &HP_1);
	EndBatchDraw();//˫����
}