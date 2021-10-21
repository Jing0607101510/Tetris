#ifndef __MAP_H__
#define __MAP_H__

#include <vector>
#include "Square.h"

class Map {
    public:
        Map(int width, int height);
        ~Map();
        bool CheckHit(int x, int y);
        int RemoveLineIfNeed(const Square& square);

    private:
        const int width_;
        const int height_;
        std::vector<bool*> frame_;  // 局面
};

#endif