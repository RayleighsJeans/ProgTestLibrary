#pragma once


#include <chrono>
#include <iostream>
#include <list>

namespace helper
{

/// @brief A helper object that measures and prints the time between tick() and
/// tock() and holds a lists of points in time.
class Timer
{
 private:
  using time = std::chrono::high_resolution_clock::time_point;
  using clock = std::chrono::high_resolution_clock;

  /// @brief The starting point (in time).
  time m_tick;
  /// @brief List of the stopped timers/lap times.
  std::list<time> m_tocks;

 public:
  /// @brief ctor. Start the timer.
  Timer() : m_tick(clock::now()) { m_tocks.push_back(m_tick); };

  /// @brief dtor. Nothing.
  ~Timer() = default;


 public:
  /// @brief Start the timer (restart if starting point already exists).
  void tick() { m_tick = clock::now(); };

  /// @brief Measure the timer and remember the 'lap time'.
  void tock(const bool debug = true)
  {
    m_tocks.push_back(clock::now());

    if (debug) {
      double duration = std::chrono::duration<double, std::milli>(
                          std::chrono::duration_cast<std::chrono::milliseconds>(
                            m_tocks.back() - m_tick))
                          .count();
      std::cout << ">> time past: " << duration << "ms;\n";
    }
  } // tock

  /// @brief Get the last timed section.
  /// @return Last elapsed lap time (high precision clock milliseconds).
  double elapsed() const
  {
    return (std::chrono::duration<double, std::milli>(
              std::chrono::duration_cast<std::chrono::milliseconds>(
                m_tocks.back() - m_tick))
              .count());
  } // elapsed

  /// @brief Get the time since creation.
  /// @return Last elapsed total time (high precision clock milliseconds).
  double timeSinceStart() const
  {
    return (std::chrono::duration<double, std::milli>(
              std::chrono::duration_cast<std::chrono::milliseconds>(
                m_tocks.back() - m_tocks.front()))
              .count());
  } // timeSinceStart
}; // class Timer
} // namespace helper