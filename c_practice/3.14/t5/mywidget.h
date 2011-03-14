#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QUdpSocket>

class MyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = 0);

    QUdpSocket* socket;
signals:

public slots:
    void SocketReadReady();

};

#endif // MYWIDGET_H
