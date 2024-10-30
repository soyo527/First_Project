#define _CRT_SECURE_NO_WARNINGS 1
#include"something.h"

#include <graphics.h> // EasyX 图形库头文件
#include<windows.h>
#include<iostream>
#include <conio.h>
int num = 1;
int music_buttom_1 = 1;
/*李莎*/
/*设置的页面函数设计*/
void setting()
{
	//清屏
	cleardevice();
	//输出图片
	IMAGE img1, img2, img3, img4, img5, img6, img6a, img3a, img4a, img5a;
	loadimage(&img2, "./picture/menu.png", 1200, 720, SRCPAINT);
	putimage(0, 0, &img2);
	//返回键设置
	setbkmode(TRANSPARENT);
	loadimage(&img1, "./picture/返回.png", 50, 50, SRCPAINT);
	putimage(800, 190, &img1);
	//设置文字颜色
	settextcolor(RGB(118, 190, 225));
	//设置文字样式，大小，字体
	settextstyle(35, 20, _T("宋体"));
	outtextxy(450, 280, "音效：");
	outtextxy(450, 340, "难度：");
	outtextxy(550, 400, "低：");
	outtextxy(550, 470, "中:");
	outtextxy(550, 540, "高:");
	//处理设置操作
		//音效
		//播放图片按钮

	ExMessage msg;
	while (true)
	{
		msg = getmessage();
		if (msg.message == WM_LBUTTONDOWN)
		{
			if (msg.x >= 580 && msg.x <= 630 && msg.y >= 275 && msg.y <= 325)
			{
				if (music_buttom_1)
				{
					music_buttom_1 = 0;

					mciSendString("pause LL_menu ", 0, 0, 0);//主页音乐暂停

				}
				else
				{
					music_buttom_1 = 1;


					mciSendString("play LL_menu repeat", 0, 0, 0); // 播放音乐，repeat表示循环播放


				}
			}
		}

		/*渲染画面*/
		if (music_buttom_1)
		{

			loadimage(&img6a, "./picture/暂停(1).png", 50, 50, SRCPAINT);
			putimage(580, 275, &img6a);
		}
		else {
			loadimage(&img6, "./picture/暂停后(1).png", 50, 50, SRCPAINT);
			putimage(580, 275, &img6);;
		}

		// 主循环
		//难易度变换

		if (num == 1)
		{
			loadimage(&img3a, "./picture/勾选.png", 50, 50, SRCPAINT);
			putimage(620, 390, &img3a);
			loadimage(&img4, "./picture/空选.png", 50, 50, SRCPAINT);
			putimage(620, 460, &img4);
			loadimage(&img5a, "./picture/空选.png", 50, 50, SRCPAINT);
			putimage(620, 530, &img5a);


		}
		else if (num == 2)
		{
			loadimage(&img3a, "./picture/空选.png", 50, 50, SRCPAINT);
			putimage(620, 390, &img3a);
			loadimage(&img4, "./picture/勾选.png", 50, 50, SRCPAINT);
			putimage(620, 460, &img4);
			loadimage(&img5a, "./picture/空选.png", 50, 50, SRCPAINT);
			putimage(620, 530, &img5a);

		}
		else if (num == 3)
		{
			loadimage(&img3a, "./picture/空选.png", 50, 50, SRCPAINT);
			putimage(620, 390, &img3a);
			loadimage(&img4, "./picture/空选.png", 50, 50, SRCPAINT);
			putimage(620, 460, &img4);
			loadimage(&img5, "./picture/勾选.png", 50, 50, SRCPAINT);
			putimage(620, 530, &img5);

		}

		if (msg.message == WM_LBUTTONDOWN)//鼠标左键
		{
			int mouseX = msg.x;
			int mouseY = msg.y;
			if (mouseX > 620 && mouseX < 670 && mouseY > 390 && mouseY < 440) {
				num = 1;

				//loadimage(&img3, "./picture/勾选.png", 50, 50, SRCPAINT);
				//putimage(620, 390, &img3);
			}
			else
			{
				/*loadimage(&img3a, "./picture/空选.png", 50, 50, SRCPAINT);
				putimage(620, 390, &img3a);*/
			}

			if (mouseX > 620 && mouseX < 670 && mouseY > 460 && mouseY < 510) {
				num = 2;
				/*loadimage(&img4, "./picture/勾选.png", 50, 50, SRCPAINT);
				putimage(620, 460, &img4);*/
			}
			else
			{
				/*loadimage(&img4a, "./picture/空选.png", 50, 50, SRCPAINT);
				putimage(620, 460, &img4a);*/
			}

			if (mouseX > 620 && mouseX < 670 && mouseY > 530 && mouseY < 580) {
				num = 3;
				/*loadimage(&img5, "./picture/勾选.png", 50, 50, SRCPAINT);
				putimage(620, 530, &img5);*/
			}
			else
			{
				/*loadimage(&img5a, "./picture/空选.png", 50, 50, SRCPAINT);
				putimage(620, 530, &img5a);*/
			}


			//显示退出按钮
			if (mouseX > 800 && mouseX < 850 && mouseY > 190 && mouseY < 240)
			{
				draw();

			}
		}
	}
	Sleep(1);
}