#ifndef __TETRIS_H__
#define __TETRIS_H__

#include "Map.h"

class Tetris {
    public:
        Tetris(int width, int height);
        void Run();

    private:
        bool Welcome();
        bool Playing();
        bool End();
    
    private:
        Map map_;
        int level_; // 难度
        int score_; // 得分

};

#endif