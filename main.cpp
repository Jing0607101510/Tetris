#include <windows.h>
#include <iostream>
#include <conio.h>
#include <vector>
using namespace std;

#include "Tetris.h"
#include "Utils.h"

int main(void) {
    int width = 24;
    int height = 26;
    int vertical_middle_bar = 15;
    int horizontal_middle_bar = 15;
    Tetris game(width, height, vertical_middle_bar, horizontal_middle_bar);
    game.Run();
    return 0;
}