#include "mywidget.h"
#include <QHostAddress>
#include <QVBoxLayout>

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent)
{
    socket = new QTcpSocket(this);
    socket->connectToHost(QHostAddress("127.0.0.1"), 8900);

    connect(socket, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));

    edit = new QTextEdit();
    button = new QPushButton("send");

    QVBoxLayout * layout = new QVBoxLayout();
    layout->addWidget(edit);
    layout->addWidget(button);
    setLayout(layout);

    connect(button, SIGNAL(clicked()), this, SLOT(slotSendMessage()));
}

void MyWidget::slotSendMessage()
{
    QString str = edit->toPlainText();
    edit->clear();
    socket->write(str.toAscii());
}

void MyWidget::slotReadyRead()
{
    QByteArray ba = socket->read(1024);
    qDebug() << ba;
}

#include <QApplication>
int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    MyWidget win;
    win.show();

    return app.exec();
}
