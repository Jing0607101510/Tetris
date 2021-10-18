#include <conio.h>
#include <windows.h>

namespace utils {
    // 设置颜色
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
            default:
                color = 0x07;
                break;
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    }

    
}