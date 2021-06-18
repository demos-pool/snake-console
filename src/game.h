#ifndef GAME
#define GAME
#include "frame.h"
#include "snake.h"

enum GameStatus {
    INIT,
    STARTING,
    PAUSING,
    OVER,
};

struct Times {
    static int walk;
};

class Game {
public:
    Frame frame;
    Snake snake;
    GameStatus status;

    Game();

    void init();
    void go();
    void draw();
    void restart();
    void start();
    void pause();
    void over();
    bool snakeMove();
    vector<vector<string> > getNodes(vector<pair<int, int> >);
    bool ifDie();
    vector<vector<string> > getObstacleNodes();
};
#endif