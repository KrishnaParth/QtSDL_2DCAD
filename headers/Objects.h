#pragma once
#ifndef paint_hpp
#define paint_hpp

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <vector>

#include<qdebug.h>


//#undef main

class Objects {

public:
	virtual void drawobject(SDL_Renderer* renderer) const = 0;
	 ~Objects(){}

	//virtual SDL_Rect GetBounds() = 0;
};



#endif

