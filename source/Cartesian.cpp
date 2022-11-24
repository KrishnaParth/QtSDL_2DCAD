// gDL2 lSDL2_ttf -ldl++ -std=c++11 Cartesian.cpp -o prog -lS

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <SDL.h>
#include <SDL_ttf.h>

using namespace std;

void write(std::string path,int x , int y){
   ofstream out(path);
   char buffer[50];
   sprintf_s(buffer,"*( %d , %d )",x,y);
   out<<buffer;
}

string read(string path){
  string coord;
  ifstream in(path);
  getline(in,coord);
 // cout<<"coordinates are"<<coord<<endl;
  return coord;
}

SDL_Rect drawrect(SDL_Rect rectangle,int x, int y,int w, int h) {
    rectangle.x = x;
    rectangle.y = y;
    rectangle.w = w;
    rectangle.h = h;

    return rectangle;
}

SDL_Texture* textsurf( SDL_Renderer* renderer,SDL_Surface* surfaceText,SDL_Texture* textureText,TTF_Font* ourFont){

    string text = read("./assets/coordinates.txt");
    surfaceText = TTF_RenderText_Solid(ourFont,text.c_str(),{255,255,255});
    textureText = SDL_CreateTextureFromSurface(renderer,surfaceText);
    SDL_FreeSurface(surfaceText); 
     
    return textureText;
}


int main(int argc, char* argv[]){

    SDL_Window* window=nullptr;
//    SDL_Surface* screen;

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "SDL could not be initialized: " <<
                  SDL_GetError();
    }else{
        std::cout << "SDL video system is ready to go\n";
    }

    window = SDL_CreateWindow("C++ SDL2 Window",
            20,
            20,
            640,
            480,
            SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = nullptr;
    //for draw calls to affect this window, calling SDL_CreateRenderer
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);


    if(TTF_Init() == -1){
        std::cout << "Could not initailize SDL2_ttf, error: " << TTF_GetError() << std::endl; 
    }else{
        std::cout << "SDL2_ttf system ready to go!" << std::endl;
    }

    TTF_Font* ourFont = TTF_OpenFont("./fonts/8bitOperatorPlus8-Regular.ttf",32);
    // Confirm that it was loaded
    if(ourFont == nullptr){
        std::cout << "Could not load font" << std::endl;
        exit(1);
    }

    // Pixels from our text
    
    SDL_Surface* Xsurf = TTF_RenderText_Solid(ourFont,"X",{255,255,255});   
    SDL_Texture* Xtexture = SDL_CreateTextureFromSurface(renderer,Xsurf);
    SDL_FreeSurface(Xsurf); 
    SDL_Rect Xrect;
    Xrect.x=600;
    Xrect.y=250;
    Xrect.h=20;
    Xrect.w=40;

    SDL_Surface* Ysurf = TTF_RenderText_Solid(ourFont,"Y",{255,255,255});
    SDL_Texture* Ytexture = SDL_CreateTextureFromSurface(renderer,Ysurf);
    SDL_FreeSurface(Ysurf);
    SDL_Rect Yrect;
    Yrect.x=260;
    Yrect.y=10;
    Yrect.h=20;
    Yrect.w=40;
    
    // Setup the Coordinates texture
    SDL_Texture* textureText = nullptr;
    SDL_Texture* texture = nullptr;
    SDL_Surface* surfaceText = nullptr ;
    
    SDL_Rect rect;
    SDL_Rect rectdraw;
     int xmov,ymov;
     int xstart,ystart;
     int width,height;

    // Infinite loop for our application
    bool gameIsRunning = true;
    // Main application loop
    while(gameIsRunning){
        SDL_Event event;
        bool drawrectangle = false;
        int x,y;
        
       
        
        Uint32 buttons,mouse;
        buttons = SDL_GetMouseState(&x,&y);
       // mouse = SDL_GetMouseState(&xmov,&ymov);
        texture = textsurf( renderer,surfaceText,textureText,ourFont);
        
        SDL_FreeSurface(surfaceText); 
        
        // Start our event loop
        while(SDL_PollEvent(&event)){
            // Handle each specific event
            if(event.type == SDL_QUIT){
                gameIsRunning= false;
            }
            if(event.button.button == SDL_BUTTON_LEFT){
                std::cout << "left mouse button was pressed (" << x << "," << y << ")\n" ;    
                write("./coordinates.txt",x-320,240-y);
                rect = drawrect(rect,x ,y,150,20);
            }
            

            if(event.type == SDL_MOUSEMOTION) {
               xmov = event.motion.x - 320;
               ymov = 240 - event.motion.y;
               write("./rectangle.txt",xmov,ymov); 
               cout<<"x and y moving"<<xmov<<"&"<<ymov<<endl;              
            }
         
            if(event.button.button == SDL_BUTTON_RIGHT){
                drawrectangle = true;
                std::cout << "right mouse button was pressed (" << x << "," << y << ")\n" ;
                xstart=x-320; ystart=240-y;
                
                
                //write("./rectangle.txt",x-320,240-y); 
                //rectdraw = drawrect(rectdraw,xstart-320,240-ystart,xmov-xstart-320,240-ymov-ystart);      
            }
            
            if(event.button.button == SDL_BUTTON_MIDDLE) { drawrectangle = false; cout<<"draw rectangle is false"<<endl;}
            
        }   

        //set the color used for drawing or filling rectangles,lines etc.
        SDL_SetRenderDrawColor(renderer,0,0,0,SDL_ALPHA_OPAQUE);
        //get the current rendering target with the drawing color- i.e. clear the entire 
        //screen to our desired color
        SDL_RenderClear(renderer); 

        SDL_SetRenderDrawColor(renderer,0,0,0xFF,SDL_ALPHA_OPAQUE);
        SDL_RenderDrawLine(renderer,320,0,320,480);
        SDL_RenderDrawLine(renderer,0,240,640,240);

        if(drawrectangle == true) {
         //rectdraw = drawrect(rectdraw,xstart-320,240-ystart,xmov-xstart-320,240-ymov-ystart);
       //  width = xmov - xstart; height = ymov - ystart;
                //cout<<"width is"<<width<<"& height is "<<height<<endl;
         //cout<<"draw "<<xstart<<"rectangle is true"<<"length is "<<xmov-320<<"-"<<endl;
      
          //rectdraw = drawrect(rectdraw,xstart,ystart,xmov-xstart-320,240-ymov-ystart);
          //rectdraw = drawrect(rectdraw,320,240,xmov-320,240-ymov);
          //SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,SDL_ALPHA_OPAQUE);
        
          //SDL_RenderDrawRect(renderer,&rectdraw);
        ////SDL_RenderPresent(renderer);
        }
        

        // Render our text on a rectangle
        SDL_RenderCopy(renderer,texture,NULL,&rect);
        SDL_RenderCopy(renderer,Xtexture,NULL,&Xrect);
        SDL_RenderCopy(renderer,Ytexture,NULL,&Yrect);


        //Up until now everything was drawn behind the scenes,  Finally show what we've drawn
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyTexture(textureText);
    TTF_CloseFont(ourFont);
    
    SDL_Quit();
    return 0;
}
