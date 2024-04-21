#pragma once

#include <chrono>

namespace QApp {
namespace Library {

class Time {
public:
  Time() = default;

  static Time MicroSeconds(long long microseconds);
  static Time MilliSeconds(long long milliseconds);
  static Time Seconds(long long seconds);

  friend Time operator+(const Time& first, const Time& second);
  friend Time operator-(const Time& first, const Time& second);
  Time& operator+=(const Time& other);
  Time& operator-=(const Time& other);

  friend bool operator<(const Time& first, const Time& second);
  friend bool operator>(const Time& first, const Time& second);
  friend bool operator<=(const Time& first, const Time& second);
  friend bool operator>=(const Time& first, const Time& second);
  friend bool operator==(const Time& first, const Time& second);
  friend bool operator!=(const Time& first, const Time& second);
  Time operator-() const;

  long long toMicroSecondsI() const;
  long long toMilliSecondsI() const;
  long long toSecondsI() const;
  long long toMinutesI() const;
  long long toHoursI() const;

  double toMicroSecondsF() const;
  double toMilliSecondsF() const;
  double toSecondsF() const;
  double toMinutesF() const;
  double toHoursF() const;

  static constexpr long long kMicrosecondsInMilliseconds = 1'000;
  static constexpr long long kMicrosecondsInSeconds = 1'000'000;
  static constexpr long long kMillisecondsInSeconds = 1'000;
  static constexpr long long kMicrosecondsInMinutes = 60'000'000;
  static constexpr long long kMicrosecondsInHours = 3'600'000'000;

protected:
  explicit Time(long long microseconds);

  long long Microseconds_ = 0;
};

class Timer {
public:
  Timer();
  Time get() const;
  void restart();

private:
  std::chrono::time_point<std::chrono::steady_clock> start_;
};

} // namespace Library
} // namespace QApp
