#pragma once
#ifndef CARTESIANGRAPH_H_
//#define CARTESIANGRAPH_H_

#include<math.h>
#include"DrawObjects.h"
#include<qwidget.h>
#include<qmainwindow.h>
#include"Point.h"


#define InputSize_Horz_cm 	  15.0   //in centimeters
#define InputSize_Vert_cm 	  10.0

#define InputSize_Horz_mm 	  150.0   //in mm
#define InputSize_Vert_mm 	  100.0

#define InputSize_Horz_mil 	  5905.0   //in mili
#define InputSize_Vert_mil 	  3935.0

#define CENTI_PER_INCH 2.54

#define MIL_PER_INCH 1000

#define MM_PER_INCH 25.4

struct Unit_system {
    bool centi = false ;
    bool mili = false ;
    bool mil = false ;
};

struct scalar2 {
	float x;
	float y;
};          //DPI - dots per inch

class CartesianWindow: public QObject {


    vector<SDL_Point>Points;
    float		Width = NULL;
    float 		Height = NULL;

private:
   SDL_Point* p1 = new SDL_Point;
    //std::shared_ptr<SDL_Point> *p1 ( SDL_Point());
public:

    //CartesianWindow(QWidget* parent) : QObject(parent) {}
    CartesianWindow(){}
    ~CartesianWindow() { delete p1; }
    scalar2 dpi;
    Unit_system chosen_unit;
    SDL_Point& get_Point () { return *p1; }
    
    void dispToMM(SDL_Window * window, Unit_system )
    {
        //qDebug() << "                                 ";
        int disp,W,H;

        disp = SDL_GetWindowDisplayIndex(window);
        SDL_GetDisplayDPI(disp, NULL, &dpi.x, &dpi.y);
        SDL_Log("hdpi: %f", dpi.x);
        SDL_Log("vdpi: %f", dpi.y);

        /*
        qDebug() << "                                                 ";
        qDebug() << "        N            E               W           ";
        qDebug() << "                                                 ";
        qDebug() << "inside disptomm centi is" << chosen_unit.centi;
        qDebug() << "inside disptomm mili is" << chosen_unit.mili;
        qDebug() << "inside disptomm mil is" << chosen_unit.mil;

        qDebug() << "                                                  ";
        */

        if (chosen_unit.mili == true) {

            Width = roundf(InputSize_Horz_mm / MM_PER_INCH * dpi.x);

            Height = roundf(InputSize_Vert_mm / MM_PER_INCH * dpi.y);   // cm * pixel/cm  //1cm =44pixel
            //qDebug() << "width & height is in MILIMETRE : <<" << Width << "&" << Height ;

        }

        else if (chosen_unit.mil == true) {

            Width = roundf(InputSize_Horz_mil / MIL_PER_INCH * dpi.x);

            Height = roundf(InputSize_Vert_mil / MIL_PER_INCH * dpi.y);   // cm * pixel/cm  //1cm =44pixel
            //qDebug() << "width & height is in MIL :<<" << Width << "&" << Height ;

        }

        else if (chosen_unit.centi == true) {

            Width = roundf(InputSize_Horz_cm / CENTI_PER_INCH * dpi.x);

            Height = roundf(InputSize_Vert_cm / CENTI_PER_INCH * dpi.y);   // cm * pixel/cm  //1cm =44pixel
            //qDebug() << "width & height is in CENTIMETER : <<" << Width << "&" << Height ;

        }
        
        else
        {
            Width = roundf(InputSize_Horz_mm / MM_PER_INCH * dpi.x);

            Height = roundf(InputSize_Vert_mm / MM_PER_INCH * dpi.y);   // cm * pixel/cm  //1cm =44pixel
            //qDebug() << "width & height is in CENTIMETER : <<" << Width << "&" << Height;
            
            /*
            SDL_GL_GetDrawableSize(window, &W, &H);
            SDL_Log("hdpi: %f", W);
            SDL_Log("vdpi: %f", H);
            W = roundf(InputSize_Horz_mm / CENTI_PER_INCH * W);
            H = roundf(InputSize_Vert_mm / CENTI_PER_INCH * H);   // cm * pixel/cm  //1cm =44pixel
            qDebug() << "width & height is in MILIMETRE : <<" << W << "&" << H;
            */
        }

        SDL_SetWindowSize(window, Width, Height);
        char title[50];
        SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
        SDL_SetWindowResizable(window,SDL_TRUE);
        SDL_GetWindowSize(window, &W, &H);

        sprintf_s(title, "%dx%d ", (int)Width, (int)Height);
        SDL_SetWindowTitle(window, title);
        SDL_ShowWindow(window);
        //qDebug() << "changes in mainwindow";

        Unit_changed_value(window, chosen_unit);
    }

    void drawGraphPoints(SDL_Renderer* renderer,SDL_Window* window)  {
        int W, H;
        SDL_GetWindowSize(window, &W, &H);
        for (int i = 0; i < Width; i+=10)
         {
            for (int j = 0; j < Height; j+=10)
            {
                SDL_SetRenderDrawColor(renderer, 124, 252, 0, 255);
                SDL_RenderDrawPoint(renderer, i, j);
                Points.push_back({ i, j });
                
            }
        }

        // SDL_RenderPresent(renderer);
    }

    SDL_Point Unit_changed_value(SDL_Window* window,Unit_system &chosen_unit)
    {
        /*
        qDebug() << "                                          ";
        qDebug() << "inside point centi is" << chosen_unit.centi;
        qDebug() << "inside point mili is" << chosen_unit.mili;
        qDebug() << "inside point mil is" << chosen_unit.mil;
        */

        if (chosen_unit.centi == true) 
        {      

        Width = roundf(96 / CENTI_PER_INCH);
        Height = roundf(96 / CENTI_PER_INCH);
        p1->x = Width;
        p1->y = Height;
        
        //qDebug() << "Point in centi is :" << p1->x << "&" << p1->y;
        return *p1;
        }

        else if (chosen_unit.mili == true) {

            Width = roundf(96 / CENTI_PER_INCH);
            Height = roundf(96 / CENTI_PER_INCH);
            p1->x = Width;
            p1->y = Height;
           
           // qDebug() << "Point in mm is :" << p1->x << "&" << p1->y;
            return *p1;
        }

        else if (chosen_unit.mil == true) {

            Width = roundf(96 / CENTI_PER_INCH);
            Height = roundf(96 / CENTI_PER_INCH);
            p1->x = Width;
            p1->y = Height;
            
            //qDebug() << "Point in mil is :" << p1->x << "&" << p1->y;
            return *p1;
        }

        else
        {

            Width = roundf(96 / CENTI_PER_INCH);
            Height = roundf(96 / CENTI_PER_INCH);
            p1->x = Width;
            p1->y = Height;
            
            //qDebug() << "Point in else is :" << p1->x << "&" << p1->y;
            return *p1;
        }

    }


 
//****************using as static library*********************************************

    void DrawGraphLines(SDL_Renderer* renderer, SDL_Window* window, SDL_Point &p1) 
    {
        int W, H;
        SDL_GetWindowSize(window, &W,  &H);
       //qDebug() << "Point in lines is :" << p1.x << "&" << p1.y;
      

        for (int i = W / 2; i > 0; i -= (p1.x))   //1cm = 44pixel //44
        {
            SDL_SetRenderDrawColor(renderer, 34, 139, 34, 255);
            SDL_RenderDrawLine(renderer, i, 0, i, H);   //x1 y1 x2 y2
        }

        for (int i = W/2; i < W; i += (p1.x))   //1cm = 44pixel //44
        {
            SDL_SetRenderDrawColor(renderer, 34, 139, 34, 255);
            SDL_RenderDrawLine(renderer, i, 0, i, H);   //x1 y1 x2 y2
        }

        for (int i = H/2; i < H; i += (p1.y)) //44
        {
            SDL_SetRenderDrawColor(renderer, 34, 139, 34, 255);
            SDL_RenderDrawLine(renderer, 0, i, W, i);
        }

        for (int i = H / 2; i > 0; i -= (p1.y)) //44
        {
            SDL_SetRenderDrawColor(renderer, 34, 139, 34, 255);
            SDL_RenderDrawLine(renderer, 0, i, W, i);
        }
        
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderDrawLine(renderer, W / 2, 0, W / 2, H);
        SDL_RenderDrawLine(renderer, 0, H / 2, W, H / 2);

         char title[50];
        sprintf_s(title, "%dx%d", (int)W, (int)H);
        SDL_SetWindowTitle(window, title);
    }


};

#endif