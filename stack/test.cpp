#include <iostream>
#include "stack.h"

int main(){
  algo::stack1T<float> s;
  s.push(10);
  s.push(11);
  std::cout<<s.size()<<std::endl;
  std::cout<<s.empty()<<std::endl;
  std::cout<<s.top()<<std::endl;
  s.pop();
  std::cout<<s.top()<<std::endl;
  s.pop();
  std::cout<<s.top()<<std::endl;
  std::cout<<s.size()<<std::endl;
  std::cout<<s.empty()<<std::endl;
}
