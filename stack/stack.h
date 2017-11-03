#pragma once

#include "node.h"

namespace algo {

template<typename T>
class stack1T {
private:
    node<T> *head;
    node<T> *tail;
    size_t length;
public:
    stack1T() : head(new node<T>(T(0))), length(0) { tail = head; }
    ~stack1T() {}
    T& top();
    const T& top() const;

    bool empty() const;
    size_t size() const;

    void push(T value);
    void pop();
};

template<typename T>
T& stack1T<T>::top() {
  return tail->value;
}

template<typename T>
const T& stack1T<T>::top() const {
  return tail->value;
}

template<typename T>
bool stack1T<T>::empty() const {
  return (head == tail);
}

template<typename T>
size_t stack1T<T>::size() const {
  return length;
}

template<typename T>
void stack1T<T>::push(T value) {
  node<T>* tmp = new node<T>(value, tail, NULL);
  tail->after = tmp;
  tail = tail->after;
  length++;
}

template<typename T>
void stack1T<T>::pop() {
  if(tail != head) {
    node<T>* tmp = tail;
    tail = tail->before;
    T val = tmp->value;
    delete tmp;
    length--;
  }
}

}
