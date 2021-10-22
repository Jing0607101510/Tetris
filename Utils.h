#include <memory>

#include "Square.h"

namespace utils {
    void SetColor(int color_id);
    void SetPosition(short x, short y);
    void SetCursorNotVisible();
    void DrawScore(int x, int y, int score);
    void DrawBoundary(int width, int height, int vertical_middle_bar, int horizontal_middle_bar);
    void DrawSquare(std::unique_ptr<Square>& square);
    void EraseSquare(std::unique_ptr<Square>& square);
}