#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <ctime>
#include <cstdlib>

typedef std::pair<std::pair<int,int>, int> block;
typedef std::vector<block> block_list;

class blockData {
    private:
        int block_count;
        int max_r;
        int max_c;
        int max_h;

        double weight[100][100][100] = {0};

        void setWeight();
        double getWeight(int r, int c, int h);

    public:
        blockData(int _block_count, int _max_r, int _max_c, int _max_h);

        block_list generateBlock();
        void printResult();
};