#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QPushButton>
#include <QTextEdit>

class MyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = 0);
    QTcpSocket* socket;

    QTextEdit* edit;
    QPushButton* button;
signals:

public slots:
    void slotReadyRead();
    void slotSendMessage();

};

#endif // MYWIDGET_H
