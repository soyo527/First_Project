/*
�滭��Ϸ����

������ : ����
���� : ��һҳ��ҳ����С����Աչʾ
������ͼ����װ����
�ֱ𽫸������ܵ��������к�������
˳���Ľ����������
�����ܵĽ���
*/

#include "something.h"
extern int music_buttom_1;

//�˵�ҳ��
void draw() {
    while (1) {
        cleardevice();//����
        //����ԭ��
        setorigin(0, 0);
        BeginBatchDraw();
        mciSendString("open music/LL_menu.mp3 alias LL_menu", 0, 0, 0);
        if (music_buttom_1) {
            Music_LL_menu();
        }

        mciSendString("close music/LL_homepage.mp3", 0, 0, 0);
        Picture_LL_menu();
        Picture_LL_six_function();
        EndBatchDraw();
        enterOrReturnInterface();
    }
}

void One_draw() {
    //������ҳ
    LL_Homepage();
    while (1) {
        ExMessage LL;
        if (peekmessage(&LL)) {
            if (LL.message == WM_LBUTTONDOWN) {
                draw();
            }
        }
    }
}

// ��дԭ�е�putimage����,�޸���͸��ͼƬ����������ʾ
void putimage(int x, int y, IMAGE* img) {
    int w = img->getwidth();
    int h = img->getheight();
    AlphaBlend(GetImageHDC(NULL), x, y, w, h,
        GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}

//��ҳ����
void Music_LL_homepage() {
    mciSendString("open music/LL_homepage.mp3", 0, 0, 0);
    mciSendString("play music/LL_homepage.mp3 repeat", 0, 0, 0);
}

//�˵�����
void Music_LL_menu() {
    mciSendString("play LL_menu repeat ", 0, 0, 0);
}

//��ҳͼƬ
void Picture_LL_homepage() {
    IMAGE HP_1;
    loadimage(&HP_1, "picture/LL_homepage.png", 1200, 720);
    putimage(0, 0, &HP_1);
}

//�˵�ͼƬ
void Picture_LL_menu() {
    IMAGE P_menu;
    loadimage(&P_menu, "picture/LL_menu.png", 1200, 720);
    putimage(0, 0, &P_menu);
}

//�˵�������
void Picture_LL_six_function() {
    setbkmode(TRANSPARENT); // ���ñ���ģʽΪ͸��
    settextstyle(60, 0, _T("��������"));

    int frame_width = 1200;
    int line_height = 60;

    int offset = 10; // ��С��ƫ����

    settextcolor(RGB(45, 255, 0));
    outtextxy((frame_width - textwidth(_T("��ʼ��Ϸ"))) / 2, 200 - offset, _T("��ʼ��Ϸ"));

    settextcolor(RGB(23, 217, 255));
    outtextxy((frame_width - textwidth(_T("��Ϸ˵��"))) / 2, 200 + line_height - offset, _T("��Ϸ˵��"));

    settextcolor(YELLOW);
    outtextxy((frame_width - textwidth(_T("���а�"))) / 2, 200 + 2 * line_height - offset, _T("���а�"));

    settextcolor(RGB(255, 33, 180));
    outtextxy((frame_width - textwidth(_T("�̳ǻ���"))) / 2, 200 + 3 * line_height - offset, _T("�̳ǻ���"));

    settextcolor(RGB(255, 185, 136));
    outtextxy((frame_width - textwidth(_T("����"))) / 2, 200 + 4 * line_height - offset, _T("����"));

    settextcolor(RGB(254, 0, 0));
    outtextxy((frame_width - textwidth(_T("�˳���Ϸ"))) / 2, 200 + 5 * line_height - offset, _T("�˳���Ϸ"));
}



//��ҳҳ����ʾ
void LL_Homepage() {
    Music_LL_homepage();
    Picture_LL_six_function();
    Picture_LL_homepage();
}

//�˵���ť�ӿ�
void enterOrReturnInterface() {
    while (1) {
        ExMessage LL_menu_items;
        if (peekmessage(&LL_menu_items)) {
            if (LL_menu_items.message == WM_MOUSEMOVE) {
                // ���֮ǰ�Ĳ˵������»���
                Picture_LL_six_function();
                settextstyle(60, 0, _T("��������"));
                int frame_width = 1200;
                int line_height = 60;

                int offset = 10; // ��С��ƫ����

                if (LL_menu_items.x > 510 && LL_menu_items.x < 690) {
                    if (LL_menu_items.y > 200 && LL_menu_items.y < 200 + line_height) {
                        settextcolor(RGB(211, 0, 133));
                        outtextxy((frame_width - textwidth(_T("��ʼ��Ϸ"))) / 2, 200 - offset, _T("��ʼ��Ϸ"));
                    }
                    else if (LL_menu_items.y > 200 + line_height && LL_menu_items.y < 200 + 2 * line_height) {
                        settextcolor(RGB(254, 136, 212));
                        outtextxy((frame_width - textwidth(_T("��Ϸ˵��"))) / 2, 200 + line_height - offset, _T("��Ϸ˵��"));
                    }
                    else if (LL_menu_items.y > 200 + 2 * line_height && LL_menu_items.y < 200 + 3 * line_height) {
                        settextcolor(RGB(254, 136, 212));
                        outtextxy((frame_width - textwidth(_T("���а�"))) / 2, 200 + 2 * line_height - offset, _T("���а�"));
                    }
                    else if (LL_menu_items.y > 200 + 3 * line_height && LL_menu_items.y < 200 + 4 * line_height) {
                        settextcolor(RGB(254, 136, 212));
                        outtextxy((frame_width - textwidth(_T("�̳ǻ���"))) / 2, 200 + 3 * line_height - offset, _T("�̳ǻ���"));
                    }
                    else if (LL_menu_items.y > 200 + 4 * line_height && LL_menu_items.y < 200 + 5 * line_height) {
                        settextcolor(RGB(254, 136, 212));
                        outtextxy((frame_width - textwidth(_T("����"))) / 2, 200 + 4 * line_height - offset, _T("����"));
                    }
                    else if (LL_menu_items.y > 200 + 5 * line_height && LL_menu_items.y < 200 + 6 * line_height) {
                        settextcolor(RGB(254, 136, 212));
                        outtextxy((frame_width - textwidth(_T("�˳���Ϸ"))) / 2, 200 + 5 * line_height - offset, _T("�˳���Ϸ"));
                    }
                }
            }

            if (LL_menu_items.message == WM_LBUTTONDOWN) {
                if (LL_menu_items.x > 510 && LL_menu_items.x < 690) {
                    if (LL_menu_items.y > 200 && LL_menu_items.y < 250) {
                        mciSendString("close LL_menu ", 0, 0, 0); // ��ҳ������ͣ
                        game_logic_holistic_work();
                        break;
                    }
                    else if (LL_menu_items.y > 260 && LL_menu_items.y < 310) {
                        show_game_instruction();
                        break;
                    }
                    else if (LL_menu_items.y > 320 && LL_menu_items.y < 370) {
                        show_leader_board();
                        break;
                    }
                    else if (LL_menu_items.y > 380 && LL_menu_items.y < 430) {
                        mciSendString("close LL_menu ", 0, 0, 0); // ��ҳ������ͣ
                        shop_skin();
                        break;
                    }
                    else if (LL_menu_items.y > 440 && LL_menu_items.y < 490) {
                        setting();
                        break;
                    }
                    else if (LL_menu_items.y > 500 && LL_menu_items.y < 550) {
                        exit_game();
                        break;
                    }
                }
            }
        }
    }
}

