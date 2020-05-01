//
// Created by dylan on 5/1/2020.
//

#ifndef GAME_OF_LIFE_PARALLEL_SERIALBOARD_H
#define GAME_OF_LIFE_PARALLEL_SERIALBOARD_H

#include "Board.h"

class SerialBoard : public Board {
public:
    SerialBoard(size_t M, size_t N);
    void tick() override;
};

#endif //GAME_OF_LIFE_PARALLEL_SERIALBOARD_H
