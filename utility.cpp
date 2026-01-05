#include "blockGenerator.h"

void blockData::printData() {
    int tmp[MAX_SIZE][MAX_SIZE] = {0};

    for(Block b : data)
        tmp[b.first.first][b.first.second] = b.second;

    for(int i = MID - max_r; i <= MID + max_r; i++) {
        for(int j = MID - max_c; j <= MID + max_c; j++)
            std::cout << tmp[i][j] << " ";
        std::cout << "\n";
    }
}

void blockData::printStatus() {
    std::cout << "block_count : " << block_count << "\n";
    std::cout << "size(r, c, h) : " << size_r << " / " << size_c << " / " << size_h << "\n";
    std::cout << "border(r, c) : " << smallest_r << "~" << biggest_r << " / " << smallest_c << "~" << biggest_c << "\n";

}