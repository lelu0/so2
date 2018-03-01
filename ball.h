#ifndef BALL_H
#define BALL_H
#include <stdlib.h>

class Ball{
    private:
        int direction;
        void changeDirection();
    public:
        Ball(int id);
        ~Ball();
        int id;
        int currentX,currentY;
        int lastX, lastY;     
        bool toUpdate();
        void updateBall();
        bool cordsValid(int y, int x);
    
};
#endif