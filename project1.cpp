#include "window.h"
#include "shared.h"
#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
Shared *shared;
Window *window;
AppConfig *config;

void *ballFunction(void *arg)
{
    int id = (int)arg;
    while (true)
    {
        usleep(config->speed);
        shared->balls[id]->updateBall();
    }
}

void *updateWindowFct(void *arg)
{
    while (true)
    {
        usleep(50000);
        window->updateWindow(shared);
    }
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
    std::vector<pthread_t *> threads;
    threads.push_back(new pthread_t());
    pthread_create(threads[0], NULL, updateWindowFct, NULL);
    for (int i = 0; i < config->balls; i++)
    {
        shared->AddBall();
        threads.push_back(new pthread_t());
        pthread_create(threads[i + 1], NULL, ballFunction, (void *)i);
        sleep(config->delay);
    }
    getchar();
    pthread_exit(NULL);
    delete window;
}