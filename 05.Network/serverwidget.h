#ifndef SERVER_WIDGET_H
#define SERVER_WIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QString>


QT_BEGIN_NAMESPACE
namespace Ui { class ServerWidget; }
QT_END_NAMESPACE

class ServerWidget : public QWidget {
Q_OBJECT

public:
    explicit ServerWidget(QWidget *parent = nullptr);

    ~ServerWidget() override;

public slots:
    void on_sendBtn_clicked();

private:
    Ui::ServerWidget *ui;
    QTcpServer *m_tcpServer;
    QTcpSocket *m_tcpSocket;
    quint16 m_port;
};


#endif //SERVER_WIDGET_H
