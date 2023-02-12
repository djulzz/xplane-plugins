/**
 * @file MainWindow.hpp
 * @author Julien Esposito (julien.esposito@gmail.com)
 * @brief Part of the "qt_server" project.
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
#include <QElapsedTimer>
#include <cstdint>

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
        QElapsedTimer   m_timer;
        uint32_t        m_counter_receptions;
        double          m_sum_receptions;

    protected:
        void processTheDatagram( const QNetworkDatagram& dg );
        void onReachingMaxNumReceptions( void );
};

#endif /* MAINWINDOW_HPP defined */