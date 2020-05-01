//
// Created by dylan on 4/30/2020.
//

#include "CPPThreadBoard.h"
#include <thread>
#include <vector>
#include <functional>

using std::vector;
using std::thread;

CPPThreadBoard::CPPThreadBoard(size_t M, size_t N) : Board(M,N){};

void CPPThreadBoard::tick() {
    int P;
    int boardSize = M * N;
    if(N * M < 1000){
        P = 1;
    }
    else{
        P = (boardSize / 1000);
    }
    auto partition = [P, N = boardSize] (int tid) { return N * tid / P; };
    vector<thread> threads;
    bool *futureCells = new bool[this->M * this->N]{false};

    for(int i = 1; i < P; ++i){
        int low = partition(i);
        int high = partition(i+1);

        threads.emplace_back(std::mem_fn(&CPPThreadBoard::tickLogic),this,low,high,futureCells);
    }
    for (auto& t : threads) {
        t.join();
    }
    int low = partition(0);
    int high = partition(1);
    tickLogic(low, high, futureCells);
    this->cells = futureCells;
}

void CPPThreadBoard::tickLogic(int low, int high, bool *futureCells){
    int rowsMAX = M - 1;
    int colsMAX = N - 1;
    for(int i = low; i < high; ++i){
            if((i / this->N) % rowsMAX == 0){
                continue;
            }
            else if((i % this->N) % colsMAX == 0){
                continue;
            }

            int numNeighbors = 0;

            for (int dm = -1; dm <= 1; ++dm) {
                for (int dn = -1; dn <= 1; ++dn) {
                    int m = i / this->N;
                    int n = i % this->N;
                    numNeighbors += this->cells[(m + dm) * this->N + (n + dn)] ? 1 : 0;
                }
            }

            if (this->cells[i]) {
                numNeighbors -= 1;
            }

            if (!this->cells[i] && numNeighbors == 3) {
                // Cell is born
                futureCells[i] = true;
            } else {
                // Cell survives with two or three neighbors, dies otherwise
                // Cell is not born
                futureCells[i] = this->cells[i] && (numNeighbors == 2 || numNeighbors == 3);
            }
        }
    }
