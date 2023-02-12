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
#include <QHostAddress>
#include <Qstring>
#include <QChar>

#include <a429/a429base.hpp>
#include <a429/a429bcd.hpp>
#include <a429/a429bnr.hpp>
#include <a429/a429bcd.hpp>
#include <a429/a429base.hpp>

#include <cstdio>
#include <cstring>
#include <cstdint>

#define BAE_PERIOD_MS   10
#define ALIVE_PERIOD_MS 1000

#define BUF_SIZE_1024   1024

#define MAX_COUNTER 1000

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void MainWindow::onClose( void )
{
    m_timer_alive->stop(  );
    m_timer->stop(  );
    m_udp_socket->close(  );
    updateActivity(  );
    close(  );
    return;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void MainWindow::closeEvent( QCloseEvent* e )
{
    onClose(  );
    e->accept(  );
    return;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void MainWindow::sendData( void )
{
    int sigbits = 19;
    int endbit = 28;
    int signbit = 29;
    a429::a429bnr msg;
    msg.SetBNR( 3.1418, 0.006548, sigbits, endbit, signbit );
    
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
void MainWindow::updateActivity( void )
{
    bool isValid = m_udp_socket->isValid(  );
    char buffer[ BUF_SIZE_1024 ];
    char buffer2[ BUF_SIZE_1024 ];
    QString addr = m_udp_socket->localAddress(  ).toString(  );
    QChar* data = addr.data(  );
    char* c_str = ( char* )data;
    
    memset( buffer2, 0, BUF_SIZE_1024 );

    if( false == isValid ) {
        // m_timer_alive->stop(  );
        m_counter_seconds_alive = 0;
        sprintf( buffer, "Failed to connect to %s on port %i", c_str, m_udp_socket->localPort(  ) );
    } else {
        m_counter_seconds_alive = m_counter_seconds_alive + 1;
        sprintf( buffer, "Successfully connected to %s on port %i", c_str, m_udp_socket->localPort(  ) );
        sprintf( buffer2, "%i", m_counter_seconds_alive );
    }
    m_ui.lbl_ontime_2->setText( QString( ( char* )buffer ) );
    m_ui.lbl_ontime->setText( QString( ( char* )buffer2 ) );
    return;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
MainWindow::MainWindow( QWidget* parent )
    : QMainWindow( parent ), m_counter( 0 ), m_counter_seconds_alive( 0 )
{
    m_ui.setupUi( this );
    resize( 1024, 768 );

    m_timer = new QTimer( this );
    m_timer->setSingleShot( false );
    m_timer->setInterval( BAE_PERIOD_MS );

    m_timer_alive = new QTimer( this );
    m_timer_alive->setSingleShot( false );
    m_timer_alive->setInterval( ALIVE_PERIOD_MS );


    m_udp_socket = new QUdpSocket( this );
    m_udp_socket->bind( QHostAddress::LocalHost, CLIENT_PORT );

    connect( m_timer, &QTimer::timeout, this, &MainWindow::sendData );
    connect( m_timer_alive, &QTimer::timeout, this, &MainWindow::updateActivity );
    connect( m_ui.actionExit, &QAction::triggered, this, &MainWindow::onClose );

    bool isValid = m_udp_socket->isValid(  );

    setWindowTitle( QString( "QT CLIENT" ) );
    setWindowIcon( QIcon( ":/icon.png" ) );
    m_timer->start(  );
    m_timer_alive->start(  );
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
MainWindow::~MainWindow( void )
{
    onClose(  );
}
