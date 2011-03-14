#include "mywidget.h"
#include <QApplication>
#include <QVBoxLayout>

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent)
{
    server = new QTcpServer(this);
    server->listen(QHostAddress::Any, 8900);

    connect(server, SIGNAL(newConnection()), this, SLOT(slotConnect()));

    edit = new QTextEdit();
    edit2 = new QTextEdit();
    
    button = new QPushButton();

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(edit,8);
    layout->addWidget(edit2,2);
    layout->addWidget(button);

    setLayout(layout);

   // connect(button, SIGNAL(clicked()), this, SLOT(slotSendMessage()));

}
void MyWidget::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Return)
    {
        slotSendMessage();

        QString str = edit2->toPlainText();

        str = str.left(str.length() - 1);

        edit->append("dong:");
        edit->append(str);
        edit2->clear();
    }
}

void MyWidget::slotSendMessage()
{
    QString str = edit->toPlainText();
    edit->clear();
    socket->write(str.toAscii());
}

void MyWidget::slotConnect()
{
    socket = server->nextPendingConnection();
    connect(socket, SIGNAL(readyRead()), this, SLOT(slotReadReady()));

    qDebug() << "connected";
}

void MyWidget::slotReadReady()
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
