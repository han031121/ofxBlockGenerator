#include "generateBlock.h"

void blockData::generateBlock() {

}

void blockData::printData() {
    int tmp[MAX_SIZE][MAX_SIZE] = {0};
    int mid = MAX_SIZE / 2;

    for(Block b : data)
        tmp[b.first.first][b.first.second] = b.second;

    for(int i = mid - max_r; i <= mid + max_r; i++) {
        for(int j = mid - max_c; j <= mid + max_c; j++)
            std::cout << tmp[i][j] << " ";
        std::cout << "\n";
    }
}

int main() {
    int i1, i2, i3, i4, i5; //block_count_1, block_count_2, max_r, max_c, max_h
    std::cin >> i1 >> i2 >> i3 >> i4 >> i5;

    blockData b(i1, i2, i3, i4, i5);
    b.generateBlock();
    b.printData();
    return 0;
}