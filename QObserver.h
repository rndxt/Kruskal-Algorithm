#pragma once

#include "QPorts.h"

#include <cassert>
#include <functional>
#include <list>
#include <type_traits>

namespace QApp {

namespace Library {

template<class TData>
class CObserver;

template<class TData>
class CObservable;

template<class TData>
class CObserver : protected QReceiver {
  using CData = TData;
  using CObservable = CObservable<CData>;
  using CSignature = void(CData&&);
  using CAction = std::function<CSignature>;

  friend CObservable;

public:
  template<class T>
  CObserver(T&& onNotify) : onNotify_(std::forward<T>(onNotify)) {
    assert(onNotify_);
  }

  CObserver(const CObserver&) = delete;
  CObserver(CObserver&&) noexcept = delete;
  CObserver& operator=(const CObserver&) = delete;
  CObserver& operator=(CObserver&&) noexcept = delete;
  ~CObserver() {
    unsubscribe();
  }

  void unsubscribe();
  bool isSubscribed() const {
    return Observable_ != nullptr;
  }

private:
  void action(std::any&& data) override {
    onNotify_(std::any_cast<CData>(std::move(data)));
  }

  QReceiver* address() {
    return this;
  }

  void setObservable(CObservable* observable) {
    assert(observable);
    Observable_ = observable;
  }

  CObservable* Observable_ = nullptr;
  CAction onNotify_;
};

template<class TData>
class CObservable : protected QSender {
  using CData = TData;
  using CObserver = CObserver<CData>;
  using CObserversContainer = std::list<CObserver*>;
  using CReturn = const CData&;
  using CSignature = CReturn();
  using CGetAction = std::function<CSignature>;
  using CListeners = std::list<CObserver*>;

  friend CObserver;

public:
  template<class TF>
  CObservable(TF&& Data) : Data_(std::forward<TF>(Data)) {
    assert(Data_);
  }

  CObservable(const CObservable&) = delete;
  CObservable(CObservable&&) noexcept = delete;
  CObservable& operator=(const CObservable&) = delete;
  CObservable& operator=(CObservable&&) noexcept = delete;
  ~CObservable() {
    unsubscribeAll();
  }

  void notify() const {
    for (CObserver* obs : Listeners_)
      QSender::send(obs->address(), Data_());
  }

  void subscribe(CObserver* obs) {
    assert(obs);
    if (obs->isSubscribed())
      obs->unsubscribe();
    Listeners_.push_back(obs);
    obs->setObservable(this);
    QSender::send(obs->address(), Data_());
  }

  void unsubscribeAll() {
    while (!Listeners_.empty())
      Listeners_.front()->unsubscribe();
  }

private:
  void detach_(CObserver* obs) {
    assert(obs);
    Listeners_.remove(obs);
  }

  CGetAction Data_;
  CListeners Listeners_;
};

template<class TData>
void CObserver<TData>::unsubscribe() {
  if (!isSubscribed())
    return;
  Observable_->detach_(this);
  Observable_ = nullptr;
}

template<>
class CObserver<void> : protected QReceiver {
  using CData = void;
  using CObservable = CObservable<CData>;
  using CSignature = void();
  using CAction = std::function<CSignature>;

  friend CObservable;

public:
  template<class T>
  CObserver(T&& onNotify) : onNotify_(std::forward<T>(onNotify)) {
    assert(onNotify_);
  }

  CObserver(const CObserver&) = delete;
  CObserver(CObserver&&) noexcept = delete;
  CObserver& operator=(const CObserver&) = delete;
  CObserver& operator=(CObserver&&) noexcept = delete;
  ~CObserver() {
    unsubscribe();
  }

  void unsubscribe();

  bool isSubscribed() const {
    return Observable_ != nullptr;
  }

private:
  void action(std::any&&) override {
    onNotify_();
  }

  QReceiver* address() {
    return this;
  }

  void setObservable(CObservable* observable) {
    assert(observable);
    Observable_ = observable;
  }

  CObservable* Observable_ = nullptr;
  CAction onNotify_;
};

template<>
class CObservable<void> : protected QSender {
  using CData = void;
  using CObserver = CObserver<CData>;
  using CObserversContainer = std::list<CObserver*>;
  using CListeners = std::list<CObserver*>;

  friend CObserver;

public:
  CObservable() = default;
  CObservable(const CObservable&) = delete;
  CObservable(CObservable&&) noexcept = delete;
  CObservable& operator=(const CObservable&) = delete;
  CObservable& operator=(CObservable&&) noexcept = delete;
  ~CObservable() {
    unsubscribeAll();
  }

  void notify() const {
    for (CObserver* obs : Listeners_)
      QSender::send(obs->address(), std::any());
  }

  void subscribe(CObserver* obs) {
    assert(obs);
    if (obs->isSubscribed())
      obs->unsubscribe();
    Listeners_.push_back(obs);
    obs->setObservable(this);
    QSender::send(obs->address(), std::any());
  }

  void unsubscribeAll() {
    while (!Listeners_.empty())
      Listeners_.front()->unsubscribe();
  }

private:
  void detach_(CObserver* obs) {
    assert(obs);
    Listeners_.remove(obs);
  }

  CListeners Listeners_;
};

inline void CObserver<void>::unsubscribe() {
  if (!isSubscribed())
    return;
  Observable_->detach_(this);
  Observable_ = nullptr;
}

template<class TData>
class CObservableMono : protected CObservable<TData> {
  using CData = TData;
  using CBase = CObservable<CData>;
  using CObserver = CObserver<CData>;

public:
  using CBase::CBase;

  using CBase::notify;

  void subscribe(CObserver* obs) {
    CBase::unsubscribeAll();
    CBase::subscribe(obs);
  }
};

namespace detail {

template<class TData>
class CStorage {
  using CData = TData;

public:
  template<class... TArgs>
  explicit CStorage(TArgs&&... args) : Data_(std::forward<TArgs>(args)...) {
  }

protected:
  template<class... TArgs>
  void set(TArgs&&... args) {
    Data_ = CData(std::forward<TArgs>(args)...);
  }

  CData Data_{};
};

template<class TData, template<class T1> class TObservable>
class CObservableDataImpl : protected CStorage<TData>,
                            public TObservable<TData> {
  using CStorageBase = CStorage<TData>;
  using CObservableBase = TObservable<TData>;

public:
  template<class... TArgs>
  explicit CObservableDataImpl(TArgs&&... args)
      : CStorageBase(std::forward<TArgs>(args)...),
        CObservableBase(
            [&Data = CStorageBase::Data_]() -> const TData& { return Data; }) {
  }

  template<class... TArgs>
  void set(TArgs&&... args) {
    CStorageBase::set(std::forward<TArgs>(args)...);
    CObservableBase::notify();
  }
};
} // namespace detail

template<class TData>
using CObservableData = detail::CObservableDataImpl<TData, CObservable>;

template<class TData>
using CObservableDataMono = detail::CObservableDataImpl<TData, CObservableMono>;

} // namespace Library
} // namespace QApp
