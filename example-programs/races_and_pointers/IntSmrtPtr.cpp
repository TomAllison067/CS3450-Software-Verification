#include <iostream>

// IntSmrtPointer.cpp
using namespace std;

class IntSmartPtr
{
private:
  int* pData;

public:
  IntSmartPtr(int* pValue) : pData(pValue){}

  int& operator* ()
  {
    return *pData;
  }

  int* operator->()
  {
    return pData;
  }

  ~IntSmartPtr() {
    delete pData;
  }
};

int main() {
  IntSmartPtr ptr(new int(42));
  cout << *ptr << endl;
}
