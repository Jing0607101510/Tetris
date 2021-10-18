#include <windows.h>
#include <iostream>
#include <conio.h>
#include <vector>
using namespace std;

#include "Tetris.h"

int main(void) {
    int width = 15;
    int height = 30;
    Tetris game(width, height);
    game.Run();
    return 0;
}