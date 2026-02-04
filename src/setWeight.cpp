#include "blockGenerator.h"

bool blockData::checkCreatable(int r, int c, int h) {
    if(r >= max_r || r < 0)
        return false;
    if(c >= max_c || c < 0)
        return false;
    if(h > max_h)
        return false;
    
    if(h > 1 && cubic_data[r][c][h-1] == false)
        return false;

    if(!checkObscure(r, c, h))
        return false;
    
    return true;
}

bool blockData::checkObscure(int r, int c, int h) {
    //TODO : implement this fucking function
    int check_r, check_c, check_h;
    //std::cout << "checkObscure - (r,c,h) = " << "(" << r << ", " << c << ", " << h << ") ";

    if(r-1 >= 0 && c+1 < max_c) {
        check_r = r-1;
        check_c = c;
        check_h = height_data[check_r][check_c];

        if(h > check_h && (height_data[r-1][c+1] > check_h || height_data[r][c+1] > check_h))
            return false;
    }
    if(r-1 >= 0 && c-1 >= 0) {
        check_r = r-1;
        check_c = c-1;
        check_h = height_data[check_r][check_c];

        if(h > check_h && (height_data[r-1][c] > check_h || height_data[r][c-1] > check_h))
            return false;
    }
    if(r+1 < max_r && c-1 >= 0) {
        check_r = r;
        check_c = c-1;
        check_h = height_data[check_r][check_c];

        if(h > check_h && (height_data[r+1][c] > check_h || height_data[r+1][c-1] > check_h))
            return false;
    }

    return true;
}

double blockData::getWeight(int r, int c, int h) {
    if(!checkCreatable(r,c,h))
        return 0;
    //std::cout << "DEBUG - calc weight : " << r << " " << c << " " << h <<"\n";

    double mul = 1.0;
    double possibility = weight_field[r][c][h];

    if(!checkCreatable(r,c,h))
        return 0.0;

    mul *= exp(-DEDUP_COEFF * created_count[r][c][h] * dedup_var);

    possibility *= mul;
    return possibility;
}

void blockData::setWeight() {
    for(int r = 0; r < max_r; r++) {
        for(int c = 0; c < max_c; c++) {
            double dist = sqrt(r*r + c*c);
            for(int h=0; h <= max_h; h++)
                weight_field[r][c][h] = DEFAULT_WEIGHT * exp(-DENSITY_COEFF * dist * density_var);
        }
    }
}