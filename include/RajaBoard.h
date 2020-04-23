//
// Created by Ryan Malesic on 4/17/20.
//

#ifndef GAMEOFLIFE_INCLUDE_RAJABOARD_H
#define GAMEOFLIFE_INCLUDE_RAJABOARD_H

#include "Board.h"

class RajaBoard : public Board {
public:
  RajaBoard(size_t M, size_t N);
  void tick() override;
};

#endif //GAMEOFLIFE_INCLUDE_RAJABOARD_H
