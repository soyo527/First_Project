#define _CRT_SECURE_NO_WARNINGS 1


/*
退出游戏接口

负责人 : 罗磊
功能 : 退出游戏
*/



#include"something.h"

void exit_game() {
	cleardevice();//清屏

	Picture_LL_exit_game();
	while (1) {


		ExMessage LL_exit;
		if (peekmessage(&LL_exit)) {
			if (LL_exit.message == WM_LBUTTONDOWN && LL_exit.x > 300 && LL_exit.y > 300 && LL_exit.x < 418 && LL_exit.y < 367) {
				mciSendString("close LL_menu ", 0, 0, 0);//主页音乐暂停
				closegraph();//关闭窗口
				std::cout << "退出成功";
			}
			//返回菜单
			if (LL_exit.message == WM_LBUTTONDOWN && LL_exit.x > 500 && LL_exit.y > 300 && LL_exit.x < 618 && LL_exit.y < 367) {
				break;
			}
		}


	}
}
//退出游戏界面
void Picture_LL_exit_game() {
	BeginBatchDraw();//双缓冲
	IMAGE HP_1;
	loadimage(&HP_1, "picture/LL_exit_game.png", 1200, 720);
	putimage(0, 0, &HP_1);
	EndBatchDraw();//双缓冲
}