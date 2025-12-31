#include "generateBlock.h"

int main() {
    int i1, i2, i3, i4, i5; //block_count_1, block_count_2, max_r, max_c, max_h
    std::cin >> i1 >> i2 >> i3 >> i4 >> i5;
    std::cin.get();

    blockData b(i1, i2, i3, i4, i5);
    b.generateBlock();
    b.printData();

    std::cout << "press any key";
    std::cin.get();
    return 0;
}