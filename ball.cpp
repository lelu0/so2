#include "ball.h"

Ball::Ball(int id)
{
    this->id = id;
    changeDirection();
    this->currentX = 8;
    this->currentY = 8;
}

Ball::~Ball()
{
}

void Ball::changeDirection()
{
    this->direction = rand() % 7 + 0;
}

bool Ball::toUpdate()
{
    return currentX != lastX || currentY != lastY;
}
bool Ball::cordsValid(int y, int x)
{
    return !(x <= 1 || x >= 15 || y <= 0 || y >= 16);
}

void Ball::updateBall()
{
    if (!cordsValid(currentY, currentX))
        changeDirection();
    int tmpX = currentX;
    int tmpY = currentY;
    while (true)
    {
        switch (direction)
        {
        case 0:
            tmpY--;
            break;
        case 1:
            tmpX++;
            tmpY--;
            break;
        case 2:
            tmpX++;
            break;
        case 3:
            tmpX++;
            tmpY++;
            break;
        case 4:
            tmpY++;
            break;
        case 5:
            tmpX--;
            tmpY++;
            break;
        case 6:
            tmpX--;
            break;
        case 7:
            tmpY--;
            tmpX--;
            break;
        }
        if (cordsValid(tmpY, tmpX))
            break;
        else{
            changeDirection();
            tmpX = currentX;
            tmpY = currentY;
        }
            
    }
    lastX = currentX;
    lastY = currentY;
    currentX = tmpX;
    currentY = tmpY;
}
