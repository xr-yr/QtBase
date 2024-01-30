// You may need to build the project (run Qt uic code generator) to get "ui_Win.h" resolved

#include "win.h"
#include "ui_Win.h"

Win::Win(QWidget *parent) :
        QWidget(parent), ui(new Ui::Win) {
    ui->setupUi(this);

    // qDebug() << "btnStart: " << ui->btnStart << " win: " << this;
    connect(ui->btnExit, &QPushButton::clicked, this, &QWidget::close);

    p1 = new Person(this);
    auto *h1 = new House(this);

    // connect(p1, &Person::eat, h1, &House::doCook);
    void (Person::*sig_eat_void)() = &Person::eat;
    void (Person::*sig_eat_QSting)(const QString &) = &Person::eat;

    void (House::*slot_doCook_void)() = &House::doCook;
    void (House::*slot_doCook_QSting)(const QString &) = &House::doCook;

    connect(p1, sig_eat_void, h1, slot_doCook_void);
    connect(p1, sig_eat_QSting, h1, slot_doCook_QSting);
}

Win::~Win() {
    delete ui;
}

void Win::on_btnStart_clicked() {
    // qDebug() << "btn start" << this;

    const QString &food = ui->editSth->text();
    if (food.isEmpty()) {
        emit p1->eat();
    } else {
        emit p1->eat(food);
    }
}
