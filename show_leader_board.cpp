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


int game_count = 0, * score = &get_score; // ��ָ��ָ��÷֣���Ҫȷ����ͷ�ļ�����extern������Ӧ��
struct Player {
    int count; // �������ĵڼ��� ֻ�����ļ��п���
    int score; // ��ҷ���
};

std::vector<Player> player; // ����ṹ������

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

void save_scores(const std::string& filename) { // ����������ļ���
    std::ofstream outfile(filename, std::ios::trunc);
    if (outfile.is_open()) {
        for (const auto& p : player) {
            outfile << p.count << " " << p.score << std::endl;
        }
        outfile.close(); // �ر��ļ�
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
    settextstyle(30, 0, "Courier New"); // �����ı���ʽ
    settextcolor(RGB(202, 249, 130));   // ����������ɫΪǳ��ɫ
    setbkmode(TRANSPARENT);

    int x_start = 434;  // �ı���ʼλ��x
    int y_start = 281;  // �ı���ʼλ��y
    int x_gap = 136;    // ������÷�֮���ˮƽ��ࣨ���أ�
    int y_gap = 30;     // ��������֮��Ĵ�ֱ��ࣨ���أ�

    // ֻ��ʾǰ10��
    for (int i = 0; i < min(10, num); ++i) {
        std::string rank_text = std::to_string(i + 1) + " ";
        std::string score_text = std::to_string(player[i].score);

        // ��������
        outtextxy(x_start, y_start + y_gap * i, rank_text.c_str());

        // ���Ƶ÷�
        outtextxy(x_start + x_gap, y_start + i * y_gap, score_text.c_str());
    }
}

void show_leader_board() {
    cleardevice(); // ����豸
    IMAGE background;
    loadimage(&background, "./picture/background.png"); // ���а�ı���ͼƬ
    putimage(0, 0, &background);

    load_scores("./scores/scores.txt");
    game_count = player.size();

    if (*score == 0) { // ����÷�Ϊ��
        if (game_count == 0) { // ���û���κμ�¼
            std::string warning_txt = "������Ϸ���а������, ���������!";
            settextstyle(30, 0, "΢���ź�"); // ����������ֺ�
            settextcolor(RED); // ����������ɫΪ��ɫ
            setbkmode(TRANSPARENT);
            outtextxy(434, 281, warning_txt.c_str()); // �����������
        }
        else { // �м�¼����ʾ���а�
            print_to(game_count);
        }
    }
    else { // ����е�ǰ�÷�
        if (*score > 0) { // ֻ�е÷ִ���0��д���ļ�
            add_score(*score); // ��ӵ÷֣����һ��Զ�����
            game_count = player.size(); // ������Ϸ����
        }
        print_to(game_count);
    }

    int mark_return = 0; // �Ƿ��ܷ���������˵�
    while (mark_return == 0) // ѭ���ȴ��û�����
    {
        if (MouseHit()) // ����Ƿ��������Ϣ����
        {
            MOUSEMSG msg = GetMouseMsg(); // ��ȡ�����Ϣ

            if (msg.uMsg == WM_LBUTTONDOWN) // �ж��Ƿ��������
            {
                // �жϵ��λ���Ƿ���ָ�����η�Χ��
                if (msg.x >= 746 && msg.x <= 797 && msg.y >= 163 && msg.y <= 218) {
                    mark_return = 1;
                }
            }
        }
    }

    *score = 0; // �����󽫷�����Ϊ0
    if (mark_return) {
        cleardevice(); // �ر�ͼ�δ���
        draw();
    }
}