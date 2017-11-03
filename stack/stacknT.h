#pragma once

#include "node.h"
#include <atomic>
#include <mutex>

std::mutex cout_mutex;

namespace algo {

template<typename T>
class stacknT {
private:
  std::timed_mutex stackTimedMutex;
  std::atomic<node<T>*> head;
  std::atomic<node<T>*> tail;
  size_t length;
public:
  stacknT() : head(new node<T>(T(0))), length(0) { tail.store(head.load()); }
  ~stacknT() {}

  T& top();
  const T& top() const;

  bool empty() const;
  size_t size() const;

  void push(T value);
  void pop();
};

template<typename T>
T& stacknT<T>::top() {
  return tail.load()->value;
}

template<typename T>
const T& stacknT<T>::top() const {
  return tail.load()->value;
}

template<typename T>
bool stacknT<T>::empty() const {
  return (head.load() == tail.load());
}

template<typename T>
size_t stacknT<T>::size() const {
  return length;
}

template<typename T>
void stacknT<T>::push(T value) {
  using milliSeconds = std::chrono::milliseconds;
  node<T>* tmp = new node<T>(value, tail, NULL);
  {
    if(stackTimedMutex.try_lock_for(milliSeconds(100))) {
      tail.load()->after = tmp;
      tail.store(tail.load()->after);
      length++;
      stackTimedMutex.unlock();
    }else{
      std::lock_guard<std::mutex> lg(cout_mutex);
      std::cerr<<"Couldn't push in 100 milli seconds, returning.."<<std::endl;
    }
  }
}

template<typename T>
void stacknT<T>::pop() {
  using milliSeconds = std::chrono::milliseconds;
  node<T>* tmp = NULL;
  {
    if(stackTimedMutex.try_lock_for(milliSeconds(100))) {
      std::lock_guard<std::timed_mutex> lg(stackTimedMutex, std::adopt_lock_t());
      tmp = tail.load();
      tail.store(tail.load()->before);
      length--;
      // God! I forgot this!
      //stackTimedMutex.unlock();
    }else{
      std::lock_guard<std::mutex> lg(cout_mutex);
      std::cerr<<"Couldn't pop in 100 milli seconds, returning.."<<std::endl;
    }
  }
  delete tmp;
}

}
