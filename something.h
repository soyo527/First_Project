#pragma once


#include<stdio.h>
#include<easyX.h>
#include<iostream>
#include<cmath>
#include<ctime>
#include<iomanip>
#include <mmsystem.h> // ������ý���豸�ӿ�ͷ�ļ�
#pragma comment(lib, "winmm.lib") // ���ؾ�̬��
#pragma comment(lib,"MSIMG32.LIB") // ����ͼ�����
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
      ���ڵĳ�ʼ��

      ������;
      ����:����һ������Ϊ1200��600�Ĵ���

*/

//void Init();/

/*
      �滭��Ϸ����

      ������;
      ����:���Խ����ڳ�ʼ��
           ������ͼ����װ����
           �ֱ𽫸������ܵ��������к�������
           ˳���Ľ����������

*/
void draw();

void One_draw();

/*----------------------------------------------------*/
/*----------------------------------------------------*/
/*----------------------------------------------------*/
/*----------------------------------------------------*/
/*----------------------------------------------------*/
/*----------------------------------------------------*/

/*��ʼ��Ϸҳ�溯������*/
/*������֡��������⣬�����޸�*/

void game_logic_holistic_work();//���幤������

/*----------------------------------------------------*/
/*----------------------------------------------------*/
/*----------------------------------------------------*/
/*----------------------------------------------------*/
/*----------------------------------------------------*/
/*----------------------------------------------------*/


/*
     ���а��ҳ�溯�����

     ������:
     ����:��¼���ִ�С,�����ܹ���˳������
          ���ϽǷ��ذ�ť��������ز˵�
     ����:void
     ����ֵ:void



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
     ��Ϸ˵����ҳ�溯�����

     ������:
     ����:��һ�ν�����Ϸ������
     ���ϽǷ��ذ�ť��������ز˵�
     ����:void
     ����ֵ:void




*/

void show_game_instruction();

/*
     �̳ǻ�����ҳ�溯�����

     ������:
     ����:�����и��ָ����ķ���Ƥ����ÿ��Ƥ����Ӧ��Ҫ��ҵĶ���
     ���½Ƕ�Ӧ�Ž������
     ���ϽǷ��ذ�ť��������ز˵�
     ����:void
     ����ֵ:void

      Ҫ��:1.��Ƥ���������̳ǣ��ܹ����й���
           2.����Ǹ�Ƥ�������Ǹ�Ƥ��


*/

void load_skin();

void shop_skin();

/*
     ���õ�ҳ�溯�����

     ������:
     ����:1.��������
          2.������Ϸ�Ѷ�
     ���ϽǷ��ذ�ť��������ز˵�
     ����:void
     ����ֵ:void

     Ҫ��:1.����Ϸ���ϱ�������
*/
void setting();

/*
     �˳���Ϸ��ҳ�溯�����

     //���˳���Ϸ��ť��Ϸ����
*/
void exit_game();



/*

   draw��exit_game�е�һЩ��������

 */
// ��дԭ�е�putimage����,�޸���͸��ͼƬ����������ʾ
void putimage(int x, int y, IMAGE* img);

//��ҳ����
void Music_LL_homepage();

//�˵�����
void Music_LL_menu();

//��ҳͼƬ
void Picture_LL_homepage();

//�˵�ͼƬ
void Picture_LL_menu();

//�˵�������ͼƬ
void Picture_LL_six_function();

//��ҳҳ����ʾ
void LL_Homepage();
//�˵���ť�ӿ�
void enterOrReturnInterface();
//�˳���Ϸ����
void Picture_LL_exit_game();


/*
    ��Ϸҳ�溯������
*/
void showMainMenu(int img_center_x, int img_center_y, const char* texts[], int text_y_positions[], POINT cursorPos);

void showGameInstructions(int img_center_x, int img_center_y, POINT cursorPos);

void showGameFeatures(int img_center_x, int img_center_y, POINT cursorPos);

void showGameProcess(int img_center_x, int img_center_y, POINT cursorPos);

void showGameMenu(int img_center_x, int img_center_y, POINT cursorPos);

bool showReturnButton(int img_center_x, int img_center_y, POINT cursorPos, IMAGE& img_return_mask, IMAGE& img_return);

bool checkExitButton(POINT cursorPos);


