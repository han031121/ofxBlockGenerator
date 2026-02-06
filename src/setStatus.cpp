#include "blockGenerator.h"

void blockData::measureSize(Tuple added) {
    biggest_r = std::max(get<0>(added), biggest_r);
    biggest_c = std::max(get<1>(added), biggest_c);
    biggest_h = std::max(get<2>(added), biggest_h);
    smallest_r = std::min(get<0>(added), smallest_r);
    smallest_c = std::min(get<1>(added), smallest_c);

    size_r = biggest_r - smallest_r + 1;
    size_c = biggest_c - smallest_c + 1;
    size_h = biggest_h;
}

void blockData::init() {
    data = {};
    std::fill(&cubic_data[0][0][0], &cubic_data[0][0][0] + MAX_SIZE*MAX_SIZE*MAX_SIZE, 0);
    std::fill(&height_data[0][0], &height_data[0][0] + MAX_SIZE*MAX_SIZE, 0);

    biggest_r = 0;
    biggest_c = 0;
    biggest_h = 0;
    smallest_r = MAX_SIZE;
    smallest_c = MAX_SIZE;
    size_r = 0;
    size_c = 0;
    size_h = 0;
}