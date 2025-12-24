#include "generateBlock.h"

int main() {
    int i1, i2, i3, i4;
    std::cin >> i1 >> i2 >> i3 >> i4;

    blockData b(i1, i2, i3, i4);
    b.generateBlock();
    b.printResult();
    return 0;
}