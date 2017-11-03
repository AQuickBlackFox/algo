#pragma once

template<typename T>
class node {
public:
    node *before;
    T value;
    node *after;
    node() :
      before(NULL), after(NULL) {}
    node(T value) :
      value(value), before(NULL), after(NULL) {}
    node(T value, node* before) :
      value(value), before(before), after(NULL) {}
    node(T value, node* before, node* after) :
      value(value), before(before), after(after) {}
};
