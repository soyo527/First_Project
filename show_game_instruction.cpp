#define _CRT_SECURE_NO_WARNINGS 1  // ���ð�ȫ���棬������ʹ��һЩ����ȫ�ĺ�������fopen�ȡ�

#include <windows.h>  // ����Windows API��ͷ�ļ������ڴ��ڹ����ͼ�β�����
#include "something.h"  // �����û��Զ����ͷ�ļ������ܰ���һЩ����������������

/*
��ͩ

*/

/*��Ϸ˵����ҳ�溯�����*/

enum GameState {
    MAIN_MENU,          // ���˵�״̬
    GAME_INSTRUCTIONS,  // ��Ϸ˵��״̬
    GAME_FEATURES,      // ��Ϸ��ɫ״̬
    GAME_PROCESS,       // ��Ϸ����״̬
    GAME_MENU,          // ��Ϸ�˵�״̬
    EXIT                // �˳�״̬
};

void show_game_instruction() {
    IMAGE img_mm;  // �������˵�����ͼƬ����
    loadimage(&img_mm, "picture/ZTBJ.png");  // �������˵�����ͼƬ

    IMAGE img_return;  // �������ذ�ťͼƬ����
    loadimage(&img_return, "picture/���ؼ�.png", 40, 40);  // ���ط��ذ�ťͼƬ

    IMAGE img_return_mask;  // �������ذ�ť����ͼƬ����
    loadimage(&img_return_mask, "picture/fh-1.png", 40, 40); // ��������ͼƬ�����ںϳɷ��ذ�ťͼ��

    setbkmode(TRANSPARENT);  // ���ñ���ģʽΪ͸��
    int img_center_x = getwidth() / 2;  // ��ȡ���ڿ�ȵ��м�λ��
    int img_center_y = getheight() / 2;  // ��ȡ���ڸ߶ȵ��м�λ��

    const char* texts[] = {
        "��Ϸ˵��",             // ����
        "һ. ��Ϸ����",         // ��Ϸ�������
        "��. ��Ϸ�淨",         // ��Ϸ�淨����
        "��. ��Ϸ��ɫ",         // ��Ϸ��ɫ����
        "��. ��Ϸ����"          // ��Ϸ���̽���
    };

    int text_y_positions[5];  // �洢�ı��������λ��
    int offset = 20; // �����ƶ���ƫ����
    for (int i = 0; i < 5; ++i) {
        text_y_positions[i] = img_center_y - 120 + i * 60 + offset;  // ����ÿ���ı���������
    }

    GameState gameState = MAIN_MENU;  // ��ʼ����Ϸ״̬Ϊ���˵�
    stack<GameState> gameStateStack;  // ������Ϸ״̬ջ�����ڱ�����ʷ״̬

    while (true) {  // ��ѭ��
        BeginBatchDraw();  // ��ʼ��������

        setbkcolor(WHITE);  // ���ñ�����ɫΪ��ɫ
        cleardevice();  // ����豸��ʾ����
        putimage(0, 0, &img_mm);  // �������˵�����ͼƬ

        POINT cursorPos;  // �������λ�ñ���
        GetCursorPos(&cursorPos);  // ��ȡ������Ļ����
        ScreenToClient(GetHWnd(), &cursorPos);  // ���������ת��Ϊ��������

        if (gameState == MAIN_MENU) {  // �����Ϸ״̬�����˵�
            showMainMenu(img_center_x, img_center_y, texts, text_y_positions, cursorPos);  // ��ʾ���˵�

            if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {  // �������갴ť�Ƿ񱻰���
                for (int i = 1; i < 5; ++i) {  // �����˵�ѡ����Ա����У�
                    int textWidth = textwidth(texts[i]);  // ��ȡ�ı����
                    int textX = img_center_x - textWidth / 2;  // �����ı��ĺ�����
                    if (cursorPos.x >= textX && cursorPos.x <= textX + textWidth &&
                        cursorPos.y >= text_y_positions[i] && cursorPos.y <= text_y_positions[i] + textheight(texts[i])) {  // ������Ƿ����ı�������
                        gameStateStack.push(gameState);  // ���浱ǰ��Ϸ״̬
                        if (i == 1) gameState = GAME_MENU;  // ���ݵ�����ı��ı���Ϸ״̬
                        else if (i == 2) gameState = GAME_INSTRUCTIONS;
                        else if (i == 3) gameState = GAME_FEATURES;
                        else if (i == 4) gameState = GAME_PROCESS;
                        Sleep(200);  // ��ʱ200���룬��ֹ�ظ����
                    }
                }
                if (checkExitButton(cursorPos)) {  // ����˳���ť�Ƿ񱻵��
                    gameState = EXIT;  // ������Ϸ״̬Ϊ�˳�
                }
            }
        }
        else if (gameState == GAME_MENU) {  // �����Ϸ״̬����Ϸ�˵�
            showGameMenu(img_center_x, img_center_y, cursorPos);  // ��ʾ��Ϸ�˵�
            if (showReturnButton(img_center_x, img_center_y, cursorPos, img_return_mask, img_return)) {  // ��ⷵ�ذ�ť�Ƿ񱻵��
                gameState = gameStateStack.top();  // �ָ�֮ǰ�������Ϸ״̬
                gameStateStack.pop();  // ����״̬ջ�е�״̬
            }
            if (checkExitButton(cursorPos)) {  // ����˳���ť�Ƿ񱻵��
                gameState = EXIT;  // ������Ϸ״̬Ϊ�˳�
            }
        }
        else if (gameState == GAME_INSTRUCTIONS) {  // �����Ϸ״̬����Ϸ˵��
            showGameInstructions(img_center_x, img_center_y, cursorPos);  // ��ʾ��Ϸ˵��
            if (showReturnButton(img_center_x, img_center_y, cursorPos, img_return_mask, img_return)) {  // ��ⷵ�ذ�ť�Ƿ񱻵��
                gameState = gameStateStack.top();  // �ָ�֮ǰ�������Ϸ״̬
                gameStateStack.pop();  // ����״̬ջ�е�״̬
            }
            if (checkExitButton(cursorPos)) {  // ����˳���ť�Ƿ񱻵��
                gameState = EXIT;  // ������Ϸ״̬Ϊ�˳�
            }
        }
        else if (gameState == GAME_FEATURES) {  // �����Ϸ״̬����Ϸ��ɫ
            showGameFeatures(img_center_x, img_center_y, cursorPos);  // ��ʾ��Ϸ��ɫ
            if (showReturnButton(img_center_x, img_center_y, cursorPos, img_return_mask, img_return)) {  // ��ⷵ�ذ�ť�Ƿ񱻵��
                gameState = gameStateStack.top();  // �ָ�֮ǰ�������Ϸ״̬
                gameStateStack.pop();  // ����״̬ջ�е�״̬
            }
            if (checkExitButton(cursorPos)) {  // ����˳���ť�Ƿ񱻵��
                gameState = EXIT;  // ������Ϸ״̬Ϊ�˳�
            }
        }
        else if (gameState == GAME_PROCESS) {  // �����Ϸ״̬����Ϸ����
            showGameProcess(img_center_x, img_center_y, cursorPos);  // ��ʾ��Ϸ����
            if (showReturnButton(img_center_x, img_center_y, cursorPos, img_return_mask, img_return)) {  // ��ⷵ�ذ�ť�Ƿ񱻵��
                gameState = gameStateStack.top();  // �ָ�֮ǰ�������Ϸ״̬
                gameStateStack.pop();  // ����״̬ջ�е�״̬
            }
            if (checkExitButton(cursorPos)) {  // ����˳���ť�Ƿ񱻵��
                gameState = EXIT;  // ������Ϸ״̬Ϊ�˳�
            }
        }
        else if (gameState == EXIT) {  // �����Ϸ״̬���˳�
            break;  // �˳���ѭ��
        }

        EndBatchDraw();  // ������������

        Sleep(16);  // ��ʱ16���룬����֡��
    }

    // closegraph();  // �ر�ͼ�δ��ڣ��ͷ���Դ�����б�ע�͵��ˣ�
}


void showMainMenu(int img_center_x, int img_center_y, const char* texts[], int text_y_positions[], POINT cursorPos) {
    for (int i = 0; i < 5; ++i) {  // �����˵��ı�
        int textWidth, textHeight;
        int fontSize = 50;  // ���������СΪ50

        // �����ı����������ı���ɫ
        if (i == 0) {
            settextcolor(RGB(191, 85, 255));  // ������ɫ
        }
        else if (i == 1) {
            settextcolor(RGB(254, 0, 161));  // ��һ����ɫ
        }
        else if (i == 2) {
            settextcolor(YELLOW);  // �ڶ�����ɫ
        }
        else if (i == 3) {
            settextcolor(RGB(255, 0, 0));  // ��������ɫ
        }
        else if (i == 4) {
            settextcolor(RGB(99, 255, 81));  // ��������ɫ
        }
        else {
            settextcolor(YELLOW);  // Ĭ����ɫ
        }

        settextstyle(fontSize, 0, _T("��������"));  // ����������ʽ
        textWidth = textwidth(texts[i]);  // ��ȡ�ı����
        textHeight = textheight(texts[i]);  // ��ȡ�ı��߶�
        int textX = img_center_x - textWidth / 2;  // �����ı��ĺ�����

        // ���������ı������ڣ���ı��ı���ɫ
        if (cursorPos.x >= textX && cursorPos.x <= textX + textWidth &&
            cursorPos.y >= text_y_positions[i] && cursorPos.y <= text_y_positions[i] + textHeight) {
            settextcolor(RGB(86, 225, 255));  // ������ɫ
        }

        outtextxy(textX, text_y_positions[i], texts[i]);  // �����ı�
    }
}

void showGameInstructions(int img_center_x, int img_center_y, POINT cursorPos) {
    setbkmode(TRANSPARENT);  // ���ñ���ģʽΪ͸��

    const char* instructions[] = {
        "",
        "",
        "1.��ɫ���ƣ�",
        "ͨ���������̿ո��ʹ������Ծ",
        "2.���������ϰ�����Ϸֱ�ӽ���"
    };

    int colors[] = { RGB(1,1,1), RGB(210,135,254), RGB(254, 0, 161), RGB(255, 192, 203) };

    settextstyle(40, 0, _T("��������"));  // ����������ʽ

    for (int i = 1; i < 5; ++i) {  // ����˵���ı�������ǰ���У�
        settextcolor(colors[i - 1]);  // �����ı���ɫ
        int text_y = img_center_y - 80 + (i - 1) * 50;  // �����ı���������
        outtextxy(img_center_x - textwidth(instructions[i]) / 2, text_y, instructions[i]);  // �����ı�
    }
}

void showGameFeatures(int img_center_x, int img_center_y, POINT cursorPos) {
    setbkmode(TRANSPARENT);  // ���ñ���ģʽΪ͸��

    const char* features[] = {
        "1.�����ʱ��Խ�ã�����Խ��",
        "2.��Խ�ߣ�����Խ��",
        "3.�����ռ���ͼ�еĽ�������������ɫ",
        "4.�ḻ��Ƥ��װ��ϵͳ",
        ""
    };

    int colors[] = { RGB(255, 0, 0), RGB(0, 255, 0), RGB(255,165,0), RGB(255, 255, 0), RGB(210,135,254) };

    settextstyle(40, 0, _T("��������"));  // ����������ʽ

    for (int i = 0; i < 5; ++i) {  // ������ɫ�ı�
        settextcolor(colors[i]);  // �����ı���ɫ
        int text_y = img_center_y - 80 + i * 50;  // �����ı���������
        outtextxy(img_center_x - textwidth(features[i]) / 2, text_y, features[i]);  // �����ı�
    }
}

void showGameProcess(int img_center_x, int img_center_y, POINT cursorPos) {
    setbkmode(TRANSPARENT);  // ���ñ���ģʽΪ͸��

    const char* process[] = {
        "1.������Ϸ����",
        "2.�����ʼ��Ϸ",
        "3.���Ʒ��������Ծ���ܿ��ϰ���ռ����",
        "4.��Ϸ�������˳���Ϸ�����߼�������"
    };

    int colors[] = { RGB(255, 0, 0), RGB(0, 255, 0), RGB(254,0,161), RGB(255, 255, 0) };

    settextstyle(40, 0, _T("��������"));  // ����������ʽ

    for (int i = 0; i < 4; ++i) {  // ���������ı�
        settextcolor(colors[i]);  // �����ı���ɫ
        int text_y = img_center_y - 80 + i * 50;  // �����ı���������
        outtextxy(img_center_x - textwidth(process[i]) / 2, text_y, process[i]);  // �����ı�
    }
}

void showGameMenu(int img_center_x, int img_center_y, POINT cursorPos) {
    setbkmode(TRANSPARENT);  // ���ñ���ģʽΪ͸��

    const char* menuOptions[] = {
        "",
        "��Ϸ���湲��6�� �ֱ���",
        "��ʼ��Ϸ�����а�",
        "��Ϸ˵�����̳ǻ���",
        "���á��˳���Ϸ"
    };

    int menuColors[] = { RGB(255, 165, 0), RGB(255, 165, 0), RGB(255,254,39), RGB(210,135,254), RGB(45,255,0), RGB(45,255,0) };

    settextstyle(40, 0, _T("��������"));  // ����������ʽ

    for (int i = 0; i < 5; ++i) {  // �����˵�ѡ��
        settextcolor(menuColors[i]);  // �����ı���ɫ
        int text_y = img_center_y - 150 + i * 60;  // �����ı���������
        outtextxy(img_center_x - textwidth(menuOptions[i]) / 2, text_y, menuOptions[i]);  // �����ı�
    }
}

bool showReturnButton(int img_center_x, int img_center_y, POINT cursorPos, IMAGE& img_return_mask, IMAGE& img_return) {
    int imgWidth = img_return.getwidth();  // ��ȡ���ذ�ťͼ��Ŀ��
    int imgHeight = img_return.getheight();  // ��ȡ���ذ�ťͼ��ĸ߶�
    int imgX = img_center_x - imgWidth / 2 + 13;  // ���㷵�ذ�ť�ĺ�����
    int imgY = img_center_y + 220 - imgHeight / 2;  // ���㷵�ذ�ť��������

    putimage(imgX, imgY, &img_return_mask, SRCAND);  // ���Ʒ��ذ�ť������ͼ��
    putimage(imgX, imgY, &img_return, SRCPAINT);  // ���Ʒ��ذ�ť��ͼ��

    // ������Ƿ��ڷ��ذ�ť������
    if (cursorPos.x >= imgX && cursorPos.x <= imgX + imgWidth &&
        cursorPos.y >= imgY && cursorPos.y <= imgY + imgHeight) {
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {  // �������갴ť�Ƿ񱻰���
            return true;  // ������£�����true
        }
    }

    return false;  // ���򷵻�false
}

bool checkExitButton(POINT cursorPos) {
    int buttonX = 955;  // �˳���ť�ĺ�����
    int buttonY = 220;  // �˳���ť��������
    int buttonWidth = 80;  // �˳���ť�Ŀ��
    int buttonHeight = 80;  // �˳���ť�ĸ߶�

    // ������Ƿ����˳���ť������
    if (cursorPos.x >= buttonX && cursorPos.x <= buttonX + buttonWidth &&
        cursorPos.y >= buttonY && cursorPos.y <= buttonY + buttonHeight) {
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {  // �������갴ť�Ƿ񱻰���
            return true;  // ������£�����true
        }
    }
    return false;  // ���򷵻�false
}