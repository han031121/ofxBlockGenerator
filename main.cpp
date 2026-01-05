#include "blockGenerator.h"

int main() {
    int i1, i2, i3, i4, i5; //block_count_1, block_count_2, max_r, max_c, max_h
    std::cin >> i1 >> i2 >> i3 >> i4 >> i5;

    blockData b(i1, i2, i3, i4, i5);

    int tc;
    std::cout << "testcase count : ";
    std::cin >> tc;
    std::cin.get();

    for(int i=1; i<=tc; i++) {
        std::cout << "\n----- case " << i << " -----\n";
        
        b.generateBlock();

        b.printStatus();
        b.printData();
    }

    std::cout << "press any key";
    std::cin.get();
    return 0;
}