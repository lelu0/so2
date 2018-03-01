#include "window.h"
#include "shared.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
    srand(time(NULL));
    Window *window = new Window();
    window->drawSquare();
    Shared *shared = new Shared();
    shared->AddBall();
    window->updateWindow(shared);
    while(true)
    {
        usleep(50000);
        shared->balls[0]->updateBall();
        window->updateWindow(shared);
    }

    getchar();
    delete window;
}