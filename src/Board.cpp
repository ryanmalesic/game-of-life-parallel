//
// Created by Ryan Malesic on 4/17/20.
//

#include <iostream>
#include "Board.h"

Board::Board(size_t M, size_t N) : M(M), N(N), board(new bool[M * N]{false}) {};

void Board::print() {
  for (int m = 0; m < this->M; ++m) {
    for (int n = 0; n < this->N; ++n) {
      std::cout << (this->board[m * N + n] ? "*" : ".");
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}