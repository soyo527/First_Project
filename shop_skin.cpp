#define _CRT_SECURE_NO_WARNINGS 1

#define _CRT_SECURE_NO_WARNINGS 1

/*
	�̾�
*/


#include"something.h"
extern int music_buttom_1;


extern int get_gold_1;

int skin[14] = { 0 };


int get_gold_file;//��ȡ���浵�Ľ��

void show_now_skin(int now_skin);


//��ȡ�浵��Һ���
void read_gold() {
	ifstream infile("./gold/gold.txt");
	if (infile.is_open()) {
		infile >> get_gold_file;

	}
}

//�������
void save_gold() {
	ofstream outFile("./gold/gold.txt");
	if (outFile.is_open()) {
		outFile << (get_gold_file - 1000);
	}
	outFile.close();
}

//�̾���Ҫ�����load_gold����
void load_gold() {
	int old_gold = 0;
	// �����Զ�ȡģʽ���ļ�
	ifstream file("./gold/gold.txt");

	if (!file) {
		// �ļ��޷��򿪣�˵���ļ������ڣ��������ļ�����ʼ��Ϊ0
		ofstream createFile("./gold/gold.txt");
		createFile << get_gold_1;
		createFile.close();
	}
	else {
		// �ļ��ɹ��򿪣����ж�ȡ�ɵĻƽ�����
		file >> old_gold;
		file.close(); // ��ȡ��ɺ�ر��ļ�

		// ���� get_gold
		get_gold_1 += old_gold;

		// ������д��ģʽ���ļ��������ļ�����
		ofstream file("./gold/gold.txt");
		file << get_gold_1;
		file.close();
		get_gold_1 = 0;
	}
}


int now_skin = 0;
void load_skin() {//���ڶ�ȡƤ����װ��Ƥ����Ϣ

	// �����Զ�ȡģʽ���ļ�
	ifstream file("./skin/now_skin.txt");

	if (file.is_open()) {
		// �ļ��ɹ��򿪣����ж�ȡװ��Ƥ�����
		file >> now_skin;
		file.close(); // ��ȡ��ɺ�ر��ļ�
	}
}


//����װ��Ƥ����Ϣ
void save_skin() {//���ڶ�ȡƤ����װ��Ƥ����Ϣ

	// �����Զ�ȡģʽ���ļ�
	ofstream file("./skin/now_skin.txt");

	if (file.is_open()) {
		// �ļ��ɹ��򿪣�����д��װ��Ƥ����ŵ��浵
		file << now_skin;
		file.close(); // ��ȡ��ɺ�ر��ļ�
	}
}






//����
void save_skin_num() {//������ӵ��Ƥ�����浵

	// �����Զ�ȡģʽ���ļ�
	ofstream file("./skin/skin_num.txt");

	if (file.is_open()) {

		for (int i = 0; i < 14; i++)
		{
			file << skin[i] << endl;

		}

		file.close(); // ��ȡ��ɺ�ر��ļ�
	}
}


//��ȡ
void load_skin_num()//��ȡ�浵������ݵ�skin����
{

	ifstream file("./skin/skin_num.txt");
	if (file.is_open()) {

		for (int i = 0; i < 14; i++)
		{
			file >> skin[i];


		}

		file.close(); // ��ȡ��ɺ�ر��ļ�
	}



}




IMAGE img;
IMAGE img_skin[14];
ExMessage msg1 = { 0 };




void music_skin();  //����
void mouse_skin();  //�������λ���ж�

/*�̳ǻ�����ҳ�溯�����*/
void shop_skin()
{
	//load_gold();
	cleardevice();
	mciSendString("open ./music/LL_skin.mp3 alias bgm", 0, 0, 0);

	if (music_buttom_1)
	{
		music_skin();  //������
	}


	//���������������
	loadimage(&img, "./picture/beijing.png", 1200, 720);
	putimage(0, 0, &img);
	loadimage(&img, "./picture/jinbi1.png", 50, 50);
	putimage(800, 600, &img);
	loadimage(&img, "./picture/����.png", 60, 60);
	putimage(950, 200, &img);


	setbkmode(TRANSPARENT);
	settextcolor(YELLOW);
	settextstyle(20, 0, "����");
	outtextxy(910, 280, "��ǰЯ��Ƥ��");
	setfillcolor(WHITE);
	
	show_now_skin(now_skin);

	//Ƥ����һ��
	loadimage(img_skin + 1, "./picture/skin01.png", 70, 75);
	putimage(200, 250, img_skin + 1);
	loadimage(&img, "./picture/jinbi1.png", 35, 35);
	putimage(170, 330, &img);




	loadimage(img_skin + 2, "./picture/skin02.png", 70, 75);
	putimage(320, 250, img_skin + 2);
	loadimage(&img, "./picture/jinbi1.png", 35, 35);
	putimage(290, 330, &img);


	loadimage(img_skin + 3, "./picture/skin03.png", 70, 75);
	putimage(440, 250, img_skin + 3);
	loadimage(&img, "./picture/jinbi1.png", 35, 35);
	putimage(410, 330, &img);


	loadimage(img_skin + 4, "./picture/skin04.png", 70, 75);
	putimage(560, 250, img_skin + +4);
	loadimage(&img, "./picture/jinbi1.png", 35, 35);
	putimage(530, 330, &img);


	loadimage(img_skin + 5, "./picture/skin05.png", 70, 75);
	putimage(680, 250, img_skin + 5);
	loadimage(&img, "./picture/jinbi1.png", 35, 35);
	putimage(650, 330, &img);


	loadimage(img_skin + 6, "./picture/skin06.png", 70, 75);
	putimage(800, 250, img_skin + 6);
	loadimage(&img, "./picture/jinbi1.png", 35, 35);
	putimage(770, 330, &img);


	//Ƥ���ڶ���
	loadimage(img_skin + 7, "./picture/skin07.png", 70, 75);
	putimage(200, 380, img_skin + 7);
	loadimage(&img, "./picture/jinbi1.png", 35, 35);
	putimage(170, 460, &img);


	loadimage(img_skin + 8, "./picture/skin08.png", 70, 75);
	putimage(320, 380, img_skin + 8);
	loadimage(&img, "./picture/jinbi1.png", 35, 35);
	putimage(290, 460, &img);


	loadimage(img_skin + 9, "./picture/skin09.png", 70, 75);
	putimage(440, 380, img_skin + 9);
	loadimage(&img, "./picture/jinbi1.png", 35, 35);
	putimage(410, 460, &img);


	loadimage(img_skin + 10, "./picture/skin10.png", 70, 75);
	putimage(560, 380, img_skin + 10);
	loadimage(&img, "./picture/jinbi1.png", 35, 35);
	putimage(530, 460, &img);


	loadimage(img_skin + 11, "./picture/skin11.png", 70, 75);
	putimage(680, 380, img_skin + 11);
	loadimage(&img, "./picture/jinbi1.png", 35, 35);
	putimage(650, 460, &img);


	loadimage(img_skin + 12, "./picture/skin12.png", 70, 75);
	putimage(800, 380, img_skin + 12);
	loadimage(&img, "./picture/jinbi1.png", 35, 35);
	putimage(770, 460, &img);


	//Ƥ��������
	loadimage(img_skin + 13, "./picture/skin13.png", 70, 75);
	putimage(200, 510, img_skin + 13);
	loadimage(&img, "./picture/jinbi1.png", 35, 35);
	putimage(170, 590, &img);


	loadimage(img_skin + 14, "./picture/skin14.png", 70, 75);
	putimage(320, 510, img_skin + 14);
	loadimage(&img, "./picture/jinbi1.png", 35, 35);
	putimage(290, 590, &img);




	read_gold();
	load_skin_num();







	mouse_skin();

	//����������
	//��ʾ����������˳���ť
	//����Ƥ���Ĺ���

}














//�������������
void music_skin()
{

	mciSendString("play bgm repeat", 0, 0, 0);
}


//���ʵ�� �˳�  ����  ��������
bool inArea(int mx, int my, int x, int y, int w, int h)  //�ж����mx��my�Ƿ���ָ���ľ�������
{
	if (mx > x && mx<x + w && my>y && my < y + h)
	{
		return true;
	}
	return false;
}

bool button(int x, int y, int w, int h)  //���ڰ�ť����ʱ
{

	//�жϰ�ť�Ƿ񱻵��
	if (msg1.message == WM_LBUTTONDOWN && inArea(msg1.x, msg1.y, x, y, w, h))
	{
		return true;
	}
	return false;
}







void money_not_enough()//Ǯ����
{
	setfillcolor(RGB(6, 11, 66));
	setlinecolor(RED);
	fillrectangle(400, 210, 800, 510);
	setbkmode(TRANSPARENT);
	settextcolor(YELLOW);
	settextstyle(25, 0, "����");
	outtextxy(470, 270, "��Ҳ���,�������ؼ�");
	while (1)
	{
		if (peekmessage(&msg1, EX_MOUSE))
		{
			if (msg1.x > 400 && msg1.x <= 800 && msg1.y >= 210 && msg1.y <= 510)
			{
				shop_skin();
			}

		}
	}
}


void money_enough(int i)//Ǯ�������ڹ���ĺ���
{

	setfillcolor(RGB(6, 11, 66));
	setlinecolor(RED);
	fillrectangle(400, 210, 800, 510);
	setbkmode(TRANSPARENT);
	settextcolor(YELLOW);
	settextstyle(50, 0, "����");
	outtextxy(520, 270, "ȷ�Ϲ���?");
	outtextxy(470, 370, "��");
	outtextxy(670, 370, "��");

	while (1)
	{
		if (peekmessage(&msg1, EX_MOUSE))
		{
			if (button(470, 370, 50, 50))
			{
				save_gold();
				skin[i] = 1;
				save_skin_num();
				shop_skin();
			}

			else if (button(670, 370, 50, 50))
			{
				shop_skin();
			}
		}

	}


}



void show_now_skin(int i);

void use_skin(int i)//����װ���ĺ���
{


	now_skin = i;
	save_skin_num();
	load_skin_num();
	save_skin();
	show_now_skin(now_skin);
}


void show_now_skin(int now_skin)
{

	load_skin();


	switch (now_skin)
	{

	case 0:setlinecolor(RGB(2, 6, 146));
		setfillcolor(RGB(2, 6, 146));
		fillrectangle(950, 320, 1018, 394);
		loadimage(img_skin + 0, "./picture/skin01.png", 70, 75, SRCPAINT);
		putimage(950, 320, img_skin + 0);
		break;

	case 1:setlinecolor(RGB(2, 6, 146));
		setfillcolor(RGB(2, 6, 146));
		fillrectangle(950, 320, 1018, 394);
		loadimage(img_skin + 1, "./picture/skin02.png", 70, 75, SRCPAINT);
		putimage(950, 320, img_skin + 1);
		break;

	case 2:setlinecolor(RGB(2, 6, 146));
		setfillcolor(RGB(2, 6, 146));
		fillrectangle(950, 320, 1018, 394);
		loadimage(img_skin + 2, "./picture/skin03.png", 70, 75, SRCPAINT);
		putimage(950, 320, img_skin + 2);
		break;

	case 3:setlinecolor(RGB(2, 6, 146));
		setfillcolor(RGB(2, 6, 146));
		fillrectangle(950, 320, 1018, 394);
		loadimage(img_skin + 3, "./picture/skin04.png", 70, 75, SRCPAINT);
		putimage(950, 320, img_skin + 3);
		break;

	case 4:setlinecolor(RGB(2, 6, 146));
		setfillcolor(RGB(2, 6, 146));
		fillrectangle(950, 320, 1018, 394);
		loadimage(img_skin + 4, "./picture/skin05.png", 70, 75, SRCPAINT);
		putimage(950, 320, img_skin + 4);
		break;

	case 5:setlinecolor(RGB(2, 6, 146));
		setfillcolor(RGB(2, 6, 146));
		fillrectangle(950, 320, 1018, 394);
		loadimage(img_skin + 5, "./picture/skin06.png", 70, 75, SRCPAINT);
		putimage(950, 320, img_skin + 5);
		break;

	case 6:setlinecolor(RGB(2, 6, 146));
		setfillcolor(RGB(2, 6, 146));
		fillrectangle(950, 320, 1018, 394);
		loadimage(img_skin + 6, "./picture/skin07.png", 70, 75, SRCPAINT);
		putimage(950, 320, img_skin + 6);
		break;

	case 7:setlinecolor(RGB(2, 6, 146));
		setfillcolor(RGB(2, 6, 146));
		fillrectangle(950, 320, 1018, 394);
		loadimage(img_skin + 7, "./picture/skin08.png", 70, 75, SRCPAINT);
		putimage(950, 320, img_skin + 7);
		break;

	case 8:setlinecolor(RGB(2, 6, 146));
		setfillcolor(RGB(2, 6, 146));
		fillrectangle(950, 320, 1018, 394);
		loadimage(img_skin + 8, "./picture/skin09.png", 70, 75, SRCPAINT);
		putimage(950, 320, img_skin + 8);
		break;

	case 9:setlinecolor(RGB(2, 6, 146));
		setfillcolor(RGB(2, 6, 146));
		fillrectangle(950, 320, 1018, 394);
		loadimage(img_skin + 9, "./picture/skin10.png", 70, 75, SRCPAINT);
		putimage(950, 320, img_skin + 9);
		break;

	case 10:setlinecolor(RGB(2, 6, 146));
		setfillcolor(RGB(2, 6, 146));
		fillrectangle(950, 320, 1018, 394);
		loadimage(img_skin + 10, "./picture/skin11.png", 70, 75, SRCPAINT);
		putimage(950, 320, img_skin + 10);
		break;

	case 11:setlinecolor(RGB(2, 6, 146));
		setfillcolor(RGB(2, 6, 146));
		fillrectangle(950, 320, 1018, 394);
		loadimage(img_skin + 11, "./picture/skin12.png", 70, 75, SRCPAINT);
		putimage(950, 320, img_skin + 11);
		break;

	case 12:
		setlinecolor(RGB(2, 6, 146));
		setfillcolor(RGB(2, 6, 146));
		fillrectangle(950, 320, 1018, 394);
		loadimage(img_skin + 12, "./picture/skin13.png", 70, 75, SRCPAINT);
		putimage(950, 320, img_skin + 12);
		break;

	case 13:setlinecolor(RGB(2, 6, 146));
		setfillcolor(RGB(2, 6, 146));
		fillrectangle(950, 320, 1018, 394);
		loadimage(img_skin + 13, "./picture/skin14.png", 70, 75, SRCPAINT);
		putimage(950, 320, img_skin + 13);
		break;
	}





}





























//����Ƥ��
void mouse_skin()
{

	while (1)
	{

		settextstyle(50, 0, "����"); // ���ִ�С����ȣ����壻����������ʽ
		setbkmode(TRANSPARENT); // ȥ�����ֱ���
		settextcolor(RGB(255, 222, 125));
		char num_gold[20];
		sprintf_s(num_gold, "%d", get_gold_file);
		outtextxy(850, 600, num_gold);




		settextcolor(YELLOW);   //����1000����ı�
		settextstyle(20, 0, "����");
		setbkmode(TRANSPARENT);

		//��ʾ��ӵ�кͽ��1000���ж��߼�

		//��һ��1
		if (skin[0] == 0)
		{
			loadimage(&img, "./picture/��ӵ��.png", 70, 30);
			putimage(200, 330, &img);
		}
		else
		{
			loadimage(&img, "./picture/��ӵ��.png", 70, 30);
			putimage(200, 330, &img);
		}

		//��һ��2
		if (skin[1] == 0)
		{
			outtextxy(330, 337, "1000");
		}
		else
		{
			loadimage(&img, "./picture/��ӵ��.png", 70, 30);
			putimage(320, 330, &img);
		}

		//��һ��3
		if (skin[2] == 0)
		{
			outtextxy(450, 337, "1000");
		}
		else
		{
			loadimage(&img, "./picture/��ӵ��.png", 70, 30);
			putimage(440, 330, &img);
		}


		//��һ��4
		if (skin[3] == 0)
		{
			outtextxy(570, 337, "1000");
		}
		else
		{
			loadimage(&img, "./picture/��ӵ��.png", 70, 30);
			putimage(560, 330, &img);
		}

		//��һ��5
		if (skin[4] == 0)
		{
			outtextxy(690, 337, "1000");
		}
		else
		{
			loadimage(&img, "./picture/��ӵ��.png", 70, 30);
			putimage(680, 330, &img);
		}



		//��һ��6
		if (skin[5] == 0)
		{
			outtextxy(810, 337, "1000");
		}
		else
		{
			loadimage(&img, "./picture/��ӵ��.png", 70, 30);
			putimage(800, 330, &img);
		}


		//Ƥ���ڶ���1
		if (skin[6] == 0)
		{
			outtextxy(210, 467, "1000");
		}
		else
		{
			loadimage(&img, "./picture/��ӵ��.png", 70, 30);
			putimage(200, 460, &img);
		}


		//Ƥ���ڶ���2
		if (skin[7] == 0)
		{
			outtextxy(330, 467, "1000");
		}
		else
		{
			loadimage(&img, "./picture/��ӵ��.png", 70, 30);
			putimage(320, 460, &img);
		}

		//Ƥ���ڶ���3
		if (skin[8] == 0)
		{
			outtextxy(450, 467, "1000");
		}
		else
		{
			loadimage(&img, "./picture/��ӵ��.png", 70, 30);
			putimage(440, 460, &img);
		}

		//Ƥ���ڶ���4
		if (skin[9] == 0)
		{
			outtextxy(570, 467, "1000");
		}
		else
		{
			loadimage(&img, "./picture/��ӵ��.png", 70, 30);
			putimage(560, 460, &img);
		}

		//Ƥ���ڶ���5
		if (skin[10] == 0)
		{
			outtextxy(690, 467, "1000");
		}
		else
		{
			loadimage(&img, "./picture/��ӵ��.png", 70, 30);
			putimage(680, 460, &img);
		}

		//Ƥ���ڶ���6
		if (skin[11] == 0)
		{
			outtextxy(810, 467, "1000");
		}
		else
		{
			loadimage(&img, "./picture/��ӵ��.png", 70, 30);
			putimage(800, 460, &img);
		}




		//Ƥ��������1
		if (skin[12] == 0)
		{
			outtextxy(210, 597, "1000");
		}
		else
		{
			loadimage(&img, "./picture/��ӵ��.png", 70, 30);
			putimage(200, 590, &img);
		}


		//Ƥ��������2
		if (skin[12] == 0)
		{
			outtextxy(330, 597, "1000");
		}
		else
		{
			loadimage(&img, "./picture/��ӵ��.png", 70, 30);
			putimage(320, 590, &img);
		}





		//���̵��

		if (peekmessage(&msg1, EX_MOUSE))
		{


			if (button(950, 200, 60, 60))     //�������˵�
			{
				mciSendString("close bgm", 0, 0, 0);
				draw();
			}

			else if (button(200, 250, 70, 75))  //Ƥ����һ�е�һ��
			{
				if (skin[0] == 0)
				{
					skin[0] == 1;
					use_skin(0);
				}

				else if (skin[0] == 1)
				{
					use_skin(0);
				}

			}

			else if (button(320, 250, 70, 75))  //Ƥ����һ�еڶ���
			{



				if (skin[1] == 0 && get_gold_file < 1000)
				{
					money_not_enough();
				}
				else if (skin[1] == 0 && get_gold_file >= 1000)
				{

					money_enough(1);

				}
				else if (skin[1] == 1)
				{
					use_skin(1);
				}
			}

			else if (button(440, 250, 70, 75))  //Ƥ����һ�е�����
			{
				if (skin[2] == 0 && get_gold_file >= 1000)
				{
					money_enough(2);
				}

				else if (skin[2] == 0 && get_gold_file < 1000)
				{
					money_not_enough();
				}

				else if (skin[2] == 1)
				{
					use_skin(2);
				}

			}

			else if (button(560, 250, 70, 75))  //Ƥ����һ�е��ĸ�
			{
				if (skin[3] == 0 && get_gold_file >= 1000)
				{
					money_enough(3);
				}

				else if (skin[3] == 0 && get_gold_file < 1000)
				{
					money_not_enough();
				}

				else if (skin[3] == 1)
				{
					use_skin(3);
				}
			}

			else if (button(680, 250, 70, 75))  //Ƥ����һ�е����
			{
				if (skin[4] == 0 && get_gold_file >= 1000)
				{
					money_enough(4);
				}

				else if (skin[4] == 0 && get_gold_file < 1000)
				{
					money_not_enough();
				}

				else if (skin[4] == 1)
				{
					use_skin(4);
				}
			}

			else if (button(800, 250, 70, 75))  //Ƥ����һ�е�����
			{
				if (skin[5] == 0 && get_gold_file >= 1000)
				{
					money_enough(5);
				}

				else if (skin[5] == 0 && get_gold_file < 1000)
				{
					money_not_enough();
				}

				else if (skin[5] == 1)
				{
					use_skin(5);
				}
			}

			else if (button(200, 380, 70, 75))  //Ƥ���ڶ��е�һ��
				if (skin[6] == 0 && get_gold_file >= 1000)
				{
					money_enough(6);
				}

				else if (skin[6] == 0 && get_gold_file < 1000)
				{
					money_not_enough();
				}

				else if (skin[6] == 1)
				{
					use_skin(6);
				}
		}

		else if (button(320, 380, 70, 75))  //Ƥ���ڶ��еڶ���
		{
			if (skin[7] == 0 && get_gold_file >= 1000)
			{
				money_enough(7);
			}

			else if (skin[7] == 0 && get_gold_file < 1000)
			{
				money_not_enough();
			}

			else if (skin[7] == 1)
			{
				use_skin(7);
			}
		}

		else if (button(440, 380, 70, 75))  //Ƥ���ڶ��е�����
		{
			if (skin[8] == 0 && get_gold_file >= 1000)
			{
				money_enough(8);
			}

			else if (skin[8] == 0 && get_gold_file < 1000)
			{
				money_not_enough();
			}

			else if (skin[8] == 1)
			{
				use_skin(8);
			}
		}

		else if (button(560, 380, 70, 75))  //Ƥ���ڶ��е��ĸ�
		{
			if (skin[9] == 0 && get_gold_file >= 1000)
			{
				money_enough(9);

			}

			else if (skin[9] == 0 && get_gold_file < 1000)
			{
				money_not_enough();
			}

			else if (skin[9] == 1)
			{
				use_skin(9);
			}
		}

		else if (button(680, 380, 70, 75))  //Ƥ���ڶ��е����
		{
			if (skin[10] == 0 && get_gold_file >= 1000)
			{
				money_enough(10);
			}

			else if (skin[10] == 0 && get_gold_file < 1000)
			{
				money_not_enough();
			}

			else if (skin[10] == 1)
			{
				use_skin(10);
			}
		}

		else if (button(800, 380, 70, 75))  //Ƥ���ڶ��е�����
		{
			if (skin[11] == 0 && get_gold_file >= 1000)
			{
				money_enough(11);
			}

			else if (skin[11] == 0 && get_gold_file < 1000)
			{
				money_not_enough();
			}

			else if (skin[11] == 1)
			{
				use_skin(11);
			}
		}

		else if (button(200, 510, 70, 75))  //Ƥ�������е�һ��
		{
			if (skin[12] == 0 && get_gold_file >= 1000)
			{
				money_enough(12);
			}

			else if (skin[12] == 0 && get_gold_file < 1000)
			{
				money_not_enough();
			}

			else if (skin[12] == 1)
			{
				use_skin(12);
			}
		}

		else if (button(320, 510, 70, 75))  //Ƥ�������е�һ��
		{
			if (skin[13] == 0 && get_gold_file >= 1000)
			{
				money_enough(13);
			}

			else if (skin[13] == 0 && get_gold_file < 1000)
			{
				money_not_enough();
			}

			else if (skin[13] == 1)
			{
				use_skin(13);
			}
		}
	}

}















