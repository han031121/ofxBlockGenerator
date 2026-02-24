#include "blockGenerator.h"

void blockData::printHeightData() {
    for(int i = 0; i < max_r; i++) {
        for(int j = 0; j < max_c; j++) {
            if(height_data[i][j] == 0)
                std::cout << "." << " ";
            else
                std::cout << height_data[i][j] << " ";
        }
        std::cout << "\n";
    }
}

void blockData::printStatus() {
    std::cout << "block_count : " << block_count << "\n";
    std::cout << "size(r, c, h) : " << size_r << " / " << size_c << " / " << size_h << "\n";
    std::cout << "border(r, c) : " << smallest_r << "~" << biggest_r << " / " << smallest_c << "~" << biggest_c << "\n";
}