#ifndef CLIENT_WIDGET_H
#define CLIENT_WIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QHostAddress>

QT_BEGIN_NAMESPACE
namespace Ui { class ClientWidget; }
QT_END_NAMESPACE

class ClientWidget : public QWidget {
Q_OBJECT

public:
    explicit ClientWidget(QWidget *parent = nullptr);

    ~ClientWidget() override;

public slots:
    void on_connBtn_clicked();

    void on_sendBtn_clicked();

    void on_closeBtn_clicked();

private:
    Ui::ClientWidget *ui;
    QTcpSocket *m_tcpSocket;
};


#endif //CLIENT_WIDGET_H
