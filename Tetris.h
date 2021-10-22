#ifndef __TETRIS_H__
#define __TETRIS_H__

#include <memory>

#include "Map.h"

class Tetris {
    public:
        Tetris(int width, int height, int vertical_middle_bar, int horizontal_middle_bar);
        void Run();

    private:
        bool Welcome();
        bool Playing();
        bool End();
        bool Pause();
        bool Judge(const std::unique_ptr<Square>& square);
        void MoveSquare(std::unique_ptr<Square>& square, int dx, int dy);
        void RotateSquare(std::unique_ptr<Square>& square);
        void DropSquare(std::unique_ptr<Square>& cur_square, std::unique_ptr<Square>& next_square);

    private:
        Map map_;
        int level_; // 难度
        int score_; // 得分
        const int width_;
        const int height_;
        const int vertical_middle_bar_;
        const int horizontal_middle_bar_;      
};

#endif