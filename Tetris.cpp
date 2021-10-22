#include <iostream>
#include <windows.h>
#include <conio.h>
#include <memory>

#include "Tetris.h"
#include "Utils.h"


Tetris::Tetris(int width, int height, int vertical_middle_bar, int horizontal_middle_bar) 
            : map_(vertical_middle_bar, height), 
              level_(1), 
              score_(0),
              width_(width),
              height_(height),
              vertical_middle_bar_(vertical_middle_bar),
              horizontal_middle_bar_(horizontal_middle_bar) {
}

bool Tetris::Welcome() {
    utils::SetColor(0);
    std::cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << std::endl;
    std::cout << "                  俄罗斯方块               " << std::endl;
    std::cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << std::endl;
    std::cout << "                   操作方式                " << std::endl;
    std::cout << "                 w - 旋转                  " << std::endl;
    std::cout << "                 s - 加速下移              " << std::endl;
    std::cout << "                 a - 左移                  " << std::endl;
    std::cout << "                 d - 右移                  " << std::endl;
    std::cout << "                 空格 - 暂停               " << std::endl;
    std::cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << std::endl;
    std::cout << "                按1-3选择难度              " << std::endl;
    std::cout << "                    按q退出                " << std::endl;
    std::cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << std::endl;
    
    char choose;
    while (true) {
        if (_kbhit()) {
            choose = _getch();
            if ('q' == choose) {
                return true;
            }
            else if(choose >= '1' && choose <= '3') {
                level_ = choose - '0';
                system("cls");
                return false;
            }
        }
        Sleep(1000);
    }
    return false;
}

bool Tetris::Judge(const std::unique_ptr<Square>& square) {
    auto base_pos = square->GetBasePos();
    int base_x = base_pos.first;
    int base_y = base_pos.second;
    auto points = square->GetPiecePoints();
    for (auto& point : points) {
        int x = base_x + point.first;
        int y = base_y + point.second;
        if (y < 0) {
            continue;
        }
        if (x<0 || x>=vertical_middle_bar_ || y>=height_ || map_.CheckHit(x, y)) {
            return false;
        }
    }
    return true;
}

void Tetris::MoveSquare(std::unique_ptr<Square>& square, int dx, int dy) {
    square->Move(dx, dy);
    if (Judge(square)) {
        square->Move(-dx, -dy);
        utils::EraseSquare(square);
        square->Move(dx, dy);
        utils::DrawSquare(square);
    }
    else {
        square->Move(-dx, -dy);
    }
}

void Tetris::RotateSquare(std::unique_ptr<Square>& square) {
    int rotation_type = square->GetRotationType();
    square->SetRotationType(rotation_type+1);
    if (Judge(square)) {
        square->SetRotationType(rotation_type);
        utils::EraseSquare(square);
        square->SetRotationType(rotation_type+1);
        utils::DrawSquare(square);
    }
    else {
        square->SetRotationType(rotation_type);
    }
}

bool Tetris::DropSquare(std::unique_ptr<Square>& cur_square, std::unique_ptr<Square>& next_square) {
    cur_square->Move(0, 1);
    if (Judge(cur_square)) {
        cur_square->Move(0, -1);
        utils::EraseSquare(cur_square);
        cur_square->Move(0, 1);
        utils::DrawSquare(cur_square);
        return true;
    }
    else {
        // 不能再向下了，那么就需要合并到map中
        // 判断是否能够消除
        // 判断是否游戏结束
        cur_square->Move(0, -1);
        bool is_over = false;
        score_ += map_.MergeSquare(cur_square, is_over);
        
        if (is_over) {
            return false;   
        }
        else {
            utils::EraseSquare(next_square);
            std::unique_ptr<Square> tmp = std::move(cur_square);
            cur_square = std::move(next_square);
            cur_square->SetBasePos({vertical_middle_bar_/2, -cur_square->GetPieceHeight()});
            next_square = std::move(tmp);
            next_square->SetBasePos({vertical_middle_bar_+5, horizontal_middle_bar_-6});
            next_square->RandSetPieceType();
            next_square->RandSetRotationType();
            utils::DrawScore(vertical_middle_bar_+4, 4, score_);
            utils::DrawSquare(next_square);
            return true;
        }
    }
}

void Tetris::Playing() {
    utils::DrawBoundary(width_, height_, vertical_middle_bar_, horizontal_middle_bar_);
    
    map_.InitMap();

    score_ = 0;
    int square_drop_wait_steps = 15 * (4 - level_);

    std::unique_ptr<Square> cur_square(new Square());
    cur_square->SetBasePos({vertical_middle_bar_/2, -cur_square->GetPieceHeight()});
    std::unique_ptr<Square> next_square(new Square({vertical_middle_bar_+5, horizontal_middle_bar_-6}));
    utils::DrawScore(vertical_middle_bar_+4, 4, score_);
    utils::DrawSquare(next_square);


    int step = 0;
    while (true) {
        if (step == square_drop_wait_steps) {
            step = 0;
            if(!DropSquare(cur_square, next_square)) {
                return;
            }
        }
        if (_kbhit()) {
            char key = _getch();
            switch (key) {
                case 'a':   // 向左
                    MoveSquare(cur_square, -1, 0);
                    break;
                case 'd':   // 向右
                    MoveSquare(cur_square, 1, 0);
                    break;
                case 'w':   // 旋转
                    RotateSquare(cur_square);
                    break;
                case 's':   // 加速向下
                    MoveSquare(cur_square, 0, 1);
                    break;
                case ' ':   // 暂停
                    Pause();
                    break;
            }
        }
        Sleep(1);
        step++;
    }
}

void Tetris::Pause() {
    utils::SetPosition((vertical_middle_bar_+3)*2, horizontal_middle_bar_-1);
    utils::SetColor(5);
    std::cout << "游戏暂停";

    while (true) {
        if (_kbhit()) {
            if (_getch() == ' ') {
                break;
            }
        }
        Sleep(1000);
    }
    
    utils::SetPosition((vertical_middle_bar_+3)*2, horizontal_middle_bar_-1);
    std::cout << "        ";
}

bool Tetris::End() {
    system("cls");
    utils::SetColor(0);

    std::cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << std::endl;
    std::cout << "                  俄罗斯方块               " << std::endl;
    std::cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << std::endl;
    std::cout << "               游戏结束，您的分数:          " << std::endl;
    std::cout << "                " << score_ << "           " << std::endl;
    std::cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << std::endl;
    std::cout << "             按非q的任意键返回开始界面       " << std::endl;
    std::cout << "                    按q退出                " << std::endl;
    std::cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << std::endl;

    char choose;
    while (true) {
        if (_kbhit()) {
            choose = _getch();
            if ('q' == choose) {
                return true;
            }
            else {
                system("cls");
                return false;
            }
        }
        Sleep(1000);
    }
}

void Tetris::Run() {
    utils::SetCursorNotVisible();

    bool quit = false;
    while (true) {
        quit = Welcome();
        if (quit) {
            break;
        }

        Playing();

        quit = End();
        if (quit) {
            break;
        }
    }
}



 
