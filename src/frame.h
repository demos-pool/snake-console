#ifndef FRAME
#define FRAME
#include "snake.h"

class Frame {
public:
    int width;
    int height;
    pair<int, int> food;
    vector<pair<int, int>> obstacles;

    Frame(int width = 12, int height = 12);
    bool ifTouchBorder(pair<int, int>);
    pair<int, int> produceFood(vector<pair<int, int> > placeholders);
    // vector<vector<string>> getNodes();
    vector<pair<int, int>> genObstacles(); 
    vector<pair<int, int>> getNodes();
    bool ifHasFood();
};
#endif
