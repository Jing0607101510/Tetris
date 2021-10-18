#include <string.h>

#include "Map.h"

Map::Map(int width, int height) 
    : width_(width),
      height_(height),
      frame_(height, nullptr) {
    for (int i = 0; i < height; i++) {
        frame_[i] = new bool[width];
    }
}

Map::~Map() {
    for (int i = 0; i < height_; i++) {
        delete [] frame_[i];
        frame_[i] = nullptr;
    }
}

bool Map::CheckHit(const Square& square) {
    // TODO: 判断是否和边界，和frame上的方块接触（方法：先假设移动，再判断）
    return false;
}

int Map::RemoveLineIfNeed(const Square& square) {
    int height = square.GetPieceHeight();
    auto base_pos = square.GetBasePos();
    
    int win_score = 0;
    for (int i = base_pos.first; i < base_pos.first + height; i++) {
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
            }
            frame_[0] = tmp;

            win_score += width_;
        }
    }
    return win_score;
}