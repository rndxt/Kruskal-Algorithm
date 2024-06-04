#include "Time.h"

#include <QDebug>

namespace QApp {
namespace Library {

Time Time::MicroSeconds(long long microseconds) {
  return Time(microseconds);
}

Time Time::MilliSeconds(long long milliseconds) {
  return Time(kMicrosecondsInMilliseconds * milliseconds);
}

Time Time::Seconds(long long seconds) {
  return Time(kMicrosecondsInSeconds * seconds);
}

Time operator+(const Time& first, const Time& second) {
  return Time(first.Microseconds_ + second.Microseconds_);
}

Time operator-(const Time& first, const Time& second) {
  return Time(first.Microseconds_ - second.Microseconds_);
}

Time& Time::operator+=(const Time& other) {
  Microseconds_ += other.Microseconds_;
  return *this;
}

Time& Time::operator-=(const Time& other) {
  Microseconds_ -= other.Microseconds_;
  return *this;
}

bool operator<(const Time& first, const Time& second) {
  return first.Microseconds_ < second.Microseconds_;
}

bool operator>(const Time& first, const Time& second) {
  return second < first;
}

bool operator<=(const Time& first, const Time& second) {
  return !(second < first);
}

bool operator>=(const Time& first, const Time& second) {
  return !(first < second);
}

bool operator==(const Time& first, const Time& second) {
  return first.Microseconds_ == second.Microseconds_;
}

bool operator!=(const Time& first, const Time& second) {
  return !(first == second);
}

Time Time::operator-() const {
  return Time(-Microseconds_);
}

long long Time::toMicroSecondsI() const {
  return Microseconds_;
}

long long Time::toMilliSecondsI() const {
  return Microseconds_ / kMicrosecondsInMilliseconds;
}

long long Time::toSecondsI() const {
  return Microseconds_ / kMicrosecondsInSeconds;
}

long long Time::toMinutesI() const {
  return Microseconds_ / kMicrosecondsInMinutes;
}

long long Time::toHoursI() const {
  return Microseconds_ / kMicrosecondsInHours;
}

double Time::toMicroSecondsF() const {
  return static_cast<double>(Microseconds_);
}

double Time::toMilliSecondsF() const {
  return Microseconds_ / static_cast<double>(kMicrosecondsInMilliseconds);
}

double Time::toSecondsF() const {
  return Microseconds_ / static_cast<double>(kMicrosecondsInSeconds);
}

double Time::toMinutesF() const {
  return Microseconds_ / static_cast<double>(kMicrosecondsInMinutes);
}

double Time::toHoursF() const {
  return Microseconds_ / static_cast<double>(kMicrosecondsInHours);
}

Time::Time(long long microseconds) : Microseconds_(microseconds) {
}

Timer::Timer() : start_(std::chrono::steady_clock::now()) {
}

Time Timer::get() const {
  using namespace std::chrono;
  auto elapsed = duration_cast<microseconds>(steady_clock::now() - start_);
  return Time::MicroSeconds(elapsed.count());
}

void Timer::restart() {
  start_ = std::chrono::steady_clock::now();
}

} // namespace Library
} // namespace QApp
