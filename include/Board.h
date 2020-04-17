//
// Created by Ryan Malesic on 4/17/20.
//

#ifndef GAMEOFLIFE_INCLUDE_BOARD_H
#define GAMEOFLIFE_INCLUDE_BOARD_H

#include <cstddef>

class Board {
public:
  Board(size_t M, size_t N);
  void print();
  virtual void randomize() = 0;
  virtual void tick() = 0;
protected:
  bool* board;
  size_t M, N;
};

#endif //GAMEOFLIFE_INCLUDE_BOARD_H
