#ifndef SHARED_H
#define SHARED_H
#include "ball.h"
#include <vector>
class Shared
{
  public:
    Shared();
    ~Shared();
    int ballCounter;
    std::vector<Ball*> balls;
    void AddBall();    
};
#endif