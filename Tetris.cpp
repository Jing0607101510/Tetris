#include <iostream>

#include "Tetris.h"

Tetris::Tetris(int width, int height) 
            : map_(width, height), level_(1), score_(0) {
}

bool Tetris::Welcome() {
    std::cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << std::endl;
    std::cout << "                  俄罗斯方块               " << std::endl;
    std::cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << std::endl;
    std::cout << "                   操作方式                " << std::endl;
    std::cout << "                 w - 旋转                  " << std::endl;
    std::cout << "		           s - 加速下移              " << std::endl;
    std::cout << "		           a - 左移                  " << std::endl;
    std::cout << "            	   d - 右移                  " << std::endl;
    std::cout << "		           空格 - 暂停               " << std::endl;
    std::cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << std::endl;
    std::cout << "                按1-3选择难度              " << std::endl;
    std::cout << "                    按q退出                " << std::endl;
    std::cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << std::endl;
    
    char choose;
    while (true) {
        choose = getchar();
        if ('q' == choose) {
            return false;
        }
        else if(choose >= '1' && choose <= '3') {
            level_ = choose - '0';
            return true;
        }
    }
    return false;
}

bool Tetris::Playing() {
    return true;
}

bool Tetris::End() {
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
        choose = getchar();
        if ('q' == choose) {
            return false;
        }
        else {
            return true;
        }
    }
}

void Tetris::Run() {
    bool quit = false;
    while (true) {
        quit = Welcome();
        if (quit) {
            break;
        }

        quit = Playing();
        if (quit) {
            break;
        }

        quit = End();
        if (quit) {
            break;
        }
    }
}