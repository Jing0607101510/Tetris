#include <iostream>
#include <conio.h>
#include <windows.h>

#include "Utils.h"

namespace utils {
    // ������ɫ
    void SetColor(int color_id) {
        int color;
        switch (color_id) {
            case 0:
                color = 0x08;
                break;
            case 1:
                color = 0x0C;
                break;
            case 2:
                color = 0x0D;
                break;
            case 3:
                color = 0x0E;
                break;
            case 4:
                color = 0x0A;
                break;
            case 5:
                color = 0x03;
            default:
                color = 0x07;
                break;
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    }

    void SetPosition(short x, short y) {
        COORD position = {x, y};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
    }

    void SetCursorNotVisible() {
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO cursor_info;
        GetConsoleCursorInfo(handle, &cursor_info);
        cursor_info.bVisible = false;
        SetConsoleCursorInfo(handle, &cursor_info);
    }
    
    void DrawScore(int x, int y, int score) {
        SetColor(0);
        SetPosition(2*x, y);
        std::cout << "���ķ�����";
        SetPosition(2*x, y+1);
        std::cout << score;
        SetPosition(2*x, y+3);
        std::cout << "��һ������";
    }

    void DrawBoundary(int width, int height, int vertical_middle_bar, int horizontal_middle_bar) {
        // ���ĸ��������ǳ��ȶ�����λ��
        SetColor(5);
        // �ϱ߽�
        width += 2;
        height += 2;
        vertical_middle_bar += 1;
        horizontal_middle_bar += 1;

        for (int i = 0; i < width; i++) {
            SetPosition(i * 2, 0);
            std::cout << "��";  // һ����ռ����λ��
            SetPosition(i * 2, height-1);
            std::cout << "��";
        }

        for (int i = 1; i < height - 1; i++) {
            SetPosition(0, i);
            std::cout << "��";
            SetPosition(vertical_middle_bar * 2, i);
            std::cout << "��";
            SetPosition((width-1)*2, i);
            std::cout << "��";
        }

        for (int i = vertical_middle_bar + 1; i < width - 1; i++) {
            SetPosition(i * 2, horizontal_middle_bar);
            std::cout << "��";
        }
    }

    void DrawSquare(std::unique_ptr<Square>& square) {
        auto base_pos = square->GetBasePos();
        auto base_x = base_pos.first;
        auto base_y = base_pos.second;
        auto points = square->GetPiecePoints();
        auto point_cnt = points.size();
        for(int i = 0; i < point_cnt; i++) {
            int x = base_x + points[i].first;
            int y = base_y + points[i].second;
            if (y >= 0) {
                x = x + 1;
                y = y + 1;
                utils::SetColor(i+1);
                utils::SetPosition(x*2, y);
                std::cout << "��";
            }
        }
    }

    void EraseSquare(std::unique_ptr<Square>& square) {
        auto base_pos = square->GetBasePos();
        int base_x = base_pos.first;
        int base_y = base_pos.second;
        auto points = square->GetPiecePoints();
        for(auto& point : points) {
            int x = base_x + point.first;
            int y = base_y + point.second;
            if (y >= 0) {
                x += 1;
                y += 1;
                utils::SetPosition(x*2, y);
                std::cout << "  ";
            }
        }
    }
} 