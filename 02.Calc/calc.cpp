// You may need to build the project (run Qt uic code generator) to get "ui_Calc.h" resolved

#include "calc.h"
#include "ui_Calc.h"

const QVector<QString> Calc::numsBtn = {"7", "8", "9", "4", "5", "6", "1", "2", "3", "0", "."};
const QVector<QString> Calc::cmdLines = {"AC", "def", "%"};
const QVector<QString> Calc::cmdOps = {"÷", "×", "-", "+", "="};

QString Calc::buf = "0";

Calc::Calc(QWidget *parent) :
        QWidget(parent), ui(new Ui::Calc) {
    ui->setupUi(this);

    setFixedSize(240, 360);

    auto *myWidget = new QWidget(this);
    myWidget->setFixedSize(240, 360);
    auto *btnLayout = new QGridLayout(myWidget);
    // void setHorizontalSpacing(int spacing); // 设置水平方向的间距
    // btnLayout->setHorizontalSpacing(0);
    // void setVerticalSpacing(int spacing); // 设置垂直方向的间距
    // btnLayout->setVerticalSpacing(0);
    // void setSpacing(int spacing) override; // 设置两个方向的间距
    btnLayout->setSpacing(0);
    btnLayout->setContentsMargins(0, 60, 0, 0);
    QPushButton *btn = nullptr;

    // cmdLines
    for (int i = 0; i < 3; ++i) {
        btn = new QPushButton(cmdLines[i], this);
        btn->setFixedSize(60, 60);
        btn->setStyleSheet("QPushButton:pressed { background-color: #626262; }"
                           "QPushButton { background-color: #424242;font-size: 22px; color: #ebe9eb;"
                           "border-radius: 0px; border: 1px solid rgb(44,44,46);}");
        btn->setObjectName(QString("btn_%1").arg(cmdLines[i]));
        connect(btn, &QPushButton::clicked, this, &Calc::pressLineBtn);
        btnLayout->addWidget(btn, 0, i);
    }

    // cmdOps
    for (int i = 0; i < 5; ++i) {
        btn = new QPushButton(cmdOps[i], this);
        btn->setFixedSize(60, 60);
        btn->setStyleSheet("QPushButton:pressed {background-color: #c67e20;}"
                           "QPushButton {background-color: #f99f2b;font-size: 25px; color: #ebe9eb;"
                           "border-radius: 0px;border: 1px solid rgb(44,44,46);}");
        btn->setObjectName(QString("btn_%1").arg(cmdOps[i]));
        connect(btn, &QPushButton::clicked, this, &Calc::pressOpBtn);
        btnLayout->addWidget(btn, i, 3);
    }

    // numsBtn
    int pos = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            btn = new QPushButton(numsBtn[pos], this);
            btn->setFixedSize(60, 60);
            btn->setStyleSheet("QPushButton:press {background-color: #9f9e9e;}"
                               "QPushButton {background-color: #5e5d5c;font-size: 24px;"
                               "border-radius: 0px;border: 1px solid black}");
            btn->setObjectName(QString("btn_%1").arg(numsBtn[pos]));
            connect(btn, &QPushButton::clicked, this, &Calc::pressNumBtn);
            btnLayout->addWidget(btn, i + 1, j);
            ++pos;
        }
    }
    // 0 .
    for (int i = 0; i < 2; ++i) {
        btn = new QPushButton(numsBtn[pos], this);
        btn->setStyleSheet("QPushButton:press {background-color: #9f9e9e;}"
                           "QPushButton {background-color: #5e5d5c;font-size: 24px;"
                           "border-radius: 0px;border: 1px solid black}");
        if (i == 0) {
            btn->setFixedSize(120, 60);
            btnLayout->addWidget(btn, 4, 0);
        } else {
            btn->setFixedSize(60, 60);
            btnLayout->addWidget(btn, 4, 2);
        }
        btn->setObjectName(QString("btn_%1").arg(numsBtn[pos]));
        connect(btn, &QPushButton::clicked, this, &Calc::pressNumBtn);
        ++pos;
    }

    ui->LabText->setText(buf);
}

Calc::~Calc() {
    delete ui;
    buf = "0";
}

void Calc::pressNumBtn() {
    auto *btn = (QPushButton *) sender();
    qDebug() << "press " << btn->objectName();
    const QString &value = btn->objectName().remove("btn_");

    buf.append(value);
    if (buf.at(0) == '0' &&
        !(buf.at(1) == '.' || buf.at(1) == "÷" || buf.at(1) == "×" || buf.at(1) == "-" || buf.at(1) == "+")) {
        buf.remove(0, 1);
    }
    setText();
}

void Calc::pressOpBtn() {
    auto *btn = (QPushButton *) sender();
    qDebug() << "press " << btn->objectName();
    const QString &value = btn->objectName().remove("btn_");

    if (value == "=") {
        double ans = toNums();
        buf = QString::number(ans);
        setText();
        buf = "0";
        return;
    }

    buf.append(value);
    setText();
}

void Calc::pressLineBtn() {
    auto *btn = (QPushButton *) sender();
    qDebug() << "press " << btn->objectName();
    const QString &value = btn->objectName().remove("btn_");

    if (value == "AC") {
        acQString();
        setText();
    } else if (value == "def") {
        defQString();
        setText();
    } else {
        percent();
        setText();
    }
}

void Calc::setText() {
    ui->LabText->setText(buf);
}

double Calc::toNums() {
    double num1 = 0.0;
    double num2 = 0.0;
    int i = 0;
    int size = buf.size();
    int pre = 0;
    int cur = 0;
    QString temp;

    pre = i;
    while (i < size && ((buf[i] >= '0' && buf[i] <= '9') || buf[i] == '.')) {
        ++i;
    }
    cur = i;
    temp = buf.mid(pre, cur);
    num1 = temp.toDouble();

    QString op = "";
    while (i < size && !(buf[i] >= '0' && buf[i] <= '9')) {
        op.append(buf[i]);
        ++i;
    }
    pre = i;
    while (i < size && buf[i] >= '0' && buf[i] <= '9') {
        ++i;
    }
    cur = i - 1;
    temp = buf.mid(pre, cur);
    num2 = temp.toDouble();

    if (op == "÷") {
        return num1 / num2;
    } else if (op == "×") {
        return num1 * num2;
    } else if (op == "+") {
        return num1 + num2;
    } else if (op == "-") {
        return num1 - num2;
    } else {
        return num1;
    }
}

void Calc::defQString() {
    buf.chop(1);
    if (buf.isEmpty()) {
        buf = "0";
    }
}

void Calc::acQString() {
    buf = "0";
}

void Calc::percent() {
    double ans = buf.toDouble() / 100;
    buf = QString::number(ans);
}
