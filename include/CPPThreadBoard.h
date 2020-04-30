//
// Created by dylan on 4/30/2020.
//

#ifndef GAMEOFLIFE_CPPTHREADBOARD_H
#define GAMEOFLIFE_CPPTHREADBOARD_H

#include "Board.h"

class CPPThreadBoard : public Board{
    public:
        CPPThreadBoard(size_t M, size_t N);
        void tick() override;
    private:
        void tickLogic(int low, int high, bool *futureCells);
};

#endif //GAMEOFLIFE_CPPTHREADBOARD_H
