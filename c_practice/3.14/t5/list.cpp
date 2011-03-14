
#include <QApplication>
#include <QWidget>
#include "mywidget.h"


int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    MyWidget win;
    win.show();

    return app.exec();
}
