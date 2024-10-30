#define _CRT_SECURE_NO_WARNINGS 1

#include "something.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <graphics.h>

extern int get_score_1;
extern int get_gold_1;
int get_score = get_score_1;
int get_gold= get_gold_1;


int game_count = 0, * score = &get_score; // 用指针指向得分，但要确保在头文件中用extern声明对应的
struct Player {
    int count; // 玩家游玩的第几次 只能在文件中看到
    int score; // 玩家分数
};

std::vector<Player> player; // 定义结构体数组

void load_scores(const std::string& filename) {
    std::ifstream infile(filename);
    if (infile.is_open()) {
        player.clear();
        Player p;
        while (infile >> p.count >> p.score) {
            player.push_back(p);
        }
        infile.close();
        game_count = player.size();
    }
    else {
        game_count = 0;
    }
}

void save_scores(const std::string& filename) { // 保存分数到文件中
    std::ofstream outfile(filename, std::ios::trunc);
    if (outfile.is_open()) {
        for (const auto& p : player) {
            outfile << p.count << " " << p.score << std::endl;
        }
        outfile.close(); // 关闭文件
    }
}

void add_score(int score) {
    game_count++;
    player.push_back({ game_count, score });
    std::sort(player.begin(), player.end(), [](const Player& a, const Player& b) {
        return a.score > b.score;
        });
    save_scores("./scores/scores.txt");
}

void print_to(int num) {
    settextstyle(30, 0, "Courier New"); // 设置文本样式
    settextcolor(RGB(202, 249, 130));   // 设置文字颜色为浅绿色
    setbkmode(TRANSPARENT);

    int x_start = 434;  // 文本起始位置x
    int y_start = 281;  // 文本起始位置y
    int x_gap = 136;    // 名次与得分之间的水平间距（像素）
    int y_gap = 30;     // 相邻名次之间的垂直间距（像素）

    // 只显示前10名
    for (int i = 0; i < min(10, num); ++i) {
        std::string rank_text = std::to_string(i + 1) + " ";
        std::string score_text = std::to_string(player[i].score);

        // 绘制名次
        outtextxy(x_start, y_start + y_gap * i, rank_text.c_str());

        // 绘制得分
        outtextxy(x_start + x_gap, y_start + i * y_gap, score_text.c_str());
    }
}

void show_leader_board() {
    cleardevice(); // 清空设备
    IMAGE background;
    loadimage(&background, "./picture/background.png"); // 排行榜的背景图片
    putimage(0, 0, &background);

    load_scores("./scores/scores.txt");
    game_count = player.size();

    if (*score == 0) { // 如果得分为空
        if (game_count == 0) { // 如果没有任何记录
            std::string warning_txt = "暂无游戏排行榜的数据, 请先游玩吧!";
            settextstyle(30, 0, "微软雅黑"); // 设置字体和字号
            settextcolor(RED); // 设置文字颜色为红色
            setbkmode(TRANSPARENT);
            outtextxy(434, 281, warning_txt.c_str()); // 输出到界面上
        }
        else { // 有记录则显示排行榜
            print_to(game_count);
        }
    }
    else { // 如果有当前得分
        if (*score > 0) { // 只有得分大于0才写入文件
            add_score(*score); // 添加得分，并且会自动排序
            game_count = player.size(); // 更新游戏次数
        }
        print_to(game_count);
    }

    int mark_return = 0; // 是否能返回主界面菜单
    while (mark_return == 0) // 循环等待用户按键
    {
        if (MouseHit()) // 检测是否有鼠标消息发生
        {
            MOUSEMSG msg = GetMouseMsg(); // 获取鼠标消息

            if (msg.uMsg == WM_LBUTTONDOWN) // 判断是否左键按下
            {
                // 判断点击位置是否在指定矩形范围内
                if (msg.x >= 746 && msg.x <= 797 && msg.y >= 163 && msg.y <= 218) {
                    mark_return = 1;
                }
            }
        }
    }

    *score = 0; // 结束后将分数设为0
    if (mark_return) {
        cleardevice(); // 关闭图形窗口
        draw();
    }
}