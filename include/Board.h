//
// Created by Ryan Malesic on 4/17/20.
//

#ifndef GAMEOFLIFE_INCLUDE_BOARD_H
#define GAMEOFLIFE_INCLUDE_BOARD_H

#include <cstddef>

class Board {
public:
  Board(size_t M, size_t N);
  virtual ~Board() = default;
  void print();
  void randomize();
  virtual void tick() = 0;
protected:
  bool *cells;
  size_t M, N;
};

#endif //GAMEOFLIFE_INCLUDE_BOARD_H
