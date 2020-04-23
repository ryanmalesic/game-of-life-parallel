//
// Created by Ryan Malesic on 4/17/20.
//

#include <iostream>
#include <random>
#include "Board.h"

Board::Board(size_t M, size_t N) : M(M), N(N), cells(new bool[M * N]{false}) {};

Board::~Board() {
  delete [] this->cells;
}

void Board::print() {
  for (int m = 0; m < this->M; ++m) {
    for (int n = 0; n < this->N; ++n) {
      std::cout << (this->cells[m * N + n] ? "*" : ".");
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

void Board::randomize() {
  std::minstd_rand rng(std::random_device{}());

  for (int m = 1; m < this->M - 1; ++m) {
    for (int n = 1; n < this->N - 1; ++n) {
      cells[m * N + n] = (rng() % 2) == 1;
    }
  }
}