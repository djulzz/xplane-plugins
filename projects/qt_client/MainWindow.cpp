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

#include <cstdio>
#include <cstring>
#include <cstdint>


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void MainWindow::populateSchedulers( void )
{
    a429::UCHAR message_10_ms[ NUM_MESSAGES_10_MS ] = { MSG_10_MS_001, MSG_10_MS_002, MSG_10_MS_003, MSG_10_MS_004 };

    a429::UCHAR message_60_ms[ NUM_MESSAGES_60_MS ] = { MSG_60_MS_001, MSG_60_MS_002 };

    a429::UCHAR message_240_ms[ NUM_MESSAGES_240_MS ] = { MSG_240_MS_001, MSG_240_MS_002, MSG_240_MS_003, MSG_240_MS_004, 
    MSG_240_MS_005, MSG_240_MS_006, MSG_240_MS_007, MSG_240_MS_008, MSG_240_MS_009, MSG_240_MS_010, MSG_240_MS_011,
     MSG_240_MS_012, MSG_240_MS_013, MSG_240_MS_014 };

    double amplitude_10_ms = 1000.0;
    double amplitude_60_ms =  100.0;
    double amplitude_240_ms =  10.0;

    double offsets_10_ms[ NUM_MESSAGES_10_MS ] = { 1.0, 2.0, 3.0, 4.0 };
    double offsets_60_ms[ NUM_MESSAGES_60_MS ] = { 1.0, 2.0 };
    double offsets_240_ms[ NUM_MESSAGES_240_MS ] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0 };

    for( int ii = 0; ii < NUM_MESSAGES_10_MS; ii++ ) {
        Scheduler* scheduler = new Scheduler;
        scheduler->SetAmplitude( amplitude_10_ms );
        scheduler->SetOffset( offsets_10_ms[ ii ] );
        scheduler->SetPeriodMs( 10.0 );
        scheduler->SetReferenceCount( 1 );
        scheduler->SetLabel( message_10_ms[ ii ] );

        m_schedulers.push_back( scheduler );
    }

    for( int ii = 0; ii < NUM_MESSAGES_60_MS; ii++ ) {
        Scheduler* scheduler = new Scheduler;
        scheduler->SetAmplitude( amplitude_60_ms );
        scheduler->SetOffset( offsets_60_ms[ ii ] );
        scheduler->SetPeriodMs( 60.0 );
        scheduler->SetReferenceCount( 6 );
        scheduler->SetLabel( message_60_ms[ ii ] );

        m_schedulers.push_back( scheduler );
    }

    for( int ii = 0; ii < NUM_MESSAGES_240_MS; ii++ ) {
        Scheduler* scheduler = new Scheduler;
        scheduler->SetAmplitude( amplitude_240_ms );
        scheduler->SetOffset( offsets_240_ms[ ii ] );
        scheduler->SetPeriodMs( 240.0 );
        scheduler->SetReferenceCount( 24 );
        scheduler->SetLabel( message_240_ms[ ii ] );

        m_schedulers.push_back( scheduler );
    }
    return;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void MainWindow::onClose( void )
{
    m_timer_alive->stop(  );
    m_timer->stop(  );
    m_udp_socket->close(  );

    for( int ii = 0; ii < m_schedulers.size(  ); ii++ )
        delete m_schedulers[ ii ];
    m_schedulers.clear(  );

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
void MainWindow::updateSchedulers( void )
{
    int nSchedulers = NUM_DIFFERENT_MESSAGES;
    for( int ii = 0; ii < nSchedulers; ii++ )   {
        m_schedulers[ ii ]->update(  m_counter * BAE_PERIOD_MS * MS_TO_SEC );
        a429::a429bnr msg = m_schedulers[ ii ]->Message(  );
        bool validity = m_schedulers[ ii ]->isValueValid(  );
        if( true == validity ) {
            msg.SetSDI( a429::UCHAR( SDI_OK ) );
        } else {
            msg.SetSDI( a429::UCHAR( SDI_FAILURE ) );
        }
        m_buffer[ ii ] = a429::UINT( msg );
    }
    return;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void MainWindow::sendData( void )
{
    m_counter = m_counter + 1;
    updateSchedulers(  );
    int size = NUM_DIFFERENT_MESSAGES * sizeof( a429::UINT );
    qint64 sent = m_udp_socket->writeDatagram( ( const char* )m_buffer, size, QHostAddress::LocalHost, SERVER_PORT );
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
    populateSchedulers(  );

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
