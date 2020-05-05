set(TARGET GameOfLife)
add_executable(${TARGET} main.cpp Board.cpp OmpBoard.cpp RajaBoard.cpp CppThreadsBoard.cpp SerialBoard.cpp)