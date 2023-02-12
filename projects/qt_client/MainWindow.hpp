/**
 * @file MainWindow.hpp
 * @author Julien Esposito (julien.esposito@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-02-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QUdpSocket>
#include <QTimer>

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow( QWidget* parent = 0 );
        virtual ~MainWindow( void );

    public slots:
        void sendData( void );

    protected:
        QUdpSocket* m_udp_socket;
        QTimer*     m_timer;
        int         m_counter;
};

#endif /* MAINWINDOW_HPP defined */
