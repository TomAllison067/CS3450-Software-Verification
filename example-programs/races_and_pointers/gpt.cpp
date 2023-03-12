#include <iostream>
#include <memory>

using namespace std;

class MyClass {
public:
    MyClass(int n) : number(n) {}
    int getNumber() { return number; }
private:
    int number;
};

int main() {
    unique_ptr<MyClass> ptr(new MyClass(42));
    int n = ptr->getNumber();
    cout << "The number is: " << n << endl;
    return 0;
}

