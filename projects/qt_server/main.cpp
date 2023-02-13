/**
 * @file main.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-02-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "MainWindow.hpp"
#include <QApplication>

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
int main( int argc, char* argv[  ] )
{
    QApplication app( argc, argv );
    MainWindow* mw = new MainWindow;
    mw->show(  );
    return app.exec(  );
}
