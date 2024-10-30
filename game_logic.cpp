#include "something.h"
#define BUFFERSIZE 1024
extern int num;
extern int music_buttom_1;
extern int now_skin;
int get_gold_1;
int get_score_1;






/*--------------------------------------------------------------------数据设计---------------------------------------------------------------------*/

/*----------------------------------窗口初始化----------------------------------*/
//设置窗口的宽度和高度
int width = 1200;
int height = 720;

//设置地板距离
int ground = 258;

//用于检测是否按下按钮
// 鼠标操作
ExMessage msg;

/*----------------------------------障碍物基本数据初始化----------------------------------*/

//矩形与三角边长
float length_side = 70;

//障碍物间隔修改
int obstacle_gap = 310;			//可以调整此变量以改变障碍物间隔 一共有大约1200的大间距
const int num_obstacles = 4;	//障碍物的个数

/*----------------------------------图片区域----------------------------------*/

//角色图片
IMAGE part_img;

//障碍物正方形图片
IMAGE img_obstacle;

//背景图
IMAGE background_img;

//金币圆型图片
IMAGE img_gold;
IMAGE img_gold_bk;

//播放图片按钮
IMAGE img_music_pause;//暂停时显示的图片
IMAGE img_music_play;//播放时显示的图片

//暂停按钮
IMAGE img_pause;//未按下暂停显示的图片
IMAGE img_play;//已按下暂停显示的图片

//重新开始按钮
IMAGE img_resume;//重新开始的图片

//主页按钮
IMAGE img_home;//重新开始的图片








/*----------------------------------倒反天罡参数----------------------------------*/

int change_state = 0;//未发生倒转现象















/*----------------------------------按钮初始化参数----------------------------------*/




//速度初始化
int speed = 10;

//暂停点击确认
int pause_buttom;//播放中

//游戏结算
int game_over = 0;




/*----------------------------------小球、障碍物结构体和参数初始化----------------------------------*/

// Ball结构体定义，包含小球的所有参数
struct Ball {
	float radius;    // 小球半径
	float x, y;      // 小球的x和y坐标
	float vy;        // 小球的垂直速度
	float gravity;   // 重力加速度
	bool can_jump;   // 跳跃状态标志
};

//小球半径,小球的x和y坐标,小球的垂直速度, 重力加速度,跳跃状态标志
Ball ball = { 20, width / 4,ground - ball.radius , 0 ,0.55,true };

// Obstacle结构体定义，包含障碍物的所有参数
struct Obstacle {
	float left_x, top_y;  // 障碍物左上角的x和y坐标
	float width, height;  // 障碍物的宽度和高度
	float vx;             // 障碍物的水平速度
	int obrand;           // 层数随机结果
	bool gold_rand;		  // 金币是否生成
	int get_gold;		  // 金币数量
	int get_score;		  // 得分
};




/*--------------------------------------------------------------------函数设计---------------------------------------------------------------------*/

/*----------------------------------重置单个障碍物的位置和高度----------------------------------*/
void reset_obstacle(Obstacle& obs, float offset_x, bool is_first) {
	obs.left_x = width + offset_x;			// 将障碍物的 x 坐标设置到窗口右边外面，距离为窗口宽度加上偏移量

	//如果是第一个障碍物
	if (is_first) {
		obs.top_y = ground - 2 * length_side - obs.height;						//第一个障碍的高度是3个正方形高度

	}
	else {
		// 随机生成障碍物的高度，确保障碍物高度在一定范围内
		obs.top_y = ground - (rand() % 4 + 1) * length_side - obs.height;		//后续障碍的高度是2到5个正方形高度
	}
	obs.gold_rand = rand() % 2;
}

/*----------------------------------绘制暂停----------------------------------*/
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
	settextstyle(50, 0, "楷体");
	setbkmode(TRANSPARENT);
	outtextxy(0, -360, "得分:");
	char num_score[20];
	sprintf_s(num_score, "%d", obstacles[0].get_score);
	outtextxy(130, -360, num_score);
	putimage(0, -310, 70, 70, &img_gold_bk, 0, 0, SRCPAINT);
	settextcolor(RGB(24, 66, 245));
	settextstyle(50, 0, "楷体");
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
						mciSendString("pause bgm1", 0, 0, 0); // 关闭音乐
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
			/*重新开始的*/
			if (msg.x >= width - 110 && msg.x <= width - 110 + 50 && msg.y >= -345 && msg.y <= 60)
			{
				mciSendString("pause bgm1", 0, 0, 0); // 关闭音乐
				pause_buttom = 1;
				change_state = 1;
				game_over = 0;
				game_logic_holistic_work();
				cout << "返回主页！" << endl;  // 通过控制台查看调试信息
			}


		}
	}

	//人物贴图
	putimage(ball.x - ball.radius, ball.y - ball.radius, ball.radius * 2, ball.radius * 2, &part_img, 0, 0); // 横坐标，纵坐标；图片位置


	//setaspectratio(1, 1);
	//游戏结算绘图
	if (game_over)
	{
		setlinecolor(RGB(80, 81, 101));
		setfillcolor(RGB(2, 4, 141));
		fillrectangle(400, -200, 800, 100);

		settextcolor(RGB(24, 66, 245)); // 设置文字颜色
		settextstyle(80, 0, "华文彩云"); // 文字大小，宽度，字体；设置文字样式
		outtextxy(430, -180, "游戏结束！");

		//得分
		settextcolor(RGB(24, 66, 245)); // 设置文字颜色
		settextstyle(50, 0, "方正舒体"); // 文字大小，宽度，字体；设置文字样式
		setbkmode(TRANSPARENT); // 去除文字背景
		outtextxy(480, -80, "得分:");
		char num_score1[20];
		sprintf_s(num_score1, "%d", obstacles[0].get_score);
		outtextxy(630, -80, num_score1);

		//金币数量
		putimage(550, 0, 70, 70, &img_gold_bk, 0, 0, SRCPAINT);
		settextcolor(RGB(24, 66, 245)); // 设置文字颜色
		settextstyle(50, 0, "方正舒体"); // 文字大小，宽度，字体；设置文字样式
		setbkmode(TRANSPARENT); // 去除文字背景
		char num_gold1[20];
		sprintf_s(num_gold1, "%d", obstacles[0].get_gold);
		settextcolor(RGB(255, 222, 125));
		outtextxy(630, 0, num_gold1); // 横坐标，纵坐标，字符串
	}

	// 刷新绘图设备
	FlushBatchDraw();
}


/*----------------------------------开始游戏主体函数----------------------------------*/






















void game_logic_holistic_work()
{


	pause_buttom = 1;//播放中



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




	









	//加载图片，如果在while里加载会卡
	loadimage(&background_img, "./picture/beijin.png", width + 10, height);
	loadimage(&img_obstacle, "./picture/four.png", 70, 70);
	loadimage(&img_gold_bk, "./picture/jinbi.png", 50, 50);
	loadimage(&img_music_pause, "./picture/pause.png", 50, 50);
	loadimage(&img_music_play, "./picture/play.png", 50, 50);
	loadimage(&img_pause, "./picture/暂停.png", 50, 50);
	loadimage(&img_play, "./picture/暂停后.png", 50, 50);
	loadimage(&img_home, "./picture/主菜单.png", 50, 50);
	loadimage(&img_resume, "./picture/重新开始.png", 50, 50);

	//设置原点
	setorigin(0, 360);

	// 设置随机数种子
	srand((unsigned int)time(NULL));

	// 初始化障碍物参数
	Obstacle obstacles[num_obstacles];	//障碍数组
	obstacles[0].get_gold = 0;		//初始化金币
	obstacles[0].get_score = 0;		//初始化得分
	float offset_x = 0;		//初始偏移量

	for (int i = 0; i < num_obstacles; ++i) {
		obstacles[i] = { width + offset_x, 0, length_side, length_side, -5 };
		reset_obstacle(obstacles[i], offset_x, i == 0);		// 第一个障碍物高度限制
		offset_x += obstacle_gap;	// 更新偏移量，确保障碍物之间的间隔
	}


	//主体循环
	while (1)
	{
		/*--------------检测空格键，处理跳跃逻辑--------------*/

		if (GetAsyncKeyState(VK_SPACE) && ball.can_jump)
		{
			//球向上初速度
			ball.vy = -16;// 给小球一个向上的速度
			ball.can_jump = false; // 设置跳跃标志为false

		}

		/*--------------更新小球初速度--------------*/

		ball.vy += ball.gravity;// 速度增加
		ball.y += ball.vy;// 更新y坐标

		//判断落地后位置结束本次跳跃数据
		if (ball.y >= ground - ball.radius)// 如果小球落到地面
		{
			ball.vy = 0;         // 速度为0
			ball.y = ground - ball.radius; // 固定y坐标
			ball.can_jump = true; // 重置跳跃标志
		}


		/*--------------障碍物绘制和实体逻辑--------------*/

		// 更新障碍物位置和重置逻辑
		for (int i = 0; i < num_obstacles; ++i) {
			obstacles[i].left_x += obstacles[i].vx; // 更新x坐标
			if (obstacles[i].left_x + obstacles[i].width <= 0) { // 如果障碍物超出左边界
				reset_obstacle(obstacles[i], 0, i == 0); // 重置障碍物,首块默认是3，不然会跳不过去
				if (i > 0) {
					// 确保相邻两个障碍物之间的高度差不超过140
					int delta_y = obstacles[i].top_y - obstacles[i - 1].top_y;
					if (delta_y > 140)
						obstacles[i].top_y = obstacles[i - 1].top_y + 140;
					else if (delta_y < -140)
						obstacles[i].top_y = obstacles[i - 1].top_y - 140;
				}
			}
		}

		// 碰撞检测逻辑
		bool is_on_top = false; // 标志小球是否在障碍物上方

		for (int i = 0; i < num_obstacles; ++i) {
			float obstacle_x = obstacles[i].left_x;
			float obstacle_y = obstacles[i].top_y;

			if ((ball.x + ball.radius >= obstacle_x) &&
				(ball.x - ball.radius <= obstacle_x + obstacles[i].width)) {
				if (ball.y + ball.radius >= obstacle_y && ball.y - ball.radius <= obstacle_y) {
					ball.y = obstacle_y - ball.radius; // 更新小球最低高度
					ball.vy = 0; // 设置速度为0
					ball.can_jump = true; // 重置跳跃标志
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

		/*--------------绘图--------------*/

		// 清空绘图设备
		cleardevice();

		//批量绘图
		BeginBatchDraw();

		//贴图

		//背景贴图
		putimage(0, -360, width, height, &background_img, 0, 0);

		//障碍物贴图
		for (int i = 0; i < num_obstacles; ++i)
		{
			//障碍物绘图
			for (int j = 0; j <= 4; j++)
			{
				if (obstacles[i].top_y + j * 70 >= 250)
					break;
				else
					putimage(obstacles[i].left_x, obstacles[i].top_y + j * 70, 70, 70, &img_obstacle, 0, 0);
			}

			//金币绘图
			if (obstacles[i].gold_rand)
				putimage(obstacles[i].left_x + 10, obstacles[i].top_y - 50, 70, 70, &img_gold_bk, 0, 0, SRCPAINT);

		}

		//得分
		settextcolor(RGB(24, 66, 245)); // 设置文字颜色
		settextstyle(50, 0, "楷体"); // 文字大小，宽度，字体；设置文字样式
		setbkmode(TRANSPARENT); // 去除文字背景
		outtextxy(0, -360, "得分:");
		if (pause_buttom == 1)
			obstacles[0].get_score++;
		char num_score[20];
		sprintf_s(num_score, "%d", obstacles[0].get_score);
		outtextxy(130, -360, num_score);

		//金币数量
		putimage(0, -310, 70, 70, &img_gold_bk, 0, 0, SRCPAINT);
		settextcolor(RGB(24, 66, 245)); // 设置文字颜色
		settextstyle(50, 0, "楷体"); // 文字大小，宽度，字体；设置文字样式
		setbkmode(TRANSPARENT); // 去除文字背景
		char num_gold[20];
		sprintf_s(num_gold, "%d", obstacles[0].get_gold);
		settextcolor(RGB(255, 222, 125));
		outtextxy(70, -310, num_gold); // 横坐标，纵坐标，字符串

		//按钮逻辑

		//音乐播放按钮相关
		if (music_buttom_1)
		{
			//播放时按钮
			putimage(width - 230, -345, 50, 50, &img_music_play, 0, 0, SRCPAINT);
			//播放音乐
			mciSendString("open music/bgm1.mp3 alias bgm1", 0, 0, 0); // 打开音乐，名字改为"bgm1"
			mciSendString("play bgm1 repeat", 0, 0, 0); // 播放音乐，repeat表示循环播放
		}
		else {
			//暂停音乐时按钮
			putimage(width - 230, -345, 50, 50, &img_music_pause, 0, 0, SRCPAINT);
		}
		//暂停按钮
		if (pause_buttom)
			//未按下暂停键按钮
			putimage(width - 170, -345, 50, 50, &img_pause, 0, 0, SRCPAINT);
		else
			//已经按下暂停键按钮
			putimage(width - 170, -345, 50, 50, &img_play, 0, 0, SRCPAINT);

		//重新开始按钮
		putimage(width - 110, -345, 50, 50, &img_resume, 0, 0, SRCPAINT);

		//返回主页按钮
		putimage(width - 50, -345, 50, 50, &img_home, 0, 0, SRCPAINT);

		//按钮区域判定
		if (peekmessage(&msg))
		{
			if (msg.message == WM_LBUTTONDOWN)
			{

				if (change_state)//
				{

				}

				/*音乐位置*/
				if (msg.x >= width - 230 && msg.x <= width - 230 + 50 && msg.y >= -345 && msg.y <= 60)
				{
					if (music_buttom_1)
					{
						music_buttom_1 = 0;
						mciSendString("pause bgm1", 0, 0, 0); // 关闭音乐
					}
					else
						music_buttom_1 = 1;
				}

				/*暂停的*/
				if (msg.x >= width - 170 && msg.x <= width - 170 + 50 && msg.y >= -345 && msg.y <= 60)
				{
					if (pause_buttom)
					{
						pause_buttom = 0;
						while (!pause_buttom)	game_draw(obstacles);
					}
					else	pause_buttom = 1;
				}

				/*重新开始的*/
				if (msg.x >= width - 110 && msg.x <= width - 110 + 50 && msg.y >= -345 && msg.y <= 60)
				{
					mciSendString("pause bgm1", 0, 0, 0); // 关闭音乐
					game_over = 0;
					game_logic_holistic_work();
					cout << "返回主页！" << endl;  // 通过控制台查看调试信息
				}

				/*返回主页的*/
				if (msg.x >= width - 50 && msg.x <= width && msg.y >= -345 && msg.y <= 60)
				{
					mciSendString("pause bgm1", 0, 0, 0); // 关闭音乐
					draw();
					cout << "重新开始！" << endl;  // 通过控制台查看调试信息
				}
			}
		}


		//人物贴图
		putimage(ball.x - ball.radius, ball.y - ball.radius, ball.radius * 2, ball.radius * 2, &part_img, 0, 0); // 横坐标，纵坐标；图片位置

		// 刷新绘图设备
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

