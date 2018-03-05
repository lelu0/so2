#include "window.h"
#include <ncurses.h>
#include <unistd.h>

Window::Window()
{
    initWindow();
}
Window::~Window()
{
    clear();
    refresh();
    endwin();
}

void Window::initWindow()
{
    initscr();
    noecho();
    curs_set(FALSE);
    clear();
    refresh();
}

void Window::drawSquare()
{
    for (int i = 1; i < 16; i++)
    {
        mvprintw(0, i, "-");
        mvprintw(16, i, "-");
    }
    for (int i = 1; i < 16; i++)
    {
        mvprintw(i, 1, "|");
        mvprintw(i, 15, "|");
    }
    refresh();
}
void Window::updateWindow(Shared *shared){
    for(int i = 0; i < shared->ballCounter; i++){
        if(shared->balls[i]->toUpdate()){
            clearFootprint(shared->balls[i]->lastY,shared->balls[i]->lastX);
            drawBall(shared->balls[i]->currentY,shared->balls[i]->currentX);
        }
    }
    refresh();
}
void Window::clearFootprint(int y, int x){
    mvprintw(y, x, " ");
}
void Window::drawBall(int y, int x){
    mvprintw(y, x, "o");
}