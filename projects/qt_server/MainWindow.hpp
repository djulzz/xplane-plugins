/**
 * @file MainWindow.hpp
 * @author your name (you@domain.com)
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
#include <QNetworkDatagram>

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow( QWidget* parent = 0 );

        virtual ~MainWindow( void );

    public slots:
        void readPendingDatagrams( void );

    protected:
        QUdpSocket* m_udp_socket;

    protected:
        void processTheDatagram( const QNetworkDatagram& dg );
};

#endif /* MAINWINDOW_HPP defined */