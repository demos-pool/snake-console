#include <iostream>
#include <map>
#include <thread>
#include <chrono>
#include "game.h"
#include "keyboard.h"
#include "const.h"

int Times::walk = 500;

int game_width = 12;
int game_height = 12;

Game::Game() {
    init();
}

/**
 * 绘制画面
 */
void Game::draw() {
    vector<vector<string>> map(game_height + 2, vector<string>(game_width + 2, characters::floor));

    for (auto &i : frame.obstacles) {
        map[i.second][i.first] = characters::wall;
    }

    map[frame.food.second][frame.food.first] = characters::food;

    for (int i = snake.body.size() - 1; i >= 1; i--) {
        pair<int, int> snakeNode = snake.body[i];
        map[snakeNode.second][snakeNode.first] = characters::snakeBody;
    }
    pair<int, int> snakeHeader = snake.body[0];
    map[snakeHeader.second][snakeHeader.first] = characters::snakeHeader;

    if (status == OVER) {
        // string msg = "失败（按R重新开始）";
        // map[0][0] = "失败(重新kai)";
        map[game_height / 2]     = {"⬛  失败（按R 重新开始）  ⬛"};
        // map[game_height / 2 + 1] = {"⬛      按R 重新开始     ⬛"};
        // map[game_height / 2 + 1] = {""};
    }

    for (auto &row : map) {
        for (auto &node : row) {
            cout << node;
        }
        cout << endl;
    }
}

void Game::init() {
    frame = {game_width, game_height};
    snake = {game_width, game_height, {1, 1}};
    
    frame.produceFood(snake.body);
}

void Game::go() {
    status = STARTING;

    map<char, Direction> keyMap = {
        {'w', UP},
        {'s', DOWN},
        {'a', LEFT},
        {'d', RIGHT}
    };

    while (true) {
        // if (status == OVER) {
        //     return;
        // }
        while (!kbhit()) {
            if (status == STARTING) {
                snakeMove();
            }
        }

        char key = cin.get();
        cout << key << endl;
        switch (key) {
            case 'w':
            case 's':
            case 'a':
            case 'd':
                {
                    Direction d = keyMap[key];
                    snake.turn(d);
                    snakeMove();
                }
                break;
            case 'r':
                restart();
                break;
            case ' ':
                pause();
                break;
        }
    }
}


/**
 * 判断是否死了
 */
bool Game::ifDie() {
    vector<pair<int, int>> obstacles = frame.obstacles;
    obstacles.insert(obstacles.end(), snake.body.begin() + 1, snake.body.end());

    return find(obstacles.begin(), obstacles.end(), snake.body[0]) != obstacles.end();
}

bool Game::snakeMove() {
    system("clear");

    snake.go();

    if (ifDie()) {
        status = OVER;
        draw();
        return false;
    }

    // 吃吃吃
    bool isEat = snake.eatFood(frame.food);
    if (isEat) {
        frame.produceFood(snake.body);
    }

    draw();
    this_thread::sleep_for(chrono::milliseconds(Times::walk));
}

void Game::start() {
    status = STARTING;
}

void Game::pause() {
    status = status == STARTING ? PAUSING : STARTING;
}

void Game::restart() {
    init();
    start();
}

