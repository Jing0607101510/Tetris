#include <string.h>
#include <iostream>

#include "Map.h"
#include "Utils.h"

Map::Map(int width, int height) 
    : width_(width),
      height_(height),
      frame_(height, nullptr) {
    for (int i = 0; i < height; i++) {
        frame_[i] = new bool[width];
    }
    InitMap();
}

Map::~Map() {
    for (int i = 0; i < height_; i++) {
        delete [] frame_[i];
        frame_[i] = nullptr;
    }
}

bool Map::CheckHit(int x, int y) {
    return frame_[y][x] == true;
}

// 处理方块的合并，能够消除的消除
int Map::MergeSquare(const std::unique_ptr<Square>& square, bool& is_over) {
    auto base_pos = square->GetBasePos();
    auto points = square->GetPiecePoints();
    int x, y;
    for (auto& point : points) {
        x = base_pos.first + point.first;
        y = base_pos.second + point.second;
        if (base_pos.second < 0) {
            is_over = true;
            return 0;
        }
        frame_[y][x] = true;
        utils::SetPosition(x*2, y);
        utils::SetColor(0);
        std::cout << "■";

        if (y < top_) {
            top_ = y;
        }
    }

    return RemoveLineIfNeed(base_pos.second, square->GetPieceHeight());
}

int Map::RemoveLineIfNeed(int base_y, int height) {
    int win_score = 0;
    utils::SetColor(0);

    for (int i = base_y; i < base_y + height; i++) {
        bool flag = true;
        for(int j = 0; j < width_; j++) {
            if (!frame_[i][j]) {
                flag = false;
                break;
            }
        }

        if (flag) {
            bool* tmp = frame_[i];
            memset(tmp, 0, width_);

            for (int j = i; j > 0; j--) {
                frame_[j] = frame_[j-1];
                for (int k = 0; k < width_; k++) {
                    utils::SetPosition(k*2, j);
                    if (frame_[j][k]) {
                        std::cout << "■";
                    }
                    else {
                        std::cout << "  ";
                    }
                }
            }

            frame_[0] = tmp;
            for (int k = 0; k < width_; k++) {
                utils::SetPosition(k*2, 0);
                std::cout << " ";
            }

            win_score += width_;
            top_++;
        }
    }
    return win_score;
}

bool Map::LineUp() {

}

void Map::InitMap() {
    top_ = height_;
    for (int i = 0; i < height_; i++) {
        memset(frame_[i], 0, width_);
    }
}