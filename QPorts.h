#pragma once

#include <QEvent>
#include <QPointer>

#include <any>

namespace QApp {
namespace Library {

namespace detail {

class Message : public QEvent {
public:
  static QEvent::Type type();

  Message(QObject* address, const std::any& data);
  Message(QObject* address, std::any&& data);

  std::any&& extract();

  bool isAlive() const;
  QObject* receiver() const;

private:
  QPointer<QObject> address_;
  std::any data_;
};

} // namespace detail

class QSender : public QObject {
  Q_OBJECT
  using Message = detail::Message;

public:
  void send(QObject* receiver, std::any data) const;

private:
};

class QReceiver : public QObject {
  Q_OBJECT
  using Message = detail::Message;

public:
  bool event(QEvent* event) override;

protected:
  virtual void action(std::any&& data) = 0;

private:
  static constexpr bool k_is_processed = true;
};

} // namespace Library
} // namespace QApp
