/*
绘画游戏界面

负责人 : 罗磊
功能 : 第一页主页介绍小组人员展示
将背景图画安装合理
分别将各个功能的文字排列合理，美观
顺利的进入程序并运行
各功能的交互
*/

#include "something.h"
extern int music_buttom_1;

//菜单页面
void draw() {
    while (1) {
        cleardevice();//清屏
        //设置原点
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
    //进入主页
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

// 重写原有的putimage函数,修复了透明图片不能正常显示
void putimage(int x, int y, IMAGE* img) {
    int w = img->getwidth();
    int h = img->getheight();
    AlphaBlend(GetImageHDC(NULL), x, y, w, h,
        GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}

//主页音乐
void Music_LL_homepage() {
    mciSendString("open music/LL_homepage.mp3", 0, 0, 0);
    mciSendString("play music/LL_homepage.mp3 repeat", 0, 0, 0);
}

//菜单音乐
void Music_LL_menu() {
    mciSendString("play LL_menu repeat ", 0, 0, 0);
}

//主页图片
void Picture_LL_homepage() {
    IMAGE HP_1;
    loadimage(&HP_1, "picture/LL_homepage.png", 1200, 720);
    putimage(0, 0, &HP_1);
}

//菜单图片
void Picture_LL_menu() {
    IMAGE P_menu;
    loadimage(&P_menu, "picture/LL_menu.png", 1200, 720);
    putimage(0, 0, &P_menu);
}

//菜单六大功能
void Picture_LL_six_function() {
    setbkmode(TRANSPARENT); // 设置背景模式为透明
    settextstyle(60, 0, _T("华文琥珀"));

    int frame_width = 1200;
    int line_height = 60;

    int offset = 10; // 减小的偏移量

    settextcolor(RGB(45, 255, 0));
    outtextxy((frame_width - textwidth(_T("开始游戏"))) / 2, 200 - offset, _T("开始游戏"));

    settextcolor(RGB(23, 217, 255));
    outtextxy((frame_width - textwidth(_T("游戏说明"))) / 2, 200 + line_height - offset, _T("游戏说明"));

    settextcolor(YELLOW);
    outtextxy((frame_width - textwidth(_T("排行榜"))) / 2, 200 + 2 * line_height - offset, _T("排行榜"));

    settextcolor(RGB(255, 33, 180));
    outtextxy((frame_width - textwidth(_T("商城换肤"))) / 2, 200 + 3 * line_height - offset, _T("商城换肤"));

    settextcolor(RGB(255, 185, 136));
    outtextxy((frame_width - textwidth(_T("设置"))) / 2, 200 + 4 * line_height - offset, _T("设置"));

    settextcolor(RGB(254, 0, 0));
    outtextxy((frame_width - textwidth(_T("退出游戏"))) / 2, 200 + 5 * line_height - offset, _T("退出游戏"));
}



//主页页面显示
void LL_Homepage() {
    Music_LL_homepage();
    Picture_LL_six_function();
    Picture_LL_homepage();
}

//菜单按钮接口
void enterOrReturnInterface() {
    while (1) {
        ExMessage LL_menu_items;
        if (peekmessage(&LL_menu_items)) {
            if (LL_menu_items.message == WM_MOUSEMOVE) {
                // 清除之前的菜单，重新绘制
                Picture_LL_six_function();
                settextstyle(60, 0, _T("华文琥珀"));
                int frame_width = 1200;
                int line_height = 60;

                int offset = 10; // 减小的偏移量

                if (LL_menu_items.x > 510 && LL_menu_items.x < 690) {
                    if (LL_menu_items.y > 200 && LL_menu_items.y < 200 + line_height) {
                        settextcolor(RGB(211, 0, 133));
                        outtextxy((frame_width - textwidth(_T("开始游戏"))) / 2, 200 - offset, _T("开始游戏"));
                    }
                    else if (LL_menu_items.y > 200 + line_height && LL_menu_items.y < 200 + 2 * line_height) {
                        settextcolor(RGB(254, 136, 212));
                        outtextxy((frame_width - textwidth(_T("游戏说明"))) / 2, 200 + line_height - offset, _T("游戏说明"));
                    }
                    else if (LL_menu_items.y > 200 + 2 * line_height && LL_menu_items.y < 200 + 3 * line_height) {
                        settextcolor(RGB(254, 136, 212));
                        outtextxy((frame_width - textwidth(_T("排行榜"))) / 2, 200 + 2 * line_height - offset, _T("排行榜"));
                    }
                    else if (LL_menu_items.y > 200 + 3 * line_height && LL_menu_items.y < 200 + 4 * line_height) {
                        settextcolor(RGB(254, 136, 212));
                        outtextxy((frame_width - textwidth(_T("商城换肤"))) / 2, 200 + 3 * line_height - offset, _T("商城换肤"));
                    }
                    else if (LL_menu_items.y > 200 + 4 * line_height && LL_menu_items.y < 200 + 5 * line_height) {
                        settextcolor(RGB(254, 136, 212));
                        outtextxy((frame_width - textwidth(_T("设置"))) / 2, 200 + 4 * line_height - offset, _T("设置"));
                    }
                    else if (LL_menu_items.y > 200 + 5 * line_height && LL_menu_items.y < 200 + 6 * line_height) {
                        settextcolor(RGB(254, 136, 212));
                        outtextxy((frame_width - textwidth(_T("退出游戏"))) / 2, 200 + 5 * line_height - offset, _T("退出游戏"));
                    }
                }
            }

            if (LL_menu_items.message == WM_LBUTTONDOWN) {
                if (LL_menu_items.x > 510 && LL_menu_items.x < 690) {
                    if (LL_menu_items.y > 200 && LL_menu_items.y < 250) {
                        mciSendString("close LL_menu ", 0, 0, 0); // 主页音乐暂停
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
                        mciSendString("close LL_menu ", 0, 0, 0); // 主页音乐暂停
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

