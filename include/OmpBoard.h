//
// Created by Ryan Malesic on 4/23/20.
//

#ifndef GAMEOFLIFE_INCLUDE_OMPBOARD_H
#define GAMEOFLIFE_INCLUDE_OMPBOARD_H

#include "Board.h"

class OmpBoard : public Board {
public:
  OmpBoard(size_t M, size_t N);
  void tick() override;
};

#endif //GAMEOFLIFE_INCLUDE_OMPBOARD_H
