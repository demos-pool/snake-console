#ifndef SNAKE
#define SNAKE
#include <vector>

using namespace std;

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Snake {
public:
    static vector<Direction> ver;
    static vector<Direction> hor;

    // pair<int, int> position;
    int width;
    int height;
    vector<pair<int, int> > body;
    Direction currentDirection;

    Snake(int width = 12, int height = 12, pair<int, int> position = {1, 1});

    void go();
    void turn(Direction direction);
    bool ifCanTurn(Direction direction);
    bool eatFood(pair<int, int>&);
    bool ifTouchBody();
    vector<vector<string> > getNodes();
};
#endif