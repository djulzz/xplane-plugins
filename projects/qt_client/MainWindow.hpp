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

#include <a429/a429base.hpp>
#include <a429/a429bcd.hpp>
#include <a429/a429bnr.hpp>
#include <a429/a429bcd.hpp>
#include <a429/a429base.hpp>

#include "../arin429_TestMessages.hpp"

#include "MainWindowUI.hpp"
#include <QMainWindow>
#include <QUdpSocket>
#include <QTimer>
#include <QCloseEvent>
#include <vector>
#include <cmath>

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
class Scheduler {
    public:
        

        Scheduler( void ) : counter( 0 ), isValid( false ), reference_count( 1 ), period_ms( 10 ), amplitude( 1.0 ), offset( 0.0 ),
                sigbits( DEFAULT_SIG_DIGITS ), endbit( DEFAULT_END_BITS ), signbit( DEFAULT_SIG_BITS ), resolution( DEFAULT_RESOLUTION )
        {
        }

        virtual ~Scheduler( void )
        {}

        void SetReferenceCount( int reference_count_i ) { reference_count = reference_count_i; return; }
        void SetPeriodMs( double period_ms_i ) { period_ms = period_ms_i; return; }
        void SetAmplitude( double amplitude_i ) { amplitude = amplitude_i; return; }
        void SetOffset( double offset_i ) { offset = offset_i; return; }
        bool isValueValid( void ) { return isValid; }
        void SetLabel( a429::UCHAR label )
        {
            msg.SetLbl( label );
            return;
        }


        double update( double time_ms )
        {
            double res = amplitude * cos( 0.001 * time_ms * period_ms );
            counter++;
            if( counter == reference_count )    {
                isValid = true;
                counter = 0;
                msg.SetBNR( res, resolution, sigbits, endbit, signbit );
            } else {
                isValid = false;
            }
            return res;
        }

        a429::a429bnr Message(  )
        {
            return msg;
        }

    private:
        int                 counter;
        int                 reference_count;
        double              period_ms;
        double              amplitude;
        double              offset;
        a429::a429bnr       msg;
        bool                isValid;

        int                 sigbits;
        int                 endbit;
        int                 signbit;
        double              resolution;
};

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
        void populateSchedulers( void );
        void updateSchedulers( void );

    protected:
        Ui::MainWindow              m_ui;
        QUdpSocket*                 m_udp_socket;
        QTimer*                     m_timer;
        int                         m_counter;
        QTimer*                     m_timer_alive;
        int                         m_counter_seconds_alive;
        std::vector< Scheduler* >   m_schedulers;

        a429::UINT                  m_buffer[ NUM_DIFFERENT_MESSAGES + 1 ];
};

#endif /* MAINWINDOW_HPP defined */
