#pragma once
#ifndef MOUSEEVENT_H_
#define MOUSEEVENT_H_

#include"DrawObjects.h"
#include"CartesianGraph.h"
#include<set>
#include<iostream>
#include<qstring.h>
#include<QObject>
#include <fstream>
#include <sstream>
#include <cstring>


class MouseEvent {
    SDL_Window* window;
    
public:
    CartesianWindow* cart_graph;
    MouseEvent(CartesianWindow* graph) { cart_graph = graph; }
    vector<SDL_Rect> rectangle;
    SDL_Rect rect;
    bool leftButtonPressed = false;
    bool mouseMoves = false;

    struct shape {
        int x;
        int y;
        int width;
        int height;
    };

    shape s;

    struct window_size {
        int width;
        int height;
    };

    window_size sdl_window_size;

    struct MouseCoords {
        int x = -1;
        int y = -1;
    };

    MouseCoords start_coords;
    MouseCoords move_coords;
    MouseCoords end_coords;
    MouseCoords every_coords;

    struct screen_coord
    {
        int x = 0;
        int y = 0;
    };

    screen_coord s_coord;

    struct world_coord
    {
        int x = 0;
        int y = 0;
    };

    world_coord w_coord;

    void setState(Uint32 eventType, SDL_Event event,SDL_Window* window) {

        if (eventType == SDL_MOUSEBUTTONDOWN) {
            this->leftButtonPressed = true;
            SDL_GetMouseState(&this->start_coords.x, &this->start_coords.y);
            //get_Centered_Coord(&start_coords, window);
        }

        if (eventType == SDL_MOUSEBUTTONUP) {
            this->leftButtonPressed = false;
            SDL_GetMouseState(&this->end_coords.x, &this->end_coords.y);
            //get_Centered_Coord(&end_coords, window);
            createLastBox();
            
        }

        if (eventType == SDL_MOUSEMOTION) {
            this->mouseMoves = true;
            this->move_coords.x = event.motion.x;
            this->move_coords.y = event.motion.y;
            //get_Centered_Coord(&move_coords, window);
        }
        if (eventType == SDL_MOUSEBUTTONDOWN || eventType == SDL_MOUSEMOTION ) {
            
            this->every_coords.x = event.motion.x;
            this->every_coords.y = event.motion.y;
            
            get_Centered_Coord(&every_coords, window);

            if (cart_graph->chosen_unit.centi == true)
            {
                write_coords("./assets/Coordinates.txt", every_coords.x/38, every_coords.y/38);
            }
            else if (cart_graph->chosen_unit.mili == true)
            {
                write_coords("./assets/Coordinates.txt", every_coords.x/3.8, every_coords.y/3.8);
            }
            else if (cart_graph->chosen_unit.mil == true)
            {
                write_coords("./assets/Coordinates.txt", every_coords.x / 0.096, every_coords.y / 0.096);
            }
            else
            {
                write_coords("./assets/Coordinates.txt", every_coords.x / 38, every_coords.y / 38);
            }
            
            }
        else 
        {
            this->mouseMoves = false;
            
        }
        /*  if (eventType == SDL_USEREVENT) {
            void (*p) (void*) = event.user.data1;
            p(event.user.data2);
            
        }*/
    }
  
     // Provides coordinates when mousebutton down
     
    MouseCoords getCoordinates() {
        return this->every_coords;
    }

    
    //  Creates selector rect, call this in the render loop
    
    void createSelectBox(SDL_Renderer* renderer) {
        if (this->leftButtonPressed) {
            Rectangle rect(
                this->start_coords.x,
                this->start_coords.y,
                this->move_coords.x - this->start_coords.x,
                this->move_coords.y - this->start_coords.y
            );
            rect.drawobject(renderer);
            
        } 
        draw_ui_shape();
        Rectangle::drawSavedRect(rectangle, renderer);
    }

    void createLastBox() {

        rectangle.push_back({ start_coords.x, start_coords.y,
                              end_coords.x - start_coords.x,end_coords.y - start_coords.y });

    }

    void draw_ui_shape()
    {
        //qDebug() << "x :" << s.x;
        rectangle.push_back({ s.x,s.y,s.width,s.height });
    }

    void get_Centered_Coord(MouseCoords* mouse_coords, SDL_Window* window)
    {
        int W, H;
        SDL_GetWindowSize(window, &W, &H);
        mouse_coords->x = mouse_coords->x - (W/2);
        mouse_coords->y = (H/2)- mouse_coords->y;
        
     // qDebug() << "2 mouse moving X :" << mouse_coords.x << " & Y:" << mouse_coords.y;
    }

    void write_coords(string path, int x, int y) {
        ofstream out(path);
        char buffer[50];
        sprintf_s(buffer, " %d , %d ", x, y);
        out << buffer;
    }

    void get_window_size(SDL_Window* window)
    {
        int W, H;
        SDL_GetWindowSize(window, &W, &H);
        sdl_window_size.width =  W;
        sdl_window_size.height = H;
        //qDebug() << "width" << sdl_window_size.width;
    }
};

#endif
