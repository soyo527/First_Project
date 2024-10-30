#pragma once


#include<stdio.h>
#include<easyX.h>
#include<iostream>
#include<cmath>
#include<ctime>
#include<iomanip>
#include <mmsystem.h> // 包含多媒体设备接口头文件
#pragma comment(lib, "winmm.lib") // 加载静态库
#pragma comment(lib,"MSIMG32.LIB") // 加载图像处理库
#include <vector>
#include <fstream>
#include <conio.h>
#include <graphics.h>
#include <algorithm>
#include <string>
#include <stack>
#include <Windows.h>
#include <mmsystem.h>


using namespace std;


/*
      窗口的初始化

      负责人;
      功能:建立一个像素为1200×600的窗口

*/

//void Init();/

/*
      绘画游戏界面

      负责人;
      功能:可以将窗口初始画
           将背景图画安装合理
           分别将各个功能的文字排列合理，美观
           顺利的进入程序并运行

*/
void draw();

void One_draw();

/*----------------------------------------------------*/
/*----------------------------------------------------*/
/*----------------------------------------------------*/
/*----------------------------------------------------*/
/*----------------------------------------------------*/
/*----------------------------------------------------*/

/*开始游戏页面函数声明*/
/*除麦昊林、杨泽康以外，切勿修改*/

void game_logic_holistic_work();//整体工作函数

/*----------------------------------------------------*/
/*----------------------------------------------------*/
/*----------------------------------------------------*/
/*----------------------------------------------------*/
/*----------------------------------------------------*/
/*----------------------------------------------------*/


/*
     排行榜的页面函数设计

     负责人:
     功能:记录积分大小,并且能够按顺序排名
          右上角返回按钮，点击返回菜单
     参数:void
     返回值:void



*/






void add_score(int get_score);
void load_gold();

void show_leader_board();


/*----------------------------------------------------*/
/*----------------------------------------------------*/
/*----------------------------------------------------*/
/*----------------------------------------------------*/
/*----------------------------------------------------*/
/*----------------------------------------------------*/



/*
     游戏说明的页面函数设计

     负责人:
     功能:有一段介绍游戏的文字
     右上角返回按钮，点击返回菜单
     参数:void
     返回值:void




*/

void show_game_instruction();

/*
     商城换肤的页面函数设计

     负责人:
     功能:界面中各种各样的方块皮肤，每个皮肤对应需要金币的多少
     右下角对应着金币数量
     右上角返回按钮，点击返回菜单
     参数:void
     返回值:void

      要求:1.将皮肤排列在商城，能够进行购买
           2.点击那个皮肤换上那个皮肤


*/

void load_skin();

void shop_skin();

/*
     设置的页面函数设计

     负责人:
     功能:1.开关音乐
          2.调整游戏难度
     右上角返回按钮，点击返回菜单
     参数:void
     返回值:void

     要求:1.给游戏加上背景音乐
*/
void setting();

/*
     退出游戏的页面函数设计

     //按退出游戏按钮游戏结束
*/
void exit_game();



/*

   draw和exit_game中的一些函数声明

 */
// 重写原有的putimage函数,修复了透明图片不能正常显示
void putimage(int x, int y, IMAGE* img);

//主页音乐
void Music_LL_homepage();

//菜单音乐
void Music_LL_menu();

//主页图片
void Picture_LL_homepage();

//菜单图片
void Picture_LL_menu();

//菜单六大功能图片
void Picture_LL_six_function();

//主页页面显示
void LL_Homepage();
//菜单按钮接口
void enterOrReturnInterface();
//退出游戏界面
void Picture_LL_exit_game();


/*
    游戏页面函数声明
*/
void showMainMenu(int img_center_x, int img_center_y, const char* texts[], int text_y_positions[], POINT cursorPos);

void showGameInstructions(int img_center_x, int img_center_y, POINT cursorPos);

void showGameFeatures(int img_center_x, int img_center_y, POINT cursorPos);

void showGameProcess(int img_center_x, int img_center_y, POINT cursorPos);

void showGameMenu(int img_center_x, int img_center_y, POINT cursorPos);

bool showReturnButton(int img_center_x, int img_center_y, POINT cursorPos, IMAGE& img_return_mask, IMAGE& img_return);

bool checkExitButton(POINT cursorPos);


