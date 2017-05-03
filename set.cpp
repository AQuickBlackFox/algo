#include <iostream>
#include <cassert>

#define NUM_ELEMENTS 16

template<typename T>
class Set {
private:
  T **Ptr;
  unsigned NumElements;
  unsigned UsedElements;
public:
  Set() : NumElements(NUM_ELEMENTS), UsedElements(0) {
    Ptr = new T*[NumElements];
    for (unsigned i = 0; i < NumElements;i++) {
      Ptr[i] = new T;
    }
  }
  ~Set() {
    for (unsigned i = 0; i < NumElements; i++) {
      delete Ptr[i];
    }
    delete Ptr;
  }
  void Append(T val) {
    if (UsedElements < NumElements) {
      *Ptr[UsedElements] = val;
      UsedElements++;
    }
  }

  void Print() {
    for (unsigned i = 0; i < UsedElements; i++) {
      std::cout << *Ptr[i] << std::endl;
    }
  }
};

int main() {
  Set<float> s;
  s.Append(10);
  s.Append(11);
  s.Append(12);
  s.Print();
  std::cout << std::endl;
}
