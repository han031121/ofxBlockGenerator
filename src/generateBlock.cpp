#include "blockGenerator.h"

std::random_device rd;
std::mt19937 mt(rd());

void blockData::generateBlock() {
    init();
    
    int dr[2] = {0, 1};
    int dc[2] = {1, 0};
    int cur_count = 0;
    std::uniform_int_distribution<int> dis(block_count_pair.first, block_count_pair.second);
    block_count = dis(mt);

    temp_data[0][0][1] = 1;
    std::vector<Tuple> created;
    
    cur_count++;
    created.push_back(std::make_tuple(0,0,1));
    measureSize(std::make_tuple(0,0,1));

    while(cur_count < block_count) {
        double weight_sum = 0;
        std::vector<Tuple> adj;
        bool selected[MAX_SIZE][MAX_SIZE][MAX_SIZE] = {0};
        std::vector<std::pair<Tuple,double>> weight_list;

        for(Tuple cur : created) {
            for(int i=0; i<3; i++) {
                Tuple next;
                if(i < 2)
                    next = std::make_tuple(get<0>(cur) + dr[i], get<1>(cur) + dc[i], get<2>(cur));
                else if(i == 2)
                    next = std::make_tuple(get<0>(cur), get<1>(cur), get<2>(cur) + 1);

                if(temp_data[get<0>(next)][get<1>(next)][get<2>(next)])
                    continue;
                if(selected[get<0>(next)][get<1>(next)][get<2>(next)])
                    continue;
                adj.push_back(next);
                selected[get<0>(next)][get<1>(next)][get<2>(next)] = 1;
            }
        }

        for(Tuple t : adj) {
            //std::cout << "adj : " << get<0>(t) << " " << get<1>(t) << " " << get<2>(t) << "\n";
            weight_sum += getWeight(get<0>(t), get<1>(t), get<2>(t));
            weight_list.push_back({t, weight_sum});
        }

        std::uniform_real_distribution<double> dis_weight(0, weight_sum);
        double cur_weight = dis_weight(mt);

        if(weight_list.empty() || weight_sum <= EPSILON) {
            std::cout << "generateBlock - Cannot generate block anymore" << "\n";
            break;
        }

        for(std::pair<Tuple,double> p : weight_list) {
            if(cur_weight <= p.second) {
                Tuple cur = p.first;

                created.push_back(cur);
                temp_data[get<0>(cur)][get<1>(cur)][get<2>(cur)] = 1;
                created_count[get<0>(cur)][get<1>(cur)][get<2>(cur)]++;
                cur_count++;
                measureSize(cur);
                //std::cout << "generateBlock - selected : " << get<0>(cur) << " " << get<1>(cur) << " " << get<2>(cur) << "\n";
                break;
            }
        }
    }

    convertBlockData();
}

void blockData::init() {
    data = {};
    std::fill(&temp_data[0][0][0], &temp_data[0][0][0] + MAX_SIZE*MAX_SIZE*MAX_SIZE, 0);
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

void blockData::convertBlockData() {
    for(int i = 0; i < max_r; i++) {
        for(int j = 0; j < max_c; j++) {
            for(int k = max_h; k >= 1; k--) {
                if(temp_data[i][j][k]) {
                    Block tmp = {i,j,k};
                    data.push_back(tmp);
                    height_data[i][j] = k;
                    break;
                }
            }
        }
    }
}

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