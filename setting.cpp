#define _CRT_SECURE_NO_WARNINGS 1
#include"something.h"

#include <graphics.h> // EasyX ͼ�ο�ͷ�ļ�
#include<windows.h>
#include<iostream>
#include <conio.h>
int num = 1;
int music_buttom_1 = 1;
/*��ɯ*/
/*���õ�ҳ�溯�����*/
void setting()
{
	//����
	cleardevice();
	//���ͼƬ
	IMAGE img1, img2, img3, img4, img5, img6, img6a, img3a, img4a, img5a;
	loadimage(&img2, "./picture/menu.png", 1200, 720, SRCPAINT);
	putimage(0, 0, &img2);
	//���ؼ�����
	setbkmode(TRANSPARENT);
	loadimage(&img1, "./picture/����.png", 50, 50, SRCPAINT);
	putimage(800, 190, &img1);
	//����������ɫ
	settextcolor(RGB(118, 190, 225));
	//����������ʽ����С������
	settextstyle(35, 20, _T("����"));
	outtextxy(450, 280, "��Ч��");
	outtextxy(450, 340, "�Ѷȣ�");
	outtextxy(550, 400, "�ͣ�");
	outtextxy(550, 470, "��:");
	outtextxy(550, 540, "��:");
	//�������ò���
		//��Ч
		//����ͼƬ��ť

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

					mciSendString("pause LL_menu ", 0, 0, 0);//��ҳ������ͣ

				}
				else
				{
					music_buttom_1 = 1;


					mciSendString("play LL_menu repeat", 0, 0, 0); // �������֣�repeat��ʾѭ������


				}
			}
		}

		/*��Ⱦ����*/
		if (music_buttom_1)
		{

			loadimage(&img6a, "./picture/��ͣ(1).png", 50, 50, SRCPAINT);
			putimage(580, 275, &img6a);
		}
		else {
			loadimage(&img6, "./picture/��ͣ��(1).png", 50, 50, SRCPAINT);
			putimage(580, 275, &img6);;
		}

		// ��ѭ��
		//���׶ȱ任

		if (num == 1)
		{
			loadimage(&img3a, "./picture/��ѡ.png", 50, 50, SRCPAINT);
			putimage(620, 390, &img3a);
			loadimage(&img4, "./picture/��ѡ.png", 50, 50, SRCPAINT);
			putimage(620, 460, &img4);
			loadimage(&img5a, "./picture/��ѡ.png", 50, 50, SRCPAINT);
			putimage(620, 530, &img5a);


		}
		else if (num == 2)
		{
			loadimage(&img3a, "./picture/��ѡ.png", 50, 50, SRCPAINT);
			putimage(620, 390, &img3a);
			loadimage(&img4, "./picture/��ѡ.png", 50, 50, SRCPAINT);
			putimage(620, 460, &img4);
			loadimage(&img5a, "./picture/��ѡ.png", 50, 50, SRCPAINT);
			putimage(620, 530, &img5a);

		}
		else if (num == 3)
		{
			loadimage(&img3a, "./picture/��ѡ.png", 50, 50, SRCPAINT);
			putimage(620, 390, &img3a);
			loadimage(&img4, "./picture/��ѡ.png", 50, 50, SRCPAINT);
			putimage(620, 460, &img4);
			loadimage(&img5, "./picture/��ѡ.png", 50, 50, SRCPAINT);
			putimage(620, 530, &img5);

		}

		if (msg.message == WM_LBUTTONDOWN)//������
		{
			int mouseX = msg.x;
			int mouseY = msg.y;
			if (mouseX > 620 && mouseX < 670 && mouseY > 390 && mouseY < 440) {
				num = 1;

				//loadimage(&img3, "./picture/��ѡ.png", 50, 50, SRCPAINT);
				//putimage(620, 390, &img3);
			}
			else
			{
				/*loadimage(&img3a, "./picture/��ѡ.png", 50, 50, SRCPAINT);
				putimage(620, 390, &img3a);*/
			}

			if (mouseX > 620 && mouseX < 670 && mouseY > 460 && mouseY < 510) {
				num = 2;
				/*loadimage(&img4, "./picture/��ѡ.png", 50, 50, SRCPAINT);
				putimage(620, 460, &img4);*/
			}
			else
			{
				/*loadimage(&img4a, "./picture/��ѡ.png", 50, 50, SRCPAINT);
				putimage(620, 460, &img4a);*/
			}

			if (mouseX > 620 && mouseX < 670 && mouseY > 530 && mouseY < 580) {
				num = 3;
				/*loadimage(&img5, "./picture/��ѡ.png", 50, 50, SRCPAINT);
				putimage(620, 530, &img5);*/
			}
			else
			{
				/*loadimage(&img5a, "./picture/��ѡ.png", 50, 50, SRCPAINT);
				putimage(620, 530, &img5a);*/
			}


			//��ʾ�˳���ť
			if (mouseX > 800 && mouseX < 850 && mouseY > 190 && mouseY < 240)
			{
				draw();

			}
		}
	}
	Sleep(1);
}