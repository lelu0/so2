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
bool running = true;

void *exitListener(void *arg)
{
    while (running)
    {
        char c = getchar();
        if(c == 'x')
            running = false;
    }
    pthread_exit(NULL);
}
void *ballFunction(void *arg)
{
    int id = (int)arg;
    while (running)
    {
        usleep(config->speed);
        shared->balls[id]->updateBall();
    }
    pthread_exit(NULL);
}

void *updateWindowFct(void *arg)
{
    while (running)
    {
        usleep(50000);
        window->updateWindow(shared);
    }
    pthread_exit(NULL);
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
    //create control threads
    threads.push_back(new pthread_t());
    pthread_create(threads[0], NULL, updateWindowFct, NULL);
    threads.push_back(new pthread_t());
    pthread_create(threads[1], NULL, exitListener, NULL);
    //create ball threads
    for (int i = 0; i < config->balls; i++)
    {
        shared->AddBall();
        threads.push_back(new pthread_t());
        pthread_create(threads[i + 2], NULL, ballFunction, (void *)i);
        sleep(config->delay);
    }
    while(running);
    sleep(1);
    delete window;
    return 0;
    
}