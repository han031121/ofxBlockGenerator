#include "blockGenerator.h"

bool blockData::checkCreatable(int r, int c, int h) {
    if(size_r >= max_r && (r > biggest_r || r < smallest_r))
        return false;
    if(size_c >= max_c && (c > biggest_c || c < smallest_c))
        return false;
    if(size_h >= max_h && h > biggest_h)
        return false;

    if(h > 1 && tempData[r][c][h-1] == false)
        return false;
        
    return true;
}

double blockData::setWeight(int r, int c, int h) {
    double mul = 1.0;

    if(!checkCreatable(r,c,h))
        return 0.0;

    //TODO : Density implement

    //TODO : Duplication implement

    return DEFAULT_WEIGHT * mul;
}