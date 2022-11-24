#undef main

#include "MainWindow.h"
#include <QtWidgets/QApplication>

#include <iostream>

#include "headers/mouseEvent.h"
#include "headers/Point.h"

//#include<pthread.h>
//#include<Windows.h>
//#include <stdio.h>
//#include <fcntl.h>           
//#include <semaphore.h>



#include<graph_lib.h>
#include<../../DLL/Vector2D/Vector2D.h>
#include<../../DLL/Dllcheck/Calculator.h>

using namespace std;

SDL_Window* window ;
SDL_Renderer* renderer;
SDL_Surface* surface;
SDL_Texture* texture;
//MouseEvent mouse;
CartesianWindow CartesianGraph;
MouseEvent mouse(&CartesianGraph);
SDL_Point point;


void StoW()
{

}

void WtoS()
{

}


void update()
{
    point = CartesianGraph.get_Point();
    //Graph::Graph::DrawGraphLines(renderer, window, CartesianGraph.get_Point());
    CartesianGraph.DrawGraphLines(renderer, window, CartesianGraph.get_Point());
}

void renderWindow() {


    window = SDL_CreateWindow("", 0, 0, 0, 0, SDL_WINDOW_HIDDEN );
    //window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (int)InputSize_Horz_cm, (int)InputSize_Vert_cm, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, -1, 0);
    CartesianGraph.dispToMM(window, CartesianGraph.chosen_unit);


    //surface = SDL_GetWindowSurface(window);
    //texture = SDL_CreateTextureFromSurface(renderer, surface);
    //SDL_FreeSurface(surface);
}

void Destroy() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Window ended" << std::endl;
}

void renderGame(MouseEvent mouse) {
    //MainWindow m(&CartesianGraph, nullptr);
    // SDL_UpdateWindowSurface(window);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    SDL_RenderClear(renderer);

    update();
    mouse.createSelectBox(renderer);
    //pushButton_shape_ok_clicked(renderer);
    //SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}


void gameLoop() {
    bool game_run = true;

    while (game_run) {

        mouse.get_window_size(window);
        Uint32 start = SDL_GetTicks();
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                game_run = false;
            }
            mouse.setState(event.type, event, window);
        }

        renderGame(mouse);
        Uint32 elapsed_time = SDL_GetTicks() - start;
        if (elapsed_time > 1)
        {
            point = CartesianGraph.get_Point();
        }
        // SDL_Delay(15);
    }

}


int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    QApplication a(argc, argv);

    /* Testing Vector DLL */
   
   /* Vector2D vec1(1.0, 2.0);
    Vector2D vec2(4.0, 6.0);
    Vector2D vec3 = vec1 + vec2;
    qDebug() << "The vec3.x = " << vec3.X << " & " << " vec3.y = " << vec3.Y;*/

    
        qDebug() << "The sum of 4 & 5  = " << addition(4, 5);

        MainWindow w(&mouse,&CartesianGraph, nullptr);

        w.show();
        

        renderWindow();
        gameLoop();
        Destroy();
        return a.exec();  

}