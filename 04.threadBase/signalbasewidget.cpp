// You may need to build the project (run Qt uic code generator) to get "ui_SignalBaseWidget.h" resolved

#include "signalbasewidget.h"
#include "ui_SignalBaseWidget.h"
#include <QRandomGenerator>
#include <QDebug>
#include "sortThread.h"


SignalBaseWidget::SignalBaseWidget(QWidget *parent) :
        QWidget(parent), ui(new Ui::SignalBaseWidget) {
    ui->setupUi(this);
    ui->numEdit->setPlaceholderText("随机数数量,默认为10");
    ui->maxEdit->setPlaceholderText("数据的最大值,默认为100");
    ui->minEdit->setPlaceholderText("数据的最小值,默认为1");

    countNum = 10;
    maxNum = 100;
    minNum = 1;
    src_data.clear();

    connect(ui->makeBtn, &QPushButton::clicked, this, &SignalBaseWidget::pressMakeBtn);
    connect(ui->bubbleBtn, &QPushButton::clicked, this, &SignalBaseWidget::pressBubbleBtn);
    connect(ui->quickBtn, &QPushButton::clicked, this, &SignalBaseWidget::pressQuickBtn);
}

SignalBaseWidget::~SignalBaseWidget() {
    delete ui;
}

void SignalBaseWidget::pressMakeBtn() {
    checkNum();

    auto makeNum = new GenerateDataThread(this, countNum, maxNum, minNum);
    src_data.clear();
    ui->randList->clear();

    connect(makeNum, &GenerateDataThread::dataReady, this, &SignalBaseWidget::dataReady);
    connect(makeNum, &QThread::finished, makeNum, &QObject::deleteLater);
    makeNum->start();
    ui->makeBtn->setText("生成中...");
}

void SignalBaseWidget::dataReady(const QVector<int> &data) {
    src_data = data;
    ui->randList->setUpdatesEnabled(false);
    for (auto &num: src_data) {
        ui->randList->addItem(QString::number(num));
    }
    ui->randList->setUpdatesEnabled(true);
    ui->makeBtn->setText("产生随机数");
}

void SignalBaseWidget::pressBubbleBtn() {
    auto bubble = new SortThread(SortThread::BubbleSortName, &src_data);
    ui->bubbleList->clear();
    connect(bubble, &SortThread::dataReady, this, &SignalBaseWidget::bubbleSortReady);
    connect(bubble, &QThread::finished, bubble, &QObject::deleteLater);

    bubble->start();
    ui->bubbleBtn->setText("排序中...");
}

void SignalBaseWidget::bubbleSortReady(const QVector<int> &data) {
    ui->bubbleList->setUpdatesEnabled(false);
    for (auto &num: data) {
        ui->bubbleList->addItem(QString::number(num));
    }
    ui->bubbleList->setUpdatesEnabled(true);
    ui->bubbleBtn->setText("冒泡排序");
}

void SignalBaseWidget::pressQuickBtn() {
    auto quick = new SortThread(SortThread::QuickSortName, &src_data);
    ui->quickList->clear();
    connect(quick, &SortThread::dataReady, this, &SignalBaseWidget::quickSortReady);
    connect(quick, &QThread::finished, quick, &QObject::deleteLater);

    quick->start();
    ui->quickBtn->setText("排序中...");
}

void SignalBaseWidget::quickSortReady(const QVector<int> &data) {
    ui->quickList->setUpdatesEnabled(false);
    for (auto &num: data) {
        ui->quickList->addItem(QString::number(num));
    }
    ui->quickList->setUpdatesEnabled(true);
    ui->quickBtn->setText("快速排序");
}

void SignalBaseWidget::checkNum() {
    // 检查输入数据是否合法
    if (!ui->numEdit->text().isEmpty() && ui->numEdit->text().toInt() != 0) {
        countNum = ui->numEdit->text().toInt();
    }

    if (!ui->maxEdit->text().isEmpty() && ui->maxEdit->text().toInt() != 0) {
        maxNum = ui->maxEdit->text().toInt();
    }

    minNum = ui->minEdit->text().toInt();

    if (countNum > (maxNum - minNum)) {
        countNum = 10;
        maxNum = 100;
        minNum = 1;
        qDebug() << "Illegal range of random numbers";
    }
}
