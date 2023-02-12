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

#include "MainWindowUI.hpp"
#include <QMainWindow>
#include <QUdpSocket>
#include <QTimer>
#include <QCloseEvent>

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
        void updateActivity( void );
        void onClose( void );

    private:
        void closeEvent( QCloseEvent* e );

    protected:
        Ui::MainWindow  m_ui;
        QUdpSocket*     m_udp_socket;
        QTimer*         m_timer;
        int             m_counter;
        QTimer*         m_timer_alive;
        int             m_counter_seconds_alive;
};

#endif /* MAINWINDOW_HPP defined */
