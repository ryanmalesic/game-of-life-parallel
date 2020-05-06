//
// Created by Ryan Malesic on 4/17/20.
//

#include <RajaBoard.h>
#include <RAJA/RAJA.hpp>

RajaBoard::RajaBoard(size_t M, size_t N) : Board(M, N) {}

void RajaBoard::tick() {
  using namespace RAJA::statement;
  using COLLPASE_POLICY = RAJA::KernelPolicy<
      RAJA::statement::For<1, RAJA::omp_parallel_for_exec,
                           RAJA::statement::For<0, RAJA::loop_exec,
                                                RAJA::statement::Lambda<0>
                           >
      >
  >;

  bool *futureCells = new bool[M * N]{false};

  auto mRange = RAJA::RangeSegment(1, (this->M) - 1);
  auto nRange = RAJA::RangeSegment(1, (this->N) - 1);

  RAJA::kernel<COLLPASE_POLICY>(
      RAJA::make_tuple(mRange, nRange),
      [=, this](int m, int n) {
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
  );

  delete[] this->cells;
  this->cells = futureCells;
}