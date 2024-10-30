#include "something.h"
#define BUFFERSIZE 1024
extern int num;
extern int music_buttom_1;
extern int now_skin;
int get_gold_1;
int get_score_1;






/*--------------------------------------------------------------------�������---------------------------------------------------------------------*/

/*----------------------------------���ڳ�ʼ��----------------------------------*/
//���ô��ڵĿ�Ⱥ͸߶�
int width = 1200;
int height = 720;

//���õذ����
int ground = 258;

//���ڼ���Ƿ��°�ť
// ������
ExMessage msg;

/*----------------------------------�ϰ���������ݳ�ʼ��----------------------------------*/

//���������Ǳ߳�
float length_side = 70;

//�ϰ������޸�
int obstacle_gap = 310;			//���Ե����˱����Ըı��ϰ����� һ���д�Լ1200�Ĵ���
const int num_obstacles = 4;	//�ϰ���ĸ���

/*----------------------------------ͼƬ����----------------------------------*/

//��ɫͼƬ
IMAGE part_img;

//�ϰ���������ͼƬ
IMAGE img_obstacle;

//����ͼ
IMAGE background_img;

//���Բ��ͼƬ
IMAGE img_gold;
IMAGE img_gold_bk;

//����ͼƬ��ť
IMAGE img_music_pause;//��ͣʱ��ʾ��ͼƬ
IMAGE img_music_play;//����ʱ��ʾ��ͼƬ

//��ͣ��ť
IMAGE img_pause;//δ������ͣ��ʾ��ͼƬ
IMAGE img_play;//�Ѱ�����ͣ��ʾ��ͼƬ

//���¿�ʼ��ť
IMAGE img_resume;//���¿�ʼ��ͼƬ

//��ҳ��ť
IMAGE img_home;//���¿�ʼ��ͼƬ








/*----------------------------------���������----------------------------------*/

int change_state = 0;//δ������ת����















/*----------------------------------��ť��ʼ������----------------------------------*/




//�ٶȳ�ʼ��
int speed = 10;

//��ͣ���ȷ��
int pause_buttom;//������

//��Ϸ����
int game_over = 0;




/*----------------------------------С���ϰ���ṹ��Ͳ�����ʼ��----------------------------------*/

// Ball�ṹ�嶨�壬����С������в���
struct Ball {
	float radius;    // С��뾶
	float x, y;      // С���x��y����
	float vy;        // С��Ĵ�ֱ�ٶ�
	float gravity;   // �������ٶ�
	bool can_jump;   // ��Ծ״̬��־
};

//С��뾶,С���x��y����,С��Ĵ�ֱ�ٶ�, �������ٶ�,��Ծ״̬��־
Ball ball = { 20, width / 4,ground - ball.radius , 0 ,0.55,true };

// Obstacle�ṹ�嶨�壬�����ϰ�������в���
struct Obstacle {
	float left_x, top_y;  // �ϰ������Ͻǵ�x��y����
	float width, height;  // �ϰ���Ŀ�Ⱥ͸߶�
	float vx;             // �ϰ����ˮƽ�ٶ�
	int obrand;           // ����������
	bool gold_rand;		  // ����Ƿ�����
	int get_gold;		  // �������
	int get_score;		  // �÷�
};




/*--------------------------------------------------------------------�������---------------------------------------------------------------------*/

/*----------------------------------���õ����ϰ����λ�ú͸߶�----------------------------------*/
void reset_obstacle(Obstacle& obs, float offset_x, bool is_first) {
	obs.left_x = width + offset_x;			// ���ϰ���� x �������õ������ұ����棬����Ϊ���ڿ�ȼ���ƫ����

	//����ǵ�һ���ϰ���
	if (is_first) {
		obs.top_y = ground - 2 * length_side - obs.height;						//��һ���ϰ��ĸ߶���3�������θ߶�

	}
	else {
		// ��������ϰ���ĸ߶ȣ�ȷ���ϰ���߶���һ����Χ��
		obs.top_y = ground - (rand() % 4 + 1) * length_side - obs.height;		//�����ϰ��ĸ߶���2��5�������θ߶�
	}
	obs.gold_rand = rand() % 2;
}

/*----------------------------------������ͣ----------------------------------*/
void game_draw(Obstacle* obstacles)
{
	cleardevice();

	BeginBatchDraw();
	putimage(0, -360, width, height, &background_img, 0, 0);
	for (int i = 0; i < num_obstacles; ++i)
	{
		for (int j = 0; j <= 4; j++)
		{
			if (obstacles[i].top_y + j * 70 >= 250)
				break;
			else
				putimage(obstacles[i].left_x, obstacles[i].top_y + j * 70, 70, 70, &img_obstacle, 0, 0);
		}
		if (obstacles[i].gold_rand)
			putimage(obstacles[i].left_x + 10, obstacles[i].top_y - 50, 70, 70, &img_gold_bk, 0, 0, SRCPAINT);
	}
	settextcolor(RGB(24, 66, 245));
	settextstyle(50, 0, "����");
	setbkmode(TRANSPARENT);
	outtextxy(0, -360, "�÷�:");
	char num_score[20];
	sprintf_s(num_score, "%d", obstacles[0].get_score);
	outtextxy(130, -360, num_score);
	putimage(0, -310, 70, 70, &img_gold_bk, 0, 0, SRCPAINT);
	settextcolor(RGB(24, 66, 245));
	settextstyle(50, 0, "����");
	setbkmode(TRANSPARENT);
	char num_gold[20];
	sprintf_s(num_gold, "%d", obstacles[0].get_gold);
	settextcolor(RGB(255, 222, 125));
	outtextxy(70, -310, num_gold);
	if (music_buttom_1)
	{
		putimage(width - 230, -345, 50, 50, &img_music_play, 0, 0, SRCPAINT);
		mciSendString("open music/bgm1.mp3 alias bgm1", 0, 0, 0);
		mciSendString("play bgm1 repeat", 0, 0, 0);
	}
	else	putimage(width - 230, -345, 50, 50, &img_music_pause, 0, 0, SRCPAINT);
	if (pause_buttom)	putimage(width - 170, -345, 50, 50, &img_pause, 0, 0, SRCPAINT);
	else		putimage(width - 170, -345, 50, 50, &img_play, 0, 0, SRCPAINT);
	putimage(width - 110, -345, 50, 50, &img_resume, 0, 0, SRCPAINT);
	putimage(width - 50, -345, 50, 50, &img_home, 0, 0, SRCPAINT);
	if (peekmessage(&msg))
	{
		if (msg.message == WM_LBUTTONDOWN)
		{



			if (msg.x >= width - 230 && msg.x <= width - 230 + 50 && msg.y >= -345 && msg.y <= 60)
			{
				if (msg.x >= width - 230 && msg.x <= width - 230 + 50 && msg.y >= -345 && msg.y <= 60)
				{
					if (music_buttom_1)
					{
						music_buttom_1 = 0;
						mciSendString("pause bgm1", 0, 0, 0); // �ر�����
					}
					else
						music_buttom_1 = 1;
				}
			}
			if (msg.x >= width - 170 && msg.x <= width - 170 + 50 && msg.y >= -345 && msg.y <= 60 && !game_over)
			{
				if (pause_buttom)	pause_buttom = 0;
				else	pause_buttom = 1;
			}
			if (msg.x >= width - 50 && msg.x <= width && msg.y >= -345 && msg.y <= 60)
			{
				mciSendString("pause bgm1", 0, 0, 0);
				draw();
			}
			/*���¿�ʼ��*/
			if (msg.x >= width - 110 && msg.x <= width - 110 + 50 && msg.y >= -345 && msg.y <= 60)
			{
				mciSendString("pause bgm1", 0, 0, 0); // �ر�����
				pause_buttom = 1;
				change_state = 1;
				game_over = 0;
				game_logic_holistic_work();
				cout << "������ҳ��" << endl;  // ͨ������̨�鿴������Ϣ
			}


		}
	}

	//������ͼ
	putimage(ball.x - ball.radius, ball.y - ball.radius, ball.radius * 2, ball.radius * 2, &part_img, 0, 0); // �����꣬�����ꣻͼƬλ��


	//setaspectratio(1, 1);
	//��Ϸ�����ͼ
	if (game_over)
	{
		setlinecolor(RGB(80, 81, 101));
		setfillcolor(RGB(2, 4, 141));
		fillrectangle(400, -200, 800, 100);

		settextcolor(RGB(24, 66, 245)); // ����������ɫ
		settextstyle(80, 0, "���Ĳ���"); // ���ִ�С����ȣ����壻����������ʽ
		outtextxy(430, -180, "��Ϸ������");

		//�÷�
		settextcolor(RGB(24, 66, 245)); // ����������ɫ
		settextstyle(50, 0, "��������"); // ���ִ�С����ȣ����壻����������ʽ
		setbkmode(TRANSPARENT); // ȥ�����ֱ���
		outtextxy(480, -80, "�÷�:");
		char num_score1[20];
		sprintf_s(num_score1, "%d", obstacles[0].get_score);
		outtextxy(630, -80, num_score1);

		//�������
		putimage(550, 0, 70, 70, &img_gold_bk, 0, 0, SRCPAINT);
		settextcolor(RGB(24, 66, 245)); // ����������ɫ
		settextstyle(50, 0, "��������"); // ���ִ�С����ȣ����壻����������ʽ
		setbkmode(TRANSPARENT); // ȥ�����ֱ���
		char num_gold1[20];
		sprintf_s(num_gold1, "%d", obstacles[0].get_gold);
		settextcolor(RGB(255, 222, 125));
		outtextxy(630, 0, num_gold1); // �����꣬�����꣬�ַ���
	}

	// ˢ�»�ͼ�豸
	FlushBatchDraw();
}


/*----------------------------------��ʼ��Ϸ���庯��----------------------------------*/






















void game_logic_holistic_work()
{


	pause_buttom = 1;//������



	switch (now_skin)
	{
		case 0:  loadimage(&part_img, "./picture/skin01.png", ball.radius * 2, ball.radius * 2);  break;
		case 1:  loadimage(&part_img, "./picture/skin02.png", ball.radius * 2, ball.radius * 2);  break;
		case 2:  loadimage(&part_img, "./picture/skin03.png", ball.radius * 2, ball.radius * 2);  break;
		case 3:  loadimage(&part_img, "./picture/skin04.png", ball.radius * 2, ball.radius * 2);  break;
		case 4:  loadimage(&part_img, "./picture/skin05.png", ball.radius * 2, ball.radius * 2);  break;
		case 5:  loadimage(&part_img, "./picture/skin06.png", ball.radius * 2, ball.radius * 2);  break;
		case 6:  loadimage(&part_img, "./picture/skin07.png", ball.radius * 2, ball.radius * 2);  break;
		case 7:  loadimage(&part_img, "./picture/skin08.png", ball.radius * 2, ball.radius * 2);  break;
		case 8:  loadimage(&part_img, "./picture/skin09.png", ball.radius * 2, ball.radius * 2);  break;
		case 9:  loadimage(&part_img, "./picture/skin10.png", ball.radius * 2, ball.radius * 2);  break;
		case 10: loadimage(&part_img, "./picture/skin11.png", ball.radius * 2, ball.radius * 2);  break;
		case 11: loadimage(&part_img, "./picture/skin12.png", ball.radius * 2, ball.radius * 2);  break;
		case 12: loadimage(&part_img, "./picture/skin13.png", ball.radius * 2, ball.radius * 2);  break;
		case 13: loadimage(&part_img, "./picture/skin14.png", ball.radius * 2, ball.radius * 2);  break;
	}




	









	//����ͼƬ�������while����ػῨ
	loadimage(&background_img, "./picture/beijin.png", width + 10, height);
	loadimage(&img_obstacle, "./picture/four.png", 70, 70);
	loadimage(&img_gold_bk, "./picture/jinbi.png", 50, 50);
	loadimage(&img_music_pause, "./picture/pause.png", 50, 50);
	loadimage(&img_music_play, "./picture/play.png", 50, 50);
	loadimage(&img_pause, "./picture/��ͣ.png", 50, 50);
	loadimage(&img_play, "./picture/��ͣ��.png", 50, 50);
	loadimage(&img_home, "./picture/���˵�.png", 50, 50);
	loadimage(&img_resume, "./picture/���¿�ʼ.png", 50, 50);

	//����ԭ��
	setorigin(0, 360);

	// �������������
	srand((unsigned int)time(NULL));

	// ��ʼ���ϰ������
	Obstacle obstacles[num_obstacles];	//�ϰ�����
	obstacles[0].get_gold = 0;		//��ʼ�����
	obstacles[0].get_score = 0;		//��ʼ���÷�
	float offset_x = 0;		//��ʼƫ����

	for (int i = 0; i < num_obstacles; ++i) {
		obstacles[i] = { width + offset_x, 0, length_side, length_side, -5 };
		reset_obstacle(obstacles[i], offset_x, i == 0);		// ��һ���ϰ���߶�����
		offset_x += obstacle_gap;	// ����ƫ������ȷ���ϰ���֮��ļ��
	}


	//����ѭ��
	while (1)
	{
		/*--------------���ո����������Ծ�߼�--------------*/

		if (GetAsyncKeyState(VK_SPACE) && ball.can_jump)
		{
			//�����ϳ��ٶ�
			ball.vy = -16;// ��С��һ�����ϵ��ٶ�
			ball.can_jump = false; // ������Ծ��־Ϊfalse

		}

		/*--------------����С����ٶ�--------------*/

		ball.vy += ball.gravity;// �ٶ�����
		ball.y += ball.vy;// ����y����

		//�ж���غ�λ�ý���������Ծ����
		if (ball.y >= ground - ball.radius)// ���С���䵽����
		{
			ball.vy = 0;         // �ٶ�Ϊ0
			ball.y = ground - ball.radius; // �̶�y����
			ball.can_jump = true; // ������Ծ��־
		}


		/*--------------�ϰ�����ƺ�ʵ���߼�--------------*/

		// �����ϰ���λ�ú������߼�
		for (int i = 0; i < num_obstacles; ++i) {
			obstacles[i].left_x += obstacles[i].vx; // ����x����
			if (obstacles[i].left_x + obstacles[i].width <= 0) { // ����ϰ��ﳬ����߽�
				reset_obstacle(obstacles[i], 0, i == 0); // �����ϰ���,�׿�Ĭ����3����Ȼ��������ȥ
				if (i > 0) {
					// ȷ�����������ϰ���֮��ĸ߶Ȳ����140
					int delta_y = obstacles[i].top_y - obstacles[i - 1].top_y;
					if (delta_y > 140)
						obstacles[i].top_y = obstacles[i - 1].top_y + 140;
					else if (delta_y < -140)
						obstacles[i].top_y = obstacles[i - 1].top_y - 140;
				}
			}
		}

		// ��ײ����߼�
		bool is_on_top = false; // ��־С���Ƿ����ϰ����Ϸ�

		for (int i = 0; i < num_obstacles; ++i) {
			float obstacle_x = obstacles[i].left_x;
			float obstacle_y = obstacles[i].top_y;

			if ((ball.x + ball.radius >= obstacle_x) &&
				(ball.x - ball.radius <= obstacle_x + obstacles[i].width)) {
				if (ball.y + ball.radius >= obstacle_y && ball.y - ball.radius <= obstacle_y) {
					ball.y = obstacle_y - ball.radius; // ����С����͸߶�
					ball.vy = 0; // �����ٶ�Ϊ0
					ball.can_jump = true; // ������Ծ��־
					is_on_top = true;
				}
				else if (ball.y + ball.radius > obstacle_y && ball.y - ball.radius > obstacle_y) {
					pause_buttom = 0;
					game_over = 1;
					get_score_1 = obstacles[0].get_score;
					get_gold_1 = obstacles[0].get_gold;

					add_score(get_score_1);
					load_gold();


					while (!pause_buttom)	game_draw(obstacles);
				}
			}

			//setaspectratio(1, -1);

			if ((ball.x + ball.radius >= obstacles[i].left_x + 35) &&
				(ball.x - ball.radius <= obstacles[i].left_x + 35) &&
				(ball.y - ball.radius <= obstacles[i].top_y - 35) &&
				(ball.y + ball.radius >= obstacles[i].top_y - 35)) {
				if (obstacles[i].gold_rand == 1)
					obstacles[0].get_gold++;
				obstacles[i].gold_rand = 0;
			}

		}

		/*--------------��ͼ--------------*/

		// ��ջ�ͼ�豸
		cleardevice();

		//������ͼ
		BeginBatchDraw();

		//��ͼ

		//������ͼ
		putimage(0, -360, width, height, &background_img, 0, 0);

		//�ϰ�����ͼ
		for (int i = 0; i < num_obstacles; ++i)
		{
			//�ϰ����ͼ
			for (int j = 0; j <= 4; j++)
			{
				if (obstacles[i].top_y + j * 70 >= 250)
					break;
				else
					putimage(obstacles[i].left_x, obstacles[i].top_y + j * 70, 70, 70, &img_obstacle, 0, 0);
			}

			//��һ�ͼ
			if (obstacles[i].gold_rand)
				putimage(obstacles[i].left_x + 10, obstacles[i].top_y - 50, 70, 70, &img_gold_bk, 0, 0, SRCPAINT);

		}

		//�÷�
		settextcolor(RGB(24, 66, 245)); // ����������ɫ
		settextstyle(50, 0, "����"); // ���ִ�С����ȣ����壻����������ʽ
		setbkmode(TRANSPARENT); // ȥ�����ֱ���
		outtextxy(0, -360, "�÷�:");
		if (pause_buttom == 1)
			obstacles[0].get_score++;
		char num_score[20];
		sprintf_s(num_score, "%d", obstacles[0].get_score);
		outtextxy(130, -360, num_score);

		//�������
		putimage(0, -310, 70, 70, &img_gold_bk, 0, 0, SRCPAINT);
		settextcolor(RGB(24, 66, 245)); // ����������ɫ
		settextstyle(50, 0, "����"); // ���ִ�С����ȣ����壻����������ʽ
		setbkmode(TRANSPARENT); // ȥ�����ֱ���
		char num_gold[20];
		sprintf_s(num_gold, "%d", obstacles[0].get_gold);
		settextcolor(RGB(255, 222, 125));
		outtextxy(70, -310, num_gold); // �����꣬�����꣬�ַ���

		//��ť�߼�

		//���ֲ��Ű�ť���
		if (music_buttom_1)
		{
			//����ʱ��ť
			putimage(width - 230, -345, 50, 50, &img_music_play, 0, 0, SRCPAINT);
			//��������
			mciSendString("open music/bgm1.mp3 alias bgm1", 0, 0, 0); // �����֣����ָ�Ϊ"bgm1"
			mciSendString("play bgm1 repeat", 0, 0, 0); // �������֣�repeat��ʾѭ������
		}
		else {
			//��ͣ����ʱ��ť
			putimage(width - 230, -345, 50, 50, &img_music_pause, 0, 0, SRCPAINT);
		}
		//��ͣ��ť
		if (pause_buttom)
			//δ������ͣ����ť
			putimage(width - 170, -345, 50, 50, &img_pause, 0, 0, SRCPAINT);
		else
			//�Ѿ�������ͣ����ť
			putimage(width - 170, -345, 50, 50, &img_play, 0, 0, SRCPAINT);

		//���¿�ʼ��ť
		putimage(width - 110, -345, 50, 50, &img_resume, 0, 0, SRCPAINT);

		//������ҳ��ť
		putimage(width - 50, -345, 50, 50, &img_home, 0, 0, SRCPAINT);

		//��ť�����ж�
		if (peekmessage(&msg))
		{
			if (msg.message == WM_LBUTTONDOWN)
			{

				if (change_state)//
				{

				}

				/*����λ��*/
				if (msg.x >= width - 230 && msg.x <= width - 230 + 50 && msg.y >= -345 && msg.y <= 60)
				{
					if (music_buttom_1)
					{
						music_buttom_1 = 0;
						mciSendString("pause bgm1", 0, 0, 0); // �ر�����
					}
					else
						music_buttom_1 = 1;
				}

				/*��ͣ��*/
				if (msg.x >= width - 170 && msg.x <= width - 170 + 50 && msg.y >= -345 && msg.y <= 60)
				{
					if (pause_buttom)
					{
						pause_buttom = 0;
						while (!pause_buttom)	game_draw(obstacles);
					}
					else	pause_buttom = 1;
				}

				/*���¿�ʼ��*/
				if (msg.x >= width - 110 && msg.x <= width - 110 + 50 && msg.y >= -345 && msg.y <= 60)
				{
					mciSendString("pause bgm1", 0, 0, 0); // �ر�����
					game_over = 0;
					game_logic_holistic_work();
					cout << "������ҳ��" << endl;  // ͨ������̨�鿴������Ϣ
				}

				/*������ҳ��*/
				if (msg.x >= width - 50 && msg.x <= width && msg.y >= -345 && msg.y <= 60)
				{
					mciSendString("pause bgm1", 0, 0, 0); // �ر�����
					draw();
					cout << "���¿�ʼ��" << endl;  // ͨ������̨�鿴������Ϣ
				}
			}
		}


		//������ͼ
		putimage(ball.x - ball.radius, ball.y - ball.radius, ball.radius * 2, ball.radius * 2, &part_img, 0, 0); // �����꣬�����ꣻͼƬλ��

		// ˢ�»�ͼ�豸
		FlushBatchDraw();


		if (num == 1)
		{
			speed = 10;
		}
		else if (num == 2)
		{
			speed = 6;
		}
		else {
			speed = 3;
		}


		Sleep(speed);
	}
}

