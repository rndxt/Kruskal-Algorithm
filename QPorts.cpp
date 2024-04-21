#include "QPorts.h"

#include <QApplication>

namespace QApp {
namespace Library {

namespace detail {

namespace {
bool isNumberCorrect(int number) {
  return number >= QEvent::User && number <= QEvent::MaxUser;
}
} // namespace
// namespace

QEvent::Type Message::type() {
  static int message_type = registerEventType();
  assert(isNumberCorrect(message_type));
  return QEvent::Type(message_type);
}

Message::Message(QObject* address, const std::any& data)
    : QEvent(type()), address_(address), data_(data) {
}

Message::Message(QObject* address, std::any&& data)
    : QEvent(type()), address_(address), data_(std::move(data)) {
}

std::any&& Message::extract() {
  return std::move(data_);
}

bool Message::isAlive() const {
  return address_;
}

QObject* Message::receiver() const {
  return address_;
}
} // namespace detail

void QSender::send(QObject* receiver, std::any data) const {
  QCoreApplication::postEvent(QCoreApplication::instance(),
                              new Message(receiver, std::move(data)));
}

bool QReceiver::event(QEvent* event) {
  if (event->type() == Message::type()) {
    Message* msg = static_cast<Message*>(event);
    action(msg->extract());
    return k_is_processed;
  }
  return QObject::event(event);
}

} // namespace Library
} // namespace QApp
