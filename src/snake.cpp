#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <string>
// #include <thread>
#include "./snake.h"

using namespace std;

map<Direction, pair<int, int> > dirMap = {
    {DOWN, {0, 1}},
    {UP, {0, -1}},
    {LEFT, {-1, 0}},
    {RIGHT, {1, 0}},
};

vector<Direction> Snake::ver{UP, DOWN};
vector<Direction> Snake::hor{LEFT, RIGHT};

Snake::Snake(int width, int height, pair<int, int> position): width(width), height(height) {
	currentDirection = DOWN;
    body.push_back(position);
}

/**
 * 是否可以拐弯
 * @param {Direction} driection 方向
 * @return {bool}
 */
bool Snake::ifCanTurn(Direction direction) {
	return find(Snake::ver.begin(), Snake::ver.end(), direction) == Snake::ver.end() &&
		find(Snake::ver.begin(), Snake::ver.end(), currentDirection) != Snake::ver.end() ||
		find(Snake::hor.begin(), Snake::hor.end(), direction) == Snake::hor.end() &&
		find(Snake::hor.begin(), Snake::hor.end(), currentDirection) != Snake::hor.end();
}

/**
 * 从direction方向移动一个单位
 * @param {Dirsction} direction
 */
void Snake::go() {
	int len = body.size();
	if (len > 1) {
        body.erase(body.end() - 1);
        body.insert(body.begin() + 1, body[0]);
	}

	auto vals = dirMap[currentDirection];
	body[0].first += vals.first;
	body[0].second += vals.second;
	// cout << body[0].second << "," << vals.second << endl;
}

void Snake::turn(Direction direction) {
	if (ifCanTurn(direction)) {
		currentDirection = direction;
	}
}

/**
 * 添加身体节点
 * @param {pair<int, int>} node
 * @return {vector<pair<int, int> >}
 */
bool Snake::eatFood(pair<int, int> &node) {
	if (node == body[0]) {
		int len = body.size();
		if (len > 1) {
            body.push_back({
                2 * body[len - 1].first - body[len - 2].first,
                2 * body[len - 1].second - body[len - 2].second
            });
        } else {
            auto vals = dirMap[currentDirection];
            body.push_back({
                body[0].first - vals.first,
                body[0].second - vals.second
            });
        }
		node = {0, 0};
		return true;
	}
	return false;
}

/**
 * 头是否触碰到身体
 */
bool Snake::ifTouchBody() {
	auto it = find(body.begin() + 1, body.end(), body[0]);
	return it != body.end();
}

vector<vector<string> > getNodes() {
	 
}