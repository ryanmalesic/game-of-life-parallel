//
// Created by Ryan Malesic on 4/23/20.
//

#include <omp.h>
#include <OmpBoard.h>

OmpBoard::OmpBoard(size_t M, size_t N) : Board(M, N) {}

void OmpBoard::tick() {
  bool *futureCells = new bool[this->M * this->N]{false};

#pragma omp parallel for
  for (size_t m = 1; m < this->M - 1; ++m) {
#pragma omp parallel for
    for (size_t n = 1; n < this->N - 1; ++n) {
      int numNeighbors = 0;

      for (int dm = -1; dm <= 1; ++dm) {
        for (int dn = -1; dn <= 1; ++dn) {
          numNeighbors += this->cells[(m + dm) * this->N + (n + dn)] ? 1 : 0;
        }
      }

      if (this->cells[m * this->N + n]) {
        numNeighbors -= 1;
      }

      if (!this->cells[m * this->N + n] && numNeighbors == 3) {
        // Cell is born
        futureCells[m * this->N + n] = true;
      } else {
        // Cell survives with two or three neighbors, dies otherwise
        // Cell is not born
        futureCells[m * this->N + n] = this->cells[m * this->N + n] && (numNeighbors == 2 || numNeighbors == 3);
      }
    }
  }

  delete[] this->cells;
  this->cells = futureCells;
}