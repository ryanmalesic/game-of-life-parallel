//
// Created by Ryan Malesic on 4/17/20.
//

#include <RajaBoard.h>
#include <RAJA/RAJA.hpp>

RajaBoard::RajaBoard(size_t M, size_t N) : Board(M, N) {}

void RajaBoard::tick() {
  using namespace RAJA::statement;
  using COLLPASE_POLICY = RAJA::KernelPolicy<
      Collapse<
          RAJA::omp_parallel_collapse_exec,
          RAJA::ArgList<0, 1>,
          Lambda<0>
      >
  >;

  bool *futureCells = new bool[M * N]{false};

  RAJA::View<bool, RAJA::Layout<2>> CellsView(this->cells, this->M, this->N);
  RAJA::View<bool, RAJA::Layout<2>> FutureCellsView(futureCells, this->M, this->N);

  auto mRange = RAJA::RangeSegment(1, (this->M) - 1);
  auto nRange = RAJA::RangeSegment(1, (this->N) - 1);

  RAJA::kernel<COLLPASE_POLICY>(
      RAJA::make_tuple(mRange, nRange),
      [=](int m, int n) {
        int numNeighbors = 0;

        for (int dm = -1; dm <= 1; ++dm) {
          for (int dn = -1; dn <= 1; ++dn) {
            numNeighbors += CellsView((m + dm), (n + dn)) ? 1 : 0;
          }
        }

        if (CellsView(m, n)) {
          numNeighbors -= 1;
        }

        if (!CellsView(m, n) && numNeighbors == 3) {
          // Cell is born
          FutureCellsView(m, n) = true;
        } else {
          // Cell survives with two or three neighbors, dies otherwise
          // Cell is not born
          FutureCellsView(m, n) = CellsView(m, n) && (numNeighbors == 2 || numNeighbors == 3);
        }
      }
  );

  this->cells = futureCells;
}