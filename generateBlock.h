#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <random>

#define MAX_SIZE 21
#define MID 10

typedef std::tuple<int,int,int> Tuple;
typedef std::pair<std::pair<int,int>, int> Block; //{position, height}
typedef std::vector<Block> BlockList;

using std::get;

std::random_device rd;
std::mt19937 mt(rd());

class blockData {
    private:
        std::pair<int,int> block_count_pair; //max : max_r * max_c * max_h
        int block_count; //current block_count : randomly decided in block_count_pair
        int max_r; //max : MAX_SIZE / 2
        int max_c; //max : MAX_SIZE / 2
        int max_h; //max : MAX_SIZE - 1
        
        bool tempData[MAX_SIZE][MAX_SIZE][MAX_SIZE];
        int created_count[MAX_SIZE][MAX_SIZE][MAX_SIZE];
        BlockList data = {};

        bool checkCreatable(int r, int c, int h); //check invisibility and max size limit
        double setWeight(int r, int c, int h); //calculate weight of specific position
        void convertBlockData(); //create blockData based on tempData

    public:
        blockData(int _bc1, int _bc2, int _max_r, int _max_c, int _max_h)
            : max_r(_max_r), max_c(_max_c), max_h(_max_h) {
                block_count_pair = {std::min(_bc1, _bc2), std::max(_bc1, _bc2)};
                
                if(std::max(_bc1, _bc2) > max_r * max_c * max_h)
                    throw std::length_error("block_count is too big");
                if (_max_r > MAX_SIZE/2 || _max_c > MAX_SIZE/2 || _max_h > MAX_SIZE-1)
                    throw std::length_error("max size is too big");
            }

        void generateBlock(); //make new Block data
        void printData();
        const BlockList& getData() const { return data; } //get current Block data
};