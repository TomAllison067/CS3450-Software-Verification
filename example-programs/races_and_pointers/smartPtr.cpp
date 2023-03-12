#include <iostream>

using namespace std;

template <typename T> class SmartPtr
{
private:
  T* pData;

public:
  SmartPtr(T* pValue) : pData(pValue){}

  T& operator* ()
  {
    return *pData;
  }

  T* operator->()
  {
    return pData;
  }
};

int main() {
  SmartPtr ptr(new int(42));
  cout << *ptr << endl;
}