#include <iostream>
#include <cassert>

#define NUM_ELEMENTS 16

template<typename T>
class Set {
private:
  T **Ptr;
  unsigned NumElements;
  unsigned UsedElements;

  T __pop__(T val) {
    T tmp;
    unsigned i = 0;
    while (Ptr[i] != nullptr && i < UsedElements) {
      if (*Ptr[i] == val) {
        tmp = *Ptr[i];
        delete Ptr[i];
        UsedElements--;
        for (; i < UsedElements; i++) {
          Ptr[i] = Ptr[i + 1];
        }
        break;
      }
      i++;
    }
    return tmp;
  }
public:
  Set() : NumElements(NUM_ELEMENTS), UsedElements(0) {
    Ptr = new T*[NumElements];
    for (unsigned i = 0; i < NumElements; i++) {
      Ptr[i] = nullptr;
    }
  }
  Set(unsigned size) : NumElements(size) {
    Ptr = new T*[NumElements];
    for (unsigned i = 0; i < NumElements; i++) {
      Ptr[i] = new T;
    }
  }
  ~Set() {
    for (unsigned i = 0; i < UsedElements; i++) {
      delete Ptr[i];
    }
    delete Ptr;
  }
  void Add(T val) {
    if (UsedElements < NumElements) {
      T* tmp = new T;
      *tmp = val;
      Ptr[UsedElements] = tmp;
      UsedElements++;
    }
  }
  void Remove(T val) {
    __pop__(val);
  }
  T Pop(T val) {
    return __pop__(val);
  }
  unsigned Capacity() {
    return NumElements;
  }
  
  typedef T(*UnaryOp)(T);

  void Map(setFunc func ) {
    std::cout << func(20) << std::endl;
  }

  void Print() {
    for (unsigned i = 0; i < UsedElements; i++) {
      std::cout << *Ptr[i] <<" ";
    }
    std::cout << std::endl;
  }
};

template<typename T>
T inc(T val) {
  val = val + 1;
  return val;
}

int main() {
  Set<float> s;
  s.Add(10);
  s.Add(11);
  s.Add(12);
  s.Add(13);
  s.Add(16);
  s.Print();
  s.Remove(13);
  s.Remove(11);
  s.Print();
  s.Map(Set<float>::UnaryOp(inc));
  std::cout << std::endl;
}
