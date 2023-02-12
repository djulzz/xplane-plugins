/**
 * @file main.cpp
 * @author Julien Esposito (julien.esposito@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-02-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <string>
#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include "MainWindow.hpp"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
int main( int argc, char* argv[  ] )
{
    QApplication app( argc, argv );
    MainWindow* mw = new MainWindow;
    mw->show(  );
    return app.exec(  );
}
