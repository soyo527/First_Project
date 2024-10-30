#define _CRT_SECURE_NO_WARNINGS 1  // 禁用安全警告，以允许使用一些不安全的函数，如fopen等。

#include <windows.h>  // 引入Windows API的头文件，用于窗口管理和图形操作。
#include "something.h"  // 引入用户自定义的头文件，可能包含一些辅助函数或声明。

/*
张桐

*/

/*游戏说明的页面函数设计*/

enum GameState {
    MAIN_MENU,          // 主菜单状态
    GAME_INSTRUCTIONS,  // 游戏说明状态
    GAME_FEATURES,      // 游戏特色状态
    GAME_PROCESS,       // 游戏流程状态
    GAME_MENU,          // 游戏菜单状态
    EXIT                // 退出状态
};

void show_game_instruction() {
    IMAGE img_mm;  // 声明主菜单背景图片对象
    loadimage(&img_mm, "picture/ZTBJ.png");  // 加载主菜单背景图片

    IMAGE img_return;  // 声明返回按钮图片对象
    loadimage(&img_return, "picture/返回键.png", 40, 40);  // 加载返回按钮图片

    IMAGE img_return_mask;  // 声明返回按钮掩码图片对象
    loadimage(&img_return_mask, "picture/fh-1.png", 40, 40); // 加载掩码图片，用于合成返回按钮图像

    setbkmode(TRANSPARENT);  // 设置背景模式为透明
    int img_center_x = getwidth() / 2;  // 获取窗口宽度的中间位置
    int img_center_y = getheight() / 2;  // 获取窗口高度的中间位置

    const char* texts[] = {
        "游戏说明",             // 标题
        "一. 游戏界面",         // 游戏界面介绍
        "二. 游戏玩法",         // 游戏玩法介绍
        "三. 游戏特色",         // 游戏特色介绍
        "四. 游戏流程"          // 游戏流程介绍
    };

    int text_y_positions[5];  // 存储文本纵坐标的位置
    int offset = 20; // 向下移动的偏移量
    for (int i = 0; i < 5; ++i) {
        text_y_positions[i] = img_center_y - 120 + i * 60 + offset;  // 计算每行文本的纵坐标
    }

    GameState gameState = MAIN_MENU;  // 初始化游戏状态为主菜单
    stack<GameState> gameStateStack;  // 声明游戏状态栈，用于保存历史状态

    while (true) {  // 主循环
        BeginBatchDraw();  // 开始批量绘制

        setbkcolor(WHITE);  // 设置背景颜色为白色
        cleardevice();  // 清除设备显示内容
        putimage(0, 0, &img_mm);  // 绘制主菜单背景图片

        POINT cursorPos;  // 声明光标位置变量
        GetCursorPos(&cursorPos);  // 获取光标的屏幕坐标
        ScreenToClient(GetHWnd(), &cursorPos);  // 将光标坐标转换为窗口坐标

        if (gameState == MAIN_MENU) {  // 如果游戏状态是主菜单
            showMainMenu(img_center_x, img_center_y, texts, text_y_positions, cursorPos);  // 显示主菜单

            if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {  // 检测左鼠标按钮是否被按下
                for (int i = 1; i < 5; ++i) {  // 遍历菜单选项（忽略标题行）
                    int textWidth = textwidth(texts[i]);  // 获取文本宽度
                    int textX = img_center_x - textWidth / 2;  // 计算文本的横坐标
                    if (cursorPos.x >= textX && cursorPos.x <= textX + textWidth &&
                        cursorPos.y >= text_y_positions[i] && cursorPos.y <= text_y_positions[i] + textheight(texts[i])) {  // 检测光标是否在文本区域内
                        gameStateStack.push(gameState);  // 保存当前游戏状态
                        if (i == 1) gameState = GAME_MENU;  // 根据点击的文本改变游戏状态
                        else if (i == 2) gameState = GAME_INSTRUCTIONS;
                        else if (i == 3) gameState = GAME_FEATURES;
                        else if (i == 4) gameState = GAME_PROCESS;
                        Sleep(200);  // 延时200毫秒，防止重复点击
                    }
                }
                if (checkExitButton(cursorPos)) {  // 检测退出按钮是否被点击
                    gameState = EXIT;  // 设置游戏状态为退出
                }
            }
        }
        else if (gameState == GAME_MENU) {  // 如果游戏状态是游戏菜单
            showGameMenu(img_center_x, img_center_y, cursorPos);  // 显示游戏菜单
            if (showReturnButton(img_center_x, img_center_y, cursorPos, img_return_mask, img_return)) {  // 检测返回按钮是否被点击
                gameState = gameStateStack.top();  // 恢复之前保存的游戏状态
                gameStateStack.pop();  // 弹出状态栈中的状态
            }
            if (checkExitButton(cursorPos)) {  // 检测退出按钮是否被点击
                gameState = EXIT;  // 设置游戏状态为退出
            }
        }
        else if (gameState == GAME_INSTRUCTIONS) {  // 如果游戏状态是游戏说明
            showGameInstructions(img_center_x, img_center_y, cursorPos);  // 显示游戏说明
            if (showReturnButton(img_center_x, img_center_y, cursorPos, img_return_mask, img_return)) {  // 检测返回按钮是否被点击
                gameState = gameStateStack.top();  // 恢复之前保存的游戏状态
                gameStateStack.pop();  // 弹出状态栈中的状态
            }
            if (checkExitButton(cursorPos)) {  // 检测退出按钮是否被点击
                gameState = EXIT;  // 设置游戏状态为退出
            }
        }
        else if (gameState == GAME_FEATURES) {  // 如果游戏状态是游戏特色
            showGameFeatures(img_center_x, img_center_y, cursorPos);  // 显示游戏特色
            if (showReturnButton(img_center_x, img_center_y, cursorPos, img_return_mask, img_return)) {  // 检测返回按钮是否被点击
                gameState = gameStateStack.top();  // 恢复之前保存的游戏状态
                gameStateStack.pop();  // 弹出状态栈中的状态
            }
            if (checkExitButton(cursorPos)) {  // 检测退出按钮是否被点击
                gameState = EXIT;  // 设置游戏状态为退出
            }
        }
        else if (gameState == GAME_PROCESS) {  // 如果游戏状态是游戏流程
            showGameProcess(img_center_x, img_center_y, cursorPos);  // 显示游戏流程
            if (showReturnButton(img_center_x, img_center_y, cursorPos, img_return_mask, img_return)) {  // 检测返回按钮是否被点击
                gameState = gameStateStack.top();  // 恢复之前保存的游戏状态
                gameStateStack.pop();  // 弹出状态栈中的状态
            }
            if (checkExitButton(cursorPos)) {  // 检测退出按钮是否被点击
                gameState = EXIT;  // 设置游戏状态为退出
            }
        }
        else if (gameState == EXIT) {  // 如果游戏状态是退出
            break;  // 退出主循环
        }

        EndBatchDraw();  // 结束批量绘制

        Sleep(16);  // 延时16毫秒，控制帧率
    }

    // closegraph();  // 关闭图形窗口，释放资源（这行被注释掉了）
}


void showMainMenu(int img_center_x, int img_center_y, const char* texts[], int text_y_positions[], POINT cursorPos) {
    for (int i = 0; i < 5; ++i) {  // 遍历菜单文本
        int textWidth, textHeight;
        int fontSize = 50;  // 设置字体大小为50

        // 根据文本行数设置文本颜色
        if (i == 0) {
            settextcolor(RGB(191, 85, 255));  // 标题颜色
        }
        else if (i == 1) {
            settextcolor(RGB(254, 0, 161));  // 第一行颜色
        }
        else if (i == 2) {
            settextcolor(YELLOW);  // 第二行颜色
        }
        else if (i == 3) {
            settextcolor(RGB(255, 0, 0));  // 第三行颜色
        }
        else if (i == 4) {
            settextcolor(RGB(99, 255, 81));  // 第四行颜色
        }
        else {
            settextcolor(YELLOW);  // 默认颜色
        }

        settextstyle(fontSize, 0, _T("华文琥珀"));  // 设置字体样式
        textWidth = textwidth(texts[i]);  // 获取文本宽度
        textHeight = textheight(texts[i]);  // 获取文本高度
        int textX = img_center_x - textWidth / 2;  // 计算文本的横坐标

        // 如果光标在文本区域内，则改变文本颜色
        if (cursorPos.x >= textX && cursorPos.x <= textX + textWidth &&
            cursorPos.y >= text_y_positions[i] && cursorPos.y <= text_y_positions[i] + textHeight) {
            settextcolor(RGB(86, 225, 255));  // 高亮颜色
        }

        outtextxy(textX, text_y_positions[i], texts[i]);  // 绘制文本
    }
}

void showGameInstructions(int img_center_x, int img_center_y, POINT cursorPos) {
    setbkmode(TRANSPARENT);  // 设置背景模式为透明

    const char* instructions[] = {
        "",
        "",
        "1.角色控制：",
        "通过按动键盘空格键使方块跳跃",
        "2.方块碰到障碍物游戏直接结束"
    };

    int colors[] = { RGB(1,1,1), RGB(210,135,254), RGB(254, 0, 161), RGB(255, 192, 203) };

    settextstyle(40, 0, _T("华文琥珀"));  // 设置字体样式

    for (int i = 1; i < 5; ++i) {  // 遍历说明文本（忽略前两行）
        settextcolor(colors[i - 1]);  // 设置文本颜色
        int text_y = img_center_y - 80 + (i - 1) * 50;  // 计算文本的纵坐标
        outtextxy(img_center_x - textwidth(instructions[i]) / 2, text_y, instructions[i]);  // 绘制文本
    }
}

void showGameFeatures(int img_center_x, int img_center_y, POINT cursorPos) {
    setbkmode(TRANSPARENT);  // 设置背景模式为透明

    const char* features[] = {
        "1.你存活的时间越久，分数越高",
        "2.分越高，排名越高",
        "3.可以收集地图中的金币来解锁更多角色",
        "4.丰富的皮肤装扮系统",
        ""
    };

    int colors[] = { RGB(255, 0, 0), RGB(0, 255, 0), RGB(255,165,0), RGB(255, 255, 0), RGB(210,135,254) };

    settextstyle(40, 0, _T("华文琥珀"));  // 设置字体样式

    for (int i = 0; i < 5; ++i) {  // 遍历特色文本
        settextcolor(colors[i]);  // 设置文本颜色
        int text_y = img_center_y - 80 + i * 50;  // 计算文本的纵坐标
        outtextxy(img_center_x - textwidth(features[i]) / 2, text_y, features[i]);  // 绘制文本
    }
}

void showGameProcess(int img_center_x, int img_center_y, POINT cursorPos) {
    setbkmode(TRANSPARENT);  // 设置背景模式为透明

    const char* process[] = {
        "1.进入游戏界面",
        "2.点击开始游戏",
        "3.控制方块进行跳跃，避开障碍物，收集金币",
        "4.游戏结束，退出游戏，或者继续游玩"
    };

    int colors[] = { RGB(255, 0, 0), RGB(0, 255, 0), RGB(254,0,161), RGB(255, 255, 0) };

    settextstyle(40, 0, _T("华文琥珀"));  // 设置字体样式

    for (int i = 0; i < 4; ++i) {  // 遍历流程文本
        settextcolor(colors[i]);  // 设置文本颜色
        int text_y = img_center_y - 80 + i * 50;  // 计算文本的纵坐标
        outtextxy(img_center_x - textwidth(process[i]) / 2, text_y, process[i]);  // 绘制文本
    }
}

void showGameMenu(int img_center_x, int img_center_y, POINT cursorPos) {
    setbkmode(TRANSPARENT);  // 设置背景模式为透明

    const char* menuOptions[] = {
        "",
        "游戏界面共有6个 分别是",
        "开始游戏、排行榜",
        "游戏说明、商城换肤",
        "设置、退出游戏"
    };

    int menuColors[] = { RGB(255, 165, 0), RGB(255, 165, 0), RGB(255,254,39), RGB(210,135,254), RGB(45,255,0), RGB(45,255,0) };

    settextstyle(40, 0, _T("华文琥珀"));  // 设置字体样式

    for (int i = 0; i < 5; ++i) {  // 遍历菜单选项
        settextcolor(menuColors[i]);  // 设置文本颜色
        int text_y = img_center_y - 150 + i * 60;  // 计算文本的纵坐标
        outtextxy(img_center_x - textwidth(menuOptions[i]) / 2, text_y, menuOptions[i]);  // 绘制文本
    }
}

bool showReturnButton(int img_center_x, int img_center_y, POINT cursorPos, IMAGE& img_return_mask, IMAGE& img_return) {
    int imgWidth = img_return.getwidth();  // 获取返回按钮图像的宽度
    int imgHeight = img_return.getheight();  // 获取返回按钮图像的高度
    int imgX = img_center_x - imgWidth / 2 + 13;  // 计算返回按钮的横坐标
    int imgY = img_center_y + 220 - imgHeight / 2;  // 计算返回按钮的纵坐标

    putimage(imgX, imgY, &img_return_mask, SRCAND);  // 绘制返回按钮的掩码图像
    putimage(imgX, imgY, &img_return, SRCPAINT);  // 绘制返回按钮的图像

    // 检测光标是否在返回按钮区域内
    if (cursorPos.x >= imgX && cursorPos.x <= imgX + imgWidth &&
        cursorPos.y >= imgY && cursorPos.y <= imgY + imgHeight) {
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {  // 检测左鼠标按钮是否被按下
            return true;  // 如果按下，返回true
        }
    }

    return false;  // 否则返回false
}

bool checkExitButton(POINT cursorPos) {
    int buttonX = 955;  // 退出按钮的横坐标
    int buttonY = 220;  // 退出按钮的纵坐标
    int buttonWidth = 80;  // 退出按钮的宽度
    int buttonHeight = 80;  // 退出按钮的高度

    // 检测光标是否在退出按钮区域内
    if (cursorPos.x >= buttonX && cursorPos.x <= buttonX + buttonWidth &&
        cursorPos.y >= buttonY && cursorPos.y <= buttonY + buttonHeight) {
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {  // 检测左鼠标按钮是否被按下
            return true;  // 如果按下，返回true
        }
    }
    return false;  // 否则返回false
}