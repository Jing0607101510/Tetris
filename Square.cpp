#include <stdlib.h>

#include "Square.h"

Square::Square(const Square::Point base_pos) {
    base_pos_ = base_pos;
    RandSetPieceType();
    RandSetRotationType();
}

void Square::RandSetPieceType() {
    int piece_type_cnt = all_pieces_.size();
    piece_type_ = rand() % piece_type_cnt;
}

void Square::Move(int dx, int dy) {
    base_pos_.first += dx;
    base_pos_.second += dy;
}

void Square::RandSetRotationType() {
    int rotation_type_cnt = all_pieces_[piece_type_].size();
    rotation_type_ = rand() % rotation_type_cnt;
}

Square::Piece Square::GetPiecePoints() {
    return all_pieces_[piece_type_][rotation_type_];
}

int Square::GetPieceHeight() const {
    return heights_[piece_type_][rotation_type_];
}

Square::Point Square::GetBasePos() const {
    return base_pos_;
}

// 所有不同类型的方块的不同旋转形式的坐标，坐标是相对左上角。左上角的坐标为（0，0）
std::vector<Square::PieceType> Square::all_pieces_ = { 
    {   // 条形
        {
            {0, 0}, {1, 0}, {2, 0}, {3, 0}
        },
        {
            {0, 0}, {0, 1}, {0, 2}, {0, 3}
        }
    },
    {   // 方形
        {
            {0, 0}, {1, 0}, {0, 1}, {1, 1}
        }
    },
    {   // L形
        {
            {0, 0}, {1, 0}, {1, 1}, {1, 2}
        },
        {
            {0, 1}, {1, 1}, {2, 0}, {2, 1}
        },
        {
            {0, 0}, {0, 1}, {0, 2}, {1, 2}
        },
        {
            {0, 0}, {0, 1}, {1, 0}, {2, 0}
        }
    },
    {   // J形
        {
            {1, 0}, {1, 1}, {1, 2}, {0, 2}
        },
        {
            {0, 0}, {0, 1}, {1, 1}, {2, 1}
        },
        {
            {0, 0}, {0, 1}, {0, 2}, {1, 0}
        },
        {
            {0, 0}, {1, 0}, {2, 0}, {2, 1}
        }
    },
    {   // T形
        {
            {1, 0}, {0, 1}, {1, 1}, {2, 1}
        },
        {
            {1, 0}, {1, 1}, {1, 2}, {0, 1}
        },
        {
            {0, 0}, {1, 0}, {2, 0}, {1, 1}
        },
        {
            {0, 0}, {0, 1}, {0, 2}, {1, 1}
        }
    },
    {   // S型
        {
            {1, 0}, {2, 0}, {1, 1}, {0, 1}
        },
        {
            {0, 0}, {0, 1}, {1, 1}, {1, 2}
        }
    },
    {   // Z型
        {
            {0, 0}, {1, 0}, {1, 1}, {2, 1}
        },
        {
            {1, 0}, {1, 1}, {0, 1}, {0, 2}
        }
    }
};

std::vector<std::vector<int>> Square::heights_ = {
    {4, 1},
    {2},
    {2, 3, 2, 3},
    {2, 3, 2, 3},
    {2, 3, 2, 3},
    {2, 3},
    {2, 3}
};


