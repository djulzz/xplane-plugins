/**
 * @file MainWindow.cpp
 * @author Julien Esposito (julien.esposito@gmail.com)
 * @brief Part of "qt_client" project.
 * @version 0.1
 * @date 2023-02-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "MainWindow.hpp"
#include "qt_client.hpp"

#include "../qt_server/qt_server.hpp"
#include <cstdio>
#include <cstring>
#include <cstdint>

#define BAE_PERIOD_MS   10
#define BUF_SIZE_1024   1024

#define MAX_COUNTER 1000

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void MainWindow::sendData( void )
{
    static char BUFFER[ BUF_SIZE_1024 ];

    m_counter = m_counter + 1;
    if( m_counter >= MAX_COUNTER + 1 )
        m_counter = 1;
    sprintf( BUFFER, "%i", m_counter );
    memset( BUFFER, 0, BUF_SIZE_1024 * sizeof( uint8_t ) );
    qint64 sent = m_udp_socket->writeDatagram( ( const char* )BUFFER, strlen( BUFFER ), QHostAddress::LocalHost, SERVER_PORT );
    return;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
MainWindow::MainWindow( QWidget* parent )
    : QMainWindow( parent ), m_counter( 0 )
{
    resize( 800, 600 );
    m_timer = new QTimer( this );
    m_timer->setSingleShot( false );
    m_timer->setInterval( BAE_PERIOD_MS );

    m_udp_socket = new QUdpSocket( this );
    m_udp_socket->bind( QHostAddress::LocalHost, CLIENT_PORT );
    connect( m_timer, &QTimer::timeout,
            this, &MainWindow::sendData );
    bool isValid = m_udp_socket->isValid(  );
    m_timer->start(  );
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
MainWindow::~MainWindow( void )
{
    m_udp_socket->close(  );
}
