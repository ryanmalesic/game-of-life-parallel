//
// Created by dylan on 4/30/2020.
//

#include "CppThreadsBoard.h"
#include <thread>
#include <vector>
#include <functional>

using std::vector;
using std::thread;

CppThreadsBoard::CppThreadsBoard(size_t M, size_t N) : Board(M, N) {};

void CppThreadsBoard::tick() {
  int P = 8;
  auto partition = [P, N = this->M * this->N](int tid) { return N * tid / P; };

  bool *futureCells = new bool[this->M * this->N]{false};

  vector<thread> threads;

  auto tickCells = [&futureCells, cells = this->cells, N = this->N, M = this->M](int low, int high) {
    for (int i = low; i < high; ++i) {
      if (!((i / N) % (M - 1) == 0 || (i % N) % (N - 1) == 0)) {

        int numNeighbors = 0;

        for (int dm = -1; dm <= 1; ++dm) {
          for (int dn = -1; dn <= 1; ++dn) {
            int m = i / N;
            int n = i % N;
            numNeighbors += cells[(m + dm) * N + (n + dn)] ? 1 : 0;
          }
        }

        if (cells[i]) {
          numNeighbors -= 1;
        }

        if (!cells[i] && numNeighbors == 3) {
          // Cell is born
          futureCells[i] = true;
        } else {
          // Cell survives with two or three neighbors, dies otherwise
          // Cell is not born
          futureCells[i] = cells[i] && (numNeighbors == 2 || numNeighbors == 3);
        }
      }
    }
  };

  for (int i = 1; i < P; ++i) {
    threads.emplace_back(tickCells, partition(i), partition(i + 1));
  }

  tickCells(partition(0), partition(1));

  for (auto &t : threads) {
    t.join();
  }

  delete[] this->cells;
  this->cells = futureCells;
}