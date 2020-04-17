//
// Created by Ryan Malesic on 4/12/20.
//

#ifndef GAMEOFLIFE_INCLUDE_RAJABOARD_HPP
#define GAMEOFLIFE_INCLUDE_RAJABOARD_HPP

#include <chrono>

template<typename Clock = std::chrono::steady_clock>
class Timer {
public:
  Timer() {
    start();
  }

  void
  start() {
    m_start = Clock::now();
  }

  void
  stop() {
    m_stop = Clock::now();
  }

  double
  getElapsedMs() const {
    auto timeDelta = m_stop - m_start;
    double elapsedMs = std::chrono::duration
        <double, std::milli>(timeDelta).count();

    return elapsedMs;
  }

private:
  decltype(Clock::now()) m_start;
  decltype(Clock::now()) m_stop;
};

#endif //GAMEOFLIFE__TIMER_HPP
