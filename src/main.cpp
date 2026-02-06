#include "blockGenerator.h"

int main() {
    int i1, i2, i3, i4, i5, i6, i7; //block_count_1, block_count_2, max_r, max_c, max_h, density, deduplication 
    int tc;

    std::cout << "block count range : ";
    std::cin >> i1 >> i2;
    std::cout << "max size (r,c,h) : ";
    std::cin >> i3 >> i4 >> i5;
    std::cout << "density variable : ";
    std::cin >> i6;
    std::cout << "deduplication variable : ";
    std::cin >> i7;

    blockData b(i1, i2, i3, i4, i5, (double)i6, (double)i7);

    std::cout << "testcase count : ";
    std::cin >> tc;
    std::cin.get();

    for(int i=1; i<=tc; i++) {
        std::cout << "\n----- case " << i << " -----\n";
        
        b.generateBlock();
        
        b.printStatus();
        b.printHeightData();
    }

    std::cout << "press any key";
    std::cin.get();
    return 0;
}