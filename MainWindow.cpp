#include "MainWindow.h"

#include<iostream>
//#include"headers/CartesianGraph.h"
#include<qstring.h>

//MainWindow* MainWindow::m_instance = 0;

MainWindow::MainWindow(MouseEvent* mouseE,CartesianWindow* graph, QWidget* parent)
    : QMainWindow(parent)
{
    mouse = mouseE;
    cartesian = graph;
    ui.setupUi(this);

    Unit_ComboBox();

    mouse_lineEdit = new QLineEdit(this);
    mouse_lineEdit->setMinimumWidth(250);
    mouse_lineEdit->setMaximumWidth(250);
    ui.statusBar->addPermanentWidget(mouse_lineEdit);
    //QString s = "0 , 0";
    //mouse_lineEdit->setText(s);
   
    connect(this->units_box, SIGNAL(currentIndexChanged(int)), this, SLOT(checking(int)));
   
    timer = new QTimer(this);
    timer->setSingleShot(false);
    connect(timer, SIGNAL(timeout()), this, SLOT(Mouse_Line_Edit()));
    timer->start(1);

    //ui.pushButton_shape_ok->setEnabled(false);
    connect(ui.shape_comboBox, SIGNAL(currentIndexChanged(int )), this,SLOT( shape_combobox_currentIndexChanged( int )));
    connect(ui.pushButton_shape_ok, SIGNAL(clicked()), this, SLOT(pushButton_shape_ok_clicked()));

    ui.lineEdit_xpos->setEnabled(false);
    ui.lineEdit_ypos->setEnabled(false);
    ui.lineEdit_width->setEnabled(false);
    ui.lineEdit_height->setEnabled(false);

}

//MainWindow& Get_Instance() 
//{ 
//    MainWindow* m_instance;
//    if (m_instance == 0) { m_instance = new MainWindow; }
//    return *m_instance;  
//}



MainWindow::~MainWindow()
{
    delete& ui;
}

void MainWindow::Unit_ComboBox()
{
    units_box = new QComboBox(this);

    units_box->addItem("Centimeter");
    units_box->addItem("Milimetre");
    units_box->addItem("Mil");
    ui.statusBar->addPermanentWidget(units_box);
}

void MainWindow::shape_combobox_currentIndexChanged(int index)
{
    if (index == 1)
    {
        ui.lineEdit_xpos->setEnabled(true);
        ui.lineEdit_ypos->setEnabled(true);
        ui.lineEdit_width->setEnabled(true);
        ui.lineEdit_height->setEnabled(true);
        
    }
}

void MainWindow::pushButton_shape_ok_clicked()
{
    //qDebug() << "i am here";
    unit_conversion();
}

QString MainWindow::read_coords(QString path)
{
    QString filecontent;
    QFile file(path);

    QString failed = "failed to open";
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) { return failed; }

    QTextStream in(&file);
    QString coord = in.readLine();
    file.close();
    return coord;
}

void MainWindow::unit_conversion()
{
    int W, H;
    W = mouse->sdl_window_size.width;
    H = mouse->sdl_window_size.height;

    qDebug() << "width:" << W;
    if (this->units_box->currentIndex() == 0)
    {
        mouse->s.x = (W / 2) + (ui.lineEdit_xpos->text().toInt() * 38) ;
        mouse->s.y = (H / 2) -  (ui.lineEdit_ypos->text().toInt() * 38);
        mouse->s.width = ui.lineEdit_width->text().toInt() * 38;
        mouse->s.height = ui.lineEdit_height->text().toInt() * 38;
    }

    else if (this->units_box->currentIndex() == 1)
    {
        mouse->s.x = (W / 2) +  (ui.lineEdit_xpos->text().toInt() * 3.8) ;
        mouse->s.y = (H / 2) -  (ui.lineEdit_ypos->text().toInt() * 3.8);
        mouse->s.width = ui.lineEdit_width->text().toInt() * 3.8;
        mouse->s.height = ui.lineEdit_height->text().toInt() * 3.8;
    }
    else if (this->units_box->currentIndex() == 2)
    {
        mouse->s.x = (W / 2) + (ui.lineEdit_xpos->text().toInt() * 0.096);
        mouse->s.y = (H / 2) - (ui.lineEdit_ypos->text().toInt() * 0.096);
        mouse->s.width = ui.lineEdit_width->text().toInt() * 0.096;
        mouse->s.height = ui.lineEdit_height->text().toInt() * 0.096;
    }

    else
    {
        mouse->s.x = (W / 2) + (ui.lineEdit_xpos->text().toInt() * 38);
        mouse->s.y = (H / 2) -  (ui.lineEdit_ypos->text().toInt() * 38);
        mouse->s.width = ui.lineEdit_width->text().toInt() * 38;
        mouse->s.height = ui.lineEdit_height->text().toInt() * 38;
    }
}


void MainWindow::Mouse_Line_Edit()
{
    QString str= read_coords("./assets/Coordinates.txt");
    //qDebug() << "Coordinates inside mainwindow :" << str;
 
    mouse_lineEdit->setText(str);
}   

