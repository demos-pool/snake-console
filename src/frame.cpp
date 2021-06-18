#include "frame.h"
#include "const.h"

Frame::Frame(int width, int height): width(width), height(height) {
    genObstacles();
}

/**
 * 判断node是否触碰到边界
 * @param {pair<int, int>} node
 * @return {bool}
 */
bool Frame::ifTouchBorder(pair<int, int> node) {
    int x = node.first;
    int y = node.second;
    return x <= 0 || x > width || y <= 0 || y > height;
}

bool Frame::ifHasFood() {
    return food != pair<int, int>{0, 0};
}

/**
 * 随机生产食物
 * @param {vector<pair<int, int>>} placeholders 障碍物
 * @return {pair<int, int>} 食物位置
 */
pair<int, int> Frame::produceFood(vector<pair<int, int> > placeholders) {
    if (ifHasFood()) return food;
    vector<pair<int, int> > positions;
    // todo optimize
    for (int x = 1; x <= width; x++) {
        for (int y = 1; y <= height; y++) {
            pair<int, int> position = {x, y};
            auto it = find(placeholders.begin(), placeholders.end(), position);
            if (it == placeholders.end()) {
                positions.push_back(position);
            }
        }
    }
    int len = positions.size();
    food = positions[rand() % len];
    return food;
}

/**
 * 获取节点
 */
vector<pair<int, int>> Frame::getNodes() {
    
}

/**
 * 生成障碍
 */
vector<pair<int, int>> Frame::genObstacles() {
    vector<pair<int, int>> obs;
    for (int x = 0; x < width + 2; x++) {
        obs.push_back({0, x});
        obs.push_back({height + 1, x});
    }
    for (int y = 1; y <= height; y++) {
        obs.push_back({y, 0});
        obs.push_back({y, width + 1});
    }
    obstacles = obs;
    return obs;
}

// vector<vector<string> > Frame::getNodes() {
//     vector<vector<string> > nodes(height + 2, vector<string>(width + 2, characters::floor));
//     for (int x = 0; x < width + 2; x++) {
//         nodes[0][x] = characters::wall;
//         nodes[height + 1][x] = characters::wall;
//     }
//     for (int y = 1; y <= height; y++) {
//         nodes[y][0] = characters::wall;
//         nodes[y][width + 1] = characters::wall;
//     }
//     nodes[food.second][food.first] = characters::food;
//     return nodes;
// }