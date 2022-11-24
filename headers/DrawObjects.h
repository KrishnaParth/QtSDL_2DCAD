#pragma once
#ifndef DRAWOBJECTS_H_
#define DRAWOBJECTS_H_

#include "../headers/Objects.h"

using namespace std;


class Rectangle : public Objects {
    SDL_Rect rect;
    vector<Rectangle*> rectangle;

public:
   Rectangle(int x, int y, int w, int h) {
        rect.x = x;
        rect.y = y;
        rect.w = w;
        rect.h = h;
    }

   // Rectangle(){}
   ~Rectangle(){}

   void drawobject(SDL_Renderer* renderer) const override 
   {
       SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
       SDL_RenderDrawRect(renderer, &rect);
   }

   static void drawSavedRect(const vector<SDL_Rect>& rect, SDL_Renderer* renderer) 
   {
       for (int i = 0; i < rect.size(); i++)
       {
           auto r = rect.at(i);
           SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
           SDL_RenderDrawRect(renderer, &r);
           
       }
   }

};
#endif
