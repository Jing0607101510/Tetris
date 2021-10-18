#include <iostream>

#include "Tetris.h"

Tetris::Tetris(int width, int height) 
            : map_(width, height), level_(1), score_(0) {
}

bool Tetris::Welcome() {
    std::cout << "������������������������������������������������������������������������������������" << std::endl;
    std::cout << "                  ����˹����               " << std::endl;
    std::cout << "������������������������������������������������������������������������������������" << std::endl;
    std::cout << "                   ������ʽ                " << std::endl;
    std::cout << "                 w - ��ת                  " << std::endl;
    std::cout << "		           s - ��������              " << std::endl;
    std::cout << "		           a - ����                  " << std::endl;
    std::cout << "            	   d - ����                  " << std::endl;
    std::cout << "		           �ո� - ��ͣ               " << std::endl;
    std::cout << "������������������������������������������������������������������������������������" << std::endl;
    std::cout << "                ��1-3ѡ���Ѷ�              " << std::endl;
    std::cout << "                    ��q�˳�                " << std::endl;
    std::cout << "������������������������������������������������������������������������������������" << std::endl;
    
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
    std::cout << "������������������������������������������������������������������������������������" << std::endl;
    std::cout << "                  ����˹����               " << std::endl;
    std::cout << "������������������������������������������������������������������������������������" << std::endl;
    std::cout << "               ��Ϸ���������ķ���:          " << std::endl;
    std::cout << "                " << score_ << "           " << std::endl;
    std::cout << "������������������������������������������������������������������������������������" << std::endl;
    std::cout << "             ����q����������ؿ�ʼ����       " << std::endl;
    std::cout << "                    ��q�˳�                " << std::endl;
    std::cout << "������������������������������������������������������������������������������������" << std::endl;

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