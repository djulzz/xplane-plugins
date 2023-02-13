/**
 * @file MainWindow.cpp
 * @author Julien Esposito (julien.esposito@gmail.com)
 * @brief Part of the "qt_server" project.
 * @version 0.1
 * @date 2023-02-11
 * 
 * @copyright Copyright (c) 2023
 * @note 2/12/2023 @ 1:36 AM PCT - Important Result
 * 
 * "avg. time between receptions = 9.625 ms."
 * "Num. receptions used for stats = 10000"
 */

#include "qt_server.hpp"
#include "MainWindow.hpp"
#include <QByteArray>
#include <QCloseEvent>
#include <QAction>

#include <cstdio>
#include <cstdint>
#include <string>
#include <cstring>

#define SERVER_MAX_NUM_RECEPTIONS 10000

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void MainWindow::onClose( void )
{
    m_udp_socket->close(  );
    return;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void MainWindow::onQuitClicked( bool clickedStatus )
{
    ( void )clickedStatus;
    onClose(  );
    close(  );
    return;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void MainWindow::closeEvent( QCloseEvent* event )
{
    onClose(  );
    event->accept(  );
    return;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void MainWindow::onReachingMaxNumReceptions( void )
{
    if( m_counter_receptions > 0 )  {
        double avg_time_between_calls_in_ms = m_sum_receptions / ( double )m_counter_receptions;
        FILE* f = fopen( "SERVER_STATS.TXT", "w" );
        fprintf( f, "avg. time between receptions = %.3f ms.\n", avg_time_between_calls_in_ms );
        fprintf( f, "Num. receptions used for stats = %i\n", SERVER_MAX_NUM_RECEPTIONS );
        fclose( f );
    }

    m_udp_socket->close(  );
    disconnect( m_udp_socket, SIGNAL( readyRead ), this, SLOT( readPendingDatagrams ) );
    return;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void MainWindow::processTheDatagram( const QNetworkDatagram& dg )
{
    // static bool everLog = false;

    if( 0 == m_counter_receptions ) {
       m_timer.start(  );
    }
    const QByteArray ba         = dg.data(  );
    qsizetype byte_array_size   = ba.size(  );
    const char* str             = ba.data(  );
    uint8_t* buf_rcv            = ( uint8_t* )( str );

    qint64 ellapsed = 0;
    if( m_counter_receptions > 0 ) {
        ellapsed = m_timer.elapsed(  );
        m_timer.start(  );
    }

    m_counter_receptions = m_counter_receptions + 1;
    m_sum_receptions = m_sum_receptions + ( double )ellapsed;
    if( m_sum_receptions == SERVER_MAX_NUM_RECEPTIONS ) {
        onReachingMaxNumReceptions(  );
    }

    
    // if( false == everLog ) {
    //     FILE* f = fopen( "SERVER_PROCESS_DATAGRAM.TXT", "w" );
    //     fprintf( f, "size = %i\n", byte_array_size );
    //     fclose( f );
    //     everLog = true;
    // }
    return;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void MainWindow::readPendingDatagrams( void )
{
    // static bool everLog = false;
    while( m_udp_socket->hasPendingDatagrams(  ) ) {
        QNetworkDatagram datagram = m_udp_socket->receiveDatagram(  );
        processTheDatagram( datagram );
    }
    // if( false == everLog ) {
    //     FILE* f = fopen( "SERVER_RECEIVED.TXT", "w" );
    //     fclose( f );
    //     everLog = true;
    // }
    return;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
MainWindow::MainWindow( QWidget* parent ) : QMainWindow( parent ), m_counter_receptions( 0 ), m_sum_receptions( 0.0 )
{
    m_ui.setupUi( this );
    resize( 800, 600 );
    m_udp_socket = new QUdpSocket( this );
    m_udp_socket->bind( QHostAddress::LocalHost, SERVER_PORT );
    connect( m_udp_socket, &QUdpSocket::readyRead,
            this, &MainWindow::readPendingDatagrams );

    connect( m_ui.actionExit, SIGNAL( triggered( bool ) ), this, SLOT( onQuitClicked( bool ) ) );

    bool isValid = m_udp_socket->isValid(  );
    // if( true == isValid ) {
    //     FILE* f = fopen( "success.txt", "w" ); fclose( f );
    // } else {
    //     FILE* f = fopen( "failure.txt", "w" ); fclose( f );
    // }
    setWindowTitle( QString( "QT SERVER" ) );
    setWindowIcon( QIcon( ":/icon.png" ) );
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
MainWindow::~MainWindow( void )
{
    m_udp_socket->close(  );
}
