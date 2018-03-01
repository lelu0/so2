#ifndef WINDOW_H
#define WINDOW_H
#include "shared.h"

class Window{
    public:
    Window();
    ~Window();
    void initWindow();
    void drawSquare();
    void reload();
    void drawBall(int y, int x);
    void clearFootprint(int y, int x);
    void updateWindow(Shared *shared);
};

#endif