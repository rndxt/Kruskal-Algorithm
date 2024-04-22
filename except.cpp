#include "Except.h"

#include <QDebug>

#include <exception>

namespace QApp {
namespace Except {
void react() noexcept {
  try {
    throw;
  } catch (std::exception& e) {
    qDebug() << "Exception: " << e.what();
  } catch (...) {
    qDebug() << "Enknown Exception!";
  }
}
} // namespace Except
} // namespace QApp
