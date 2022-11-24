#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"

#include <qcombobox.h>
#include<qtimer.h>
#include<qlineedit.h>
#include "headers/CartesianGraph.h"
#include "headers/mouseEvent.h"
#include<vector>

#include<qfile.h>
#include<qtextstream.h>



class MainWindow : public QMainWindow
{
    Q_OBJECT
        SDL_Window* window;
        SDL_Renderer* renderer;
        vector<SDL_Rect> rectangle;

public:
    MainWindow(MouseEvent* mouse,CartesianWindow* graph, QWidget* parent = nullptr);

    
    
    
    void draw_ui_shape(SDL_Renderer* renderer);

private:
    // static MainWindow* m_instance;

public:
    ~MainWindow();
    //static MainWindow& Get_Instance(); 

    void Unit_ComboBox();
   
    

public slots:

    void Mouse_Line_Edit();

    void shape_combobox_currentIndexChanged(int index);
    void pushButton_shape_ok_clicked();

    void checking(int index)
    {

        if (index == 0) 
        {
            //qDebug() << "index while checking is" << index;
            cartesian->chosen_unit.centi = true;
            cartesian->chosen_unit.mil = false;
            cartesian->chosen_unit.mili = false;
           
        }

        else if (index == 1) {
            //qDebug() << "index while checking is" << index;
            cartesian->chosen_unit.mili = true;
            cartesian->chosen_unit.centi = false;
            cartesian->chosen_unit.mil = false;
        }
        else {
            //qDebug() << "index while checking is" << index;
            cartesian->chosen_unit.mil = true;
            cartesian->chosen_unit.mili = false;
            cartesian->chosen_unit.centi = false;
        }
       
        cartesian->Unit_changed_value(window, cartesian->chosen_unit);
    }

    //signals:
public:
    void unitsChanged()
    {
        SDL_Point p1 = cartesian->get_Point();
        //qDebug() << "x & Y Position is :" << p1.x << " & " << p1.y;
    }

    QString read_coords(QString path);

    //Rectangle rect;
    void unit_conversion();

private:
    Ui::MainWindowClass ui;

    CartesianWindow* cartesian;

    MouseEvent* mouse;

    QComboBox* units_box;

    QLineEdit* mouse_lineEdit;   

    QTimer* timer;

    enum Units {
        Centimeter,
        Milimetre,
        Mil
    };
};

