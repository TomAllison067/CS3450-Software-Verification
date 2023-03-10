int main() {
    // pointer to int:
    int* pi;
    // pointer to const int:
    const int* pci;

    // constraint error
    pi = pci;
    // dangerous but permitted
    pi = (int*)pci;
}