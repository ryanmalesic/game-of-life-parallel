//
// Created by dylan on 4/30/2020.
//

#ifndef GAMEOFLIFE_CPPTHREADBOARD_H
#define GAMEOFLIFE_CPPTHREADBOARD_H

#include "Board.h"

class CppThreadsBoard : public Board {
public:
  CppThreadsBoard(size_t M, size_t N);
  void tick() override;
};

#endif //GAMEOFLIFE_CPPTHREADBOARD_H
