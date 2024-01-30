// You may need to build the project (run Qt uic code generator) to get "ui_ServerWidget.h" resolved

#include "serverwidget.h"
#include "ui_ServerWidget.h"
#include <QPushButton>
#include <QMessageBox>
#include <QByteArray>


ServerWidget::ServerWidget(QWidget *parent) :
        QWidget(parent), ui(new Ui::ServerWidget) {
    ui->setupUi(this);

    m_port = 8080;
    ui->portEdit->setPlaceholderText(QString::number(8080));
    m_tcpSocket = nullptr;
    m_tcpServer = nullptr;

    // 设置端口号
    connect(ui->openServer, &QPushButton::clicked, [=]() {
        // if (!ui->portEdit->text().isEmpty()) {
        //     m_port = ui->portEdit->text().toUShort();
        // }
        // m_tcpServer->listen(QHostAddress::Any, m_port);

        qDebug() << "重新设置端口号，待完善";
    });

    m_tcpServer = new QTcpServer(this);
    m_tcpServer->listen(QHostAddress::Any, m_port);

    connect(m_tcpServer, &QTcpServer::newConnection, [=]() {
        m_tcpSocket = m_tcpServer->nextPendingConnection();
        const QString ip = m_tcpSocket->peerAddress().toString();
        const quint16 port = m_tcpSocket->peerPort();
        QString client = QString("[%1:%2] 连接成功").arg(ip).arg(port);
        client.remove("::ffff:");
        ui->readEdit->append(client);

        connect(m_tcpSocket, &QTcpSocket::disconnected, [=]() {
            QString client = QString("[%1:%2] 断开连接").arg(ip).arg(port);
            client.remove("::ffff:");
            ui->readEdit->append(client);
        });

        connect(m_tcpSocket, &QTcpSocket::readyRead, [=]() {
            QByteArray buff = m_tcpSocket->readAll();
            ui->readEdit->append(buff);
        });
    });

    connect(ui->closeBtn, &QPushButton::clicked, [=]() {
        if (m_tcpSocket != nullptr) {
            // 主动断开客户端连接
            m_tcpSocket->disconnectFromHost();
            m_tcpSocket->close();
            m_tcpSocket = nullptr;
        }
        ServerWidget::close();
    });
}

ServerWidget::~ServerWidget() {
    delete ui;
}

void ServerWidget::on_sendBtn_clicked() {
    if (nullptr == m_tcpSocket) {
        return;
    }
    QString data = ui->sendEdit->toPlainText();
    m_tcpSocket->write(data.toUtf8().data());
}
