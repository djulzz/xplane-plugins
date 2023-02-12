/**
 * @file MainWindow.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-02-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "qt_server.hpp"
#include "MainWindow.hpp"
#include <QByteArray>
#include <cstdio>
#include <cstdint>
#include <string>
#include <cstring>

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void MainWindow::processTheDatagram( const QNetworkDatagram& dg )
{
    if( 0 == m_counter_receptions ) {
        /*
            QElapsedTimer timer;
    timer.start();
        slowOperation1();

    qDebug() << "The slow operation took" << timer.elapsed() << "milliseconds";

        */
       //elapsed()
       m_timer->start(  );
    }
    const QByteArray ba = dg.data(  );
    qsizetype byte_array_size = ba.size(  );
    const char* str = ba.data(  );
    uint8_t* buf_rcv = ( uint8_t* )( str );

    if( m_counter_receptions > 0 ) {
        qint64 ellapsed = timer.elapsed(  );
        m_timer->start(  );
    }

    m_counter_receptions = m_counter_receptions + 1;
    return;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void MainWindow::readPendingDatagrams( void )
{
    while( m_udp_socket->hasPendingDatagrams(  ) ) {
        QNetworkDatagram datagram = m_udp_socket->receiveDatagram(  );
        processTheDatagram( datagram );
    }
    return;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
MainWindow::MainWindow( QWidget* parent ) : QMainWindow( parent ), m_counter_receptions( 0 ), m_sum_receptions( 0.0 )
{
    resize( 800, 600 );
    m_udp_socket = new QUdpSocket( this );
    m_udp_socket->bind( QHostAddress::LocalHost, SERVER_PORT );
    connect( m_udp_socket, &QUdpSocket::readyRead,
            this, &MainWindow::readPendingDatagrams );
    bool isValid = m_udp_socket->isValid(  );
    // if( true == isValid ) {
    //     FILE* f = fopen( "success.txt", "w" ); fclose( f );
    // } else {
    //     FILE* f = fopen( "failure.txt", "w" ); fclose( f );
    // }
    setWindowTitle( QString( "QT SERVER" ) );
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
MainWindow::~MainWindow( void )
{
    m_udp_socket->close(  );
}
