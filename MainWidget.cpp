#include "MainWidget.h"
#include <QVBoxLayout>
#include <QDebug>
#include "01.defSigSlot/win.h"
#include "02.Calc/calc.h"
#include "03.openCVImage/imagewidget.h"
#include "04.threadBase/signalbasewidget.h"
#include "05.Network/serverwidget.h"
#include "05.Network/clientwidget.h"

typedef struct {
    QString btnName;                // 按钮的显示文本
    void (MainWidget::*handler)();  // 按钮按下后的事件处理 槽函数
} BtnInfo;

static BtnInfo btn_infos[] = {
        {"自定义信号和槽", &MainWidget::openSigSlot},
        {"Calc案例",       &MainWidget::openCalc},
        {"openCV简单案例", &MainWidget::openImage},
        {"Qt线程排序",     &MainWidget::openThread},
        {"QtTCP服务端",    &MainWidget::openServer},
        {"QtTCP客户端",    &MainWidget::openClient}
};

// 使用布局策略控件进行排列
MainWidget::MainWidget(QWidget *parent) {
    setMinimumSize(300, 200);

    countBtn = sizeof(btn_infos) / sizeof(btn_infos[0]);
    // 申请countBtn个按钮指针，保存生成按钮的对象指针
    btn = new QPushButton *[countBtn];

    // 申请一个垂直布局约束，将countBtn个按钮加入布局
    auto *mainLayout = new QVBoxLayout(this);

    for (int i = 0; i < countBtn; ++i) {
        btn[i] = new QPushButton(btn_infos[i].btnName, this);
        btn[i]->setMinimumSize(300, 50);
        // 绝对布局 固定每一个控件在父窗口的坐标值
        // btn[i]->move(10, 10 + i * 50);
        mainLayout->addWidget(btn[i]);
        connect(btn[i], &QPushButton::clicked, this, btn_infos[i].handler);
    }
}

MainWidget::~MainWidget() {
    delete[]btn;
}

void MainWidget::openSigSlot() {
    auto *win = new Win;
    win->setAttribute(Qt::WA_DeleteOnClose);
    // 子窗口关闭时，通知主窗口，主窗口设置为使能
    connect(win, &QWidget::destroyed, [this]() {
        setEnabled(true);       /* 打开小窗口时，主窗口会隐藏，关闭小窗口后主窗口显示 */
        // setVisible(true);    /* 但是在Clion中关闭小窗口后，主窗口也关闭，程序退出 */
        // setHidden(false);    /* 第一个效果时打开小窗口，主窗口不可选中，后面两个会隐藏主窗口 */
    });
    win->show();
    setEnabled(false);
    // setVisible(false);
    // setHidden(true);
}

void MainWidget::openCalc() {
    auto *calc = new Calc;
    calc->setAttribute(Qt::WA_DeleteOnClose);
    connect(calc, &QWidget::destroyed, [this]() {
        setEnabled(true);
        // setHidden(false);
    });
    calc->show();
    setEnabled(false);
    // setHidden(true);
}

void MainWidget::openImage() {
    auto *img = new ImageWidget;
    img->setAttribute(Qt::WA_DeleteOnClose);
    // 子窗口关闭时，通知主窗口，主窗口设置为使能
    connect(img, &QWidget::destroyed, [this]() {
        setEnabled(true);
    });
    img->show();
    setEnabled(false);
}

void MainWidget::openThread() {
    auto *sig = new SignalBaseWidget;
    sig->setAttribute(Qt::WA_DeleteOnClose);
    // 子窗口关闭时，通知主窗口，主窗口设置为使能
    connect(sig, &QWidget::destroyed, [this]() {
        setEnabled(true);
    });
    sig->show();
    setEnabled(false);
}

void MainWidget::openServer() {
    auto *server = new ServerWidget;
    server->setAttribute(Qt::WA_DeleteOnClose);
    // 子窗口关闭时，通知主窗口，主窗口设置为使能
    connect(server, &QWidget::destroyed, [this]() {
        setEnabled(true);
    });
    server->show();
    setEnabled(false);
}

void MainWidget::openClient() {
    auto *client = new ClientWidget;
    client->setAttribute(Qt::WA_DeleteOnClose);
    // 子窗口关闭时，通知主窗口，主窗口设置为使能
    connect(client, &QWidget::destroyed, [this]() {
        setEnabled(true);
    });
    client->show();
    setEnabled(false);
}

void MainWidget::openDefault() {
    qDebug() << "this is default";
}
