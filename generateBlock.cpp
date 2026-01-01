#include "blockGenerator.h"

std::random_device rd;
std::mt19937 mt(rd());

bool cmp(std::pair<Tuple,double> a, std::pair<Tuple,double> b) {
    return a.second < b.second;
}

void blockData::generateBlock() {
    init();
    
    int dr[4] = {-1,0,1,0};
    int dc[4] = {0,1,0,-1};
    int cur_count = 0;
    std::uniform_int_distribution<int> dis(block_count_pair.first, block_count_pair.second);
    block_count = dis(mt);

    tempData[MID][MID][1] = 1;
    std::vector<Tuple> created;
    cur_count++;

    created.push_back(std::make_tuple(MID,MID,1));

    while(cur_count < block_count) {
        double weight_sum = 0;
        std::vector<Tuple> adj;
        bool selected[MAX_SIZE][MAX_SIZE][MAX_SIZE] = {0};
        std::vector<std::pair<Tuple,double>> weight_list;

        for(Tuple cur : created) {

            for(int i=0; i<5; i++) {
                Tuple next;
                if(i < 4)
                    next = std::make_tuple(get<0>(cur) + dr[i], get<1>(cur) + dc[i], get<2>(cur));
                else if(i == 4)
                    next = std::make_tuple(get<0>(cur), get<1>(cur), get<2>(cur) + 1);

                if(tempData[get<0>(next)][get<1>(next)][get<2>(next)])
                    continue;
                if(selected[get<0>(next)][get<1>(next)][get<2>(next)])
                    continue;
                adj.push_back(next);
                selected[get<0>(next)][get<1>(next)][get<2>(next)] = 1;
            }
        }

        for(Tuple t : adj) {
            //std::cout << "adj : " << get<0>(t) << " " << get<1>(t) << " " << get<2>(t) << "\n";
            weight_sum += setWeight(get<0>(t), get<1>(t), get<2>(t));
            weight_list.push_back({t, weight_sum});
        }

        std::uniform_real_distribution<double> dis_weight(0, weight_sum);
        sort(weight_list.begin(), weight_list.end(), cmp);
        double cur_weight = dis_weight(mt);

        for(std::pair<Tuple,double> p : weight_list) {
            if(cur_weight > p.second)
                continue;
            Tuple cur = p.first;
            created.push_back(cur);
            tempData[get<0>(cur)][get<1>(cur)][get<2>(cur)] = 1;
            cur_count++;
            //std::cout << "selected : " << get<0>(cur) << " " << get<1>(cur) << " " << get<2>(cur) << "\n";
            break;
        }
    }

    convertBlockData();
}

void blockData::init() {
    data = {};
    std::fill(&tempData[0][0][0], &tempData[0][0][0] + MAX_SIZE*MAX_SIZE*MAX_SIZE, 0);
}

void blockData::convertBlockData() {
    for(int i = MID - max_r; i <= MID + max_r; i++) {
        for(int j = MID - max_c; j <= MID + max_c; j++) {
            for(int k = max_h; k >= 1; k--) {
                if(tempData[i][j][k]) {
                    data.push_back({{i,j}, k});
                    break;
                }
            }
        }
    }
}