#include <iostream>
#include <getopt.h>
#include <string>
#include <OmpBoard.h>
#include <RajaBoard.h>
#include <CPPThreadBoard.h>
#include <Timer.hpp>

void print_usage() {
  std::cout << "Usage: main -b (OMP | RAJA) -m <rows> -n <cols> [-s -p -t]" << std::endl;
  std::cout << "       main --board (OMP | RAJA) --rows <rows> --cols <cols> [--step --print --time]" << std::endl;
}

int main(int argc, char **argv) {
  size_t M = 0, N = 0;
  std::string board_string;
  bool print = false, step = false, time = false;

  int opt = 0;

  static struct option long_options[] = {
      {"board", required_argument, nullptr, 'b'},
      {"print", no_argument, nullptr, 'p'},
      {"step", no_argument, nullptr, 's'},
      {"time", no_argument, nullptr, 't'},
      {"rows", required_argument, nullptr, 'm'},
      {"cols", required_argument, nullptr, 'n'},
      {nullptr, 0, nullptr, 0}
  };

  int long_index = 0;

  while ((opt = getopt_long(argc, argv, "b:m:n:pst",
                            long_options, &long_index)) != -1) {
    switch (opt) {
    case 'b' : board_string.assign(optarg);
      break;
    case 'm' : M = strtoull(optarg, nullptr, 10);
      break;
    case 'n' : N = strtoull(optarg, nullptr, 10);
      break;
    case 'p' : print = true;
      break;
    case 's' : step = true;
      break;
    case 't' : time = true;
      break;
    default: print_usage();
      exit(EXIT_FAILURE);
    }
  }

  if (M == 0 || N == 0 || board_string.empty()) {
    print_usage();
    exit(EXIT_FAILURE);
  }

  Board *board;

  if (board_string == "RAJA") {
      board = new RajaBoard(M, N);
  } else if (board_string == "OMP") {
      board = new OmpBoard(M, N);
  } else if (board_string == "CPP"){
      board = new CPPThreadBoard(M,N);
    }else {
    std::cout << "Invalid board" << std::endl;
    print_usage();
    exit(EXIT_FAILURE);
  }

  board->randomize();

  Timer<> timer;

  do {
    if (time) {
      timer.start();
      board->tick();
      timer.stop();
      std::cout << "TICK -- " << timer.getElapsedMs() / 1000 << "s" << std::endl;
    } else {
      board->tick();
    }

    if (print) {
      board->print();
    }
  } while (!step || std::cin.get());

  delete board;

  return EXIT_SUCCESS;
}
