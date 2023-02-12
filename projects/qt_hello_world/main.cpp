





#include <QApplication>
#include <QWidget>

int main( int argc, char* argv[  ] )
{
    QApplication app( argc, argv );
    QWidget* wi = new QWidget;
    wi->resize( 800, 600 );
    wi->show(  );
    return app.exec(  );
}