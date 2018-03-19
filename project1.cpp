#include "window.h"
#include "shared.h"
#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <thread>
#include <unistd.h>
Shared *shared;
Window *window;
AppConfig *config;
bool running = true;

void exitListener()
{
    while (running)
    {
        char c = getchar();
        if(c == 'x')
            running = false;
    }
}
void ballFunction(int arg)
{
    int id = arg;
    while (running && shared->balls[id]->bounceCounter < 5)
    {
        usleep(config->speed);
        shared->balls[id]->updateBall();
    }
    shared->balls[id]->currentX = -1;
    shared->balls[id]->currentY = -1;
}

void updateWindowFct()
{
    while (running)
    {
        usleep(50000);
        window->updateWindow(shared);
    }
    delete window;
}
int main(int argc, char *argv[])
{
    srand(time(NULL));
    window = new Window();
    window->drawSquare();
    shared = new Shared();
    //config init
    config = new AppConfig();
    config->balls = argc >= 2 ? atoi(argv[1]) : 10;
    config->delay = argc >= 3 ? atoi(argv[2]) : 5;
    config->speed = argc >= 4 ? atoi(argv[3]) : 50000;
    //
    std::vector<std::thread> threads;
    //create control threads
    std::thread windowThread(updateWindowFct);    
    std::thread exitThread(exitListener);    
    //create ball threads
    for (int i = 0; i < config->balls; i++)
    {
        shared->AddBall();
        threads.push_back(std::thread(ballFunction,i));
        sleep(config->delay);
        if(!running)
            break;
    }
    windowThread.join();
    exitThread.join();
    for (int i = 2; i < config->balls+2; i++)
    {
        threads[i].join();
    }
    delete shared;
    
    return 0;
    
}