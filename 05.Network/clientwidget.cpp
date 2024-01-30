// You may need to build the project (run Qt uic code generator) to get "ui_ClientWidget.h" resolved

#include "clientwidget.h"
#include "ui_ClientWidget.h"


ClientWidget::ClientWidget(QWidget *parent) :
        QWidget(parent), ui(new Ui::ClientWidget) {
    ui->setupUi(this);

    ui->ipEdit->setPlaceholderText("127.0.0.1");
    ui->portEdit->setPlaceholderText("8080");

    m_tcpSocket = new QTcpSocket(this);

    connect(m_tcpSocket, &QTcpSocket::connected, [=]() {
        ui->readEdit->append(QString("连接成功"));
    });

    connect(m_tcpSocket, &QTcpSocket::disconnected, [=]() {
        ui->readEdit->append(QString("断开连接"));
    });

    connect(m_tcpSocket, &QTcpSocket::readyRead, [=]() {
        QByteArray buff = m_tcpSocket->readAll();
        ui->readEdit->append(buff);
    });
}

ClientWidget::~ClientWidget() {
    delete ui;
}

void ClientWidget::on_connBtn_clicked() {
    QString ip;
    quint16 port;
    if (!ui->ipEdit->text().isEmpty()) {
        ip = ui->ipEdit->text();
    } else {
        ip = "127.0.0.1";
    }
    if (ui->portEdit->text().isEmpty()) {
        port = 8080;
    } else {
        port = ui->portEdit->text().toUShort();
    }

    m_tcpSocket->connectToHost(QHostAddress(QString(ip)), port);
}

void ClientWidget::on_sendBtn_clicked() {
    QString data = ui->sendEdit->toPlainText();
    m_tcpSocket->write(data.toUtf8().data());
}

void ClientWidget::on_closeBtn_clicked() {
    m_tcpSocket->disconnectFromHost();
    m_tcpSocket->close();
    // ClientWidget::close();
}
