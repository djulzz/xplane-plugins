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

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void MainWindow::processTheDatagram( const QNetworkDatagram& dg )
{
    const QByteArray ba = dg.data(  );
    qsizetype byte_array_size = ba.size(  );
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
MainWindow::MainWindow( QWidget* parent ) : QMainWindow( parent )
{
    resize( 800, 600 );
    m_udp_socket = new QUdpSocket( this );
    m_udp_socket->bind( QHostAddress::LocalHost, SERVER_PORT );
    connect( m_udp_socket, &QUdpSocket::readyRead,
            this, &MainWindow::readPendingDatagrams );
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
MainWindow::~MainWindow( void )
{
}
