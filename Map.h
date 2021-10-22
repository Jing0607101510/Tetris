#ifndef __MAP_H__
#define __MAP_H__

#include <vector>
#include <memory>

#include "Square.h"

class Map {
    public:
        Map(int width, int height);
        ~Map();
        bool CheckHit(int x, int y);
        int MergeSquare(const std::unique_ptr<Square>& square, bool& is_over);
        void InitMap();

    private:
        int RemoveLineIfNeed(int base_y, int height);

    private:
        const int width_;
        const int height_;
        std::vector<bool*> frame_;  // æ÷√Ê
};

#endif