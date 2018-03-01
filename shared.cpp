#include "shared.h"

Shared::Shared(){
    this->ballCounter = 0;
}
Shared::~Shared(){
}

void Shared::AddBall(){
    Ball *ball = new Ball(this->ballCounter++);
    this->balls.push_back(ball);
    
}