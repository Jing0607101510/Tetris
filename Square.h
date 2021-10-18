#ifndef __SQUARE_H__
#define __SQUARE_H__

#include <vector>

// 方块类
class Square {
    public:
        typedef std::pair<int, int> Point;  // 一个小正方形的坐标
        typedef std::vector<Point> Piece;   // 一个方块的所有坐标
        typedef std::vector<Piece> PieceType;   // 一种方块

        Square(const Square::Point base_pos);
        void RandSetPieceType();
        void RandSetRotationType();
        void Move(int dx, int dy);

        Square::Piece GetPiecePoints();
        Square::Point GetBasePos() const;
        int GetPieceHeight() const;

    private:
        static std::vector<PieceType> all_pieces_; // 所有不同类型的方块的不同旋转形式的坐标，坐标是相对左上角。左上角的坐标为（0，0）
        static std::vector<std::vector<int>> heights_;
        
        Point base_pos_;   // 基本点
        int piece_type_;    // 哪一种方块
        int rotation_type_; // 哪一种旋转
};

#endif