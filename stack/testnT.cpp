#include <iostream>
#include <thread>
#include "stacknT.h"



template<typename T>
void thread1(algo::stacknT<T>&s){
  for(int i=0;i<100;i++){
    s.push(T(i));
    {
      std::lock_guard<std::mutex> lg(cout_mutex);
      std::cout<<"Push: "<<T(i)<<std::endl;
    }
  }
}

template<typename T>
void thread2(algo::stacknT<T>&s){
  while(!s.empty()) {
    {
      std::lock_guard<std::mutex> lg(cout_mutex);
      std::cout<<"Top + Pop: "<<s.top()<<std::endl;
    }
    s.pop();
  }
}

int main(){
  algo::stacknT<float> s;
  s.push(10);
  s.push(11);
  s.push(12);
  std::thread t1(thread1<float>, std::ref(s));
  std::thread t2(thread2<float>, std::ref(s));
  t1.join();
  t2.join();
}
