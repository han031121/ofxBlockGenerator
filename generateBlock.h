#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <ctime>
#include <cstdlib>

#define MAX_SIZE 17

typedef std::pair<std::pair<int,int>, int> Block; //{position, height}
typedef std::vector<Block> BlockList;

class blockData {
    private:
        std::pair<int,int> block_count; //max : max_r * max_c * max_h
        int max_r; //max : MAX_SIZE / 2
        int max_c; //max : MAX_SIZE / 2
        int max_h;
        
        int created_count[MAX_SIZE][MAX_SIZE][MAX_SIZE];
        BlockList data = {};

        double setWeight(int r, int c, int h); //calculate weight of specific position

    public:
        blockData(int _bc1, int _bc2, int _max_r, int _max_c, int _max_h)
            : max_r(_max_r), max_c(_max_c), max_h(_max_h) {
                block_count = {std::min(_bc1, _bc2), std::max(_bc1, _bc2)};

                if(std::max(_bc1, _bc2) > max_r * max_c * max_h)
                    throw std::length_error("block_count is too big");
                if (_max_r > MAX_SIZE/2 || _max_c > MAX_SIZE/2)
                    throw std::out_of_range("range error");
            }

        void generateBlock(); //make new Block data
        void printData();
        const BlockList& getData() const { return data; } //get current Block data
};