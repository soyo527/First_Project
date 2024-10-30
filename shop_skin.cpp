#define _CRT_SECURE_NO_WARNINGS 1

#define _CRT_SECURE_NO_WARNINGS 1

/*
	蔡军
*/


#include"something.h"
extern int music_buttom_1;


extern int get_gold_1;

int skin[14] = { 0 };


int get_gold_file;//获取到存档的金币

void show_now_skin(int now_skin);


//读取存档金币函数
void read_gold() {
	ifstream infile("./gold/gold.txt");
	if (infile.is_open()) {
		infile >> get_gold_file;

	}
}

//购物后函数
void save_gold() {
	ofstream outFile("./gold/gold.txt");
	if (outFile.is_open()) {
		outFile << (get_gold_file - 1000);
	}
	outFile.close();
}

//蔡军不要动这个load_gold函数
void load_gold() {
	int old_gold = 0;
	// 尝试以读取模式打开文件
	ifstream file("./gold/gold.txt");

	if (!file) {
		// 文件无法打开，说明文件不存在，创建新文件并初始化为0
		ofstream createFile("./gold/gold.txt");
		createFile << get_gold_1;
		createFile.close();
	}
	else {
		// 文件成功打开，从中读取旧的黄金数量
		file >> old_gold;
		file.close(); // 读取完成后关闭文件

		// 更新 get_gold
		get_gold_1 += old_gold;

		// 重新以写入模式打开文件，覆盖文件内容
		ofstream file("./gold/gold.txt");
		file << get_gold_1;
		file.close();
		get_gold_1 = 0;
	}
}


int now_skin = 0;
void load_skin() {//用于读取皮肤所装备皮肤信息

	// 尝试以读取模式打开文件
	ifstream file("./skin/now_skin.txt");

	if (file.is_open()) {
		// 文件成功打开，从中读取装备皮肤编号
		file >> now_skin;
		file.close(); // 读取完成后关闭文件
	}
}


//存入装备皮肤信息
void save_skin() {//用于读取皮肤所装备皮肤信息

	// 尝试以读取模式打开文件
	ofstream file("./skin/now_skin.txt");

	if (file.is_open()) {
		// 文件成功打开，从中写入装备皮肤编号到存档
		file << now_skin;
		file.close(); // 读取完成后关闭文件
	}
}






//存入
void save_skin_num() {//保存所拥有皮肤到存档

	// 尝试以读取模式打开文件
	ofstream file("./skin/skin_num.txt");

	if (file.is_open()) {

		for (int i = 0; i < 14; i++)
		{
			file << skin[i] << endl;

		}

		file.close(); // 读取完成后关闭文件
	}
}


//读取
void load_skin_num()//读取存档里的数据到skin数组
{

	ifstream file("./skin/skin_num.txt");
	if (file.is_open()) {

		for (int i = 0; i < 14; i++)
		{
			file >> skin[i];


		}

		file.close(); // 读取完成后关闭文件
	}



}




IMAGE img;
IMAGE img_skin[14];
ExMessage msg1 = { 0 };




void music_skin();  //音乐
void mouse_skin();  //鼠标点击的位置判定

/*商城换肤的页面函数设计*/
void shop_skin()
{
	//load_gold();
	cleardevice();
	mciSendString("open ./music/LL_skin.mp3 alias bgm", 0, 0, 0);

	if (music_buttom_1)
	{
		music_skin();  //放音乐
	}


	//换肤界面的整体框架
	loadimage(&img, "./picture/beijing.png", 1200, 720);
	putimage(0, 0, &img);
	loadimage(&img, "./picture/jinbi1.png", 50, 50);
	putimage(800, 600, &img);
	loadimage(&img, "./picture/返回.png", 60, 60);
	putimage(950, 200, &img);


	setbkmode(TRANSPARENT);
	settextcolor(YELLOW);
	settextstyle(20, 0, "黑体");
	outtextxy(910, 280, "当前携带皮肤");
	setfillcolor(WHITE);
	
	show_now_skin(now_skin);

	//皮肤第一行
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


	//皮肤第二行
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


	//皮肤第三行
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

	//处理换肤操作
	//显示金币数量和退出按钮
	//进行皮肤的购买

}














//换肤界面的音乐
void music_skin()
{

	mciSendString("play bgm repeat", 0, 0, 0);
}


//鼠标实现 退出  购买  换肤操作
bool inArea(int mx, int my, int x, int y, int w, int h)  //判断鼠标mx，my是否在指定的矩形区域
{
	if (mx > x && mx<x + w && my>y && my < y + h)
	{
		return true;
	}
	return false;
}

bool button(int x, int y, int w, int h)  //当在按钮区域时
{

	//判断按钮是否被点击
	if (msg1.message == WM_LBUTTONDOWN && inArea(msg1.x, msg1.y, x, y, w, h))
	{
		return true;
	}
	return false;
}







void money_not_enough()//钱不够
{
	setfillcolor(RGB(6, 11, 66));
	setlinecolor(RED);
	fillrectangle(400, 210, 800, 510);
	setbkmode(TRANSPARENT);
	settextcolor(YELLOW);
	settextstyle(25, 0, "黑体");
	outtextxy(470, 270, "金币不足,请点击返回键");
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


void money_enough(int i)//钱够了用于购买的函数
{

	setfillcolor(RGB(6, 11, 66));
	setlinecolor(RED);
	fillrectangle(400, 210, 800, 510);
	setbkmode(TRANSPARENT);
	settextcolor(YELLOW);
	settextstyle(50, 0, "黑体");
	outtextxy(520, 270, "确认购买?");
	outtextxy(470, 370, "是");
	outtextxy(670, 370, "否");

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

void use_skin(int i)//用于装备的函数
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





























//购买皮肤
void mouse_skin()
{

	while (1)
	{

		settextstyle(50, 0, "楷体"); // 文字大小，宽度，字体；设置文字样式
		setbkmode(TRANSPARENT); // 去除文字背景
		settextcolor(RGB(255, 222, 125));
		char num_gold[20];
		sprintf_s(num_gold, "%d", get_gold_file);
		outtextxy(850, 600, num_gold);




		settextcolor(YELLOW);   //设置1000金币文本
		settextstyle(20, 0, "黑体");
		setbkmode(TRANSPARENT);

		//显示已拥有和金币1000的判断逻辑

		//第一行1
		if (skin[0] == 0)
		{
			loadimage(&img, "./picture/已拥有.png", 70, 30);
			putimage(200, 330, &img);
		}
		else
		{
			loadimage(&img, "./picture/已拥有.png", 70, 30);
			putimage(200, 330, &img);
		}

		//第一行2
		if (skin[1] == 0)
		{
			outtextxy(330, 337, "1000");
		}
		else
		{
			loadimage(&img, "./picture/已拥有.png", 70, 30);
			putimage(320, 330, &img);
		}

		//第一行3
		if (skin[2] == 0)
		{
			outtextxy(450, 337, "1000");
		}
		else
		{
			loadimage(&img, "./picture/已拥有.png", 70, 30);
			putimage(440, 330, &img);
		}


		//第一行4
		if (skin[3] == 0)
		{
			outtextxy(570, 337, "1000");
		}
		else
		{
			loadimage(&img, "./picture/已拥有.png", 70, 30);
			putimage(560, 330, &img);
		}

		//第一行5
		if (skin[4] == 0)
		{
			outtextxy(690, 337, "1000");
		}
		else
		{
			loadimage(&img, "./picture/已拥有.png", 70, 30);
			putimage(680, 330, &img);
		}



		//第一行6
		if (skin[5] == 0)
		{
			outtextxy(810, 337, "1000");
		}
		else
		{
			loadimage(&img, "./picture/已拥有.png", 70, 30);
			putimage(800, 330, &img);
		}


		//皮肤第二行1
		if (skin[6] == 0)
		{
			outtextxy(210, 467, "1000");
		}
		else
		{
			loadimage(&img, "./picture/已拥有.png", 70, 30);
			putimage(200, 460, &img);
		}


		//皮肤第二行2
		if (skin[7] == 0)
		{
			outtextxy(330, 467, "1000");
		}
		else
		{
			loadimage(&img, "./picture/已拥有.png", 70, 30);
			putimage(320, 460, &img);
		}

		//皮肤第二行3
		if (skin[8] == 0)
		{
			outtextxy(450, 467, "1000");
		}
		else
		{
			loadimage(&img, "./picture/已拥有.png", 70, 30);
			putimage(440, 460, &img);
		}

		//皮肤第二行4
		if (skin[9] == 0)
		{
			outtextxy(570, 467, "1000");
		}
		else
		{
			loadimage(&img, "./picture/已拥有.png", 70, 30);
			putimage(560, 460, &img);
		}

		//皮肤第二行5
		if (skin[10] == 0)
		{
			outtextxy(690, 467, "1000");
		}
		else
		{
			loadimage(&img, "./picture/已拥有.png", 70, 30);
			putimage(680, 460, &img);
		}

		//皮肤第二行6
		if (skin[11] == 0)
		{
			outtextxy(810, 467, "1000");
		}
		else
		{
			loadimage(&img, "./picture/已拥有.png", 70, 30);
			putimage(800, 460, &img);
		}




		//皮肤第三行1
		if (skin[12] == 0)
		{
			outtextxy(210, 597, "1000");
		}
		else
		{
			loadimage(&img, "./picture/已拥有.png", 70, 30);
			putimage(200, 590, &img);
		}


		//皮肤第三行2
		if (skin[12] == 0)
		{
			outtextxy(330, 597, "1000");
		}
		else
		{
			loadimage(&img, "./picture/已拥有.png", 70, 30);
			putimage(320, 590, &img);
		}





		//键盘点击

		if (peekmessage(&msg1, EX_MOUSE))
		{


			if (button(950, 200, 60, 60))     //返回主菜单
			{
				mciSendString("close bgm", 0, 0, 0);
				draw();
			}

			else if (button(200, 250, 70, 75))  //皮肤第一行第一个
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

			else if (button(320, 250, 70, 75))  //皮肤第一行第二个
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

			else if (button(440, 250, 70, 75))  //皮肤第一行第三个
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

			else if (button(560, 250, 70, 75))  //皮肤第一行第四个
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

			else if (button(680, 250, 70, 75))  //皮肤第一行第五个
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

			else if (button(800, 250, 70, 75))  //皮肤第一行第六个
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

			else if (button(200, 380, 70, 75))  //皮肤第二行第一个
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

		else if (button(320, 380, 70, 75))  //皮肤第二行第二个
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

		else if (button(440, 380, 70, 75))  //皮肤第二行第三个
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

		else if (button(560, 380, 70, 75))  //皮肤第二行第四个
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

		else if (button(680, 380, 70, 75))  //皮肤第二行第五个
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

		else if (button(800, 380, 70, 75))  //皮肤第二行第六个
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

		else if (button(200, 510, 70, 75))  //皮肤第三行第一个
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

		else if (button(320, 510, 70, 75))  //皮肤第三行第一个
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















