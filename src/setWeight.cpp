#include "blockGenerator.h"

bool blockData::checkCreatable(int r, int c, int h) {
    if(r >= max_r || r < 0)
        return false;
    if(c >= max_c || c < 0)
        return false;
    if(h > max_h)
        return false;
    
    if(h > 1 && temp_data[r][c][h-1] == false)
        return false;

    //TODO : uncountable block rule implement
    
    
    return true;
}

double blockData::getWeight(int r, int c, int h) {
    if(!checkCreatable(r,c,h)) {
        //std::cout << "DEBUG - not creatable : " << r << " " << c << " " << h <<"\n";
        return 0;
    }

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
    std::cout << "DEBUG - set weight\n";
    for(int r = 0; r < max_r; r++) {
        for(int c = 0; c < max_c; c++) {
            double dist = sqrt(r*r + c*c);
            for(int h=0; h <= max_h; h++)
                weight_field[r][c][h] = DEFAULT_WEIGHT * exp(-DENSITY_COEFF * dist * density_var);
        }
    }
}